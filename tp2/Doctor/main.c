#include "testing.h"
#include <stdlib.h>
#include <stdio.h>

void pruebas_doctor_alumno(void);

/* ******************************************************************
 *                        PROGRAMA PRINCIPAL
 * *****************************************************************/

int main(int argc, char *argv[])
{
    printf("~~~ PRUEBAS ALUMNO ~~~\n");
    pruebas_doctor_alumno();

    return failure_count() > 0;
}
