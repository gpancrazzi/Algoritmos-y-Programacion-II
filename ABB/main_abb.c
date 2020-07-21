#include "testing.h"
#include <stdlib.h>
#include <stdio.h>

void pruebas_abb_alumno(void);

void pruebas_abb_obtener_rango(void);

/* ******************************************************************
 *                        PROGRAMA PRINCIPAL
 * *****************************************************************/

int main(int argc, char *argv[])
{
    printf("~~~ PRUEBAS ALUMNO ~~~\n");
    pruebas_abb_alumno();
    pruebas_abb_obtener_rango();

    return failure_count() > 0;
}
