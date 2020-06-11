#include "div_con.h"
#include "sort.h"
#include "testing.h"

#define VACIO NULL
#define NVACIO 0
#define CONSTANTE_VOLUMEN 10000

void prueba_es_magico_null(void) {
	print_test("Prueba arreglo no es magico con vector nulo", es_arreglo_magico(VACIO, NVACIO) == false);
}

void prueba_es_magico_true(void) {
	int arreglo1[6] = {-3, 0, 1, 3, 7, 9};
	int arreglo2[1] = {0};
	int arreglo3[7] = {0, 2, 3, 4, 7, 9, 11};
	int arreglo4[8] = {-1, 0, 1, 2, 3, 4, 5, 7};
	
	print_test("Prueba arreglo es magico con varios elementos (coincidencia en valor central)", es_arreglo_magico(arreglo1, 6) == true);
	print_test("Prueba arreglo es magico con varios elementos (coincidencia en valor inicial)", es_arreglo_magico(arreglo3, 7) == true);
	print_test("Prueba arreglo es magico con varios elementos (coincidencia en valor final)", es_arreglo_magico(arreglo4, 8) == true);
	print_test("Prueba arreglo es magico con un solo elemento", es_arreglo_magico(arreglo2, 1) == true);
}

void prueba_es_magico_false(void) {
	int arreglo1[6] = {-3, 0, 1, 2, 7, 9};
	int arreglo2[1] = {5};
	int arreglo3[7] = {1, 2, 3, 4, 7, 9, 11};
	
	print_test("Prueba arreglo no es magico con parametro par", es_arreglo_magico(arreglo1, 6) == false);
	print_test("Prueba arreglo no es magico con parametro impar", es_arreglo_magico(arreglo3, 7) == false);
	print_test("Prueba arreglo no es magico con un solo elemento", es_arreglo_magico(arreglo2, 1) == false);
}

void determinar_valores_del_arreglo(int arreglo[], int n, int inicio, int valor_agregado) {
	for (int i = inicio; i < n; i++) {
		arreglo[i] = i + valor_agregado;
	}
}

void prueba_es_magico_volumen(void) {
	int arreglo1[CONSTANTE_VOLUMEN];
	determinar_valores_del_arreglo(arreglo1, CONSTANTE_VOLUMEN, 0, 1);
	
	determinar_valores_del_arreglo(arreglo1, 1, 0, 0);
	print_test("Prueba arreglo es magico en volumen (coincidencia en valor inicial)", es_arreglo_magico(arreglo1, CONSTANTE_VOLUMEN) == true);
	determinar_valores_del_arreglo(arreglo1, 1, 0, 1);
	determinar_valores_del_arreglo(arreglo1, CONSTANTE_VOLUMEN, 0, -3);
	determinar_valores_del_arreglo(arreglo1, CONSTANTE_VOLUMEN, 9999, 0);
	print_test("Prueba arreglo es magico en volumen (coincidencia en valor final)", es_arreglo_magico(arreglo1, CONSTANTE_VOLUMEN) == true);
	determinar_valores_del_arreglo(arreglo1, CONSTANTE_VOLUMEN, 9999, -3);
	print_test("Prueba arreglo no es magico en volumen", es_arreglo_magico(arreglo1, CONSTANTE_VOLUMEN) == false);
	determinar_valores_del_arreglo(arreglo1, CONSTANTE_VOLUMEN, 5427, 5);
	determinar_valores_del_arreglo(arreglo1, 5427, 5426, 0);
	print_test("Prueba arreglo es magico en volumen (coincidencia en valor central)", es_arreglo_magico(arreglo1, CONSTANTE_VOLUMEN) == true);
	determinar_valores_del_arreglo(arreglo1, CONSTANTE_VOLUMEN, 0, 0);
}

void prueba_elemento_existe_null(void) {
	print_test("Prueba elemento no existe con vector nulo", elemento_existe(VACIO, NVACIO, NVACIO) == false);
}

void prueba_elemento_existe_true(void) {
	int arreglo1[10] = {2, 7, 9, 11, 76, 15, 29, 31, 550, -1};
	int arreglo2[1] = {78};
	int arreglo3[7] = {1, 14, 7, 9, 16, 51, 0};
	int arreglo4[16] = {-89, 56, 1, 7, 67, 14, 59, 70, 6, 0, 43, -56, 32, 12, 11, 1234};
	int dato1 = 7, dato2 = 78, dato3 = 16, dato4 = 12;
	
	print_test("Prueba elemento existe (dato en posicion inicial)", elemento_existe(arreglo1, 10, dato1) == true);
	print_test("Prueba elemento existe con un unico elemento", elemento_existe(arreglo2, 1, dato2) == true);
	print_test("Prueba elemento existe (dato en posicion central)", elemento_existe(arreglo3, 7, dato3) == true);
	print_test("Prueba elemento existe (dato en posicion final)", elemento_existe(arreglo4, 16, dato4) == true);
}

