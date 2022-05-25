#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
int sid;
struct sockaddr_in s, c;
void* multi_client(void* arg)
{
	int cid, l, n;
	char bits[100];
	l = sizeof(c);
	cid = accept(sid, (struct sockaddr*)&s, &l);
	if(cid<0){
		printf("error");
		exit(0);
	}
	n = read(cid,bits,sizeof(bits));
	bits[n] = '\0';

	int size_l = strlen(bits);

	int count = 0;
	for(int i=0;i<size_l;i++)
	{
		if(bits[i]=='1')
			count++;
	}
	//printf("%d",count);
	if(count%2==1){
		 printf("%s",bits);
		 printf("\n1\n");
		 bits[size_l]='1';
	 }
	 else
	 {
		  printf("%s",bits);
		  printf("\n0\n");
		  bits[size_l]='0';
	 }


	write(cid,&bits,sizeof(bits));
	close(cid);
}
int main()
{
	int MAX_CONNECTIONS = 3,temp;
	char bits[100];
	pthread_t th[MAX_CONNECTIONS];
	sid = socket(AF_INET,SOCK_STREAM,0);
	s.sin_family = AF_INET;
	s.sin_port = htons(1234);
	inet_aton("127.0.0.1",&s.sin_addr);
	puts("Server started!");
	bind(sid, (struct sockaddr*)&s, sizeof(s));
	listen(sid,MAX_CONNECTIONS);
	temp=MAX_CONNECTIONS;
	while(temp--)
		pthread_create(&th[temp],NULL,multi_client,NULL);
	temp=MAX_CONNECTIONS;
	while(temp--)
		pthread_join(th[temp],NULL);
	close(sid);
	puts("Server Closed");
	return 0;
}
