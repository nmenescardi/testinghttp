#include <stdio.h>
#include "menu.c"
#include "socket.c"

char nombre_host_target_global;

int main() {

	char opcionIngresada[2];
	int opcionCorrecta = -1;


	while (opcionCorrecta != 1) {

		imprimirMenuPrincipal(opcionIngresada);

		opcionCorrecta = manejarRespuesta(opcionIngresada);
	}

}
