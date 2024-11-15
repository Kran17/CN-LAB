#include<stdio.h>
#include<winsock2.h>    // For Winsock API
#include<ws2tcpip.h>   
#pragma comment(lib,"ws2_32.lib")  
void func(SOCKET sockfd, struct sockaddr_in servaddr);

int main() {
    WSADATA wsa;
    SOCKET sockfd;
    struct sockaddr_in servaddr;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("WSAStartup failed. Error Code: %d\n", WSAGetLastError());
        return 1;
    }

    printf("Winsock initialized.\n");

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == INVALID_SOCKET) {
        printf("Socket creation failed. Error Code: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    printf("\nSocket created.\n");

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(43451);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    func(sockfd, servaddr);
    closesocket(sockfd);
    WSACleanup();

    return 0;
}

void func(SOCKET sockfd, struct sockaddr_in servaddr) {
    int msg;
    int server_len = sizeof(servaddr);
    printf("\nEnter the value for principal (P): ");
    scanf("%d", &msg);
    sendto(sockfd, (char*)&msg, sizeof(msg), 0, (struct sockaddr*)&servaddr, server_len);
    printf("\nEnter the value for rate of interest (R): ");
    scanf("%d", &msg);
    sendto(sockfd, (char*)&msg, sizeof(msg), 0, (struct sockaddr*)&servaddr, server_len);

    printf("\nEnter the value for number of years (N): ");
    scanf("%d", &msg);
    sendto(sockfd, (char*)&msg, sizeof(msg), 0, (struct sockaddr*)&servaddr, server_len);

    printf("\nCompound Interest is: ");
    recvfrom(sockfd, (char*)&msg, sizeof(msg), 0, (struct sockaddr*)&servaddr, &server_len);
    printf("%d\n", msg);
}
