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
    sid = socket(AF_INET, SOCK_STREAM, 0);
    s.sin_family = AF_INET;
    s.sin_port = htons(1234);
    inet_aton("127.0.0.1", &s.sin_addr);
    //puts("Server started");
    int res;
    l = sizeof(c);
    connect(sid, (struct sockaddr *)&s, sizeof(s));
    char bitseq[100];
    puts("Enter the message");
    fgets(bitseq, 100, stdin);
    puts("Sequence obtained.Sending Sequence to Server...");
    write(sid, bitseq, strlen(bitseq));
    char new_bitseq[102];
    n = read(sid, &new_bitseq, sizeof(new_bitseq));
    printf("\n-----------EVEN PARITY-----------\n");
    printf("The modified bit sequence is: ");
    //while(getchar()!='\n');
    //printf("\n");
    int len_str = strlen(new_bitseq);
    //printf("%d",lll);
    int fl = 0;
    for(int i=0;i<len_str;i++)
    {
        if(i==len_str-2) continue;
        if(i==len_str-1) fl = new_bitseq[i];
        printf("%c",new_bitseq[i]);
    }

    printf("\n-----------ODD PARITY-----------\n");
    //int len_str = strlen(new_bitseq);
    //printf("%d",lll);
    printf("The modified bit sequence is: ");
    for(int i=0;i<len_str-1;i++)
    {
        if(i==len_str-2) continue;

        printf("%c",new_bitseq[i]);
    }
    
    if(fl==1){

        printf("0");
    }
    else
        printf("1");


    printf("\n");
    //printf("%c ",new_bitseq[5]);
    close(sid);
    return 0;
}
