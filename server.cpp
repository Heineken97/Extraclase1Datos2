//
// Created by heineken97 on 24/2/20.
//

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void error(const char *msg){
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {

    int socketON, portnumber, newsocketON, thereading;
    struct sockaddr_in server_addr{},client_addr{};
    socklen_t connectionLen;
    char buffer[256];

    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }

    socketON=socket(AF_INET,SOCK_STREAM,0); //Creando socket
    if(socketON<0){
        error("ERROR. Comprobar creacion del socket");
    }

    bzero((char*) &server_addr, sizeof(server_addr)); // Cleaning server address structure
    portnumber=atoi(argv[1]); //portnumber by input

    //Filling the structure
    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=INADDR_ANY; //current Host's IPaddress
    server_addr.sin_port=htons(portnumber);// adding & convert to Network host byte

    //Binding the socket to the current IP address, passing the file descriptor
    if(bind(socketON,(struct sockaddr*) &server_addr, sizeof(server_addr))<0) error ("ERROR. Enlazar el socket");

    //Listening incoming connections with a MAXSIZE backlog queue
    listen(socketON, 5);

    //Accepting the connection from the client
    newsocketON= accept(socketON,(struct sockaddr*) &client_addr, &connectionLen);
    if(newsocketON<0)error("ERROR. Comprobar aceptacion del nuevo socket");

    printf("Checking SERVER connection: got connection from %s port %d \n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));

    //Sending data
    send(newsocketON, "Hello Client, Sending you 36 bytes",36,0);

    //Reading data
    bzero(buffer,256);
    thereading= read(newsocketON,buffer,255);
    if(thereading<0)error("ERROR. La data no llega");

    //Checking
    printf("Heres is the Data: %s\n", buffer);

    //closing
    close(newsocketON);
    close(socketON);
    return 0;

}
