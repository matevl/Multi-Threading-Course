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

    int pthread_create(pthread_t *thread,
                    const pthread_attr_t *attr, //Attributes
                    void *(*start) (void *),    //Thread function
                    void *arg);
    }
    return 0;
}
