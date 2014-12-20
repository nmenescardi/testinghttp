#include <stdio.h>
#include "menu.c"

	 char *nombre_host_target;
	 char *cant_max_clientes_conectados;
	 char *cant_peticiones_http_por_cliente;

int main(int argc, char *argv[])
{
//TODO ver los parametros que recibe

	char opcionIngresada[2];
	int opcionCorrecta=-1;

	nombre_host_target=argv [1];
	cant_max_clientes_conectados=argv [2];
	cant_peticiones_http_por_cliente=argv [3];

	printf("El nombre del host target es: %s \n\n",nombre_host_target);
	printf("La cantidad maxima de clientes conectados para empezar el testing es: %s \n\n",cant_max_clientes_conectados);
	printf("La cantidad de peticiones HTTP que realizara cada cliente es: %s \n\n",cant_peticiones_http_por_cliente);

	while(opcionCorrecta!=1){

		imprimirMenuPrincipalServidor(opcionIngresada);
		//printf ( "Valor ingresado %s \n",opcionIngresada );
		//validarOpcionIngresada(opcionIngresada);
		opcionCorrecta=manejarRespuestaServidor(opcionIngresada);
	}
}
