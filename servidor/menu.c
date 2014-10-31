#include <stdio.h>
#include "socket.c"
/*
 * menu.c
 *
 *  Created on: Oct 12, 2014
 *      Author: nicolas
 */



int imprimirMenuPrincipalServidor(char *opcionIngresada){
    /*
     * Imprime El menu principal.
     * */

	//
	printf ( "1 - . Para Conectarse con el servidor, presione 1 (UNO) \n" );

	fgets ( opcionIngresada , 2 , stdin );

	//printf ( "Valor ingresado %s \n",opcionIngresada );

	return 1;
}


int validarOpcionIngresadaServidor(char *opcionIngresada){
	/*
	char valoresPermitidos[2]={"1"};

	char *pContenido;
	pContenido=strchr(valoresPermitidos,opcionIngresada[1]);

	if(!pContenido){
		printf ( "Valor ingresado NO permitido \n");
	}else{
		printf ( " OK \n");
	}*/

	return 1;
}


int manejarRespuestaServidor(char *opcionIngresada){
	char opcion1[] ="1";
	int resultado = 1;

	if(strcmp (opcionIngresada,opcion1) == 0){
		aceptarCliente();
	}else{
		printf ( " Opcion invalida. \n");
		resultado = -1;
	}

	return resultado;
}




