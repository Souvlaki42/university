#include "shortest.h"
#include <stdio.h>

int main() {
  int cost[N][N], i, j, co;

  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      cost[i][j] = INITIAL_DISTANCE;

  // example graph
  cost[0][1] = cost[1][0] = 4; // A->B=4
  cost[0][2] = cost[2][0] = 1; // A->C=1
  cost[1][3] = cost[3][1] = 1; // B->D=1
  cost[2][1] = cost[1][2] = 2; // C->B=2
  cost[2][3] = cost[3][2] = 5; // C->D=5
  cost[3][4] = cost[4][3] = 3; // D->E=3
  cost[1][4] = cost[4][1] = 6; // B->E=6

  co = dijkstra(cost, 0, 4);
  printf("\nThe Shortest Path: %d", co);
}