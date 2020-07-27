#include "paciente.h"
#include "testing.h"
#include <stdlib.h>
#include <string.h>

/* ******************************************************************
 *                        PRUEBAS UNITARIAS
 * *****************************************************************/

void prueba_crear(void) {
	char* nombre1 = "Pedro";
	char* anio1 = "2006";
	paciente_t* paciente1 = paciente_crear(nombre1, anio1);
	
	print_test("Prueba paciente crear paciente", paciente1);
	
	paciente_destruir(paciente1);
}

void prueba_ver_datos(void) {
	char* nombre1 = "Pedro";
	char* anio1 = "2006";
	paciente_t* paciente1 = paciente_crear(nombre1, anio1);
	
	print_test("Prueba paciente ver nombre retorna el nombre correcto", strcmp(paciente_ver_nombre(paciente1), nombre1) == 0);
	print_test("Prueba paciente ver anio retorna el anio correcto", strcmp(paciente_ver_anio(paciente1), anio1) == 0);
	
	paciente_destruir(paciente1);
}

/* ******************************************************************
 *                        FUNCION PRINCIPAL
 * *****************************************************************/

void pruebas_paciente_alumno() {
	prueba_crear();
	prueba_ver_datos();
}
