# Multi-Threading-Course
Here is my support course for introduce Multi-threading with POSIX

# Prerequisite Knowledge
To understand this course, familiarize yourself with the following C programming concepts:

- Basic C Syntax: Data types, control structures (if, for, while), and functions.
- Memory Allocation: Dynamic memory management using malloc, calloc, realloc, and free.
- Function Pointers: Understanding how to use function pointers, essential for pthread.

# Prerequisite Librarys
```shell
sudo apt-get install libcurl4-openssl-dev #for testing parallel_downloader
```

# Compiling with POSIX Threads

Require pthread.h

```shell
gcc your_code.c -o -pthread
```

Using the given Makefile

```shell
make all # Compile all given code
```
```shell
make parallel_downloader # Compile parallel_downloader
make matrix_mult # Compile matrix_mult
```
```shell
make clean # clean all binary and other trash files
```

# POSIX function

## Create a thread
```c++
int pthread_create(pthread_t *thread,
                    const pthread_attr_t *attr, //Attributes
                    void *(*start) (void *),    //Thread function
                    void *arg);                 //Argument of the thread function
```

## Terminate all threads
```c++
void pthread_exit(void *retval);
```

## Terminate a single threads
```c++
int pthread_join(pthread_t thread, void **retval);
```

## Detach a thread
```c++
int pthread_detach(pthread_t thread);
```

## Thread concurrency
```c++
// Declaration and Initialization
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
 
// Lock / Unlock
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_trylock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
 
// Destruction
int pthread_mutex_destroy(pthread_mutex_t *mutex);
```

