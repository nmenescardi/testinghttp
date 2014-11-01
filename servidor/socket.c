
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define P_SIZE sizeof(struct pmensaje)

struct pmensaje {
	uint16_t id_mensaje;
	uint16_t tiempo;
	uint16_t ip_target;
};


// Función que se encarga de leer un mensaje de aplicacion completo
// lee exactamente la cantidad de bytes que se pasan en el argumento total:

int leer_mensaje_delServidor ( int sd, char * buffer, int total ) {
	int bytes;
	int leido;

	leido = 0;
	bytes = 1;
	while ( (leido < total) && (bytes > 0) ) {

		bytes = recv ( sd , buffer + leido , total - leido , 0);
		leido = leido + bytes;

	}
	return ( leido );
}

int aceptarCliente(){

	int n;
	int sd;
	int sdc;
	int lon;
	char buffer[P_SIZE];
	struct sockaddr_in servidor;
	struct sockaddr_in cliente;
	struct pmensaje *mensaje;

	servidor.sin_family = AF_INET;
	servidor.sin_port = htons(4444);
	servidor.sin_addr.s_addr = INADDR_ANY;

	sd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (bind(sd, (struct sockaddr *) &servidor, sizeof(servidor)) < 0) {
		perror("Error en bind");
		exit(-1);
	}

	listen ( sd , 5 );

	while (1) {

		lon = sizeof(cliente);
		sdc = accept ( sd, (struct sockaddr *) &cliente, &lon );

		while ( ( n = leer_mensaje_delServidor ( sdc , buffer , P_SIZE ) ) > 0 ) {

			mensaje = (struct pmensaje *) buffer;

			printf("Recibí desde: %s puerto: %d el id de mensaje: %d \n", inet_ntoa(cliente.sin_addr), ntohs( cliente.sin_port), ntohs(mensaje->id_mensaje));

			if(ntohs(mensaje->id_mensaje)==1){
				mensaje->id_mensaje = htons(3);
				mensaje->tiempo = htons(22);
				printf("Se envia el tiempo a esperar: %d, y la ip del target: %d \n", ntohs(mensaje->tiempo), ntohs(mensaje->ip_target));
				send ( sdc , buffer, P_SIZE, 0 );
			}

			//Orden de ejecutar el testing.
			mensaje->id_mensaje = htons(4);
			send ( sdc , buffer, P_SIZE, 0 );
		}

		close (sdc);

	}

	close(sd);


}
