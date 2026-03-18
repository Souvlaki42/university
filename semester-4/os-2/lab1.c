#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_LINE 1024

// Compile command: gcc lab1.c -o lab1 -lcurl

// ----------------------------------------------------
// Callback function για το libcurl
//
// Η libcurl μάς δίνει κομμάτια δεδομένων και εμείς
// τα γράφουμε στο τοπικό αρχείο με fwrite().
//
// ptr : δείκτης στα δεδομένα που ήρθαν
// size : μέγεθος κάθε στοιχείου
// nmemb : πόσα στοιχεία ήρθαν
// stream : το FILE* που περάσαμε με CURLOPT_WRITEDATA
//
// Επιστρέφουμε πόσα στοιχεία γράψαμε.
// ----------------------------------------------------
static size_t write_cb(void *ptr, size_t size, size_t nmemb, void *stream) {
  return fwrite(ptr, size, nmemb, (FILE *)stream);
}

// ----------------------------------------------------
// Function που κατεβάζει ένα URL σε local file
//
// url : το URL που θα κατεβάσουμε
// filename : το τοπικό αρχείο εξόδου
//
// Επιστρέφει:
// 0 -> επιτυχία
// 1 -> αποτυχία
//
// Η βασική ροή είναι:
// 1. curl_global_init
// 2. curl_easy_init
// 3. fopen το output file
// 4. CURLOPT_URL
// 5. CURLOPT_WRITEFUNCTION / CURLOPT_WRITEDATA
// 6. curl_easy_perform
// 7. cleanup
// ----------------------------------------------------
int download_file(const char *url, const char *filename) {
  CURL *curl;
  CURLcode res;
  FILE *fp;

  // Αρχικοποίηση της libcurl
  if (curl_global_init(CURL_GLOBAL_DEFAULT) != CURLE_OK) {
    fprintf(stderr, "curl_global_init failed\n");
    return 1;
  }

  // Δημιουργία easy handle
  curl = curl_easy_init();
  if (curl == NULL) {
    fprintf(stderr, "curl_easy_init failed\n");
    curl_global_cleanup();
    return 1;
  }

  // Άνοιγμα τοπικού αρχείου για binary write
  fp = fopen(filename, "wb");
  if (fp == NULL) {
    perror("fopen failed");
    curl_easy_cleanup(curl);
    curl_global_cleanup();
    return 1;
  }

  // Ορισμός URL
  curl_easy_setopt(curl, CURLOPT_URL, url);

  // Callback που θα γράφει τα bytes στο αρχείο
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_cb);

  // Δίνουμε στο callback το FILE*
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

  // Για απλούστερο demo, ακολουθούμε redirects
  curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

  // Εκτέλεση download
  res = curl_easy_perform(curl);

  if (res != CURLE_OK) {
    fprintf(stderr, "Download failed for %s: %s\n", url,
            curl_easy_strerror(res));
    fclose(fp);
    curl_easy_cleanup(curl);
    curl_global_cleanup();
    return 1;
  }

  // Κλείσιμο/cleanup
  fclose(fp);
  curl_easy_cleanup(curl);
  curl_global_cleanup();

  return 0;
}

int main() {
  char url1[MAX_LINE], url2[MAX_LINE], url3[MAX_LINE];
  char cmd[MAX_LINE];
  FILE *fp;

  pid_t pid1, pid2, pid3;
  pid_t finished;
  int status;
  int done = 0;

  sprintf(cmd, "head -1 list | tail -1");
  fp = popen(cmd, "r");
  fgets(url1, sizeof(url1), fp);
  printf("%s\n", url1);

  sprintf(cmd, "head -2 list | tail -1");
  fp = popen(cmd, "r");
  fgets(url2, sizeof(url2), fp);
  printf("%s\n", url2);

  sprintf(cmd, "head -3 list | tail -1");
  fp = popen(cmd, "r");
  fgets(url3, sizeof(url3), fp);
  printf("%s\n", url3);

  url1[strcspn(url1, "\n")] = 0;
  url2[strcspn(url2, "\n")] = 0;
  url3[strcspn(url2, "\n")] = 0;

  if ((pid1 = fork()) == 0) {
    download_file(url1, "pdf1.pdf");
    printf("Child 1 done\n");
    exit(1);
  }

  if ((pid2 = fork()) == 0) {
    download_file(url2, "pdf2.pdf");
    printf("Child 2 done\n");
    exit(2);
  }

  if ((pid3 = fork()) == 0) {
    download_file(url3, "pdf3.pdf");
    printf("Child 3 done\n");
    exit(3);
  }

  while (done < 3) {
    pid_t finished = waitpid(-1, &status, WNOHANG);

    if (finished > 0) {
      done++;

      if (WIFEXITED(status)) {
        printf("Parent: Child PID=%d finished with status=%d\n", finished,
               WEXITSTATUS(status));
      }
    } else if (finished == 0) {
      printf("Parent: no child finished yet...\n");
    } else {
      perror("waitpid failed");
      exit(EXIT_FAILURE);
    }

    sleep(1); // για να μην κάνει busy loop (CPU 100%)
  }

  printf("\nAll children finished. Parent exiting.\n");

  return 0;
}
