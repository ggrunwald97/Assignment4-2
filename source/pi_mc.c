#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

int main(int argc, char* argv[]) {

  int nPointsInCircle  = 0;
  int i = 0;
  int nPointsTotal     = 0;
  int nPointsPerRegion = 0;
  int pointsReceived   = 0;
  double piEstimate;
  double x_start, y_start;
  double x_rand, y_rand, rand_radius; 
  int rank, size, squareWidth;
  MPI_Status status;
  double start, stop, tpar, tcomm;
  double globaldata[12] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

  nPointsTotal = atoi(argv[1]);

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  start = MPI_Wtime();

  // Seed RNG and make calculations for constants
  nPointsPerRegion = nPointsTotal / size;
  srand( (unsigned)time(NULL) + rank ); // seed differently per node
  squareWidth = (int) sqrt(size);

  // Place and record points in the circle
  x_start = (double)(rank % squareWidth) / squareWidth;
  y_start = (double)((rank / squareWidth)) / squareWidth;

  //printf("Rank %d out of %d has starting x %f and starting y %f on a square of size %d \n", 
  //       rank, size, x_start, y_start, squareWidth);

  for (i = 0; i < nPointsPerRegion; i++) {
    x_rand = (double)rand() / ((double)RAND_MAX * squareWidth) + x_start;
    y_rand = (double)rand() / ((double)RAND_MAX * squareWidth) + y_start;
    rand_radius = (x_rand - 0.5) * (x_rand - 0.5) + (y_rand - 0.5) * (y_rand - 0.5);
    if (rand_radius <= 0.25) {
      nPointsInCircle += 1;
    }
  }
  stop = MPI_Wtime();
  tcomm += stop - start;

  printf("Process %d finished in %f seconds\n",rank,tcomm);
  MPI_Gather(&tcomm, 1, MPI_DOUBLE, globaldata, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  MPI_Reduce(&nPointsInCircle, &pointsReceived, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  if (rank == 0) {
    piEstimate = (double)(pointsReceived * 4) / nPointsTotal;
    printf("%f\n", piEstimate);
    double get_with_the_times =0;
    int a;
    for (a=0; a<size; a++) {
        //printf("%f ", globaldata[a]);
        get_with_the_times +=globaldata[a];
        if(a%2 == 1){
            printf("%d processes takes ", a+1);
            printf("%f seconds\n", get_with_the_times);
        }
    }
    printf("\n");


  } 

  MPI_Finalize();
  return 0;
}