void prueba_elemento_existe_false(void) {
	int arreglo1[1] = {78};
	int arreglo2[7] = {1, 14, 7, 9, 16, 51, 0};
	int arreglo3[16] = {-89, 56, 1, 7, 67, 14, 59, 70, 6, 0, 43, -56, 32, 12, 11, 1234};
	int dato1 = 7, dato2 = 2, dato3 = 167;
	
	print_test("Prueba elemento no existe con un unico elemento", elemento_existe(arreglo1, 1, dato1) == false);
	print_test("Prueba elemento no existe con parametro impar", elemento_existe(arreglo2, 7, dato2) == false);
	print_test("Prueba elemento no existe con parametro par", elemento_existe(arreglo3, 16, dato3) == false);
}

void determinar_valores_aleatorios(int arreglo[], int n) {
	for (int i = 0; i < n; i++) {
		arreglo[i] = rand() % 10007;
	}
}

void prueba_elemento_existe_volumen(void) {
	int arreglo1[CONSTANTE_VOLUMEN];
	int dato1 = 10008, dato2 = 10009, dato3 = 11234, dato4 = 10089;
	
	determinar_valores_aleatorios(arreglo1, CONSTANTE_VOLUMEN);
	arreglo1[9] = dato1;
	print_test("Prueba elemento existe en volumen (dato en posicion inicial)", elemento_existe(arreglo1, CONSTANTE_VOLUMEN, dato1) == true);
	arreglo1[5678] = dato2;
	print_test("Prueba elemento existe en volumen (dato en posicion central)", elemento_existe(arreglo1, CONSTANTE_VOLUMEN, dato2) == true);
	arreglo1[9989] = dato3;
	print_test("Prueba elemento existe en volumen (dato en posicion central)", elemento_existe(arreglo1, CONSTANTE_VOLUMEN, dato3) == true);
	print_test("Prueba elemento no existe en volumen", elemento_existe(arreglo1, CONSTANTE_VOLUMEN, dato4) == false);
}

void prueba_buscar_primer_cero_null(void) {
	print_test("Prueba buscar primer cero con vector nulo retorna el indice correcto", buscar_primer_cero(VACIO, NVACIO) == -1);
}

void prueba_buscar_primer_cero_true(void) {
	int arreglo1[1] = {0};
	int arreglo3[10] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int arreglo4[11] = {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0};
	int arreglo5[15] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0};
	int arreglo6[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	
	print_test("Prueba buscar primer cero con un unico elemento retorna el indice correcto (existe el valor 0)", buscar_primer_cero(arreglo1, 1) == 0);
	print_test("Prueba buscar primer cero con varios elementos retorna el indice correcto (0 en posicion inicial)", buscar_primer_cero(arreglo3, 10) == 1);
	print_test("Prueba buscar primer cero con varios elementos retorna el indice correcto (0 en posicion central)", buscar_primer_cero(arreglo4, 11) == 6);
	print_test("Prueba buscar primer cero con varios elementos retorna el indice correcto (0 en posicion final)", buscar_primer_cero(arreglo5, 15) == 12);
	print_test("Prueba buscar primer cero con varios elementos retorna el indice correcto (todos los elementos son 0)", buscar_primer_cero(arreglo6, 9) == 0);
}

void prueba_buscar_primer_cero_false(void) {
	int arreglo1[1] = {1};
	int arreglo2[10] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
	int arreglo3[11] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
	
	print_test("Prueba buscar primer cero con un unico elemento retorna el indice correcto (no existe el valor 0)", buscar_primer_cero(arreglo1, 1) == -1);
	print_test("Prueba buscar primer cero con parametro n par retorna el indice correcto (no existe el valor 0)", buscar_primer_cero(arreglo2, 10) == -1);
	print_test("Prueba buscar primer cero con parametro n impar retorna el indice correcto (no existe el valor 0)", buscar_primer_cero(arreglo3, 11) == -1);
}

void determinar_valores_binarios(int arreglo[], int n, int cambio) {
	for (int i = 0; i < n; i++) {
		if (i >= cambio) {
			arreglo[i] = 0;
		} else {
			arreglo[i] = 1;
		}
	}
}

