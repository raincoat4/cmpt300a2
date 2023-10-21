#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int client(int sfd, fd_set rset){
    
    for(;;){
        FD_ZERO(&rset);
        FD_SET(0,&rset);
        FD_SET(sfd, &rset);
        char buff[1024]= " ";
        select(sfd +1, &rset, NULL, NULL, NULL);

        if(FD_ISSET(0,&rset)){
            printf("Enter the message:\n");
            fgets(buff, 1024);
            //scanf("%s", buff);
            write(sfd, buff, strlen(buff));
        }

        if(FD_ISSET(sfd, &rset)){
            read(sfd, buff, 1024);
            printf("Message received: %s\n", buff);
        }
    }
    close(sfd);
    return 0;

}

int main(){
    int sfd, cfd; //sfd is our socket, cfd is the connection
    fd_set rset;
    
    struct sockaddr_in server;

    sfd = socket(AF_INET, SOCK_STREAM, 0);

    if(sfd < 0){
        printf("Socket creation failed. \n");
        return -1;
    }

    bzero(&server, sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
    server.sin_port = htons(6005);
    inet_aton("142.58.15.124", &server.sin_addr);

    

    printf("Attempting to connect\n");
    if(connect(sfd, (struct sockaddr*)&server, sizeof(server))!=-1){
        printf("Connection succeeded\n");
        client(sfd,rset);
        return 0;
    }

    printf("connection failed\n");
    if(bind(sfd, (struct sockaddr*)&server, sizeof(server)) < 0){
        printf("Binding failed. \n");
        return -1;
    }

    listen(sfd, 7);
    cfd = accept(sfd, NULL, NULL);
    for (;;){
        FD_ZERO(&rset);
        FD_SET(0, &rset);
        FD_SET(cfd, &rset); //cfd
        char buff[1024] = " ";
        select(cfd+1, &rset, NULL, NULL, NULL);

        if (FD_ISSET(0, &rset)){//if rset is empty send a message
            printf("Enter the message:\n");
            fgets(buff, 1024, stdin);
            //scanf("%s", buff);
            write(cfd, buff, strlen(buff));
        }

        if(FD_ISSET(cfd, &rset)){//receiving a message
            read(cfd, buff, 1024);
            printf("Message received; %s\n", buff);
        }
    }
    close(cfd);
    close(sfd);
    return 0;
}


