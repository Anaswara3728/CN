#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 5566
int main() {
int server_sock, client_sock;
struct sockaddr_in server_addr, client_addr;
socklen_t addr_size;
int arr[100], n, i, max, min, sum = 0;
float avg;
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
addr_size = sizeof(client_addr);
client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
printf("[+]Client connected.\n");
// Receive array size
recv(client_sock, &n, sizeof(n), 0);
printf("Received array size: %d\n", n);
// Receive array elements
recv(client_sock, arr, sizeof(int) * n, 0);
printf("Received array elements: ");
for (i = 0; i < n; i++) {
 printf("%d ", arr[i]);
}
printf("\n");
// Compute max, min, and average
max = min = arr[0];
for (i = 0; i < n; i++) {
if (arr[i] > max) max = arr[i];
 if (arr[i] < min) min = arr[i];
 sum += arr[i];
}
avg = (float)sum / n;
// Send results to client
send(client_sock, &max, sizeof(max), 0);
send(client_sock, &min, sizeof(min), 0);
send(client_sock, &avg, sizeof(avg), 0);
printf("Sent max: %d, min: %d, avg: %.2f to client.\n", max, min, avg);
close(client_sock);
close(server_sock);
return 0;
}