void prueba_buscar_primer_cero_volumen(void) {
	int arreglo1[CONSTANTE_VOLUMEN];
	
	determinar_valores_binarios(arreglo1, CONSTANTE_VOLUMEN, 31);
	print_test("Prueba buscar primer cero en volumen retorna el indice correcto (0 en posicion inicial)", buscar_primer_cero(arreglo1, CONSTANTE_VOLUMEN) == 31);
	determinar_valores_binarios(arreglo1, CONSTANTE_VOLUMEN, 5213);
	print_test("Prueba buscar primer cero en volumen retorna el indice correcto (0 en posicion central)", buscar_primer_cero(arreglo1, CONSTANTE_VOLUMEN) == 5213);
	determinar_valores_binarios(arreglo1, CONSTANTE_VOLUMEN, 9871);
	print_test("Prueba buscar primer cero en volumen retorna el indice correcto (0 en posicion final)", buscar_primer_cero(arreglo1, CONSTANTE_VOLUMEN) == 9871);
	determinar_valores_binarios(arreglo1, CONSTANTE_VOLUMEN, 0);
	print_test("Prueba buscar primer cero en volumen retorna el indice correcto (todos los elementos son 0)", buscar_primer_cero(arreglo1, CONSTANTE_VOLUMEN) == 0);
	determinar_valores_binarios(arreglo1, CONSTANTE_VOLUMEN, CONSTANTE_VOLUMEN);
	print_test("Prueba buscar primer cero en volumen retorna el indice correcto (todos los elementos son 1)", buscar_primer_cero(arreglo1, CONSTANTE_VOLUMEN) == -1);
}

int calcular_raiz_cuadrada_auxiliar(int radicando, int raiz) {
	if ((raiz * raiz) == radicando) {
		return raiz;
	}
	
	if ((raiz * raiz) > radicando) {
		return raiz - 1;
	}
	
	return calcular_raiz_cuadrada_auxiliar(radicando, raiz + 1);
}

void determinar_raices_del_arreglo(int arreglo[], int n) {
	for (int i = 0; i < n; i++) {
		arreglo[i] = calcular_raiz_cuadrada_auxiliar(i, 0);
	}
}

void prueba_raiz_cuadrada(void) {
	int arreglo1[CONSTANTE_VOLUMEN];
	int arreglo2[CONSTANTE_VOLUMEN];
	
	determinar_valores_del_arreglo(arreglo1, CONSTANTE_VOLUMEN, 0, 0);
	determinar_raices_del_arreglo(arreglo2, CONSTANTE_VOLUMEN);
	bool ok = true;
	for (int i = 0; i < CONSTANTE_VOLUMEN; i++) {
		ok &= calcular_raiz_cuadrada(i) == arreglo2[i];
	}
	
	print_test("Prueba raiz cuadrada natural retorna el valor correcto (se evaluan muchos elementos)", ok);
	print_test("Prueba raiz cuadrada natural retorna el valor correcto (radicando par mayor al millon)", calcular_raiz_cuadrada(31456238) == 5608);
	print_test("Prueba raiz cuadrada natural retorna el valor correcto (radicando impar mayor al millon)", calcular_raiz_cuadrada(2693461) == 1641);
}

void prueba_arreglo_ordenado_unico(void) {
	int arreglo1[1] = {2};
	
	print_test("Prueba arreglo esta ordenado con arreglo nulo retorna false", arreglo_orden_ascendente(VACIO, 1) == false);
	print_test("Prueba arreglo esta ordenado con parametro n menor o igual a 0 retorna false", arreglo_orden_ascendente(arreglo1, 0) == false);
	print_test("Prueba arreglo esta ordenado con un solo elemento retorna true", arreglo_orden_ascendente(arreglo1, 1) == true);
}

