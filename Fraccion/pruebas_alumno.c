#include "fraccion.h"
#include "testing.h"
#include <stdlib.h>
#include <string.h>

void prueba_fraccion_crear(void) {
	fraccion_t* fraccion1 = fraccion_crear(5, 3);
	fraccion_t* fraccion2 = fraccion_crear(-7, 4);
	fraccion_t* fraccion3 = fraccion_crear(15, -7);
	fraccion_t* fraccion4 = fraccion_crear(-27, -11);
	fraccion_t* fraccion5 = fraccion_crear(15, 10);
	fraccion_t* fraccion6 = fraccion_crear(-27, 6);
	fraccion_t* fraccion7 = fraccion_crear(14, -8);
	fraccion_t* fraccion8 = fraccion_crear(-28, -6);
	fraccion_t* fraccion9 = fraccion_crear(3, 5);
	fraccion_t* fraccion10 = fraccion_crear(-4, 7);
	fraccion_t* fraccion11 = fraccion_crear(7, -15);
	fraccion_t* fraccion12 = fraccion_crear(-11, -27);
	fraccion_t* fraccion13 = fraccion_crear(10, 15);
	fraccion_t* fraccion14 = fraccion_crear(6, -27);
	fraccion_t* fraccion15 = fraccion_crear(-8, 14);
	fraccion_t* fraccion16 = fraccion_crear(-6, -28);
	fraccion_t* fraccion17 = fraccion_crear(0, 12);
	fraccion_t* fraccion18 = fraccion_crear(15, 15);
	fraccion_t* fraccion19 = fraccion_crear(-1, 1);
	fraccion_t* fraccion20 = fraccion_crear(19, -19);
	fraccion_t* fraccion21 = fraccion_crear(-199, -199);
	fraccion_t* fraccion22 = fraccion_crear(10007, 1);
	fraccion_t* fraccion23 = fraccion_crear(-28, 14);
	fraccion_t* fraccion24 = fraccion_crear(66, -6);
	fraccion_t* fraccion25 = fraccion_crear(-20000, -10);
	fraccion_t* fraccion26 = fraccion_crear(-14, 28);
	fraccion_t* fraccion27 = fraccion_crear(6, -66);
	fraccion_t* fraccion28 = fraccion_crear(-10, -20000);
	
	print_test("Prueba crear fraccion con denominador 0 retorna NULL", fraccion_crear(3, 0) == NULL);
	
	print_test("Prueba crear fraccion se crea correctamente (numerador mayor ambos parametros positivos la fraccion se mantiene)", fraccion1 != NULL);
	print_test("Prueba obtener la parte entera de la fraccion retorna el valor correcto", fraccion_parte_entera(fraccion1) == 1);
	char* representacion1 = fraccion_representacion(fraccion1);
	print_test("Prueba obtener representacion retorna la cadena correcta", strcmp(representacion1, "5/3") == 0);
	fraccion_destruir(fraccion1);
	free(representacion1);
	
	print_test("Prueba crear fraccion se crea correctamente (numerador negativo, mayor en modulo, la fraccion se mantiene)", fraccion2 != NULL);
	print_test("Prueba obtener la parte entera de la fraccion retorna el valor correcto", fraccion_parte_entera(fraccion2) == -1);
	char* representacion2 = fraccion_representacion(fraccion2);
	print_test("Prueba obtener representacion retorna la cadena correcta", strcmp(representacion2, "-7/4") == 0);
	fraccion_destruir(fraccion2);
	free(representacion2);
	
	print_test("Prueba crear fraccion se crea correctamente (numerador mayor y denominador negativo la fraccion se mantiene)", fraccion3 != NULL);
	print_test("Prueba obtener la parte entera de la fraccion retorna el valor correcto", fraccion_parte_entera(fraccion3) == -2);
	char* representacion3 = fraccion_representacion(fraccion3);
	print_test("Prueba obtener representacion retorna la cadena correcta", strcmp(representacion3, "-15/7") == 0);
	fraccion_destruir(fraccion3);
	free(representacion3);
	
	print_test("Prueba crear fraccion se crea correctamente (numerador mayor en modulo ambos parametros negativos la fraccion se mantiene)", fraccion4 != NULL);
	print_test("Prueba obtener la parte entera de la fraccion retorna el valor correcto", fraccion_parte_entera(fraccion4) == 2);
	char* representacion4 = fraccion_representacion(fraccion4);
	print_test("Prueba obtener representacion retorna la cadena correcta", strcmp(representacion4, "27/11") == 0);
	fraccion_destruir(fraccion4);
	free(representacion4);
	
	print_test("Prueba crear fraccion se crea correctamente (numerador mayor ambos parametros positivos la fraccion se simplifica)", fraccion5 != NULL);
	print_test("Prueba obtener la parte entera de la fraccion retorna el valor correcto", fraccion_parte_entera(fraccion5) == 1);
	char* representacion5 = fraccion_representacion(fraccion5);
	print_test("Prueba obtener representacion retorna la cadena correcta", strcmp(representacion5, "3/2") == 0);
	fraccion_destruir(fraccion5);
	free(representacion5);
	
	print_test("Prueba crear fraccion se crea correctamente (numerador negativo, mayor en modulo, la fraccion se simplifica)", fraccion6 != NULL);
	print_test("Prueba obtener la parte entera de la fraccion retorna el valor correcto", fraccion_parte_entera(fraccion6) == -4);
	char* representacion6 = fraccion_representacion(fraccion6);
	print_test("Prueba obtener representacion retorna la cadena correcta", strcmp(representacion6, "-9/2") == 0);
	fraccion_destruir(fraccion6);
	free(representacion6);
	
	print_test("Prueba crear fraccion se crea correctamente (numerador mayor y denominador negativo, la fraccion se simplifica)", fraccion7 != NULL);
	print_test("Prueba obtener la parte entera de la fraccion retorna el valor correcto", fraccion_parte_entera(fraccion7) == -1);
	char* representacion7 = fraccion_representacion(fraccion7);
	print_test("Prueba obtener representacion retorna la cadena correcta", strcmp(representacion7, "-7/4") == 0);
	fraccion_destruir(fraccion7);
	free(representacion7);
	
	print_test("Prueba crear fraccion se crea correctamente (numerador mayor y ambos numeros negativos, la fraccion se simplifica)", fraccion8 != NULL);
	print_test("Prueba obtener la parte entera de la fraccion retorna el valor correcto", fraccion_parte_entera(fraccion8) == 4);
	char* representacion8 = fraccion_representacion(fraccion8);
	print_test("Prueba obtener representacion retorna la cadena correcta", strcmp(representacion8, "14/3") == 0);
	fraccion_destruir(fraccion8);
	free(representacion8);
	
	print_test("Prueba crear fraccion se crea correctamente (denominador mayor y ambos numeros positivos, la fraccion se mantiene)", fraccion9 != NULL);
	print_test("Prueba obtener la parte entera de la fraccion retorna el valor correcto", fraccion_parte_entera(fraccion9) == 0);
	char* representacion9 = fraccion_representacion(fraccion9);
	print_test("Prueba obtener representacion retorna la cadena correcta", strcmp(representacion9, "3/5") == 0);
	fraccion_destruir(fraccion9);
	free(representacion9);
	
	print_test("Prueba crear fraccion se crea correctamente (numerador negativo, menor en modulo, la fraccion se mantiene)", fraccion10 != NULL);
	print_test("Prueba obtener la parte entera de la fraccion retorna el valor correcto", fraccion_parte_entera(fraccion10) == 0);
	char* representacion10 = fraccion_representacion(fraccion10);
	print_test("Prueba obtener representacion retorna la cadena correcta", strcmp(representacion10, "-4/7") == 0);
	fraccion_destruir(fraccion10);
	free(representacion10);
	
	print_test("Prueba crear fraccion se crea correctamente (denominador negativo, mayor en modulo, la fraccion se mantiene)", fraccion11 != NULL);
	print_test("Prueba obtener la parte entera de la fraccion retorna el valor correcto", fraccion_parte_entera(fraccion11) == 0);
	char* representacion11 = fraccion_representacion(fraccion11);
	print_test("Prueba obtener representacion retorna la cadena correcta", strcmp(representacion11, "-7/15") == 0);
	fraccion_destruir(fraccion11);
	free(representacion11);
	
	print_test("Prueba crear fraccion se crea correctamente (ambos numeros negativos, la fraccion se mantiene)", fraccion12 != NULL);
	print_test("Prueba obtener la parte entera de la fraccion retorna el valor correcto", fraccion_parte_entera(fraccion12) == 0);
	char* representacion12 = fraccion_representacion(fraccion12);
	print_test("Prueba obtener representacion retorna la cadena correcta", strcmp(representacion12, "11/27") == 0);
	fraccion_destruir(fraccion12);
	free(representacion12);
	
	print_test("Prueba crear fraccion se crea correctamente (denominador mayor con ambos numeros positivos, la fraccion se simplifica)", fraccion13 != NULL);
	print_test("Prueba obtener la parte entera de la fraccion retorna el valor correcto", fraccion_parte_entera(fraccion13) == 0);
	char* representacion13 = fraccion_representacion(fraccion13);
	print_test("Prueba obtener representacion retorna la cadena correcta", strcmp(representacion13, "2/3") == 0);
	fraccion_destruir(fraccion13);
	free(representacion13);
	
	print_test("Prueba crear fraccion se crea correctamente (denominador negativo, mayor en modulo, la fraccion se simplifica)", fraccion14 != NULL);
	print_test("Prueba obtener la parte entera de la fraccion retorna el valor correcto", fraccion_parte_entera(fraccion14) == 0);
	char* representacion14 = fraccion_representacion(fraccion14);
	print_test("Prueba obtener representacion retorna la cadena correcta", strcmp(representacion14, "-2/9") == 0);
	fraccion_destruir(fraccion14);
	free(representacion14);
	
	print_test("Prueba crear fraccion se crea correctamente (numerador negativo, menor en modulo, la fraccion se simplifica)", fraccion15 != NULL);
	print_test("Prueba obtener la parte entera de la fraccion retorna el valor correcto", fraccion_parte_entera(fraccion15) == 0);
	char* representacion15 = fraccion_representacion(fraccion15);
	print_test("Prueba obtener representacion retorna la cadena correcta", strcmp(representacion15, "-4/7") == 0);
	fraccion_destruir(fraccion15);
	free(representacion15);
	
	print_test("Prueba crear fraccion se crea correctamente (ambos numeros negativos, denominador mayor en modulo, la fraccion se simplifica)", fraccion16 != NULL);
	print_test("Prueba obtener la parte entera de la fraccion retorna el valor correcto", fraccion_parte_entera(fraccion16) == 0);
	char* representacion16 = fraccion_representacion(fraccion16);
	print_test("Prueba obtener representacion retorna la cadena correcta", strcmp(representacion16, "3/14") == 0);
	fraccion_destruir(fraccion16);
	free(representacion16);
	
	print_test("Prueba crear fraccion se crea correctamente (numerador 0)", fraccion17 != NULL);
	print_test("Prueba obtener la parte entera de la fraccion retorna el valor correcto", fraccion_parte_entera(fraccion17) == 0);
	char* representacion17 = fraccion_representacion(fraccion17);
	print_test("Prueba obtener representacion retorna la cadena correcta", strcmp(representacion17, "0") == 0);
	fraccion_destruir(fraccion17);
	free(representacion17);
	
	print_test("Prueba crear fraccion se crea correctamente (ambos numeros positivos iguales)", fraccion18 != NULL);
	print_test("Prueba obtener la parte entera de la fraccion retorna el valor correcto", fraccion_parte_entera(fraccion18) == 1);
	char* representacion18 = fraccion_representacion(fraccion18);
	print_test("Prueba obtener representacion retorna la cadena correcta", strcmp(representacion18, "1") == 0);
	fraccion_destruir(fraccion18);
	free(representacion18);
	
	print_test("Prueba crear fraccion se crea correctamente (numerador negativo, numeros iguales en modulo)", fraccion19 != NULL);
	print_test("Prueba obtener la parte entera de la fraccion retorna el valor correcto", fraccion_parte_entera(fraccion19) == -1);
	char* representacion19 = fraccion_representacion(fraccion19);
	print_test("Prueba obtener representacion retorna la cadena correcta", strcmp(representacion19, "-1") == 0);
	fraccion_destruir(fraccion19);
	free(representacion19);
	
	print_test("Prueba crear fraccion se crea correctamente (denominador negativo, numeros iguales en modulo)", fraccion20 != NULL);
	print_test("Prueba obtener la parte entera de la fraccion retorna el valor correcto", fraccion_parte_entera(fraccion20) == -1);
	char* representacion20 = fraccion_representacion(fraccion20);
	print_test("Prueba obtener representacion retorna la cadena correcta", strcmp(representacion20, "-1") == 0);
	fraccion_destruir(fraccion20);
	free(representacion20);
	
	print_test("Prueba crear fraccion se crea correctamente (numeros iguales negativos)", fraccion21 != NULL);
	print_test("Prueba obtener la parte entera de la fraccion retorna el valor correcto", fraccion_parte_entera(fraccion21) == 1);
	char* representacion21 = fraccion_representacion(fraccion21);
	print_test("Prueba obtener representacion retorna la cadena correcta", strcmp(representacion21, "1") == 0);
	fraccion_destruir(fraccion21);
	free(representacion21);
	
	print_test("Prueba crear fraccion se crea correctamente (denominador igual a 1)", fraccion22 != NULL);
	print_test("Prueba obtener la parte entera de la fraccion retorna el valor correcto", fraccion_parte_entera(fraccion22) == 10007);
	char* representacion22 = fraccion_representacion(fraccion22);
	print_test("Prueba obtener representacion retorna la cadena correcta", strcmp(representacion22, "10007") == 0);
	fraccion_destruir(fraccion22);
	free(representacion22);
	
	print_test("Prueba crear fraccion se crea correctamente (numerador negativo fraccion se simplifica hasta denominador igual a 1)", fraccion23 != NULL);
	print_test("Prueba obtener la parte entera de la fraccion retorna el valor correcto", fraccion_parte_entera(fraccion23) == -2);
	char* representacion23 = fraccion_representacion(fraccion23);
	print_test("Prueba obtener representacion retorna la cadena correcta", strcmp(representacion23, "-2") == 0);
	fraccion_destruir(fraccion23);
	free(representacion23);
	
	print_test("Prueba crear fraccion se crea correctamente (denominador negativo fraccion se simplifica hasta denominador igual a 1)", fraccion24 != NULL);
	print_test("Prueba obtener la parte entera de la fraccion retorna el valor correcto", fraccion_parte_entera(fraccion24) == -11);
	char* representacion24 = fraccion_representacion(fraccion24);
	print_test("Prueba obtener representacion retorna la cadena correcta", strcmp(representacion24, "-11") == 0);
	fraccion_destruir(fraccion24);
	free(representacion24);
	
	print_test("Prueba crear fraccion se crea correctamente (ambos numeros negativos fraccion se simplifica hasta denominador igual a 1)", fraccion25 != NULL);
	print_test("Prueba obtener la parte entera de la fraccion retorna el valor correcto", fraccion_parte_entera(fraccion25) == 2000);
	char* representacion25 = fraccion_representacion(fraccion25);
	print_test("Prueba obtener representacion retorna la cadena correcta", strcmp(representacion25, "2000") == 0);
	fraccion_destruir(fraccion25);
	free(representacion25);
	
	print_test("Prueba crear fraccion se crea correctamente (numerador negativo fraccion se simplifica hasta numerador igual a 1)", fraccion26 != NULL);
	print_test("Prueba obtener la parte entera de la fraccion retorna el valor correcto", fraccion_parte_entera(fraccion26) == 0);
	char* representacion26 = fraccion_representacion(fraccion26);
	print_test("Prueba obtener representacion retorna la cadena correcta", strcmp(representacion26, "-1/2") == 0);
	fraccion_destruir(fraccion26);
	free(representacion26);
	
	print_test("Prueba crear fraccion se crea correctamente (denominador negativo fraccion se simplifica hasta numerador igual a 1)", fraccion27 != NULL);
	print_test("Prueba obtener la parte entera de la fraccion retorna el valor correcto", fraccion_parte_entera(fraccion27) == 0);
	char* representacion27 = fraccion_representacion(fraccion27);
	print_test("Prueba obtener representacion retorna la cadena correcta", strcmp(representacion27, "-1/11") == 0);
	fraccion_destruir(fraccion27);
	free(representacion27);
	
	print_test("Prueba crear fraccion se crea correctamente (ambos numeros negativos fraccion se simplifica hasta numerador igual a 1)", fraccion28 != NULL);
	print_test("Prueba obtener la parte entera de la fraccion retorna el valor correcto", fraccion_parte_entera(fraccion28) == 0);
	char* representacion28 = fraccion_representacion(fraccion28);
	print_test("Prueba obtener representacion retorna la cadena correcta", strcmp(representacion28, "1/2000") == 0);
	fraccion_destruir(fraccion28);
	free(representacion28);
	
	print_test("Prueba destruir fraccion funciona correctamente", true);
}

