//Client

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
	int sockfd;
	int len;
	struct sockaddr_un address;
	int result;
	char ch;
        int arr[100];
        printf("Enter the number of integers : ");
        scanf("%d",&arr[0]);
        printf(" Enter the integers : ");
        for(int i=1; i<=arr[0]; i++)
        {
          scanf("%d",&arr[i]);
          }
          int flag=0;
          for(int i=1;i<=arr[0];i++){
              for(int j=1;j<=arr[0];j++){
                  if(arr[i]==arr[j] && i!=j){
                          flag=1;
                          break;
                          }
                 }
                 if(flag==1){
                 break;}
           }
          if(flag==1){
                printf("ERROR duplicate elements\n");
                exit(1);
            }
          
        	sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

		address.sun_family = AF_UNIX;
		strcpy(address.sun_path, "server_socket");
		len = sizeof(address);

		result = connect(sockfd, (struct sockaddr *)&address, len);
		//Connect to the server
        	
        
	
	
	if(result == -1) {
		perror("oops: client1");
		exit(1);
		
}

write(sockfd, arr, 400);
read(sockfd, arr, 400);
//read and write via sockfd

//printf("char from server = %c\n", ch);
printf(" \nSorted array of integers : ");
for(int i=1; i<=arr[0]; i++)
{
 printf("%d ", arr[i]);
}
close(sockfd);
// close the socket connection

exit(0);
}