void prueba_arreglo_ordenado_false(void) {
	int n1 = 5, n2 = 11, n3 = 13, n4 = 16;
	int arreglo1[] = {1, 2, 2, 0, 7};
	int arreglo2[] = {1, 2, 2, 4, 7, 11, 14, 20, 19, 30, 40};
	int arreglo3[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 5, 0};
	int arreglo4[] = {12, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 5, 6};
	int arreglo5[] = {1, 1, 1, 1, 14, 1, 1, 1, 1, 2, 3, 5, 6};
	int arreglo6[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 5, 6, 12, 15, 0};
	int arreglo7[] = {19, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 5, 6, 12, 15, 20};
	int arreglo8[] = {1, 1, 1, 1, 1, 1, 101, 1, 1, 2, 3, 5, 6, 12, 15, 20};
	
	print_test("Prueba arreglo no esta ordenado con parametro n impar retorna false", arreglo_orden_ascendente(arreglo1, n1) == false);
	print_test("Prueba arreglo no esta ordenado con parametro n par retorna false", arreglo_orden_ascendente(arreglo2, n2) == false);
	print_test("Prueba arreglo no esta ordenado con parametro n impar retorna false (desorden al final)", arreglo_orden_ascendente(arreglo3, n3) == false);
	print_test("Prueba arreglo no esta ordenado con parametro n impar retorna false (desorden al inicio)", arreglo_orden_ascendente(arreglo4, n3) == false);
	print_test("Prueba arreglo no esta ordenado con parametro n impar retorna false (desorden al medio)", arreglo_orden_ascendente(arreglo5, n3) == false);
	print_test("Prueba arreglo no esta ordenado con parametro n par retorna false (desorden al final)", arreglo_orden_ascendente(arreglo6, n4) == false);
	print_test("Prueba arreglo no esta ordenado con parametro n par retorna false (desorden al inicio)", arreglo_orden_ascendente(arreglo7, n4) == false);
	print_test("Prueba arreglo no esta ordenado con parametro n par retorna false (desorden al medio)", arreglo_orden_ascendente(arreglo8, n4) == false);
}

void prueba_arreglo_ordenado_true(void) {
	int n1 = 13, n2 = 16;
	int arreglo1[] = {-12, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 5, 6};
	int arreglo2[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 5, 6, 12, 15, 20};
	
	print_test("Prueba arreglo esta ordenado con parametro n impar retorna true", arreglo_orden_ascendente(arreglo1, n1) == true);
	print_test("Prueba arreglo esta ordenado con parametro n par retorna true", arreglo_orden_ascendente(arreglo2, n2) == true);
}

void prueba_arreglo_ordenado_volumen(void) {
	int arreglo1[CONSTANTE_VOLUMEN];
	int arreglo2[CONSTANTE_VOLUMEN];
	int arreglo3[CONSTANTE_VOLUMEN];
	int arreglo4[CONSTANTE_VOLUMEN];
	
	determinar_valores_aleatorios(arreglo1, CONSTANTE_VOLUMEN);
	determinar_valores_aleatorios(arreglo2, CONSTANTE_VOLUMEN);
	determinar_valores_aleatorios(arreglo3, CONSTANTE_VOLUMEN);
	determinar_valores_aleatorios(arreglo4, CONSTANTE_VOLUMEN);
	merge_sort(arreglo1, CONSTANTE_VOLUMEN);
	merge_sort(arreglo2, CONSTANTE_VOLUMEN);
	merge_sort(arreglo3, CONSTANTE_VOLUMEN);
	merge_sort(arreglo4, CONSTANTE_VOLUMEN);
	arreglo1[132] = 12000;
	arreglo2[9345] = 12000;
	arreglo3[6132] = 12000;
	print_test("Prueba arreglo esta ordenado en volumen retorna false (desorden al inicio)", arreglo_orden_ascendente(arreglo1, CONSTANTE_VOLUMEN) == false);
	print_test("Prueba arreglo esta ordenado en volumen retorna false (desorden al final)", arreglo_orden_ascendente(arreglo2, CONSTANTE_VOLUMEN) == false);
	print_test("Prueba arreglo esta ordenado en volumen retorna false (desorden al medio)", arreglo_orden_ascendente(arreglo3, CONSTANTE_VOLUMEN) == false);
	print_test("Prueba arreglo esta ordenado en volumen retorna true", arreglo_orden_ascendente(arreglo4, CONSTANTE_VOLUMEN) == true);
}

void prueba_minimo_unico(void) {
	int arreglo1[] = {4};
	
	print_test("Prueba minimo con unico elemento retorna la posicion correcta", minimo(arreglo1, 1) == 0);
	print_test("Prueba minimo con n igual a 0 retorna la posicion correcta", minimo(arreglo1, 0) == -1);
	print_test("Prueba minimo con arreglo nulo retorna la posicion correcta", minimo(VACIO, 1) == -1);
}

