#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  int size, rank, fire_count = 0;
  char filename[256], line[256] = "";

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  const char *countries[11] = {"Greece",
                               "Albania",
                               "Bulgaria",
                               "Cyprus",
                               "Albania",
                               "Kosovo",
                               "Montenegro",
                               "Serbia",
                               "Croatia",
                               "Macedonia_Former_Yugoslav_Republic_of",
                               "Bosnia_and_Herzegovina"};

  sprintf(filename, "viirs-jpss1-data-2025/viirs-jpss1_2025_%s.csv",
          countries[rank]);

  FILE *fileptr = fopen(filename, "r");
  if (fileptr == NULL) {
    fprintf(stderr, "Failed to open file at '%s'\n", filename);
    return 1;
  }

  while (fgets(line, sizeof(line), fileptr) != NULL)
    fire_count++;

  printf("%d fires have been recorded in %s in 2025\n", fire_count,
         countries[rank]);

  MPI_Finalize();
  return 0;
}
