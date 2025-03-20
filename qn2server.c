#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 5566
int main() {
int server_sock, client_sock1, client_sock2;
struct sockaddr_in server_addr, client_addr;
socklen_t addr_size;
int num, squaredNum;
// Create socket
server_sock = socket(AF_INET, SOCK_STREAM, 0);
if (server_sock < 0) {
 perror("[-]Socket error");
 exit(1);
}
printf("[+]TCP server socket created.\n");
// Server address setup
server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(PORT);
server_addr.sin_addr.s_addr = INADDR_ANY;
// Bind socket to address
if (bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
 perror("[-]Bind error");
 exit(1);
}
printf("[+]Bind to the port number: %d\n", PORT);
// Listen for connections
listen(server_sock, 5);
printf("Listening...\n");
// Accept Client1
addr_size = sizeof(client_addr);
client_sock1 = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
printf("[+]Client1 connected.\n");
// Receive integer from Client1
recv(client_sock1, &num, sizeof(num), 0);
printf("Received integer from Client1: %d\n", num);
// Square the integer
squaredNum = num * num;
printf("Squared integer: %d\n", squaredNum);
close(client_sock1); // Disconnect Client1
// Accept Client2
client_sock2 = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
printf("[+]Client2 connected.\n");
// Send squared integer to Client2
send(client_sock2, &squaredNum, sizeof(squaredNum), 0);
printf("Sent squared integer to Client2.\n");
close(client_sock2); // Disconnect Client2
close(server_sock); // Close server socket
return 0;
}
