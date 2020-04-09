/*
 ============================================================================
 Name        : socket.c
 Author      : Programadores en fuga
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	struct sockaddr_in direccionServidor;
	direccionServidor.sin_family=AF_INET;
	direccionServidor.sin_addr.s_addr=INADDR_ANY;
	direccionServidor.sin_port=htons(8987);

	int servidor=socket(AF_INET,SOCK_STREAM,0);

	int activado=1;
	setsockopt(servidor,SOL_SOCKET,SO_REUSEADDR,&activado,sizeof(activado));

	if(bind(servidor, (void*) &direccionServidor, sizeof(direccionServidor))!=0){
		perror("Falló el bind");
		return 1;
	}
	printf("Estoy escuchando\n");
	listen(servidor,100);


	struct sockaddr_in direccionCliente;
	unsigned int tamanioDireccion=sizeof(direccionCliente);
	int cliente = accept(servidor, (void*) &direccionCliente, &tamanioDireccion);

	printf("Se ha recibido una conexión en %d.\n", cliente);
	send(cliente, "Hola!",6,0);


	char*buffer=malloc(100);

	while(1){
		int bytesRecibidos = recv(cliente,buffer, 99,0);

		if(bytesRecibidos<=0){
			perror("Error");
			return 1;
		}

		buffer[bytesRecibidos]='\0';
		printf("Me llegaron %d bytes con %s\n", bytesRecibidos,buffer);
	}

	free(buffer);

	return 0;
}
