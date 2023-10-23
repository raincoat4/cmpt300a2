#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>

//int mport=6004;
//int yport=6005;

char* getIP(char* hostName){
    struct addrinfo hints, *res, *p;
    int status;
    char ipstr[INET6_ADDRSTRLEN];

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if((status = getaddrinfo(hostName, NULL, &hints, &res)) != 0){
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        return NULL;
    }

    //printf("IP addresses for %s:\n\n", hostName);
    
    for(p = res; p != NULL; p = p->ai_next){
        void *addr;
        //char *ipver;
        if(p->ai_family == AF_INET){
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
            //ipver = "IPv4";
        }
        else{
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;;
            addr = &(ipv6->sin6_addr);
            //ipver = "IPv6";
        }
        inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
        //printf(" %s: %s\n", ipver, ipstr);
    }
    freeaddrinfo(res);

    char* result = malloc(strlen(ipstr)+1);
    strcpy(result, ipstr);
    return result;
}
//these will be needed for threads 
void* sending(){
    
}

void* receiving(){

}

void* print(){

}

void* writting(){

}

int main (int argc, char *argv[]){
    int mfd, tfd;
    fd_set rset;//i think this is where you use the list ADT from assignment 1 not sure tho
    char buff[1024]=" ";
    int mport = atoi(argv[1]);
    char* ip = getIP(argv[2]);
    if(!ip){
        return 0;
    }
    int yport = atoi(argv[3]);
    struct sockaddr_in myaddr;
    struct sockaddr_in youaddr;
    
    //my endpoint socket
    if((mfd=socket(AF_INET, SOCK_DGRAM, 0))<0){
        perror("cannot create socket");
        return 0;
    }

    //destination socket

    //setting up my addr and binding it to a socket
    memset((char*)&myaddr,0,sizeof(myaddr));
    myaddr.sin_family = AF_INET; //protocall
    myaddr.sin_addr.s_addr = htonl(INADDR_ANY); //use my ip address
    myaddr.sin_port=htons(mport);//my port
    if(bind(mfd, (struct sockaddr*)&myaddr, sizeof(myaddr))<0){//binding my socket
        perror("bind failed");
        return 0;
    }
    
    //setting up destination addr
    memset((char*)&youaddr,0,sizeof(youaddr));
    youaddr.sin_family = AF_INET; //protocall
    youaddr.sin_port=htons(yport);//their port
    if (inet_aton(ip, &youaddr.sin_addr)==0) {//setting destination addr
		fprintf(stderr, "inet_aton() failed\n");
	}
    
    int recvlen;
    for(;;){
        //resetting msg
        FD_ZERO(&rset);
        FD_SET(0,&rset);
        FD_SET(mfd, &rset);

        //sending a message
        //This will be 2 or 3 threads i think. one to read with fgets(), one to use sendto(), and maybe one to print enter msg might not be needed tho
        // Will need to lock buff for all three threads
        if(FD_ISSET(0,&rset)){
            printf("enter the message\n");
            fgets(buff,1024,stdin);
            if(sendto(mfd, buff, 1024, 0, (struct sockaddr*)&youaddr, sizeof(youaddr))<0){
                perror("sendto failed");
            }
        }

        //receiving a message 
        //this will be 2 threads i think. One to use recvfrom and the other to print the msg
        //Will need to lock buff for both threads
        if(FD_ISSET(mfd,&rset)){
            printf("waiting on port %d\n", mport);
            recvlen=recvfrom(mfd, buff, 1024,0,(struct sockaddr*)&myaddr,sizeof(myaddr));
            printf("received %d bytes\n", recvlen);
            //if(recvlen>0){
                buff[recvlen]=0;
                printf("received message: \"%s\" \n", buff);
            //}
        }
    }
    //sending messages
    
    //receiving messages
    free(ip); //free ip because it was dynamically allocaged
    return 0;
}

