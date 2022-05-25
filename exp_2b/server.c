//Server

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>

/*
predefined structure
struct sockaddr_un {
               sa_family_t sun_family;	//AF_UNIX
               char sun_path[108];	//Pathname
           };

*/
void swap(int *xp, int *yp)
{

    int temp = *xp;

    *xp = *yp;

    *yp = temp;
}
 
// A function to implement bubble sort

void bubbleSort(int arr[], int n)
{

   int i, j;

   for (i = 0; i < n-1; i++)      
 

       // Last i elements are already in place   

       for (j = 0; j < n-i-1; j++) 

           if (arr[j] > arr[j+1])

               swap(&arr[j], &arr[j+1]);
 }
int main()
{
	int server_sockfd, client_sockfd;
	int server_len, client_len;
	struct sockaddr_un server_address;
	struct sockaddr_un client_address;

	unlink("server_socket"); 
	//The file should be deleted by the caller when it is no longer needed. AF_UNIX sockets can be deleted with unlink(). 
	
	server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0); 
	//SOCK_STREAM/SOCK_DGRAM, AF_UNIX(Unix file system )/AF_INET(Internet domain )

	server_address.sun_family = AF_UNIX; 
	//This socket family is used to communicate between processes on the same machine.
	
	strcpy(server_address.sun_path, "server_socket");
	//The file name referred to in addr.sun_path is created as a socket in the system file "server socket"
	
	server_len = sizeof(server_address);
	bind(server_sockfd, (struct sockaddr *)&server_address, server_len);
	// bind a name to a socket
	// Server ask the OS to enter information in the socket
	// RETURN VALUE- On success, zero is returned.  On error, -1 is returned
	
	listen(server_sockfd, 5);
	//listen the requests comming from the client
	// 5,backlog - the no of connections allowed in the queue. It can never be zero
	
	while(1) {
		//char ch;
		int arr[100];
		printf("\nserver waiting\n");

		client_len = sizeof(client_address);
		client_sockfd = accept(server_sockfd,(struct sockaddr *)&client_address, &client_len);
		//connection gets established here
		
		read(client_sockfd, arr, 400);
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
		else if(arr[0]>=2)
		{
			bubbleSort(arr+1,arr[0]);
			for(int i=1; i<=arr[0]; i++)
			{
			 	printf("%d ", arr[i]);
			}
		write(client_sockfd, arr, 400);
		}
		else
		{
			printf("ERROR");
		}
		//read and write to client on client_sockfd
		
		close(client_sockfd);
		// close the socket connection
	}
}

