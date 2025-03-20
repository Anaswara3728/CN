#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 5566
int main() {
int sock;
struct sockaddr_in server_addr;
float value;
// Create socket
sock = socket(AF_INET, SOCK_STREAM, 0);
if (sock < 0) {
 perror("[-]Socket error");
 exit(1);
}
printf("[+]TCP Client1 socket created.\n");
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
// Get float value and send to server
printf("Enter a float value to send to the server: ");
scanf("%f", &value);
send(sock, &value, sizeof(value), 0);
printf("Sent value: %.2f\n", value);
close(sock);
return 0;
}