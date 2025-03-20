#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <math.h>
#define PORT1 5566 // For Client1
#define PORT2 5567 // For Client2
int main() {
int server_sock1, server_sock2, client_sock1, client_sock2;
struct sockaddr_in server_addr1, server_addr2, client_addr;
socklen_t addr_size;
float received_value, modified_value;
// Create sockets for Client1 and Client2
server_sock1 = socket(AF_INET, SOCK_STREAM, 0);
server_sock2 = socket(AF_INET, SOCK_STREAM, 0);
if (server_sock1 < 0 || server_sock2 < 0) {
 perror("[-]Socket error");
 exit(1);
}
printf("[+]TCP server sockets created.\n");
// Setup server address for Client1
server_addr1.sin_family = AF_INET;
server_addr1.sin_port = htons(PORT1);
server_addr1.sin_addr.s_addr = INADDR_ANY;
// Bind server socket for Client1
if (bind(server_sock1, (struct sockaddr*)&server_addr1, sizeof(server_addr1)) <
0) {
 perror("[-]Bind error for Client1");
 exit(1);
}
printf("[+]Bind to port %d for Client1.\n", PORT1);
// Setup server address for Client2
server_addr2.sin_family = AF_INET;
server_addr2.sin_port = htons(PORT2);
server_addr2.sin_addr.s_addr = INADDR_ANY;
// Bind server socket for Client2
if (bind(server_sock2, (struct sockaddr*)&server_addr2, sizeof(server_addr2)) <
0) {
 perror("[-]Bind error for Client2");
 exit(1);
}
printf("[+]Bind to port %d for Client2.\n", PORT2);
// Listen for connections
listen(server_sock1, 5);
listen(server_sock2, 5);
printf("Listening...\n");
// Accept connection from Client1
addr_size = sizeof(client_addr);
client_sock1 = accept(server_sock1, (struct sockaddr*)&client_addr, &addr_size);
printf("[+]Client1 connected.\n");
// Receive float value from Client1
recv(client_sock1, &received_value, sizeof(received_value), 0);
printf("Received value from Client1: %.2f\n", received_value);
// Modify value by power of 1.5
modified_value = pow(received_value, 1.5);
printf("Modified value to send to Client2: %.2f\n", modified_value);
close(client_sock1); // Close connection with Client1
// Accept connection from Client2
client_sock2 = accept(server_sock2, (struct sockaddr*)&client_addr, &addr_size);
printf("[+]Client2 connected.\n");
// Send modified value to Client2
send(client_sock2, &modified_value, sizeof(modified_value), 0);
close(client_sock2); // Close connection with Client2
close(server_sock1);
close(server_sock2);
return 0;
}
