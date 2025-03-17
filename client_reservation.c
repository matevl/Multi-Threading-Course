#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_PORT 8080
#define BUFFER_SIZE 1024

/**
 * Function to send a reservation request to the server.
 *
 * @param server_ip The IP address of the server.
 * @param seat The seat number to reserve.
 * @param client_id The unique client ID.
 */
void send_reservation_request(const char *server_ip, int seat, int client_id) {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("Could not create socket");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    // Connect to server
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

    // Prepare reservation request
    snprintf(buffer, sizeof(buffer), "RESERVE %d %d", seat, client_id);

    // Send request to server
    send(sock, buffer, strlen(buffer), 0);
    printf("Request sent: %s\n", buffer);

    // Read server response
    read(sock, buffer, BUFFER_SIZE);
    printf("Server response: %s\n", buffer);

    // Close the socket
    close(sock);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <seat> <client_id>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *server_ip = "127.0.0.1";
    int seat = atoi(argv[1]);
    int client_id = atoi(argv[2]);

    send_reservation_request(server_ip, seat, client_id);

    return 0;
}
