
#include <math.h>
#include "tiff.h"
#include "allocate.h"
#include "randlib.h"
#include "typeutil.h"
#include "filter.h"

void error(char *name);
/* test change*/
int main (int argc, char **argv)
{
  FILE *fp;
  struct TIFF_img input_img, filtered_img, expend_img;
  double **img1;
  int32_t i,j;
  int weightmatrix[5][5] = { {1,1,1,1,1},
							 {1,2,2,2,1},
							 {1,2,3,2,1},
							 {1,2,2,2,1},
							 {1,1,1,1,1}};
  
  int test[5][5] = { { 1,1,1,1,1 },
  { 1,3,3,3,1 },
  { 1,3,5,3,1 },
  { 1,3,3,3,1 },
  { 1,1,1,1,1 } };


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
  if ( input_img.TIFF_type != 'g' ) {
    fprintf ( stderr, "error:  image must be grey mono\n" );
    exit ( 1 );
  }

  /* Allocate image of double precision floats
  Extend the image for filtering*/
  img1 = (double **)get_img(input_img.width+4,input_img.height+4,sizeof(double));
  /* set up structure for output achromatic image */
  /* to allocate a full mono image use type 'g' */
  get_TIFF ( &filtered_img, input_img.height, input_img.width, 'g' );
  get_TIFF ( &expend_img, input_img.height+4, input_img.width+4, 'g' );

  /* filter the picture*/
  for ( i = 0; i < input_img.height + 4; i++ )
  for ( j = 0; j < input_img.width + 4; j++ ) {
    if ( i >= 2 && j >= 2 && i < input_img.height+2 && j < input_img.width+2){
      img1[i][j] = input_img.mono[i-2][j-2];
    } else {
    img1[i][j] = 0;
  }
  expend_img.mono[i][j] = img1[i][j];
  }
  /*
  int reshapeWM[25];
  int reshapetest[25];
  for (int i = 0; i < 5; i++) {
  for (int j = 0; j < 5; j++) {
  int t = weightmatrix[i][j];
  reshapeWM[5 * i + j] = t;
  reshapetest[5 * i + j] = test[i][j];

  }
  }
  insertion_sort(reshapeWM, reshapetest, 25);
  printf("\n");
  for (int j = 0; j < 25; j++) {
	  printf("%d ", reshapeWM[j]);
  }

  printf("\n");
  for (int j = 0; j < 25; j++) {
	  printf("%d ", reshapetest[j]);
  }
  */
 
 WMfilter(expend_img.mono, filtered_img.mono,expend_img.height,expend_img.width,weightmatrix);

  /*int val = WeightedMedianVal(reshapeWM, expend_img.mono, 513, 769);*/
  

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
    printf("this program reads in a 24-bit mono TIFF image.\n");
    printf("It then horizontally filters the green component, adds noise,\n");
    printf("and writes out the result as an 8-bit image\n");
    printf("with the name 'green.tiff'.\n");
    printf("It also generates an 8-bit mono image,\n");
    printf("that swaps red and green components from the input image");
    exit(1);
}
