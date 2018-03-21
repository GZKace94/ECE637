# include "filter.h"


void insertion_sort(int arr[], int weight[], int len)
{
	for (int i = 1; i < len; i++) {
		for (int j = i; j > 0 && arr[j - 1] < arr[j]; j--) {

			int temp = arr[j];
			arr[j] = arr[j - 1];
			arr[j - 1] = temp;

			int temp2 = weight[j];
			weight[j] = weight[j - 1];
			weight[j - 1] = temp2;
		}
	}
}


int WeightedMedianVal(int reshapea[25], uint8_t **orig_img, int coodx, int coody)
{
	int reshapeX[25];
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			reshapeX[5 * i + j] = orig_img[coodx - 2 + i][coody - 2 + j];
		}
	}

	insertion_sort(reshapeX, reshapea, 25);
	
	int sum1 = 0;
	int sum2 = 34;
	for (int i = 0; i < 25; i++) {
		sum1 = sum1 + reshapea[i];
		sum2 = 34 - sum1;
		if (sum1 >= sum2) {
			return reshapeX[i];
		}
	}

	return -1;
}

void WMfilter(uint8_t **original_img, uint8_t **filtered_img,int height, int width,
			  int weightmatrix[5][5])
{
	int reshapeWM[25];

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			int t = weightmatrix[i][j];
			reshapeWM[5 * i + j] = t;
		}
	}
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++) {
			if (i >= 2 && j >= 2 && i < height - 2 && j < width - 2) {
				filtered_img[i - 2][j - 2] = WeightedMedianVal(reshapeWM, original_img, i, j);
			}
		}

}
















