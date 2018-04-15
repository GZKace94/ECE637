#ifndef _FILTER_H_
#define _FILTER_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "tiff.h"
#include "allocate.h"
#include "randlib.h"
#include "typeutil.h"
#include "filter.h"

void insertion_sort(int arr[], int weight[], int len);

int WeightedMedianVal(int whtmtr_reshaped[25], 
	uint8_t **orig_img, int coodx, int coody);

void WMfilter(uint8_t **original_img, uint8_t **filtered_img,
	int height, int width, int weightmatrix[5][5]);

#endif
