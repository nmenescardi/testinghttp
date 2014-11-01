#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <inttypes.h>

#define P_SIZE sizeof(struct pmensaje)

struct pmensaje {
	uint16_t id_mensaje;
	uint16_t tiempo;
	uint16_t ip_target;
};

int leer_mensaje(int sd, char* buffer, int total) {
	int bytes;
	int leido;

	leido = 0;
	bytes = 1;

	while ((leido < total) && (bytes > 0)) {
		bytes = recv(sd, buffer + leido, total - leido, 0);
		leido = leido + bytes;
	}
	return (leido);
}

int conectarseAlServidor() {
	int n;
	int sd;
	int lon;
	uint16_t tiempoDeEspera;
	uint16_t ipTarget;
	uint16_t timpoRespuestaSolicitudHttp;

	char teclado[512];
	char buffer[P_SIZE];
	struct sockaddr_in servidor;
	struct sockaddr_in cliente;
	struct hostent *h;
	struct pmensaje *mensaje;

	sd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	servidor.sin_family = AF_INET;
	servidor.sin_port = htons(4444);
	servidor.sin_addr.s_addr = inet_addr("127.0.0.1");

	lon = sizeof(servidor);

	if (connect(sd, (struct sockaddr*) &servidor, lon) < 0) {
		perror("Error en connect");
		exit(-1);
	}

	mensaje = (struct pmensaje*) buffer;

	printf(" Conectandose con el servidor \n");

	//Se setea el id del primer mensaje, solo para conectarse con el servidor.
	mensaje->id_mensaje=htons(1);
	send(sd, buffer, P_SIZE, 0);

	n=leer_mensaje(sd, buffer, P_SIZE);
	if(ntohs(mensaje->id_mensaje)==3){
		printf("El tiempo a esperar es: %d\n", ntohs(mensaje->tiempo));

		//Guardar tiempo en alguna variable global.
		tiempoDeEspera=ntohs(mensaje->tiempo);

		//Guardar ip target en otra variable global.
		ipTarget=ntohs(mensaje->ip_target);
	}


	//hilo principal sigue esperando que el server envie la orden de atacar
	while(ntohs(mensaje->id_mensaje)!=4){
		n=leer_mensaje(sd, buffer, P_SIZE);
		printf("Mensaje de cominzo de testing recibido\n");
	}

	//TODO abrir hilo para decrementar timer
	//TODO si server envie antes de que se termine el timer, cortar el hilo secundario

	enviarSolicitudHTTP(timpoRespuestaSolicitudHttp);

	//enviarle al server el resultado (tiempo de respuesta de la solicitud)
	mensaje->id_mensaje = htons(2);
	mensaje->tiempo = htons(timpoRespuestaSolicitudHttp);

	close(sd);
	return 1;
}


//funcion para enviar solicitud http get (puede ser enviada de cualquier hilo)
int enviarSolicitudHTTP(uint16_t* timpoRespuestaSolicitudHttp){

	timpoRespuestaSolicitudHttp=555;
	printf("Se realizo testing satisfactoriamente. El tiempo de respuesta del target es: %hd \n", timpoRespuestaSolicitudHttp);
	return 1;
}
