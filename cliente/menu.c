#include <stdio.h>


int imprimirMenuPrincipal(char *opcionIngresada){
    /*
     * Imprime El menu principal.
     * */

	printf ( "\n*********************************************************\n" );
	printf ( " Testing Servicio HTTP (Cliente). Ver 0.1 . \n" );
	printf ( "*********************************************************\n\n" );
	printf ( " Menu Principal: \n\n" );
	printf ( " 1 - . Para Conectarse con el servidor, presione 1 (UNO)\n\n" );
	printf ( "*********************************************************\n\n" );
	fgets ( opcionIngresada , 2 , stdin );

	//printf ( "Valor ingresado %s \n",opcionIngresada );

	return 1;
}


int validarOpcionIngresada(char *opcionIngresada){
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


int manejarRespuesta(char *opcionIngresada){
	char opcion1[] ="1";
	int resultado = 1;

	if(strcmp (opcionIngresada,opcion1) == 0){
		conectarseAlServidor();
	}else{
		printf ( "\n Opcion invalida. \n");
		resultado = -1;
	}

	return resultado;
}




