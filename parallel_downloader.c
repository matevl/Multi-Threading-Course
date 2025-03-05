#include <curl/curl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * DownloadArgs is a struct to give args to download_file function
 */
typedef struct {
  const char *url;
  const char *filename;
} DownloadArgs;

/**
 * Callback function for writing data to a file.
 *
 * @param ptr The data to write.
 * @param size The size of each element to write.
 * @param nmemb The number of elements to write.
 * @param stream The file stream to write to.
 * @return The number of bytes written.
 */
size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
  size_t written = fwrite(ptr, size, nmemb, stream);
  return written;
}

/**
 * Function executed by each thread to download a file.
 *
 * @param arg Pointer to DownloadArgs containing the URL and filename.
 * @return NULL
 */
void *download_file(void *arg) {
  DownloadArgs *args = (DownloadArgs *)arg;
  CURL *curl;
  FILE *fp;
  CURLcode res;

  curl = curl_easy_init();
  if (curl) {
    fp = fopen(args->filename, "wb");

    // curl section
    curl_easy_setopt(curl, CURLOPT_URL, args->url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
    }

    curl_easy_cleanup(curl); // Clean up the CURL handle
    fclose(fp);
  }

  printf("Finished downloading %s\n", args->url);

  // free section
  free((void *)args->url);
  free((void *)args->filename);
  free(args);

  pthread_exit(NULL);
}

/**
 * Main function to initialize and manage download threads.
 *
 * @return 0 on success.
 */
int main() {
  const char *urls[] = {
      "https://raw.githubusercontent.com/torvalds/linux/master/README",
      "https://www.rfc-editor.org/rfc/rfc1149.txt",
      "http://ipv4.download.thinkbroadband.com/5MB.zip",
      "https://jsonplaceholder.typicode.com/posts"};
  const int num_urls = sizeof(urls) / sizeof(urls[0]);
  pthread_t threads[num_urls];

  curl_global_init(CURL_GLOBAL_DEFAULT); // Initialize the CURL library

  for (int i = 0; i < num_urls; i++) {
    DownloadArgs *args = malloc(sizeof(DownloadArgs));
    args->url = strdup(urls[i]); // Duplicate the URL string
    args->filename = malloc(50);
    sprintf((char *)args->filename, "download_%d", i + 1); // Set the filename

    pthread_create(&threads[i], NULL, download_file,
                   args); // Create a new thread
  }

  for (int i = 0; i < num_urls; i++) {
    pthread_join(threads[i], NULL); // Wait for each thread to finish
  }

  curl_global_cleanup(); // Clean up the CURL library
  return 0;
}