void prueba_minimo_varios_elementos(void) {
	int n1 = 12, n2 = 13;
	int arreglo1[] = {6, 14, 14, 6, 19, 20, 12, 54, 11, 67, 11, 11};
	int arreglo2[] = {66, 14, 14, 7, 19, 20, 12, 54, 11, 67, 11, 11};
	int arreglo3[] = {66, 14, 14, 71, 19, 20, 12, 54, 111, 67, 11, 11};
	int arreglo4[] = {6, 14, 14, 7, 19, 20, 12, 54, 11, 67, 11, 11, 11};
	int arreglo5[] = {66, 14, 14, 77, 19, 2, 12, 54, 11, 67, 11, 11, 11};
	int arreglo6[] = {6, 14, 14, 7, 19, 20, 12, 54, 111, 67, 111, 1, 1};
	
	print_test("Prueba minimo con parametro n par retorna la posicion correcta (minimo al inicio)", minimo(arreglo1, n1) == 0);
	print_test("Prueba minimo con parametro n par retorna la posicion correcta (minimo al medio)", minimo(arreglo2, n1) == 3);
	print_test("Prueba minimo con parametro n par retorna la posicion correcta (minimo al final)", minimo(arreglo3, n1) == 10);
	print_test("Prueba minimo con parametro n impar retorna la posicion correcta (minimo al inicio)", minimo(arreglo4, n2) == 0);
	print_test("Prueba minimo con parametro n impar retorna la posicion correcta (minimo al medio)", minimo(arreglo5, n2) == 5);
	print_test("Prueba minimo con parametro n impar retorna la posicion correcta (minimo al final)", minimo(arreglo6, n2) == 11);
}

void determinar_valores_aleatorios_minimo(int arreglo[], int n) {
	for (int i = 0; i < n; i++) {
		arreglo[i] = rand() % 10007;
		if (arreglo[i] < 0) {
			arreglo[i] = arreglo[i] * (-1);
		}
		arreglo[i] = arreglo[i] + 10007;
	}
}

void prueba_minimo_volumen(void) {
	int arreglo1[CONSTANTE_VOLUMEN];
	int arreglo2[CONSTANTE_VOLUMEN];
	int arreglo3[CONSTANTE_VOLUMEN];
	
	determinar_valores_aleatorios_minimo(arreglo1, CONSTANTE_VOLUMEN);
	determinar_valores_aleatorios_minimo(arreglo2, CONSTANTE_VOLUMEN);
	determinar_valores_aleatorios_minimo(arreglo3, CONSTANTE_VOLUMEN);
	merge_sort(arreglo1, CONSTANTE_VOLUMEN);
	merge_sort(arreglo2, CONSTANTE_VOLUMEN);
	merge_sort(arreglo3, CONSTANTE_VOLUMEN);
	arreglo1[122] = -11;
	arreglo2[6789] = -89;
	arreglo3[9113] = -1120;
	print_test("Prueba minimo en volumen retorna la posicion correcta (minimo al inicio)", minimo(arreglo1, CONSTANTE_VOLUMEN) == 122);
	print_test("Prueba minimo en volumen retorna la posicion correcta (minimo al medio)", minimo(arreglo2, CONSTANTE_VOLUMEN) == 6789);
	print_test("Prueba minimo en volumen retorna la posicion correcta (minimo al final)", minimo(arreglo3, CONSTANTE_VOLUMEN) == 9113);
}

void prueba_elemento_desordenado_nulo(void) {
	int arreglo1[] = {4};
	
	print_test("Prueba elemento desordenado con unico elemento retorna la posicion correcta", elemento_desordenado(arreglo1, 1) == -1);
	print_test("Prueba elemento desordenado con n igual a 0 retorna la posicion correcta", elemento_desordenado(arreglo1, 0) == -1);
	print_test("Prueba elemento desordenado con arreglo nulo retorna la posicion correcta", minimo(VACIO, 1) == -1);
}

void prueba_elemento_desordenado_varios_elementos(void) {
	int n1 = 12, n2 = 13;
	int arreglo1[] = {16, 14, 15, 36, 119, 220, 312, 454, 511, 667, 711, 811};
	int arreglo2[] = {6, 14, 15, 17, 19, 2, 122, 254, 311, 467, 511, 611};
	int arreglo3[] = {6, 14, 15, 17, 19, 20, 112, 254, 311, 467, 511, 1};
	int arreglo4[] = {666, 14, 15, 17, 19, 20, 112, 254, 311, 467, 511, 611, 711};
	int arreglo5[] = {6, 14, 15, 17, 19, 20, 1, 154, 211, 367, 411, 511, 611};
	int arreglo6[] = {6, 14, 15, 17, 19, 20, 112, 254, 311, 467, 511, 611, 1};
	
	print_test("Prueba elemento desordenado con n par retorna la posicion correcta (elemento al inicio)", elemento_desordenado(arreglo1, n1) == 0);
	print_test("Prueba elemento desordenado con n par retorna la posicion correcta (elemento al medio)", elemento_desordenado(arreglo2, n1) == 5);
	print_test("Prueba elemento desordenado con n par retorna la posicion correcta (elemento al final)", elemento_desordenado(arreglo3, n1) == 11);
	print_test("Prueba elemento desordenado con n impar retorna la posicion correcta (elemento al inicio)", elemento_desordenado(arreglo4, n2) == 0);
	print_test("Prueba elemento desordenado con n impar retorna la posicion correcta (elemento al medio)", elemento_desordenado(arreglo5, n2) == 6);
	print_test("Prueba elemento desordenado con n impar retorna la posicion correcta (elemento al final)", elemento_desordenado(arreglo6, n2) == 12);
}

