#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std; //A la hora de utilizar la librería iostream, he tenido que utilizar using namespace std,
// ya que no me compilaba sin ello 

int main(int argc, char const *argv[])
{


    int client;
    bool isExit = false;
    int bufsize = 1024;
    char buffer[bufsize];


    const char * const socket_name = argv[1];// Declaración del nombre del socket.
    struct sockaddr_un server_addr;//Estructura de configuracion del socket


    //Creación y configuración del socket
    client = socket(AF_LOCAL, SOCK_STREAM, 0);
    server_addr.sun_family = AF_LOCAL;
    strcpy(server_addr.sun_path, socket_name);

    //La conexion con el socket del servidor
    connect(client,(struct sockaddr *)&server_addr, sizeof(server_addr));
    read(client, buffer, bufsize);

    printf("\nTexto + Espacio + * Para enviar el mensaje\n\n");

    //Envio y recibo de mensajes.
    do {
        printf("Client: ");
        do {
            cin >> buffer;
            //scanf("%s\n", &buffer); //me daba un warning y no sé como solucionarlo.
            send(client, buffer, bufsize, 0);
            if (*buffer == '#') {
                send(client, buffer, bufsize, 0);
                *buffer = '*';
                isExit = true;
            }
        } while (*buffer != 42);

        printf("Server: ");
        do {
            read(client, buffer, bufsize);
            printf("%s ", buffer);
            if (*buffer == '#') {
                *buffer = '*';
                isExit = true;
            }

        } while (*buffer != 42);

        printf(" \n");

    } while (!isExit);



    printf("Conexion finalizada \n\n");

    close(client);
    return 0;
}
