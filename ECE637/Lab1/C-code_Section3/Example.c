
#include <math.h>
#include "tiff.h"
#include "allocate.h"
#include "randlib.h"
#include "typeutil.h"

void error(char *name);

int main (int argc, char **argv)
{
  FILE *fp;
  struct TIFF_img input_img, filtered_img, expend_img;
  double **img1;
  int32_t i,j;
  int32_t k,n,m;

  if ( argc != 2 ) error( argv[0] );

  /* open image file */
  if ( ( fp = fopen ( argv[1], "rb" ) ) == NULL ) {
    fprintf ( stderr, "cannot open file %s\n", argv[1] );
    exit ( 1 );
  }

  /* read image */
  if ( read_TIFF ( fp, &input_img ) ) {
    fprintf ( stderr, "error reading file %s\n", argv[1] );
    exit ( 1 );
  }

  /* close image file */
  fclose ( fp );

  /* check the type of image data */
  if ( input_img.TIFF_type != 'c' ) {
    fprintf ( stderr, "error:  image must be 24-bit color\n" );
    exit ( 1 );
  }

  /* Allocate image of double precision floats
  Extend the image for filtering*/
  img1 = (double **)get_img(input_img.width+8,input_img.height+8,sizeof(double));
  /* set up structure for output achromatic image */
  /* to allocate a full color image use type 'c' */
  get_TIFF ( &filtered_img, input_img.height, input_img.width, 'c' );
  get_TIFF ( &expend_img, input_img.height+8, input_img.width+8, 'c' );
  /* filter the picture layer by layer k 0-2*/
  for ( k = 0; k < 3; k++ ) {
  for ( i = 0; i < input_img.height + 8; i++ )
  for ( j = 0; j < input_img.width + 8; j++ ) {
    if ( i >= 4 && j >= 4 && i < input_img.height+4 && j < input_img.width+4){
      img1[i][j] = input_img.color[k][i-4][j-4];
    } else {
    img1[i][j] = 0;
  }
  expend_img.color[k][i][j] = img1[i][j];
  printf("test");
  printf("test");
  }
  for ( i = 0; i < input_img.height; i++ )
  for ( j = 0; j < input_img.width; j++ ) {
    double sum = 0;
    for( n =0; n <=8; n++)
    for( m = 0; m <=8; m++){
    sum = img1[i+n][j+m]/81 + sum;
    }

    if (filtered_img.color[k][i][j] > 255) filtered_img.color[k][i][j] = 255;
    else if (filtered_img.color[k][i][j] < 0) filtered_img.color[k][i][j] = 0;
    else filtered_img.color[k][i][j] = sum;
  }
}
  /* open image file */
  if ( ( fp = fopen ( "filgered_img.tif", "wb" ) ) == NULL ) {
    fprintf ( stderr, "cannot open file filtered_img.tif\n");
    exit ( 1 );
  }

  /* write image */
  if ( write_TIFF ( fp, &filtered_img ) ) {
    fprintf ( stderr, "error writing TIFF file %s\n", argv[2] );
    exit ( 1 );
  }

  /* close image file */
  fclose ( fp );

  /* open image2 file */
  if ( ( fp = fopen ( "expend_img.tif", "wb" ) ) == NULL ) {
    fprintf ( stderr, "cannot open file filtered_img.tif\n");
    exit ( 1 );
  }

  /* write image */
  if ( write_TIFF ( fp, &expend_img ) ) {
    fprintf ( stderr, "error writing TIFF file %s\n", argv[2] );
    exit ( 1 );
  }

  /* close image file */
  fclose ( fp );


  /* de-allocate space which was used for the images */
  free_TIFF ( &(input_img) );
  free_TIFF ( &(filtered_img) );
  free_TIFF ( &(expend_img) );
  free_img( (void**)img1 );

  return(0);
}

void error(char *name)
{
    printf("usage:  %s  image.tiff \n\n",name);
    printf("this program reads in a 24-bit color TIFF image.\n");
    printf("It then horizontally filters the green component, adds noise,\n");
    printf("and writes out the result as an 8-bit image\n");
    printf("with the name 'green.tiff'.\n");
    printf("It also generates an 8-bit color image,\n");
    printf("that swaps red and green components from the input image");
    exit(1);
}
