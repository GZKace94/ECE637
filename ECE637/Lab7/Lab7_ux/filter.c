# include "filter.h"






int WeightedMedianVal(int **weightmtr, uint8_t **orig_img, int coodx, int coody) {


}

void WMfilter(uint8_t **original_img, uint8_t **filtered_img,int height, int width) {

	for (int i = 0; i < height + 4; i++)
		for (int j = 0; j < width + 4; j++) {
			if (i >= 2 && j >= 2 && i < height + 2 && j < width + 2) {
				filtered_img[i-2][j-2] = original_img[i][j];
			}
		}

}
















