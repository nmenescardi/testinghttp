#include <stdio.h>
/*
 * menu.c
 *
 *  Created on: Oct 11, 2014
 *      Author: nicolas
 */



void imprimirMenu(){

	pantalla_principal();

}

int pantalla_principal ()
{
    int resul;
    char elegido[4];

    printf ( "Usuario");
    printf ( "----------------Menu Principal--------------\n" );
    printf ( "Por favor, ingrese el número de la opción deseada y luego presione la tecla ENTER:\n\n" );
    printf ( "\t3. Para ELIMINAR TODOS sus links, presione 3 (TRES) \n" );
    printf ( "\t4. Para AGREGAR UN NUEVO LINK, presione 4 (CUATRO) \n" );
    printf ( "\t5. Para MODIFICAR UN LINK, presion 5 (CINCO) \n" );
    printf ( "\t6. Para ELIMINAR UN LINK, presione 6 (SEIS) \n" );
    printf ( "\t7. Para OBTENER TODOS SUS LINKS, presione 7 (SIETE) \n" );
    printf ( "\t8. Para hacer un LOGOUT, presione 8 (OCHO) \n" );
    printf ( "\t9. Si desea hacer SALIR, presione 9 (NUEVE) \n\n" );
    printf ( "Opción: " );
    fgets ( elegido , 3 , stdin );
    elegido[strlen ( elegido ) - 1] = '\0';
    resul = atoi ( elegido );
    return (resul);
}

/*
static void show_help(char **argv)
{
    printf
    (
        "Streaming Server v 0.1\n\n"
        "  -h            Muestra esta ayuda.\n"
        "  -f <archivo>  Especifica el archivo a servir (Path absoluto).\n"
        "  -p <puerto>   Especifica el puerto para escuchar.\n"
        "  -d            Iniciar en modo DAEMON (por defecto es en modo consola).\n\n"
        "Uso:\n"
        "   %s -f streaming.wav\n",
        argv[0]
    );

    exit(0);
}

*/
