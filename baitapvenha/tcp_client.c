#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(int argc, char * argv[]) {
    if (argc != 3) 
    {
        printf("Tham so khong dung dinh dang\n");
        return 1;
    }
    int client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(9000);

    int ret = connect(client, (struct sockaddr *)&addr, sizeof(addr));
    if (ret == -1) {
        perror("connect() failed");
        return 1;
    }

    char message[100];
    while(1) {
        fgets(message, sizeof(message), stdin);
        send(client, message, strlen(message), 0);
    }
    close(client);
}