void determinar_valores_consecutivos(int arreglo[], int n) {
	for (int i = 0; i < n; i++) {
		arreglo[i] = i;
	}
}

void prueba_elemento_desordenado_volumen(void) {
	int arreglo1[CONSTANTE_VOLUMEN];
	int arreglo2[CONSTANTE_VOLUMEN];
	int arreglo3[CONSTANTE_VOLUMEN];
	
	determinar_valores_consecutivos(arreglo1, CONSTANTE_VOLUMEN);
	determinar_valores_consecutivos(arreglo2, CONSTANTE_VOLUMEN);
	determinar_valores_consecutivos(arreglo3, CONSTANTE_VOLUMEN);
	arreglo1[122] = -11;
	arreglo2[6789] = -89;
	arreglo3[9113] = -11120;
	print_test("Prueba elemento desordenado en volumen retorna la posicion correcta (elemento al inicio)", elemento_desordenado(arreglo1, CONSTANTE_VOLUMEN) == 122);
	print_test("Prueba elemento desordenado en volumen retorna la posicion correcta (elemento al medio)", elemento_desordenado(arreglo2, CONSTANTE_VOLUMEN) == 6789);
	print_test("Prueba elemento desordenado en volumen retorna la posicion correcta (elemento al final)", elemento_desordenado(arreglo3, CONSTANTE_VOLUMEN) == 9113);
}

void prueba_posicion_pico(void) {
	int vector1[] = {0, 1, 0};
	int vector2[] = {1, 2, 3, 4, 5, 6, 7, 6, 5, 4, 3, 2, 1, 0, -1};
	int vector3[] = {1, 22, 3, 1, 1, 1, 1, 0, 0, -1, -2, -3, -11, -20, -31};
	int vector4[] = {1, 2, 3, 4, 5, 6, 7, 16, 25, 34, 43, 52, 61, 100, -1};
	size_t n1 = 3, n2 = 15;
	
	print_test("Prueba posicion pico retorna la posicion correcta (tamanio minimo)", posicion_pico(vector1, 0, n1 - 1) == 1);
	print_test("Prueba posicion pico retorna la posicion correcta (pico en el medio)", posicion_pico(vector2, 0, n2 - 1) == 6);
	print_test("Prueba posicion pico retorna la posicion correcta (pico en el inicio)", posicion_pico(vector3, 0, n2 - 1) == 1);
	print_test("Prueba posicion pico retorna la posicion correcta (pico en el final)", posicion_pico(vector4, 0, n2 - 1) == 13);
}

void determinar_pico(int arreglo[], int n, int pico) {
	for(int i = 0; i < n; i++) {
		if (i <= pico) {
			arreglo[i] = i;
		} else {
			arreglo[i] = pico - i;
		}
	}
}

void prueba_posicion_pico_volumen(void) {
	int vector1[CONSTANTE_VOLUMEN];
	int vector2[CONSTANTE_VOLUMEN];
	int vector3[CONSTANTE_VOLUMEN];
	
	determinar_pico(vector1, CONSTANTE_VOLUMEN, 6754);
	determinar_pico(vector2, CONSTANTE_VOLUMEN, 312);
	determinar_pico(vector3, CONSTANTE_VOLUMEN, 9863);
	print_test("Prueba posicion pico en volumen retorna la posicion correcta (pico en el medio)", posicion_pico(vector1, 0, CONSTANTE_VOLUMEN - 1) == 6754);
	print_test("Prueba posicion pico en volumen retorna la posicion correcta (pico en el inicio)", posicion_pico(vector2, 0, CONSTANTE_VOLUMEN - 1) == 312);
	print_test("Prueba posicion pico en volumen retorna la posicion correcta (pico en el final)", posicion_pico(vector3, 0, CONSTANTE_VOLUMEN - 1) == 9863);
}

size_t calcular_dinero(size_t bytelandes) {
	if (bytelandes < 12) {
		return bytelandes;
	}
	
	size_t moneda1 = calcular_dinero(bytelandes / 2);
	size_t moneda2 = calcular_dinero(bytelandes / 3);
	size_t moneda3 = calcular_dinero(bytelandes / 4);
	return moneda1 + moneda2 + moneda3;
}

void calcular_bytelandes_por_pesos(size_t bytelandes[], size_t n) {
	for (size_t i = 0; i < n; i++) {
		bytelandes[i] = calcular_dinero(i);
	}
}

