#include <stdio.h>
#include "menu.c"

	//extern char *ip_target_global;

int main(int argc, char *argv[])
{
//TODO ver los parametros que recibe

	char opcionIngresada[2];
	int opcionCorrecta=-1;

	//ip_target_global=argv [1];

	while(opcionCorrecta!=1){

		imprimirMenuPrincipalServidor(opcionIngresada);
		//printf ( "Valor ingresado %s \n",opcionIngresada );
		//validarOpcionIngresada(opcionIngresada);
		opcionCorrecta=manejarRespuestaServidor(opcionIngresada);
	}
}
