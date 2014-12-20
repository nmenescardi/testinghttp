#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/shm.h>
//#include <iostream.h>
#include <unistd.h>
#include <signal.h>

#define P_SIZE sizeof(struct pmensaje)

struct pmensaje {
	uint16_t id_mensaje;
	double tiempo;
	char nombre_host_target;
	int cantidadDePeticiones;
};


//void procesar_estadisticas(pmensaje *mensaje){
void procesar_estadisticas(){
	printf("algo");
}



// Función que se encarga de leer un mensaje de aplicacion completo
// lee exactamente la cantidad de bytes que se pasan en el argumento total:

int leer_mensaje_delServidor(int sd, char * buffer, int total) {
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

int aceptarCliente() {

	int n;
	int sd;
	int sdc;
	int pid;
	int lon;
	//int *cantidadDeClientesConectados;
	int maxClientesConectados = 2;
	char buffer[P_SIZE];
	struct sockaddr_in servidor;
	struct sockaddr_in cliente;
	struct pmensaje *mensaje;
	extern char *nombre_host_target;



	// SHARED MEMORY   para cantidadDeClientesConectados***************
	key_t Clave;
	int Id_Memoria;
	int *Memoria = NULL;
	Clave = ftok("/bin/ls", 33);
	if (Clave == -1) {
		//cout << "No consigo clave para memoria compartida" << endl;
		exit(0);
	}
	Id_Memoria = shmget(Clave, sizeof(int) * 100, 0777 | IPC_CREAT);
	if (Id_Memoria == -1) {
		//cout << "No consigo Id para memoria compartida" << endl;
		exit(0);
	}
	int *cantidadDeClientesConectados =
			(int *) shmat(Id_Memoria, (char *) 0, 0);
	*cantidadDeClientesConectados = 0;
	if (cantidadDeClientesConectados == NULL) {
		//cout << "No consigo memoria compartida" << endl;
		exit(0);
	}
	// Fin shared memory ***********

	// SHARED MEMORY   para tiempoPromedioTotal***************
		key_t Clave2;
		int Id_Memoria2;
		int *Memoria2 = NULL;
		Clave2 = ftok("/bin/ls", 33);
		if (Clave2 == -1) {
			//cout << "No consigo clave para memoria compartida" << endl;
			exit(0);
		}
		Id_Memoria2 = shmget(Clave2, sizeof(int) * 100, 0777 | IPC_CREAT);
		if (Id_Memoria2 == -1) {
			//cout << "No consigo Id para memoria compartida" << endl;
			exit(0);
		}
		double *tiempoPromedioTotal =
				(double *) shmat(Id_Memoria2, (char *) 0, 0);
		*tiempoPromedioTotal = 0;
		if (tiempoPromedioTotal == NULL) {
			//cout << "No consigo memoria compartida" << endl;
			exit(0);
		}
		// Fin shared memory ***********






	servidor.sin_family = AF_INET;
	servidor.sin_port = htons(4444);
	servidor.sin_addr.s_addr = INADDR_ANY;

	sd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (bind(sd, (struct sockaddr *) &servidor, sizeof(servidor)) < 0) {
		perror("Error en bind");
		exit(-1);
	}

	listen(sd, 5);

	while (1) {

		lon = sizeof(cliente);
		sdc = accept(sd, (struct sockaddr *) &cliente, &lon);

		pid = fork();

		if (pid == 0) {
			*cantidadDeClientesConectados = *cantidadDeClientesConectados + 1;
			printf("La cantidad de clientes conectados es: %i \n",
					*cantidadDeClientesConectados);

			//close(sd);

			leer_mensaje_delServidor(sdc, buffer, P_SIZE );

			mensaje = (struct pmensaje *) buffer;

			printf("Recibí desde: %s puerto: %d el id de mensaje: %d \n",
					inet_ntoa(cliente.sin_addr), ntohs(cliente.sin_port),
					ntohs(mensaje->id_mensaje));

			if (ntohs(mensaje->id_mensaje) == 1) {
				mensaje->id_mensaje = htons(3);
				mensaje->tiempo = htons(22);
				mensaje->nombre_host_target = *nombre_host_target;
				printf(
						"Se envia el tiempo a esperar: %d, y el nombre del host target: %d \n",
						ntohs(mensaje->tiempo), mensaje->nombre_host_target);
				send(sdc, buffer, P_SIZE, 0);
			}

			//Ciclo termina cuando se reciben las estadisticas
			while(1){

				if (*cantidadDeClientesConectados >= maxClientesConectados) {
					//Orden de ejecutar el testing.
					mensaje->id_mensaje = htons(4);

					//Cantidad de peticiones
					mensaje->cantidadDePeticiones = htons(17);
					send(sdc, buffer, P_SIZE, 0);

					//Espero hasta recibir las estadisticas:
					while (ntohs(mensaje->id_mensaje) != 2) {
						n=leer_mensaje_delServidor(sdc, buffer, P_SIZE );
						//printf("%d",ntohs(mensaje->id_mensaje));

					}
					printf("Id de mensaje: %d \n",	ntohs(mensaje->id_mensaje));
					printf("\n La diferencia de tiempo fue: %d \n", ntohs(mensaje->tiempo));

					*tiempoPromedioTotal = *tiempoPromedioTotal + ntohs(mensaje->tiempo);

					printf("\n El tiempo promedio total es: %f \n", *tiempoPromedioTotal);

					//Se recibieron estadisticas
					//procesar_estadisticas();
					//procesar_estadisticas(mensaje);

					//Ya se recibieron estadisticas, Termina servidor
					//*cantidadDeClientesConectados=-1;

					mensaje->id_mensaje = htons(5);
					send(sdc, buffer, P_SIZE, 0);

					printf("Termina server");

				}
			}

			//close(sdc);
			exit(0);
		} else {
			//close(sdc);
			printf("Se creo el proceso %d\n", pid);

		}

	}

	close(sd);



}


