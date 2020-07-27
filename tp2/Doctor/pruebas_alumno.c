#include "doctor.h"
#include "paciente.h"
#include "testing.h"
#include <stdlib.h>
#include <string.h>

/* ******************************************************************
 *                        PRUEBAS UNITARIAS
 * *****************************************************************/

void prueba_crear(void) {
	char* nombre1 = "Nick Riviera";
	char* especialidad1 = "Clínico";
	doctor_t* doctor1 = doctor_crear(nombre1, especialidad1);
	
	print_test("Prueba doctor crear doctor", doctor1);
	print_test("Prueba doctor la cantidad de pacientes atendidos es 0", doctor_atendidos(doctor1) == 0);
	
	doctor_destruir(doctor1);
}

void prueba_ver_datos(void) {
	char* nombre1 = "Nick Riviera";
	char* especialidad1 = "Clínico";
	doctor_t* doctor1 = doctor_crear(nombre1, especialidad1);
	
	print_test("Prueba doctor ver nombre retorna el nombre correcto", strcmp(doctor_ver_nombre(doctor1), nombre1) == 0);
	print_test("Prueba doctor ver especialidad retorna la especialidad correcta", strcmp(doctor_ver_especialidad(doctor1), especialidad1) == 0);
	
	doctor_destruir(doctor1);
}

void prueba_atender_paciente(void) {
	char* nombre1 = "Nick Riviera";
	char* especialidad1 = "Clínico";
	char* nombre2 = "Pedro";
	char* anio2 = "2006";
	char* nombre3 = "Juan";
	char* anio3 = "1999";
	paciente_t* paciente1 = paciente_crear(nombre2, anio2); 
	paciente_t* paciente2 = paciente_crear(nombre3, anio3);
	doctor_t* doctor1 = doctor_crear(nombre1, especialidad1);
	
	doctor_atender_paciente(doctor1, paciente1);
	doctor_atender_paciente(doctor1, paciente2);
	print_test("Prueba doctor atiende pacientes retorna la cantidad correcta de pacientes atendidos", doctor_atendidos(doctor1) == 2);
	
	doctor_destruir(doctor1);
}

/* ******************************************************************
 *                        FUNCION PRINCIPAL
 * *****************************************************************/

void pruebas_doctor_alumno() {
	prueba_crear();
	prueba_ver_datos();
	prueba_atender_paciente();
}
