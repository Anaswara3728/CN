#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define CLIENT2_PORT 5568
int main() {
char buffer[1024];
int udp_sock = socket(AF_INET, SOCK_DGRAM, 0);
struct sockaddr_in udp_addr;
udp_addr.sin_family = AF_INET;
udp_addr.sin_port = htons(CLIENT2_PORT);
udp_addr.sin_addr.s_addr = INADDR_ANY;
bind(udp_sock, (struct sockaddr *)&udp_addr, sizeof(udp_addr));
printf("[+] Waiting for reversed string from server...\n");
recvfrom(udp_sock, buffer, sizeof(buffer), 0, NULL, NULL);
printf("Received Reversed String: %s\n", buffer);
close(udp_sock);
return 0;
}