#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <arpa/inet.h>


int mport=6004;
int yport=6005;

void* sending(){

}

void* receiving(){

}

int main (){
    int mfd, tfd;
    fd_set rset;
    char buff[1024]=" ";

    struct sockaddr_in myaddr;
    struct sockaddr_in youaddr;
    
    if((mfd=socket(AF_INET, SOCK_DGRAM, 0))<0){
        perror("cannot create socket");
        return 0;
    }

    if((tfd=socket(AF_INET, SOCK_DGRAM, 0))<0){
        perror("cannot create socket");
        return 0;
    }

    memset((char*)&myaddr,0,sizeof(myaddr));
    myaddr.sin_family = AF_INET; //protocall
    myaddr.sin_addr.s_addr = inet_addr("142.58.15.124"); //use my ip address
    myaddr.sin_port=htons(mport);//my port
    if(bind(mfd, (struct sockaddr*)&myaddr, sizeof(myaddr))<0){
        perror("bind failed");
        return 0;
    }
    memset((char*)&youaddr,0,sizeof(youaddr));
    youaddr.sin_family = AF_INET; //protocall
    youaddr.sin_port=htons(yport);//their port
    if (inet_aton("142.58.15.124", &youaddr.sin_addr)==0) {
		fprintf(stderr, "inet_aton() failed\n");
	}

    
    
    int recvlen;
    for(;;){
        FD_ZERO(&rset);
        FD_SET(0,&rset);
        FD_SET(tfd, &rset);

        select(tfd+1,&rest, NULL,NULL );
        if(FD_ISSET(0,&rset)){
            printf("enter the message\n");
            fgets(buff,1024,stdin);
            if(sendto(tfd, buff, 1024, 0, (struct sockaddr*)&youaddr, sizeof(youaddr))<0){
                perror("sendto failed");
            }
        }

        if(FD_ISSET(tfd,&rset)){
            printf("waiting on port %d\n", mport);
            recvlen=recvfrom(tfd, buff, 1024,0,(struct sockaddr*)&myaddr,sizeof(myaddr));
            printf("received %d bytes\n", recvlen);
            if(recvlen>0){
                buff[recvlen]=0;
                printf("received message: \"%s\"\n", buff);
            }
        }
    }
    //sending messages
    
    //receiving messages
    return 0;
}

