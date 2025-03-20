#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 5567
int main() {
int sock;
struct sockaddr_in server_addr;
float received_value;
// Create socket
sock = socket(AF_INET, SOCK_STREAM, 0);
if (sock < 0) {
 perror("[-]Socket error");
 exit(1);
}
printf("[+]TCP Client2 socket created.\n");
// Setup server address
server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(PORT);
server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
// Connect to server
if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
 perror("[-]Connection error");
 exit(1);
}
printf("Connected to the server.\n");
// Receive modified value from server
recv(sock, &received_value, sizeof(received_value), 0);
printf("Received modified value: %.2f\n", received_value);
close(sock);
return 0;
}