#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <inttypes.h>
#include <time.h>
#include "http.c"

#define P_SIZE sizeof(struct pmensaje)

struct pmensaje {
	uint16_t id_mensaje;
	uint16_t tiempo;
	uint16_t ip_target;
};

char *time_stamp() {

	char *timestamp = (char *) malloc(sizeof(char) * 16);
	time_t ltime;
	ltime = time(NULL);
	struct tm *tm;
	tm = localtime(&ltime);

	sprintf(timestamp, "%02d%02d%02d", tm->tm_hour, tm->tm_min, tm->tm_sec);
	return timestamp;
}

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

	printf("\n Conectandose con el servidor \n");

	//Se setea el id del primer mensaje, solo para conectarse con el servidor.
	mensaje->id_mensaje=htons(1);
	send(sd, buffer, P_SIZE, 0);

	n=leer_mensaje(sd, buffer, P_SIZE);
	if(ntohs(mensaje->id_mensaje)==3){
		//printf("El tiempo a esperar es: %d\n", ntohs(mensaje->tiempo));
		printf("\n Conexion con el servidor realizada exitosamente \n");

		//Guardar tiempo en alguna variable global.
		tiempoDeEspera=ntohs(mensaje->tiempo);

		//Guardar ip target en otra variable global.
		ipTarget=ntohs(mensaje->ip_target);
	}


	//Sigue esperando que el server envie la orden de atacar
	while(ntohs(mensaje->id_mensaje)!=4){
		n=leer_mensaje(sd, buffer, P_SIZE);
	}


	printf("\n Se recibio mensaje de comienzo de testing  \n");
	enviarSolicitudHTTP(timpoRespuestaSolicitudHttp);

	//enviarle al server el resultado (tiempo de respuesta de la solicitud)
	while(ntohs(mensaje->id_mensaje) != 5){

		mensaje->id_mensaje = htons(2);
		mensaje->tiempo = htons(timpoRespuestaSolicitudHttp);
		send(sd, buffer, P_SIZE, 0);


		n=leer_mensaje(sd, buffer, P_SIZE);
	}

	printf("\n Se recibio mensaje de estadisticas completas \n");
	printf("\n Fin de testing. \n");

	close(sd);
	return 1;
}


//funcion para enviar solicitud http get (puede ser enviada de cualquier hilo)
int enviarSolicitudHTTP(uint16_t* timpoRespuestaSolicitudHttp){

	time_t t = time(0);
	printf(" Timestamp 1: %s\n",time_stamp());

	executeTestingHttp();

	time_t t2 = time(0);

	double dataTimeDiff = difftime(t2,t) * 1000;
	printf("\n La diferencia de tiempo es: %f \n", dataTimeDiff);
	printf(" Timestamp 2: %s\n",time_stamp());

	double i = (double) * time_stamp();
	printf(" Timestamp 3 int: %f\n",i);

	timpoRespuestaSolicitudHttp=555;
	printf("\n Se realizo testing satisfactoriamente. El tiempo de respuesta del target es: %hd \n", timpoRespuestaSolicitudHttp);
	return 1;
}



