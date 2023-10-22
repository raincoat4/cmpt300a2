#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <arpa/inet.h>

int client(int sfd, fd_set rset){
    struct sockaddr_in server;

    for(;;){
        FD_ZERO(&rset);
        FD_SET(0,&rset);
        FD_SET(sfd, &rset);
        char buff[1024]= " ";

        select(sfd +1, &rset, NULL, NULL, NULL);

        if(FD_ISSET(0,&rset)){
            printf("Enter the message:\n");
            fgets(buff, 1024, stdin);//listening for keyboard input
            //scanf("%s", buff);
            sendto(sfd, buff, strlen(buff),0, (struct sockaddr*)&server, addr_len);//writing to UDP datagram
        }

        if(FD_ISSET(sfd, &rset)){
            recvfrom(sfd, buff, 1024,1024,0,(struct sockaddr*)&server, addr_len);//receiving datagram
            printf("Message received: %s\n", buff);//printing message to screen
        }
    }
    close(sfd);

    return 0;

}
/*
int server(int sfd, fd_set rset){
    struct sockaddr_in server;

    for(;;){
        FD_ZERO(&rset);
        FD_SET(0,&rset);
        FD_SET(sfd, &rset);
        char buff[1024]= " ";

        select(sfd +1, &rset, NULL, NULL, NULL);

        if(FD_ISSET(0,&rset)){
            printf("Enter the message:\n");
            fgets(buff, 1024, stdin);//listening for keyboard input
            //scanf("%s", buff);
            sendto(sfd, buff, strlen(buff),0, (struct sockaddr*)&server, addr_len);//writing to UDP datagram
        }

        if(FD_ISSET(sfd, &rset)){
            recvfrom(sfd, buff, 1024,1024,0,(struct sockaddr*)&server, addr_len);//receiving datagram
            printf("Message received: %s\n", buff);//printing message to screen
        }
    }
    close(sfd);

    return 0;

}
*/

int main(){
    int sfd; //sfd is our socket, cfd is the connection
    fd_set rset;
    
    struct sockaddr_in server;
    socklen_t addr_len = sizeof(client);

    sfd = socket(AF_INET, SOCK_STREAM, 0);

    if(sfd < 0){
        printf("Socket creation failed. \n");
        return -1;
    }

    bzero(&server, sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
    server.sin_port = htons(6005);
    inet_aton("142.58.15.124", &server.sin_addr);
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    

    if(bind(sfd, (struct sockaddr*)&server, sizeof(server)) < 0){
        printf("Binding failed. \n");
        return -1;
    }

    client(sfd, rset);

    return 0;
}