void prueba_intercambiar_bytelandes_por_pesos(void) {
	size_t bytelandes1[CONSTANTE_VOLUMEN];
	
	calcular_bytelandes_por_pesos(bytelandes1, CONSTANTE_VOLUMEN);
	bool ok = true;
	for (size_t i = 0; i < CONSTANTE_VOLUMEN; i++) {
		ok &= bytelandes1[i] == intercambiar_bytelandes_por_pesos(i);
	}
	
	print_test("Prueba intercambiar bytelandes por pesos retona los valores correctos (se prueban muchos valores)", ok);
}

bool elemento_se_repite_mas_de_la_mitad_cuadratico(int arreglo[], size_t n) {
	size_t cant_elementos = 0;
	
	for (size_t i = 0; i < n; i++) {
		cant_elementos = 0;
		for (size_t j = i; j < n; j++) {
			if (arreglo[i] == arreglo[j]) {
				cant_elementos++;
			}
		}
		if (cant_elementos > (n / 2)) {
			return true;
		}
	}
	
	return false;
}

void prueba_elemento_se_repite_mas_de_la_mitad(void) {
	int arreglo1[] = {1, 2, 1, 2, 3}; //2
	int arreglo2[] = {1, 1, 2, 3}; //2
	int arreglo3[] = {1, 2, 3, 1, 1, 1}; //4
	int arreglo4[] = {1}; //1
	int arreglo5[] = {1, 1, 1, 1, 1, 1, 1, 1, 1}; //9
	int arreglo6[] = {14, 12, 1, 12, 12, 10, 12, 12, 12, 9}; //6
	int arreglo7[] = {14, 12, 1, 12, 12, 10, 12, 12, 12, 9, 0}; //6
	int arreglo8[] = {14, 121, 1, 12, 12, 10, 12, 12, 12, 9}; //5
	int arreglo9[] = {14, 12, 1, 12, 123, 10, 12, 12, 12, 9, 0}; //5
	int arreglo10[] = {2, 1, 4, 1, 1, 2, 1, 1, 1, 2}; //6
	int n1 = 5, n2 = 4, n3 = 6, n4 = 1, n5 = 9, n6 = 10, n7 = 11;
	bool ok = true;
	
	ok &= elemento_se_repite_mas_de_la_mitad(arreglo1, n1) == elemento_se_repite_mas_de_la_mitad_cuadratico(arreglo1, n1);
	print_test("Prueba verificar si un elemento se repite mas de la mitad, n chico impar, retorna false", ok);
	ok = true;
	ok &= elemento_se_repite_mas_de_la_mitad(arreglo2, n2) == elemento_se_repite_mas_de_la_mitad_cuadratico(arreglo2, n2);
	print_test("Prueba verificar si un elemento se repite mas de la mitad, n chico par, retorna false", ok);
	ok = true;
	ok &= elemento_se_repite_mas_de_la_mitad(arreglo3, n3) == elemento_se_repite_mas_de_la_mitad_cuadratico(arreglo3, n3);
	print_test("Prueba verificar si un elemento se repite mas de la mitad, n chico par, retorna true", ok);
	ok = true;
	ok &= elemento_se_repite_mas_de_la_mitad(arreglo4, n4) == elemento_se_repite_mas_de_la_mitad_cuadratico(arreglo4, n4);
	print_test("Prueba verificar si un elemento se repite mas de la mitad, con un solo elemento, retorna true", ok);
	ok = true;
	ok &= elemento_se_repite_mas_de_la_mitad(arreglo5, n5) == elemento_se_repite_mas_de_la_mitad_cuadratico(arreglo5, n5);
	print_test("Prueba verificar si un elemento se repite mas de la mitad, todos elementos iguales, retorna true", ok);
	ok = true;
	ok &= elemento_se_repite_mas_de_la_mitad(arreglo6, n6) == elemento_se_repite_mas_de_la_mitad_cuadratico(arreglo6, n6);
	print_test("Prueba verificar si un elemento se repite mas de la mitad, n par, retorna true", ok);
	ok = true;
	ok &= elemento_se_repite_mas_de_la_mitad(arreglo7, n7) == elemento_se_repite_mas_de_la_mitad_cuadratico(arreglo7, n7);
	print_test("Prueba verificar si un elemento se repite mas de la mitad, n impar, retorna true", ok);
	ok = true;
	ok &= elemento_se_repite_mas_de_la_mitad(arreglo8, n6) == elemento_se_repite_mas_de_la_mitad_cuadratico(arreglo8, n6);
	print_test("Prueba verificar si un elemento se repite mas de la mitad, n par, retorna false", ok);
	ok = true;
	ok &= elemento_se_repite_mas_de_la_mitad(arreglo9, n7) == elemento_se_repite_mas_de_la_mitad_cuadratico(arreglo9, n7);
	print_test("Prueba verificar si un elemento se repite mas de la mitad, n impar, retorna false", ok);
	ok = true;
	ok &= elemento_se_repite_mas_de_la_mitad(arreglo10, n6) == elemento_se_repite_mas_de_la_mitad_cuadratico(arreglo10, n6);
	print_test("Prueba verificar si un elemento se repite mas de la mitad retorna true", ok);
}

