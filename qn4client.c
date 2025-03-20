#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 5566
int main() {
int sock;
struct sockaddr_in server_addr;
int arr[100], n, max, min;
float avg;
int i;
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
// Get array size and elements
printf("Enter the number of elements in the array: ");
scanf("%d", &n);
printf("Enter %d integers: ", n);
for (i = 0; i < n; i++) {
 scanf("%d", &arr[i]);
}
// Send array size and elements to server
send(sock, &n, sizeof(n), 0);
send(sock, arr, sizeof(int) * n, 0);
// Receive max, min, and average from server
recv(sock, &max, sizeof(max), 0);
recv(sock, &min, sizeof(min), 0);
recv(sock, &avg, sizeof(avg), 0);
// Print results
printf("Maximum: %d\n", max);
printf("Minimum: %d\n", min);
printf("Average: %.2f\n", avg);
close(sock);
return 0;
}