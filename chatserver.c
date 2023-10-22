#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define BUF_SIZE 1024
#define PORT 6005

int main() {
    int sockfd;
    struct sockaddr_in peer_addr;
    socklen_t addr_len = sizeof(peer_addr);
    char buffer[BUF_SIZE];

    // Create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Configure peer address
    memset(&peer_addr, 0, sizeof(peer_addr));
    peer_addr.sin_family = AF_INET;
    peer_addr.sin_port = htons(PORT);
    inet_aton("142.58.15.124", &peer_addr.sin_addr);

    while (1) {
        // Send message to peer
        printf("Enter message: ");
        fgets(buffer, BUF_SIZE, stdin);
        sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr*)&peer_addr, addr_len);

        // Receive response from peer
        memset(buffer, 0, sizeof(buffer));
        int recv_len = recvfrom(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr*)&peer_addr, &addr_len);

        if (recv_len > 0) {
            printf("Peer: %s\n", buffer);
        }
    }

    close(sockfd);
    return 0;
}