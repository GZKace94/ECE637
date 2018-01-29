#ifndef _SUBROUTINES_H_
#define _SUBROUTINES_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "tiff.h"
#include "allocate.h"
#include "randlib.h"
#include "typeutil.h"
#include "subroutines.h"


struct pixel{
  int m,n;  /* m = row,which is height,n = col, which is column*/
};

/*create linked list structure*/
typedef struct node {
    struct pixel val;
    struct node * next;
} node_t;


void ConnectedNeighbors(struct pixel s,double T,
                        unsigned char **img,int width,
                        int height,int *M,struct pixel c[4]);

void ConnectedSet(struct pixel s,double T,
                unsigned char **img,int width,int height,
                int ClassLabel, uint8_t **seg, uint8_t **checkvisit,
                int *NumConPixels, int *large_area_number);
/*checkvisit store segmentation without filter
seg store segmentation with filter(pixel > 100)
NumConPixels store all connected points for one particular set,
*large_area_number store number of sets that have more than 100 pixel*/
#endif
