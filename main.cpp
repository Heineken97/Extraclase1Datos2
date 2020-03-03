#include "mainwindow.h"
#include <QApplication>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error( const char *msg){
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    int socketON,portnumber, thereading;
    struct sockaddr_in server_addr;
    struct hostent *server;
    char buffer[256];

    if(argc<3){
        fprintf(stderr, "Usando puerto: %s \n", argv[0]);
        exit(0);
    }

    portnumber=atoi(argv[2]);

    // creando socket
    socketON= socket(AF_INET,SOCK_STREAM,0);
    if(socketON<0) error("ERROR. Comprobar creacion del socket");

    //Obtener hostname
    server= gethostbyname(argv[1]);
    if(server==NULL){
        fprintf(stderr, "ERROR, No se encuentra el host\n");
        exit(0);
    }

    bzero((char*) &server_addr, sizeof(server_addr));

    //Filling the structure
    server_addr.sin_family=AF_INET;
    bcopy((char*)server->h_addr,(char*) &server_addr.sin_addr.s_addr,server->h_length);
    server_addr.sin_port= htons(portnumber);

    // Making the connection
    if(connect(socketON, (struct sockaddr *)&server_addr,sizeof(server_addr))<0)error("ERROR.Revisar Connect() del cliente");

    printf("Insertar mensaje: ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);

    //writing data
    thereading=write(socketON,buffer,strlen(buffer));
    if(thereading<0) error("ERROR. Escritura en el socket");

    bzero(buffer,256);

    //reading data
    thereading=read(socketON,buffer,256);
    if(thereading<0) error("ERROR. Lectura del socket");

    printf( "%s\nl", buffer);

    //Closing
    close(socketON);
    MainWindow w;
    w.show();


    return a.exec();
}
