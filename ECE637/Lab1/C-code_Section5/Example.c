
#include <math.h>
#include "tiff.h"
#include "allocate.h"
#include "randlib.h"
#include "typeutil.h"

void error(char *name);

int main (int argc, char **argv)
{
  FILE *fp;
  struct TIFF_img input_img, IIR_img;
  double **img1;
  double sum;
  int32_t i,j;
  int32_t k;

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
  use img1 to initilize output img, also extend the image for filtering*/
  img1 = (double **)get_img(input_img.width+1,input_img.height+1,sizeof(double));
  /* set up structure for output achromatic image */
  /* to allocate a full color image use type 'c' */
  get_TIFF ( &IIR_img, input_img.height, input_img.width, 'c' );

  /* filter layer by  layer*/
  for ( k = 0; k < 3; k++ ) {
  for ( i = 0; i < input_img.height+1; i++ )
  for ( j = 0; j < input_img.width+1; j++ ) {
      img1[i][j] = 0;
  }

  for ( i = 1; i < input_img.height+1; i++ )
  for ( j = 1; j < input_img.width+1; j++ ) {
    img1[i][j] = 0.01*input_img.color[k][i-1][j-1] + 0.9*(img1[i-1][j]+img1[i][j-1])-0.81*img1[i-1][j-1];
    if (img1[i][j] > 255) img1[i][j] = 255;
    if (img1[i][j] < 0) img1[i][j] = 0;
    IIR_img.color[k][i-1][j-1] = img1[i][j];
  }

}

  /* open image file */
  if ( ( fp = fopen ( "IIR_img.tif", "wb" ) ) == NULL ) {
    fprintf ( stderr, "cannot open file IIR_img.tif\n");
    exit ( 1 );
  }

  /* write image */
  if ( write_TIFF ( fp, &IIR_img ) ) {
    fprintf ( stderr, "error writing TIFF file %s\n", argv[2] );
    exit ( 1 );
  }

  /* close image file */
  fclose ( fp );


  /* de-allocate space which was used for the images */
  free_TIFF ( &(input_img) );
  free_TIFF ( &(IIR_img) );

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
