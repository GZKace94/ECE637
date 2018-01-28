

#define idx(x, y) (x * sizeY + y)


void bfs(node *x, bool *visit) {

}

#define withinBoundary(x, y) ((x < sizeX) && (x >= 0) && (y < sizeY) && (y >= 0))


void segmentation(img **double, int sizeX, int sizeY) {
  int i, j, *visit, n, k;
  int head, tail, deque[400 * 400];
  int offset[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}}

  n = sizeX * sizeY;
  visit = malloc(sizeof(int) * n);
  memset(visit, 0, n * sizeof(int));

  for(i = 0; i < sizeX; ++i)
  for(j = 0; j < sizeY, ++j) {
    if(!visit[idx(i, j)]) {
        head = 0;
        tail = 1;
        deque[head] = i * sizeY + j;
        visit[i][j] = 1;

        while(head != tail) {
          now = deque[head];

          coordx = now % sizeY;
          coordy = now - sizeY * coordx;

          for(k = 0; k < 4) {
                  x = coordx + offset[k][0];
                  y = coordy + offset[k][1];
                  if (withinBoundary(x, y) {
                          if(!visit[x][y]) {
                                  visit[x][y] = 1;
                                  deque[tail++] = idx(x, y);
                                  if(tail == N) tail = 0;
                          }
                  }


          }
          head++;
          if (head == N) head = 0;
        }
    }
  }
  free(visit);
}
