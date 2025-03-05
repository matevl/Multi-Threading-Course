#include "parrallel_task.h"

#include <stdlib.h>
#include "pthread.h"

void *parrallel_task(void *arg) {
  return NULL;
}

int main() {
  	int size = 1000;
	int *array = malloc(sizeof(int) * size);
    for (int i = 0; i < 4; i++) {

    }

    free(array);
    return 0;
}
