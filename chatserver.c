#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <arpa/inet.h>


int mport=6004;
int yport=6005;
//these will be needed for threads 
void* sending(){
    
}

void* receiving(){

}

void* print(){

}

void* writting(){
    
}

int main (){
    int mfd, tfd;
    fd_set rset;//i think this is where you use the list ADT from assignment 1 not sure tho
    char buff[1024]=" ";

    struct sockaddr_in myaddr;
    struct sockaddr_in youaddr;
    
    //my endpoint socket
    if((mfd=socket(AF_INET, SOCK_DGRAM, 0))<0){
        perror("cannot create socket");
        return 0;
    }

    //destination socket
    if((tfd=socket(AF_INET, SOCK_DGRAM, 0))<0){
        perror("cannot create socket");
        return 0;
    }
    //setting up my addr and binding it to a socket
    memset((char*)&myaddr,0,sizeof(myaddr));
    myaddr.sin_family = AF_INET; //protocall
    myaddr.sin_addr.s_addr = inet_addr("142.58.15.124"); //use my ip address
    myaddr.sin_port=htons(mport);//my port
    if(bind(mfd, (struct sockaddr*)&myaddr, sizeof(myaddr))<0){//binding my socket
        perror("bind failed");
        return 0;
    }

    //setting up destination addr
    memset((char*)&youaddr,0,sizeof(youaddr));
    youaddr.sin_family = AF_INET; //protocall
    youaddr.sin_port=htons(yport);//their port
    if (inet_aton("142.58.15.124", &youaddr.sin_addr)==0) {//setting destination addr
		fprintf(stderr, "inet_aton() failed\n");
	}

    
    
    int recvlen;
    for(;;){
        //resetting msg
        FD_ZERO(&rset);
        FD_SET(0,&rset);
        FD_SET(tfd, &rset);

        //sending a message
        //This will be 2 or 3 threads i think. one to read with fgets(), one to use sendto(), and maybe one to print enter msg might not be needed tho
        // Will need to lock buff for all three threads
        select(tfd+1,&rest, NULL,NULL );
        if(FD_ISSET(0,&rset)){
            printf("enter the message\n");
            fgets(buff,1024,stdin);
            if(sendto(tfd, buff, 1024, 0, (struct sockaddr*)&youaddr, sizeof(youaddr))<0){
                perror("sendto failed");
            }
        }

        //receiving a message 
        //this will be 2 threads i think. One to use recvfrom and the other to print the msg
        //Will need to lock buff for both threads
        if(FD_ISSET(tfd,&rset)){
            printf("waiting on port %d\n", mport);
            recvlen=recvfrom(tfd, buff, 1024,0,(struct sockaddr*)&myaddr,sizeof(myaddr));
            printf("received %d bytes\n", recvlen);
            //if(recvlen>0){
                buff[recvlen]=0;
                printf("received message: \"%s\" \n", buff);
            //}
        }
    }
    //sending messages
    
    //receiving messages
    return 0;
}

