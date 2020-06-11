#include "complejo.h"
#include "testing.h"
#include <math.h>

#define PI 3.1415926535

void pruebas_numero_complejo(void) {
	complejo_t* complejo1 = complejo_crear(3, 0);
	
	print_test("Prueba numero complejo se crea el numero correctamente", complejo1);
	print_test("Prueba numero complejo obtener la parte real retorna el valor correcto", complejo_obtener_real(complejo1) == 3);
	print_test("Prueba numero complejo obtener la parte imaginaria retorna el valor correcto", complejo_obtener_imaginaria(complejo1) == 0);
	print_test("Prueba numero complejo obtener el modulo retorna el valor correcto", complejo_obtener_modulo(complejo1) == 3);
	print_test("Prueba numero complejo obtener el angulo retorna el valor correcto", complejo_obtener_angulo(complejo1) == 0);
	complejo_t* complejo2 = complejo_crear(0, 4);
	print_test("Prueba numero complejo se crea el numero correctamente", complejo2);
	print_test("Prueba numero complejo obtener la parte real retorna el valor correcto", complejo_obtener_real(complejo2) == 0);
	print_test("Prueba numero complejo obtener la parte imaginaria retorna el valor correcto", complejo_obtener_imaginaria(complejo2) == 4);
	print_test("Prueba numero complejo obtener el modulo retorna el valor correcto", complejo_obtener_modulo(complejo2) == 4);
	print_test("Prueba numero complejo obtener el angulo retorna el valor correcto", complejo_obtener_angulo(complejo2) == (PI / 2));
	complejo_multiplicar(complejo1, complejo2);
	print_test("Prueba numero complejo multiplicar retorna el numero real correcto", complejo_obtener_real(complejo1) == 0);
	print_test("Prueba numero complejo multiplicar retorna el numero imaginario correcto", complejo_obtener_imaginaria(complejo1) == 12);
	print_test("Prueba numero complejo multiplicar retorna el numero real correcto", complejo_obtener_real(complejo2) == 0);
	print_test("Prueba numero complejo multiplicar retorna el numero imaginario correcto", complejo_obtener_imaginaria(complejo2) == 4);
	print_test("Prueba numero complejo obtener el modulo retorna el valor correcto", complejo_obtener_modulo(complejo1) == 12);
	print_test("Prueba numero complejo obtener el angulo retorna el valor correcto", complejo_obtener_angulo(complejo1) == (PI / 2));
	complejo_t* complejo3 = complejo_crear(3, 0);
	complejo_sumar(complejo3, complejo2);
	print_test("Prueba numero complejo sumar retorna el numero real correcto", complejo_obtener_real(complejo3) == 3);
	print_test("Prueba numero complejo sumar retorna el numero imaginario correcto", complejo_obtener_imaginaria(complejo3) == 4);
	print_test("Prueba numero complejo sumar retorna el numero real correcto", complejo_obtener_real(complejo2) == 0);
	print_test("Prueba numero complejo sumar retorna el numero imaginario correcto", complejo_obtener_imaginaria(complejo2) == 4);
	print_test("Prueba numero complejo obtener el modulo retorna el valor correcto", complejo_obtener_modulo(complejo3) == 5);
	double angulo = complejo_obtener_imaginaria(complejo3) / complejo_obtener_real(complejo3);
	print_test("Prueba numero complejo obtener el angulo retorna el valor correcto", complejo_obtener_angulo(complejo3) == atan(angulo));
	complejo_destruir(complejo1);
	complejo_destruir(complejo2);
	complejo_destruir(complejo3);
}
