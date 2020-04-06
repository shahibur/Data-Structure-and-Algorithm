#include <stdio.h>
#include<vector>
#include<iostream>
#define INF 99999
#define MAX 10
using namespace std;



void display(int arr[][MAX], int size);
void floyds(int D[][MAX], int S[][MAX], int size);


typedef struct results
{

    int source;
    int destination;
    int distance;
    std::vector<int>path;

}Results;

int main(void) {

  //distance array

  int D[MAX][MAX] = {
    {INF, 5, 1, 2},
    {5, INF, 3, INF},
    {1, 3, INF, 4},
    {2, INF, 4, INF}
  };

  //sequence array

  int S[MAX][MAX] = {
    {INF, 2, 3, 4},
    {1, INF, 3, 4},
    {1, 2, INF, 4},
    {1, 2, 3, INF}
  };

  int size = 4;    //total number of vertices in the graph

  floyds(D, S, size);

  return 0;
}

void floyds(int D[][MAX], int S[][MAX], int size) {
  int i, j, k, l;

  //arrays to hold data for current iteration
  /*
    we have created arrays of size 10x10 (MAX x MAX)
    but we will be using only 4x4 as the graph has 4 vertices
  */
  int Dk[MAX][MAX], Sk[MAX][MAX];

  //set Dk and Sk to 0
  for(i = 0; i < size; i++) {
    for(j = 0; j < size; j++) {
      if(i == j) {
        Dk[i][j] = INF;
        Sk[i][j] = INF;
      } else {
        Dk[i][j] = 0;
        Sk[i][j] = 0;
      }
    }
  }


  //iteration start here ** ITERATION METHOD **

  for(k = 0; k < size; k++) {

    //step 1:
    //for each iteration we copy the kth row and kth column to
    //the current array
    for(l = 0; l < size; l++) {
      //copy row
      Dk[k][l] = D[k][l];
      Sk[k][l] = S[k][l];

      //copy column
      Dk[l][k] = D[l][k];
      Sk[l][k] = S[l][k];
    }

    //step 2:
    //compute the distance and sequence value for
    //current iteration
    for(i = 0; i < size; i++) {

      //for kth iteration we skip the kth row
      if(i == k) {
        continue;
      }

      for(j = 0; j < size; j++) {

        //for kth iteration we skip the kth column
        if(j == k) {
          continue;
        }
        //if i and j are same i.e., referring to same vertex we skip it
        if(i == j) {
          continue;
        }

        //checking
        if(D[i][j] > D[i][k] + D[k][j]) {
          Dk[i][j] = D[i][k] + D[k][j];
          Sk[i][j] = (k+1);  //kth iteration, as indexing starts from 0 so, we add 1
        } else {
          Dk[i][j] = D[i][j];
          Sk[i][j] = S[i][j];
        }
      }
    }

    //step 3:
    //copy content of Dk and Sk to D and S
    for(i = 0; i < size; i++) {
      for(j = 0; j < size; j++) {
        D[i][j] = Dk[i][j];
        S[i][j] = Sk[i][j];
      }
    }
  }

    Results res[size];

    //std::cout << "ok100" << std::endl;

  //print the distance array and sequence array result
  printf("\n\nDistance array: \n");
  display(D, size);
  printf("Sequence array: \n");
  display(S, size);

}

void display(int arr[][MAX], int size) {
  int i, j;
  for(i = 0; i < size; i++) {
    for(j = 0; j < size; j++) {
      if(arr[i][j] == INF) {
        printf("%10s ", "INF");
      } else {
        printf("%10d ", arr[i][j]);
      }
    }
    printf("\n");
  }
}
