#include <iostream> //La he tenido que poner por el problema del cin. es stdio.h de c++
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

    int client, server;
    bool isExit = false;
    int bufsize = 1024;
    char buffer[bufsize];
    const char * const socket_name = argv[1]; // Declaración del nombre del socket.

    struct sockaddr_un server_addr; //Estructura de configuracion del socket
    socklen_t size; //longitud del socket

    //Creación y configuración del socket
    client = socket(AF_LOCAL, SOCK_STREAM, 0);
    server_addr.sun_family = AF_LOCAL;
    strcpy(server_addr.sun_path, socket_name);

    //Anclado del programa con el socket
    bind(client, (struct sockaddr*)&server_addr,sizeof(server_addr));


    size = sizeof(server_addr);

    printf(" \n Esperando la conexion del cliente... \n ");

    //La cola de espera del cliente.
    listen(client, 1);

    //Acepta las conexiones.
    server = accept(client,(struct sockaddr *)&server_addr,&size);

      //Instrucciones del chat
    while (server > 0)
    {
        strcpy(buffer, "=> Server connected...\n");
        write(server, buffer, bufsize);
        printf("\n=> Enter # to end the connection\n");
        printf("\nTexto + Espacio + * Para enviar el mensaje\n\n");


      //Sistema de envio y recibo de mensajes.
      printf("Client: ");
        do {
            read(server, buffer, bufsize);
            printf("%s ", buffer);
            if (*buffer == '#') {
                *buffer = '*';
                isExit = true;
            }
        } while (*buffer != '*');

        do {
            printf("\nServer: ");
            do {
                cin >> buffer; /* Es igual que el scanf lo único que esta parte
                                  la he buscado por internet y me ha funcionado.

                                */
                //scanf("%s\n", &buffer); //Me daba un warning y no sé como solucionarlo
                write(server, buffer, bufsize);
                if (*buffer == '#') {
                    write(server, buffer, bufsize);
                    *buffer = '*';
                    isExit = true;
                }
            } while (*buffer != '*');

              printf("Client: ");
            do {
                read(server, buffer, bufsize);
                printf("%s ", buffer);
                if (*buffer == '#') {
                    *buffer == '*';
                    isExit = true;
                }
            } while (*buffer != '*');
        } while (!isExit);

        printf(" \n");

        //Cerrar el socket de conexion con el cliente.
        close(server);
        isExit = false;
        exit(1);
    }
    //Cerrar el socket de conexion con el servidor
    close(client);
    return 0;
}