void prueba_fraccion_sumar(void) {
	fraccion_t* f1 = fraccion_crear(7, 3);
	fraccion_t* f2 = fraccion_crear(1, 2);
	fraccion_t* f4 = fraccion_crear(17, 5);
	fraccion_t* f5 = fraccion_crear(-1, 7);
	fraccion_t* f7 = fraccion_crear(-5, 3);
	fraccion_t* f8 = fraccion_crear(-46, 7);
	fraccion_t* f10 = fraccion_crear(4, 3);
	fraccion_t* f11 = fraccion_crear(46, 3);
	fraccion_t* f13 = fraccion_crear(5, 6);
	fraccion_t* f14 = fraccion_crear(1, 12);
	fraccion_t* f16 = fraccion_crear(3, 70);
	fraccion_t* f17 = fraccion_crear(1, 7);
	fraccion_t* f19 = fraccion_crear(3, 70);
	fraccion_t* f20 = fraccion_crear(0, 7);
	fraccion_t* f22 = fraccion_crear(3, 70);
	fraccion_t* f23 = fraccion_crear(41, 1);
	
	fraccion_t* f3 = fraccion_sumar(f1, f2);
	print_test("Prueba sumar fracciones retorna la fraccion correcta (ambos fracciones positivas)", f3 != NULL);
	print_test("Prueba obtener la parte entera de la fraccion retorna el valor correcto", fraccion_parte_entera(f3) == 2);
	char* representacion1 = fraccion_representacion(f3);
	print_test("Prueba obtener representacion retorna la cadena correcta", strcmp(representacion1, "17/6") == 0);
	fraccion_destruir(f3);
	free(representacion1);
	
	fraccion_t* f6 = fraccion_sumar(f4, f5);
	print_test("Prueba sumar fracciones retorna la fraccion correcta (una fraccion negativa)", f6 != NULL);
	print_test("Prueba obtener la parte entera de la fraccion retorna el valor correcto", fraccion_parte_entera(f6) == 3);
	char* representacion2 = fraccion_representacion(f6);
	print_test("Prueba obtener representacion retorna la cadena correcta", strcmp(representacion2, "114/35") == 0);
	fraccion_destruir(f6);
	free(representacion2);
	
	fraccion_t* f9 = fraccion_sumar(f7, f8);
	print_test("Prueba sumar fracciones retorna la fraccion correcta (fracciones negativas)", f9 != NULL);
	print_test("Prueba obtener la parte entera de la fraccion retorna el valor correcto", fraccion_parte_entera(f9) == -8);
	char* representacion3 = fraccion_representacion(f9);
	print_test("Prueba obtener representacion retorna la cadena correcta", strcmp(representacion3, "-173/21") == 0);
	fraccion_destruir(f9);
	free(representacion3);
	
	fraccion_t* f12 = fraccion_sumar(f10, f11);
	print_test("Prueba sumar fracciones retorna la fraccion correcta (fracciones con igual denominador)", f12 != NULL);
	print_test("Prueba obtener la parte entera de la fraccion retorna el valor correcto", fraccion_parte_entera(f12) == 16);
	char* representacion4 = fraccion_representacion(f12);
	print_test("Prueba obtener representacion retorna la cadena correcta", strcmp(representacion4, "50/3") == 0);
	fraccion_destruir(f12);
	free(representacion4);
	
	fraccion_t* f15 = fraccion_sumar(f13, f14);
	print_test("Prueba sumar fracciones retorna la fraccion correcta (fracciones con primer denominador divisor del segundo)", f15 != NULL);
	print_test("Prueba obtener la parte entera de la fraccion retorna el valor correcto", fraccion_parte_entera(f15) == 0);
	char* representacion5 = fraccion_representacion(f15);
	print_test("Prueba obtener representacion retorna la cadena correcta", strcmp(representacion5, "11/12") == 0);
	fraccion_destruir(f15);
	free(representacion5);
	
	fraccion_t* f18 = fraccion_sumar(f16, f17);
	print_test("Prueba sumar fracciones retorna la fraccion correcta (fracciones con segundo denominador divisor del primero)", f18 != NULL);
	print_test("Prueba obtener la parte entera de la fraccion retorna el valor correcto", fraccion_parte_entera(f18) == 0);
	char* representacion6 = fraccion_representacion(f18);
	print_test("Prueba obtener representacion retorna la cadena correcta", strcmp(representacion6, "13/70") == 0);
	fraccion_destruir(f18);
	free(representacion6);
	
	fraccion_t* f21 = fraccion_sumar(f19, f20);
	print_test("Prueba sumar fracciones retorna la fraccion correcta (fraccion con numerador 0)", f21 != NULL);
	print_test("Prueba obtener la parte entera de la fraccion retorna el valor correcto", fraccion_parte_entera(f21) == 0);
	char* representacion7 = fraccion_representacion(f21);
	print_test("Prueba obtener representacion retorna la cadena correcta", strcmp(representacion7, "3/70") == 0);
	fraccion_destruir(f21);
	free(representacion7);
	
	fraccion_t* f24 = fraccion_sumar(f22, f23);
	print_test("Prueba sumar fracciones retorna la fraccion correcta (fraccion con denominador 1)", f24 != NULL);
	print_test("Prueba obtener la parte entera de la fraccion retorna el valor correcto", fraccion_parte_entera(f24) == 41);
	char* representacion8 = fraccion_representacion(f24);
	print_test("Prueba obtener representacion retorna la cadena correcta", strcmp(representacion8, "2873/70") == 0);
	fraccion_destruir(f24);
	free(representacion8);
	
	print_test("Prueba destruir fraccion funciona correctamente", true);
}

