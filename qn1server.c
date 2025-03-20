#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 5566
#define UDP_PORT 5567
#define CLIENT2_PORT 5568
#define CLIENT2_IP "127.0.0.1"
void reverseString(char *str) {
int len = strlen(str);
for (int i = 0; i < len / 2; i++) {
 char temp = str[i];
 str[i] = str[len - i - 1];
 str[len - i - 1] = temp;
}
}
int main() {
char buffer[1024];
// TCP Setup
int tcp_sock = socket(AF_INET, SOCK_STREAM, 0);
struct sockaddr_in tcp_addr, client_addr;
tcp_addr.sin_family = AF_INET;
tcp_addr.sin_port = htons(PORT);
tcp_addr.sin_addr.s_addr = INADDR_ANY;
bind(tcp_sock, (struct sockaddr *)&tcp_addr, sizeof(tcp_addr));
listen(tcp_sock, 5);
int client_sock = accept(tcp_sock, NULL, NULL);
recv(client_sock, buffer, sizeof(buffer), 0);
printf("[TCP] Received: %s\n", buffer);
close(client_sock);
close(tcp_sock);
// UDP Setup
int udp_sock = socket(AF_INET, SOCK_DGRAM, 0);
struct sockaddr_in udp_addr;
udp_addr.sin_family = AF_INET;
udp_addr.sin_port = htons(UDP_PORT);
udp_addr.sin_addr.s_addr = INADDR_ANY;
bind(udp_sock, (struct sockaddr *)&udp_addr, sizeof(udp_addr));
recvfrom(udp_sock, buffer, sizeof(buffer), 0, NULL, NULL);
printf("[UDP] Received: %s\n", buffer);
close(udp_sock);
// Reverse String
reverseString(buffer);
printf("Reversed String: %s\n", buffer);
// Send to Client2
int udp_sock2 = socket(AF_INET, SOCK_DGRAM, 0);
struct sockaddr_in client2_addr;
client2_addr.sin_family = AF_INET;
client2_addr.sin_port = htons(CLIENT2_PORT);
client2_addr.sin_addr.s_addr = inet_addr(CLIENT2_IP);
sendto(udp_sock2, buffer, strlen(buffer), 0, (struct sockaddr *)&client2_addr,
sizeof(client2_addr));
printf("[UDP] Sent reversed string to Client2\n");
close(udp_sock2);
return 0;
}