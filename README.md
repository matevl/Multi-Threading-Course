# Multi-Theading-Course
Here is my support course for introduce Multi-threading with POSIX

# Compiling with POSIX Threads

require pthread.h

```bash
gcc your_code.c -o -pthread
```
# POSIX function

## Create a thread
```c
int pthread_create(pthread_t *thread,
                    const pthread_attr_t *attr, //Attributes
                    void *(*start) (void *),    //Thread function
                    void *arg);                 //Argument of the thread function
```

## Terminate all threads
```c
pthread_exit()
```

## Terminate a single threads
```c
int pthread_join(pthread_t thread, void **retval);
```

## Detach a thread
```c++
int pthread_detach(pthread_t thread);
```

## Thread concurrency
```c
// Declaration and Initialization
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
 
// Lock / Unlock
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_trylock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
 
// Destruction
int pthread_mutex_destroy(pthread_mutex_t *mutex);
```

