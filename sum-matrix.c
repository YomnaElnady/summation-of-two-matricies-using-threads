#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define M 3
#define N 3
#define NUM_THREADS 10

int A [M][N] = {{3, 7, 3},{9, 2, 0},{2, 2, 7}};
int B [M][N] = {{6, 5, 5},{6, 6, 8},{0, 3, 5}};
int C [M][N];

struct v {
   int i; /* row */
   int j; /* column */
};

void *summation(void *argument);

int main(int argc, char *argv[]) {

   int i,j,count=0;
   for(i = 0; i < M; i++) {
      for(j = 0; j < N; j++) {
         //Assign a row and column for each thread
         struct v *data = (struct v *) malloc(sizeof(struct v));
         data->i = i;
         data->j = j;
         /* Now create the thread passing it data as a parameter */
         pthread_t threads[NUM_THREADS];       //Thread ID
         //Create the thread
         pthread_create(&threads[count],NULL,summation,data);
         count++;
      }
   }

   //Print out the resulting matrix
   for(i = 0; i < M; i++) {
      for(j = 0; j < N; j++) {
         printf("%d ", C[i][j]);
      }
      printf("\n");
   }
}

//The thread will begin control in this function
void *summation(void *argument) {
   struct v *data = argument; // the structure that holds our data
   C[data->i][data->j] = A[data->i][data->j]+ B[data->i][data->j];
   pthread_exit(0);
}
