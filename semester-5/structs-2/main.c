#include <stdatomic.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int *create_table(int, int, int);
int *create_sorted_table_copy(int *, int);
void print_table(int *, int);
int sequential_search(int *, int, int);
int binary_search(int *, int, int);
void table_sort(int *, int);
int *merge_table(int *, int *, int);
int *read_int_table_from_file(char *, int);
void write_int_table_to_file(char *, int *, int);

int main() {
  srand(time(NULL));

  int N = 0;
  int option = 0;

  do {
    printf("Τι μέγεθος θέλεις να έχει ο πίνακας; ");
    scanf("%d", &N);
    while ((getchar()) != '\n')
      ;
  } while (N <= 0);

  int *original_random_table = create_table(N, 30, 500);
  int *table_ref = original_random_table;
  int *combined_table = NULL;

  do {
    printf("1. Σειριακή αναζήτηση\n");
    printf("2. Ταξινόμηση αντιγράφου\n");
    printf("3. Δυαδική αναζήτηση\n");
    printf("4. Συγχώνευση πινάκων\n");
    printf("5. Εκτύπωση πινάκων\n");
    printf("6. Αποθήκευση πίνακα\n");
    printf("7. Φόρτωση πίνακα\n");
    printf("8. Έξοδος\n");

    printf("Δώσε αριθμό εντολής: ");
    scanf("%d", &option);
    while ((getchar()) != '\n')
      ;

    switch (option) {
    case 1: {
      int K = 0;
      printf("Ποιόν αριθμό ψάχνεις; ");
      scanf("%d", &K);
      while ((getchar()) != '\n')
        ;
      int result = sequential_search(table_ref, N, K);
      if (result == -1) {
        fprintf(stderr, "Ο αριθμός %d δεν υπάρχει στον πίνακα\n", K);
      } else {
        fprintf(stderr, "Ο αριθμός %d βρίσκεται στην %dη θέση του πίνακα\n", K,
                result + 1);
      }
      break;
    }
    case 2: {
      if (table_ref == original_random_table)
        table_ref = create_sorted_table_copy(original_random_table, N);
      break;
    }
    case 3: {
      if (table_ref == original_random_table)
        table_ref = create_sorted_table_copy(original_random_table, N);
      int K = 0;
      printf("Ποιόν αριθμό ψάχνεις; ");
      scanf("%d", &K);
      while ((getchar()) != '\n')
        ;
      int result = binary_search(table_ref, N, K);
      if (result == -1) {
        fprintf(stderr, "Ο αριθμός %d δεν υπάρχει στον πίνακα\n", K);
      } else {
        fprintf(stderr, "Ο αριθμός %d βρίσκεται στην %dη θέση του πίνακα\n", K,
                result + 1);
      }
      break;
    }
    case 4: {
      if (table_ref == original_random_table)
        table_ref = create_sorted_table_copy(original_random_table, N);
      int *temp_array = create_table(N, 30, 500);
      table_sort(temp_array, N);
      combined_table = merge_table(table_ref, temp_array, N);
      free(temp_array);
      table_sort(combined_table, N * 2);
      break;
    }
    case 5: {
      printf("Αρχικός πίνακας: ");
      print_table(original_random_table, N);

      if (table_ref != original_random_table) {
        printf("Αντιγραμένος πίνακας: ");
        print_table(table_ref, N);
      }

      if (combined_table != NULL) {
        printf("Συνδιασμένος πίνακας: ");
        print_table(combined_table, N * 2);
      }
      break;
    }
    case 6: {
      char *file_path = malloc(256);
      printf("Ποιό αρχείο θές να γράψεις; ");
      scanf("%s", file_path);
      while ((getchar()) != '\n')
        ;
      write_int_table_to_file(file_path, original_random_table, N);
      free(file_path);
      break;
    }
    case 7: {
      char *file_path = malloc(256);
      printf("Ποιό αρχείο θές να διαβάσεις; ");
      scanf("%s", file_path);
      while ((getchar()) != '\n')
        ;
      int *numbers = read_int_table_from_file(file_path, N);
      free(file_path);
      if (numbers == NULL) {
        printf("Δεν μπόρεσε να διαβαστεί το αρχείο\n");
        return 1;
      }
      memcpy(original_random_table, numbers, N * sizeof(int));
      table_ref = original_random_table;
      free(numbers);
      break;
    }
    }
  } while (option != 8);

  if (table_ref != original_random_table)
    free(table_ref);
  if (combined_table != NULL) {
    free(combined_table);
  }
  free(original_random_table);
  return 0;
}

int *create_table(int size, int minimum, int maximum) {
  int *table = malloc(size * sizeof(int));
  for (int i = 0; i < size; i++) {
    int n = rand() % (maximum - minimum + 1) + minimum;
    *(table + i) = n;
  }
  return table;
}

int *create_sorted_table_copy(int *original, int size) {
  int *copy = malloc(size * sizeof(int));
  memcpy(copy, original, size * sizeof(int));
  table_sort(copy, size);
  return copy;
}

void write_int_table_to_file(char *file_path, int *numbers, int N) {
  FILE *fp;
  fp = fopen(file_path, "w");
  if (fp == NULL) {
    fprintf(stderr, "Δεν μπόρεσε να διαβαστεί το αρχείο: %s\n", file_path);
    return;
  }

  int i = 0;
  for (i = 0; i < N; i++) {
    fprintf(fp, "%d\n", *(numbers + i));
  }
  fclose(fp);
}

int *read_int_table_from_file(char *file_path, int N) {
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  int *numbers = malloc(N * sizeof(int));

  fp = fopen(file_path, "r");
  if (fp == NULL) {
    fprintf(stderr, "Δεν μπόρεσε να διαβαστεί το αρχείο: %s\n", file_path);
    return NULL;
  }

  int i = 0;
  while ((getline(&line, &len, fp)) != -1) {
    *(numbers + i++) = atoi(line);
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

void table_sort(int *arr, int size) {
  for (int i = 0; i < size - 1; i++) {
    for (int j = i + 1; j < size; j++) {
      if (*(arr + i) > *(arr + j)) {
        *(arr + i) ^= *(arr + j);
        *(arr + j) ^= *(arr + i);
        *(arr + i) ^= *(arr + j);
      }
    }
  }
}

int *merge_table(int *arr, int *arr2, int size) {
  int *merged_arr = (int *)malloc(2 * size * sizeof(int));
  memcpy(merged_arr, arr, size * sizeof(int));
  memcpy(merged_arr + size, arr2, size * sizeof(int));
  return merged_arr;
}