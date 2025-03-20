#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 5566
#define UDP_PORT 5567
#define SERVER_IP "127.0.0.1"
int main() {
char buffer[1024];
char message[] = "Hello from Client1";
// Sending via TCP
int tcp_sock = socket(AF_INET, SOCK_STREAM, 0);
struct sockaddr_in server_addr;
server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(PORT);
server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
if (connect(tcp_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
 perror("[-] TCP Connection Failed");
 exit(1);
}
send(tcp_sock, message, strlen(message), 0);
printf("[TCP] Sent message to server: %s\n", message);
close(tcp_sock);
// Sending via UDP
int udp_sock = socket(AF_INET, SOCK_DGRAM, 0);
struct sockaddr_in udp_server_addr;
udp_server_addr.sin_family = AF_INET;
udp_server_addr.sin_port = htons(UDP_PORT);
udp_server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
sendto(udp_sock, message, strlen(message), 0, (struct sockaddr
*)&udp_server_addr, sizeof(udp_server_addr));
printf("[UDP] Sent message to server: %s\n", message);
close(udp_sock);
return 0;
} 