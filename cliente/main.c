#include <stdio.h>
#include "menu.c"
#include "socket.c"
/*
 * main.c
 *
 *  Created on: Oct 11, 2014
 *      Author: Grupo10
 */


int main(int argc, char *argv[])
{
//TODO ver los parametros que recibe

	char opcionIngresada[2];
	int opcionCorrecta=-1;

	while(opcionCorrecta!=1){

		imprimirMenuPrincipal(opcionIngresada);
		//printf ( "Valor ingresado %s \n",opcionIngresada );
		//validarOpcionIngresada(opcionIngresada);
		opcionCorrecta=manejarRespuesta(opcionIngresada);
	}
}
