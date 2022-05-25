#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
int main()
{
	int n, cid, sid, l, N, i;
	struct sockaddr_in s, c;
	char ch;
	sid = socket(AF_INET,SOCK_STREAM,0);
	s.sin_family = AF_INET;
	s.sin_port = htons(1234);
	inet_aton("127.0.0.1",&s.sin_addr);
	puts("Ready to send");
	int res;
	l = sizeof(c);
	connect(sid, (struct sockaddr*)&s, sizeof(s));
	char bitseq[100];
	puts("Enter the message");
	fgets(bitseq,100,stdin);
	puts("Sequence obtained.Sending Sequence to Server...");
	write(sid,bitseq,strlen(bitseq));
	char new_bitseq[101];
	n = read(sid,&new_bitseq,sizeof(new_bitseq));
	printf("\nThe modified bit sequence is: %s\n", new_bitseq);
	close(sid);
	return 0;
}
