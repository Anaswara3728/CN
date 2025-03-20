#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 5566
int main() {
int sock;
struct sockaddr_in server_addr;
int squaredNum;
// Create socket
sock = socket(AF_INET, SOCK_STREAM, 0);
if (sock < 0) {
 perror("[-]Socket error");
 exit(1);
}
printf("[+]TCP client socket created.\n");
// Server address setup
server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(PORT);
server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
// Connect to server
if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
 perror("[-]Connection error");
 exit(1);
}
printf("Connected to the server.\n");
// Receive squared integer from server
recv(sock, &squaredNum, sizeof(squaredNum), 0);
printf("Received squared integer from server: %d\n", squaredNum);
close(sock);
printf("Disconnected from the server.\n");
return 0;
}
