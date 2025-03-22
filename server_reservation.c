#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define NUM_SEATS 20
#define BUFFER_SIZE 1024

int seats[NUM_SEATS]; // Array representing available seats
pthread_mutex_t mutex; // Mutex to protect access to seats

/**
 * Function to handle client connections.
 *
 * @param arg Pointer to the client's connection information.
 * @return NULL
 */
void* handle_client(void* arg) {
    int client_socket = *(int*)arg;
    char buffer[BUFFER_SIZE];
    int seat, client_id;

    // Read the client's request
    read(client_socket, buffer, BUFFER_SIZE);
    sscanf(buffer, "RESERVE %d %d", &seat, &client_id);

    // Check and reserve the seat
    pthread_mutex_lock(&mutex);
    if (seat >= 0 && seat < NUM_SEATS && seats[seat] == 0) {
        seats[seat] = client_id;
        sprintf(buffer, "Seat %d reserved for client %d\n", seat, client_id);
    } else {
        sprintf(buffer, "Seat %d not available\n", seat);
    }
    pthread_mutex_unlock(&mutex);

    // Send the response to the client
    send(client_socket, buffer, strlen(buffer), 0);
    close(client_socket);
    pthread_exit(NULL);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    pthread_t thread_id;

    // Initialize seats as available
    for (int i = 0; i < NUM_SEATS; ++i) {
        seats[i] = 0;
    }

    // Initialize the mutex
    pthread_mutex_init(&mutex, NULL);

    // Create the server socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind the socket to the address and port
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Bind error");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_socket, 5) == -1) {
        perror("Listen error");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    // Accept client connections and create threads to handle them
    while ((client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_len)) >= 0) {
        pthread_create(&thread_id, NULL, handle_client, (void*)&client_socket);
        pthread_detach(thread_id);
    }

    // Close the server socket
    close(server_socket);
    pthread_mutex_destroy(&mutex);

    return 0;
}