#include "pila.h"
#include "testing.h"
#include <stddef.h>

#define CONSTANTE_VOLUMEN 10000

void pruebas_pila_creada() {
	pila_t* pila1 = pila_crear();;
	int num = 2;
	int* val = &num;
	
	print_test("Prueba pila crear pila la pila existe", pila1 != NULL);
    print_test("Prueba pila recien creada la pila esta vacia", pila_esta_vacia(pila1) == true);
    print_test("Prueba pila recien creada ver tope es NULL", pila_ver_tope(pila1) == NULL);
    print_test("Prueba pila recien creada desapilar es NULL", pila_desapilar(pila1) == NULL);
    print_test("Prueba pila apilar un elemento es true", pila_apilar(pila1, val) == true);
    print_test("Prueba pila el tope de la pila es el correcto", pila_ver_tope(pila1) == val);
    print_test("Prueba pila la pila no esta vacia", pila_esta_vacia(pila1) == false);
    pila_destruir(pila1);
    print_test("Prueba pila la pila (con datos apilados) fue destruida", true);
}

void pruebas_pila_apilar_desapilar() {
	pila_t* pila2 = pila_crear();;
	int num[] = {5, 8, 79, 7, 6, -2, 45};
	int* val[] = {&num[0], &num[1], &num[2], &num[3], &num[4], &num[5], &num[6]};
	
	print_test("Prueba pila apilar un elemento es true", pila_apilar(pila2, val[1]) == true);
    print_test("Prueba pila el tope de la pila es el correcto", pila_ver_tope(pila2) == val[1]);
	print_test("Prueba pila apilar un segundo elemento es true", pila_apilar(pila2, val[0]) == true);
    print_test("Prueba pila el tope de la pila es el correcto", pila_ver_tope(pila2) == val[0]);
    print_test("Prueba pila apilar un tercer elemento es true", pila_apilar(pila2, val[2]) == true);
    print_test("Prueba pila el tope de la pila es el correcto", pila_ver_tope(pila2) == val[2]);
    print_test("Prueba pila desapilar devuelve el valor correcto", pila_desapilar(pila2) == val[2]);
    print_test("Prueba pila el tope de la pila es el correcto", pila_ver_tope(pila2) == val[0]);
    print_test("Prueba pila apilar un tercer elemento es true", pila_apilar(pila2, val[6]) == true);
	print_test("Prueba pila el tope de la pila es el correcto", pila_ver_tope(pila2) == val[6]);
    print_test("Prueba pila apilar un cuarto elemento es true", pila_apilar(pila2, val[3]) == true);
    print_test("Prueba pila el tope de la pila es el correcto", pila_ver_tope(pila2) == val[3]);
    print_test("Prueba pila apilar un quinto elemento es true", pila_apilar(pila2, val[4]) == true);
    print_test("Prueba pila el tope de la pila es el correcto", pila_ver_tope(pila2) == val[4]);
    print_test("Prueba pila apilar sexto elemento (valor negativo) es true", pila_apilar(pila2, val[5]) == true);
    print_test("Prueba pila el tope de la pila es el correcto", pila_ver_tope(pila2) == val[5]);
    print_test("Prueba pila apilar un septimo elemento (valor NULL) es true", pila_apilar(pila2, NULL) == true);
    print_test("Prueba pila el tope de la pila es el correcto", pila_ver_tope(pila2) == NULL);
    print_test("Prueba pila desapilar devuelve el valor correcto", pila_desapilar(pila2) == NULL);
	print_test("Prueba pila el tope de la pila es el correcto", pila_ver_tope(pila2) == val[5]);
	print_test("Prueba pila desapilar devuelve el valor correcto", pila_desapilar(pila2) == val[5]);
    print_test("Prueba pila el tope de la pila es el correcto", pila_ver_tope(pila2) == val[4]); 
    print_test("Prueba pila desapilar devuelve el valor correcto", pila_desapilar(pila2) == val[4]);
	print_test("Prueba pila el tope de la pila es el correcto", pila_ver_tope(pila2) == val[3]); 
    print_test("Prueba pila desapilar devuelve el valor correcto", pila_desapilar(pila2) == val[3]);
    print_test("Prueba pila el tope de la pila es el correcto", pila_ver_tope(pila2) == val[6]);
	print_test("Prueba pila desapilar devuelve el valor correcto", pila_desapilar(pila2) == val[6]);
    print_test("Prueba pila el tope de la pila es el correcto", pila_ver_tope(pila2) == val[0]); 
	print_test("Prueba pila desapilar devuelve el valor correcto", pila_desapilar(pila2) == val[0]);
    print_test("Prueba pila el tope de la pila es el correcto", pila_ver_tope(pila2) == val[1]); 
    print_test("Prueba pila desapilar devuelve el valor correcto", pila_desapilar(pila2) == val[1]);
	print_test("Prueba pila el tope de la pila es el correcto", pila_ver_tope(pila2) == NULL);
    print_test("Prueba pila desapilar devuelve el valor correcto", pila_desapilar(pila2) == NULL);
    print_test("Prueba pila la pila esta vacia", pila_esta_vacia(pila2) == true);
    //Pruebo si se destruye la pila correctamente.
    pila_destruir(pila2);
    print_test("Prueba pila la pila fue destruida", true);
}

void inicializar_vector_enteros(int vector[]) {
	for (int i = 0; i < CONSTANTE_VOLUMEN; i++) {
		vector[i] = i;
	}
}

void inicializar_vector_punteros(int* vector1[], int vector2[]) {
	for (int i = 0; i < CONSTANTE_VOLUMEN; i++) {
		vector1[i] = &vector2[i]; 
	}
}

void pruebas_pila_volumen() {
	pila_t* pila3 = pila_crear();;
	int vector[CONSTANTE_VOLUMEN];
	int* vector_ptr[CONSTANTE_VOLUMEN];
    
    inicializar_vector_enteros(vector);
    inicializar_vector_punteros(vector_ptr, vector);
    bool ok = true;
    for (int i = 0; i < CONSTANTE_VOLUMEN; i++) {
    	ok &= pila_apilar(pila3, vector_ptr[i]);
    	ok &= (vector_ptr[i] == pila_ver_tope(pila3));
	}
	
	print_test("Prueba pila en volumen se pudieron apilar todos los elementos", ok);
	ok = true;
	for (int i = CONSTANTE_VOLUMEN - 1; i > -1; i--) {
    	ok &= (vector_ptr[i] == pila_ver_tope(pila3));
		ok &= (pila_desapilar(pila3) == vector_ptr[i]);
	}
	
	print_test("Prueba pila en volumen se pudieron desapilar todos los elementos", ok);
	print_test("Prueba pila el tope de la pila es NULL", pila_ver_tope(pila3) == NULL);
    print_test("Prueba pila desapilar es NULL", pila_desapilar(pila3) == NULL);
    print_test("Prueba pila la pila esta vacia", pila_esta_vacia(pila3) == true);
	pila_destruir(pila3);
    print_test("Prueba pila la pila fue destruida", true);
}

void pruebas_pila_alumno() {
    pruebas_pila_creada();
    pruebas_pila_apilar_desapilar();
    pruebas_pila_volumen();
}