void prueba_elemento_se_repite_mas_de_la_mitad_volumen(void) {
	int arreglo1[CONSTANTE_VOLUMEN];
	int arreglo2[CONSTANTE_VOLUMEN];
	int arreglo3[CONSTANTE_VOLUMEN + 1];
	int arreglo4[CONSTANTE_VOLUMEN + 1];
	
	for (int i = 0; i < CONSTANTE_VOLUMEN; i++) {
		arreglo1[i] = i;
	}
	
	for (int i = 0; i < CONSTANTE_VOLUMEN + 1; i++) {
		arreglo3[i] = i;
	}
	
    for (int i = 0; i < CONSTANTE_VOLUMEN; i++) {
		if (((i > 2000) && (i < 6005)) || ((i > 8000) && (i < 9005))) {
			arreglo2[i] = -1;
		} else {
			arreglo2[i] = 5;
		}
	}
	
	for (int i = 0; i < CONSTANTE_VOLUMEN - 1; i++) {
		if (((i > 2000) && (i < 6005)) || ((i > 8000) && (i < 9005))) {
			arreglo4[i] = -1;
		} else {
			arreglo4[i] = i;
		}
	}
	
	bool ok = true;
	ok &= elemento_se_repite_mas_de_la_mitad(arreglo1, CONSTANTE_VOLUMEN) == elemento_se_repite_mas_de_la_mitad_cuadratico(arreglo1, CONSTANTE_VOLUMEN);
	print_test("Prueba verificar si valor se repite (mitad+1) en volumen par retorna false", ok);
	ok = true;
	ok &= elemento_se_repite_mas_de_la_mitad(arreglo3, CONSTANTE_VOLUMEN - 1) == elemento_se_repite_mas_de_la_mitad_cuadratico(arreglo3, CONSTANTE_VOLUMEN - 1);
	print_test("Prueba verificar si valor se repite (mitad+1) en volumen impar retorna false", ok);
	ok = true;
	ok &= elemento_se_repite_mas_de_la_mitad(arreglo2, CONSTANTE_VOLUMEN) == elemento_se_repite_mas_de_la_mitad_cuadratico(arreglo2, CONSTANTE_VOLUMEN);
	print_test("Prueba verificar si valor se repite (mitad+1) en volumen par retorna true", ok);
	ok = true;
	ok &= elemento_se_repite_mas_de_la_mitad(arreglo4, CONSTANTE_VOLUMEN - 1) == elemento_se_repite_mas_de_la_mitad_cuadratico(arreglo4, CONSTANTE_VOLUMEN - 1);
	print_test("Prueba verificar si valor se repite (mitad+1) en volumen impar retorna true", ok);
}

void pruebas_div_con_alumno() {
	prueba_es_magico_null();
	prueba_es_magico_true();
	prueba_es_magico_false();
	prueba_es_magico_volumen();
	prueba_elemento_existe_null();
	prueba_elemento_existe_true();
	prueba_elemento_existe_false();
	prueba_elemento_existe_volumen();
	prueba_buscar_primer_cero_null();
	prueba_buscar_primer_cero_true();
	prueba_buscar_primer_cero_false();
	prueba_buscar_primer_cero_volumen();
	prueba_raiz_cuadrada();
	prueba_arreglo_ordenado_unico();
	prueba_arreglo_ordenado_false();
	prueba_arreglo_ordenado_true();
	prueba_arreglo_ordenado_volumen();
	prueba_minimo_unico();
	prueba_minimo_varios_elementos();
	prueba_minimo_volumen();
	prueba_elemento_desordenado_nulo();
	prueba_elemento_desordenado_varios_elementos();
	prueba_elemento_desordenado_volumen();
	prueba_posicion_pico();
	prueba_posicion_pico_volumen();
	prueba_intercambiar_bytelandes_por_pesos();
	prueba_elemento_se_repite_mas_de_la_mitad();
	prueba_elemento_se_repite_mas_de_la_mitad_volumen();
}
