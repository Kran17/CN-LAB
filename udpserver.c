#include<stdio.h>
#include<winsock2.h>    
#include<ws2tcpip.h> #include<math.h> 
#pragma comment(lib,"ws2_32.lib")   
void func(SOCKET sockfd, struct sockaddr_in *cliaddr, int len);

int main() {
    WSADATA wsa;
    SOCKET sockfd;
    struct sockaddr_in servaddr, cliaddr;
    int len = sizeof(cliaddr);
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("Winsock initialization failed. Error Code: %d\n", WSAGetLastError());
        return 1;
    }

    printf("Winsock initialized.\n");
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

    if (bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == SOCKET_ERROR) {
        printf("\nBind failed. Error Code: %d\n", WSAGetLastError());
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    printf("\nBind successfully.\n");
    func(sockfd, &cliaddr, len);
    closesocket(sockfd);
    WSACleanup();

    return 0;
}

void func(SOCKET sockfd, struct sockaddr_in *cliaddr, int len) {
    int p, r, n, ci;
    int client_len = sizeof(*cliaddr);
    recvfrom(sockfd, (char*)&p, sizeof(p), 0, (struct sockaddr*)cliaddr, &client_len);
    printf("Received P = %d\n", p);
    recvfrom(sockfd, (char*)&r, sizeof(r), 0, (struct sockaddr*)cliaddr, &client_len);
    printf("Received R = %d\n", r);
    recvfrom(sockfd, (char*)&n, sizeof(n), 0, (struct sockaddr*)cliaddr, &client_len);
    printf("Received N = %d\n", n);

    double amount = p * pow((1 + (double)r/100), n); 
    ci = (int)(amount - p);

    printf("The compound interest is: %d\n", ci);

    sendto(sockfd, (char*)&ci, sizeof(ci), 0, (struct sockaddr*)cliaddr, client_len);
}
 