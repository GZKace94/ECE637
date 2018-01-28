# include "subroutines.h"

void ConnectedNeighbors(struct pixel s,double T,
                        unsigned char **img,int width,
                        int height,int *M,struct pixel c[4]){
*M = 4;
if (s.m == 0) {
  c[0].m = -1;
  c[0].n = -1;
  *M = *M - 1;
} else {
  if (abs(img[s.m][s.n] - img[s.m-1][s.n])<=T){
  c[0].m = s.m - 1 ;
  c[0].n = s.n;
}else{
  c[0].m = -1;
  c[0].n = -1;
  *M = *M - 1;}
}

if (s.n == 0) {
  c[1].m = -1;
  c[1].n = -1;
  *M = *M - 1;
} else{
  if (abs(img[s.m][s.n] - img[s.m][s.n-1])<=T){
  c[1].m = s.m;
  c[1].n = s.n - 1;
}else{
  c[1].m = -1;
  c[1].n = -1;
  *M = *M - 1;}
}

if (s.m == height - 1){
  c[2].m = -1;
  c[2].n = -1;
  *M = *M - 1;

} else{
  if (abs(img[s.m][s.n] - img[s.m+1][s.n])<=T){
  c[2].m = s.m + 1 ;
  c[2].n = s.n;
} else{
  c[2].m = -1;
  c[2].n = -1;
  *M = *M - 1;}
}

if (s.n == width - 1){
  c[3].m = -1;
  c[3].n = -1;
  *M = *M - 1;
} else{
  if (abs(img[s.m][s.n] - img[s.m][s.n+1])<=T){
  c[3].m = s.m;
  c[3].n = s.n + 1;
}else{
  c[3].m = -1;
  c[3].n = -1;
  *M = *M - 1;}
}
}

void push(node_t * head, struct pixel val) {
    node_t * current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    /* now we can add a new variable */
    current->next = malloc(sizeof(node_t));
    current->next->val = val;
    current->next->next = NULL;
}

struct pixel pop(node_t ** head) {
    node_t * next_node = NULL;
    struct pixel retval={-1,-1};
    if (*head == NULL) {
        printf("fail to pop!");
        return retval;
    }

    next_node = (*head)->next;
    retval = (*head)->val;
    free(*head);
    *head = next_node;
    return retval;
}

void ConnectedSet(struct pixel s,double T,
                unsigned char **img,int width,int height,
                int ClassLabel,uint8_t **seg,
                int *NumConPixels){
struct pixel c[4];
int neighbor_num;
int i;
int times = 1;
struct pixel retrieve;
/* use link list to store */
node_t * head = NULL;
head = malloc(sizeof(node_t));
if (head == NULL) {
        printf("No head!");
}
head->val = s;
head->next = NULL;

*NumConPixels = 1;
seg[head->val.m][head->val.n] = ClassLabel;
while (head!= NULL || times ==1 ){
        times = 2;
        ConnectedNeighbors (head->val,T,img,width,height, &neighbor_num, c);
        for (i =0; i < 4; i++){
                if (c[i].m!=-1 && c[i].m!=-1){
                        if(seg[c[i].m][c[i].n]!= ClassLabel){
                                seg[c[i].m][c[i].n] = ClassLabel;
                                /*printf("push c(%d,%d)",c[i].m,c[i].n); */
                                push(head,c[i]);
                                *NumConPixels += 1;
                        }
                }
        }
        retrieve = pop(&head);
        printf("POP(%d ,%d)\n", retrieve.m,retrieve.n );
        }
}