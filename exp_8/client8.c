


//client

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#define PORT 8080
#define MAXLINE 1024
int main() {
int sockfd;
char a[100],b[100];
struct sockaddr_in servaddr;
if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
perror("Socket Creation Failed"); // print error
exit(EXIT_FAILURE);// Clean up the module
}
memset(&servaddr, 0, sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_port = htons(PORT);
servaddr.sin_addr.s_addr = INADDR_ANY;
//Receiving Dataword from user
printf("Enter the data : ");
//fgets(a,100,stdin);
scanf("%s",a);
int n, len;
sendto(sockfd, (char *)a, strlen(a),
MSG_CONFIRM, (const struct sockaddr *) &servaddr,
sizeof(servaddr));
perror("Send to");
n = recvfrom(sockfd, (char *)b, MAXLINE,
MSG_WAITALL, (struct sockaddr *) &servaddr,
&len);
perror("recvfrom");
// print the buffer in case of string
b[n] = '\0';
printf("Codeword receiver from Server is : %s\n", b);
close(sockfd);
return 0;
}
