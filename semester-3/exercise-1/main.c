#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_table(int *arr, int N);
int sequential_search(int *arr, int N, int K);
int binary_search(int *arr, int N, int K);
void quick_sort(int *A, int start, int end);
void merge_table(int *arr, int N);
int* read_int_table_from_file(char *file_path, int N);
void write_int_table_to_file(char *file_path, int* numbers, int N);

int main() {
  int N = 0, i = 0;
  printf("Τι μέγεθος να έχει ο πίνακας; ");
  scanf("%d", &N);

  srand(time(NULL));

  int *A = calloc(N, sizeof(int));
  int *B = calloc(N, sizeof(int));
  int sorted = 0;
  for (i = 0; i < N; i++) {
    int n = rand() % 21 + 30;
    *(A + i) = n;
    *(B + i) = n;
  }

  printf("1. Σειριακή αναζήτηση\n");
  printf("2. Ταξινόμηση αντιγράφου\n");
  printf("3. Δυαδική αναζήτηση\n");
  printf("4. Συγχώνευση πινάκων\n");
  printf("5. Εκτύπωση πινάκων\n");
  printf("6. Αποθήκευση πίνακα\n");
  printf("7. Φόρτωμα πίνακα\n");

  int option;

  while (1) {
    printf("Δώσε αριθμό εντολής: ");
    scanf("%d", &option);
    printf("Εντολή: %d\n", option);

    if (option == 1) {
      int K = 0;
      printf("Ποιόν αριθμό ψάχνεις; ");
      scanf("%d", &K);
      int result = sequential_search(A, N, K);
      if (result == -1) {
        printf("Ο αριθμός %d δεν υπάρχει στον πίνακα\n", K);
      } else {
        printf("Ο αριθμός %d βρίσκεται στην θέση %d του πίνακα\n", K, result);
      }
    } else if (option == 2) {
      quick_sort(B, 0, N - 1);
      sorted = 1;
    } else if (option == 3) {
      if (!sorted) {
        quick_sort(B, 0, N - 1);
        sorted = 1;
      }

      int K = 0;
      printf("Ποιόν αριθμό ψάχνεις; ");
      scanf("%d", &K);
      int result = binary_search(B, N, K);
      if (result == -1) {
        printf("Ο αριθμός %d δεν υπάρχει στον πίνακα\n", K);
      } else {
        printf("Ο αριθμός %d βρίσκεται στην θέση %d του πίνακα\n", K, result);
      }
    } else if (option == 4) {
    } else if (option == 5) {
      printf("Αρχικός πίνακας: ");
      print_table(A, N);

      printf("Αντιγραμένος πίνακας: ");
      print_table(B, N);

    } else if (option == 6) {
        char *file_path;
        printf("Ποιό αρχείο θές να γράψεις; ");
        scanf("%s", file_path);
        write_int_table_to_file(file_path, A, N);
    } else if (option == 7) {
        char *file_path;
        printf("Ποιό αρχείο θές να διαβάσεις; ");
        scanf("%s", file_path);
        int* numbers = read_int_table_from_file(file_path, N);
        if (numbers == NULL) {
            printf("Δεν μπόρεσε να διαβαστεί το αρχείο\n");
            return 1;
        }

        for (i = 0; i < N; i++) {
            *(A + i) = *(numbers + i);
            *(B + i) = *(numbers + i);
        }
    } else {
      printf("Έξοδος...\n");
      break;
    }
  }

  free(A);
  free(B);
  return 0;
}

void merge_table(int *arr, int N)
{

}

void write_int_table_to_file(char *file_path, int* numbers, int N)
{
    FILE *fp;
    fp = fopen(file_path, "w");
    if (fp == NULL) {
        printf("Δεν μπόρεσε να διαβαστεί το αρχείο\n");
        return;
    }

    int i = 0;
    for (i = 0; i < N; i++) {
      fprintf(fp, "%d\n", *(numbers + i));
    }
    fclose(fp);
}

int* read_int_table_from_file(char *file_path, int N)
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    int* numbers;

    fp = fopen(file_path, "r");
    if (fp == NULL) {
      return NULL;
    }

    int i = 0;
    while ((getline(&line, &len, fp)) != -1) {
      *(numbers + i) = atoi(line);
      i++;
    }

    fclose(fp);
    if (line)
      free(line);
    return numbers;
}

void print_table(int *arr, int N) {
  for (int i = 0; i < N; i++) {
    printf("%d", *(arr + i));
    if (i == N - 1) {
      printf("\n");
    } else {
      printf(", ");
    }
  }
}

int sequential_search(int *arr, int N, int K) {
  int i = 0;
  int index = -1;
  while (i < N && index == -1) {
    if (*(arr + i) == K) {
      index = i;
    } else {
      i++;
    }
  }
  return index;
}

int binary_search(int *arr, int N, int K) {
  int start = 0;
  int end = N - 1;
  int index = -1;
  while (start <= end && index == -1) {
    int mid = (start + end) / 2;
    if (*(arr + mid) == K) {
      index = mid;
    } else if (*(arr + mid) < K) {
      start = mid + 1;
    } else {
      end = mid - 1;
    }
  }
  return index;
}

void quick_sort(int *arr, int start, int end) {
  if (start >= end) {
    return;
  }

  int p = *(arr + start);
  int i = start + 1;
  int j = end;
  int temp;

  while (i <= j) {
    while (i <= end && *(arr + i) <= p) {
      i++;
    }
    while (j >= start + 1 && *(arr + j) > p) {
      j--;
    }
    if (i < j) {
      temp = *(arr + i);
      *(arr + i) = *(arr + j);
      *(arr + j) = temp;
    }
  }
  temp = *(arr + start);
  *(arr + start) = *(arr + j);
  *(arr + j) = temp;

  quick_sort(arr, start, j - 1);
  quick_sort(arr, j + 1, end);
}