void prueba_fraccion_multiplicar(void) {
	fraccion_t* f1 = fraccion_crear(123, 4);
	fraccion_t* f2 = fraccion_crear(111, 5);
	fraccion_t* f4 = fraccion_crear(-345, 7);
	fraccion_t* f5 = fraccion_crear(-123, 5);
	fraccion_t* f7 = fraccion_crear(-675, 4);
	fraccion_t* f8 = fraccion_crear(45, 6);
	fraccion_t* f10 = fraccion_crear(0, 4);
	fraccion_t* f11 = fraccion_crear(5, 6);
	
	fraccion_t* f3 = fraccion_mul(f1, f2);
	print_test("Prueba multiplicar fracciones retorna la fraccion correcta (ambas fracciones positivas)", f3 != NULL);
	print_test("Prueba obtener la parte entera de la fraccion retorna el valor correcto", fraccion_parte_entera(f3) == 682);
	char* representacion1 = fraccion_representacion(f3);
	print_test("Prueba obtener representacion retorna la cadena correcta", strcmp(representacion1, "13653/20") == 0);
	fraccion_destruir(f3);
	free(representacion1);
	
	fraccion_t* f6 = fraccion_mul(f4, f5);
	print_test("Prueba multiplicar fracciones retorna la fraccion correcta (ambas fracciones negativas)", f6 != NULL);
	print_test("Prueba obtener la parte entera de la fraccion retorna el valor correcto", fraccion_parte_entera(f6) == 1212);
	char* representacion2 = fraccion_representacion(f6);
	print_test("Prueba obtener representacion retorna la cadena correcta", strcmp(representacion2, "8487/7") == 0);
	fraccion_destruir(f6);
	free(representacion2);
	
	fraccion_t* f9 = fraccion_mul(f7, f8);
	print_test("Prueba multiplicar fracciones retorna la fraccion correcta (una fraccion positiva y una negativa)", f9 != NULL);
	print_test("Prueba obtener la parte entera de la fraccion retorna el valor correcto", fraccion_parte_entera(f9) == -1265);
	char* representacion3 = fraccion_representacion(f9);
	print_test("Prueba obtener representacion retorna la cadena correcta", strcmp(representacion3, "-10125/8") == 0);
	fraccion_destruir(f9);
	free(representacion3);
	
	fraccion_t* f12 = fraccion_mul(f10, f11);
	print_test("Prueba multiplicar fracciones retorna la fraccion correcta (una fraccion igual a 0)", f12 != NULL);
	print_test("Prueba obtener la parte entera de la fraccion retorna el valor correcto", fraccion_parte_entera(f12) == 0);
	char* representacion4 = fraccion_representacion(f12);
	print_test("Prueba obtener representacion retorna la cadena correcta", strcmp(representacion4, "0") == 0);
	fraccion_destruir(f12);
	free(representacion4);
	
	print_test("Prueba destruir fraccion funciona correctamente", true);
}

void pruebas_fraccion_alumno() {
	prueba_fraccion_crear();
	prueba_fraccion_sumar();
	prueba_fraccion_multiplicar();
}
