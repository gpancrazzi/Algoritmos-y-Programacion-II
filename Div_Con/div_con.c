#include "div_con.h"

bool es_magico(int arreglo[], int inicio, int fin) {
	if (inicio > fin) {
		return false;
	}
	
	int mitad = (inicio + fin) / 2;
	if (arreglo[mitad] < mitad) {
		return es_magico(arreglo, mitad + 1, fin);
	}
	
	if (arreglo[mitad] > mitad) {
		return es_magico(arreglo, inicio, mitad - 1);
	}
	
	return true;
}

bool es_arreglo_magico(int arreglo[], int n) {
	return es_magico(arreglo, 0, n - 1);
}
/* 
Teorema Maestro:
T(n) = A * T(n / B) + O(n ^ C)
A = 1
B = 2
C = 0
T(n) = T(n / 2) + O(1)
Como log_B(A) = C => log_2(1) = 0 entonces el orden del algoritmo es O(log(n))
*/ 

bool buscar_dato(int arreglo[], int inicio, int fin, int dato) {
	if (inicio == fin) {
		return (arreglo[inicio] == dato);
	}
	
	int mitad = (inicio + fin) / 2;
	if (buscar_dato(arreglo, inicio, mitad, dato)) {
		return true;
	}
	
	if (buscar_dato(arreglo, mitad + 1, fin, dato)) {
		return true;
	}
	
	return false;
}

bool elemento_existe(int arreglo[], int n, int dato) {
	if (n <= 0) {
		return false;
	}
	
	return buscar_dato(arreglo, 0, n - 1, dato);
}
/* 
Teorema Maestro:
T(n) = A * T(n / B) + O(n ^ C)
A = 2
B = 2
C = 0
T(n) = 2T(n / 2) + O(1)
Como log_B(A) > C => log_2(2) = 1 entonces el orden del algoritmo es O(n ^ log_B(A)), es decir, O(n)
*/

//Ejercicio 11 de la Guia
/*
Se tiene un arreglo tal que [1, 1, 1, ..., 0, 0, ...] (es decir, unos seguidos de ceros). Se pide:
una función de orden O(log(n)) que encuentre el índice del primer 0. Si no hay ningún 0 (solo hay unos), debe devolver -1.
demostrar con el Teorema del Maestro que la función es, en efecto, O(log(n)).
*/
int obtener_indice_primer_cero(int arreglo[], int inicio, int fin) {
	if (inicio > fin) {
		return -1;
	}
	
	int mitad = (inicio + fin) / 2;
	if (arreglo[mitad] == 0) {
		if ((mitad > 0) && (arreglo[mitad - 1] == 0)) {
			return obtener_indice_primer_cero(arreglo, inicio, mitad - 1);
		}
		return mitad;
	}
	
	return obtener_indice_primer_cero(arreglo, mitad + 1, fin);
}

int buscar_primer_cero(int arreglo[], int n) {
	return obtener_indice_primer_cero(arreglo, 0, n - 1);
}
/* 
Teorema Maestro:
T(n) = A * T(n / B) + O(n ^ C)
A = 1
B = 2
C = 0
T(n) = T(n / 2) + O(1)
Como log_B(A) = C => log_2(1) = 0 entonces el orden del algoritmo es O(log(n))
*/

//Ejercicio 12 de la Guia
/*
Implementar un algoritmo que, por división y conquista, permita obtener la parte entera de la raíz cuadrada de un número n, 
en tiempo O(logn). Por ejemplo, para n=10 debe devolver 3, y para n=25 debe devolver 5.
*/
int calcular_aproximacion_radicando(int numero, int digito, int resultado) {
	if ((numero * digito) == resultado) {
		return numero;
	}
	
	if ((numero * digito) > resultado) {
		return numero - 1;
	}
	
	return calcular_aproximacion_radicando(numero + 1, digito + 1, resultado);
}

int calcular_raiz_cuadrada_entera(int radicando, int* radicando_parcial) {
	if (radicando == 0) {
		return 0;
	}
	
	int par_numerico = radicando % 100;
	int raiz_parcial = calcular_raiz_cuadrada_entera(radicando / 100, radicando_parcial);
	int radicando_nuevo = *radicando_parcial + par_numerico;
	int aproximacion_radicando_parcial = calcular_aproximacion_radicando(raiz_parcial * 20, 0, radicando_nuevo);
	int radicando_ultimo_digito = aproximacion_radicando_parcial % 10;
	raiz_parcial = raiz_parcial * 10 + radicando_ultimo_digito;
	*radicando_parcial = (radicando_nuevo - aproximacion_radicando_parcial * radicando_ultimo_digito) * 100;
	return raiz_parcial;
}

int calcular_raiz_cuadrada(int radicando) {
	int radicando_parcial = 0;
	return calcular_raiz_cuadrada_entera(radicando, &radicando_parcial);
}
/* 
Teorema Maestro:
T(n) = A * T(n / B) + O(n ^ C)
A = 1
B = 100
C = 0
T(n) = T(n / 2) + O(1)
Como log_B(A) = C => log_100(1) = 0 entonces el orden del algoritmo es O(log(n))
*/

//Ejercicio 1 de la Guia
/*
// Algoritmo ¿por D&C? para obtener el máximo de un arreglo
int maximo(int* arreglo, size_t n) {
    if (n == 1) {
        return arreglo[0];
    }
    int max_restante = maximo(arreglo, n - 1);
    return arreglo[n - 1] > max_restante ? arreglo[n - 1] : max_restante;
}

No es de division y conquista ya que no se divide el tamaño del problema en proporciones mas pequeñas, es un algoritmo recursivo
que va elemento a elemento comparando para buscar el maximo.
*/

//Ejercicio 2 de la Guia
/*
// Algoritmo ¿por D&C? para obtener el máximo de un arreglo
int maximo(int* arreglo, size_t n) {
    size_t medio = n / 2;
    int max_izquierda = _maximo(arreglo, 0, medio);
    int max_derecha = _maximo(arreglo, medio + 1, n - 1);
    return max_izquierda > max_derecha ? max_izquierda : max_derecha;
}

int _maximo(int* arreglo, size_t inicio, size_t fin) {
    int max = arreglo[inicio];
    for (size_t i = inicio + 1; i <= fin; i++) {
        if (max < arreglo[i]) {
            max = arreglo[i];
        }
    }
    return max;
}

En principio, no tiene caso base, luego podemos ver que divide el problema en dos partes pero llama a una funcion
iterativa que recorre cada mitad uno por uno. No se divide el problema en proporciones cada vez mas pequeñas.
*/

// Ejercicio 3 de la Guia
/*
// Busca un elemento usando D&C. El arreglo se encuentra ordenado.
bool elemento_esta(int* arreglo, size_t inicio, size_t fin, int elem) {
    if (inicio > fin) return false;
    size_t medio = (fin + inicio) / 2;
    if (arreglo[medio] == elem) {
        return true;
    }
    if (arreglo[medio] < elem) {
        return elemento_esta(arreglo, medio + 1, fin, elem);
    }

    for (size_t i = medio - 1; i > inicio - 1; i--) {
        if (arreglo[i] == elem) return true;
    }
    return false;
}

Si el elemento a buscar es mayor que el correspondiente al valor en la posicion "medio" del arreglo, entonces
el algoritmo se comporta como O(log(n)). Por el contrario, si es menor, el algoritmo tiene un comportamiento
de O(n). No es posible usar en este caso el Teorema Maestro porque el algoritmo no es de D&C.
La complejidad es el peor caso, es decir, O(n).
Ejemplos trabajados: 
{3 7 12 14 18 22 23 25 30 31}
- Elemento = 40. Caso elemento mayor que los del arreglo O(log(n)).
- Elemento = 1. Caso elemento menor que los del arreglo O(n/2), es decir, O(n).
*/

//Ejercicio 4 y 5 de la Guia 
/*
void imprimir_dyc(int m) {
    if (m < 4) return;
    printf("%d\n", m);
    imprimir_dyc(m / 4);
    imprimir_dyc(m - (m / 4));
}

Teorema Maestro:
T(n) = A * T(n / B) + O(n ^ C)
A = 2
B = 4/3
C = 0
T(n) = 2 * T(3 * n / 4) + O(1)
Como log_B(A) > C --> entonces la complejidad temporal del algoritmo es O(n^(2,4)). 
*/

//Ejercicio 6 de la Guia
/*
Indicar cuál es la complejidad de un algoritmo cuya ecuación de recurrencia es: T = 2 * T ((2/3) * n) + O(n^(1/2))

Teorema Maestro:
T(n) = A * T(n / B) + O(n ^ C)
A = 2
B = 3/2
C = 1/2
Como log_B(A) > C --> entonces la complejidad temporal del algoritmo es O(n^(1,7)).
*/

//Ejercicio 7 de la Guia
/*
Nos dan para elegir entre los siguientes 3 algoritmos para solucionar el mismo problema. ¿Cuál elegirías? Justificar calculando el orden de los algoritmos.
a. El algoritmo A resuelve el problema dividiéndolo en 5 subproblemas de la mitad del tamaño, 
resolviendo cada subproblema de forma recursiva, y combinando las soluciones en tiempo lineal.
b. El algoritmo B resuelve el problema (de tamaño n) dividiéndolo en 9 subproblemas de tamaño n/3, 
resolviendo cada subproblema de forma recursiva y combinando las soluciones en tiempo cuadrático de n.
c. El algoritmo C resuelve el problema (de tamaño n) eligiendo un subproblema de tamaño n-1 en tiempo O(n), 
y luego resolviendo recursivamente ese subproblema.

Calculo el orden de a):
Teorema Maestro:
T(n) = A * T(n / B) + O(n ^ C)
T(n) = 5 * T(n / 2) + O(n)
A = 5
B = 2
C = 1
Como log_B(A) > C --> entonces la complejidad temporal del algoritmo es O(n^(2,32)).

Calculo el orden de b):
Teorema Maestro:
T(n) = A * T(n / B) + O(n ^ C)
T(n) = 9 * T(n / 3) + O(n^2)
A = 9
B = 3
C = 2
Como log_B(A) = C --> entonces la complejidad temporal del algoritmo es O(n^2 * log(n)).

Calculo el orden de c):
El algoritmo recorre el tamaño n haciendo operaciones de complejidad temporal O(n). Por ende, 
la complejidad temporal del algoritmo es O(n^2).

Como conclusion, elegiria el algoritmo c).
*/

//Ejercicio 8 de la Guia
/*
Implementar, por división y conquista, una función que determine el mínimo de un arreglo. Indicar y justificar el orden.
*/
int obtener_minimo(int arreglo[], int inicio, int fin) {
	if (inicio == fin) {
		return fin;
	}
	
	int mitad = (inicio + fin) / 2;
	int minimo_izq = obtener_minimo(arreglo, inicio, mitad);
	int minimo_der = obtener_minimo(arreglo, mitad + 1, fin);
	return (arreglo[minimo_izq] <= arreglo[minimo_der]) ? minimo_izq : minimo_der;
}

int minimo(int arreglo[], int n) {
	if ((arreglo == NULL) || (n <= 0)) {
		return -1;
	}
	
	return obtener_minimo(arreglo, 0, n - 1);
}
/*
Teorema Maestro:
T(n) = A * T(n / B) + O(n ^ C)
T(n) = 2 * T(n / 2) + O(1)
A = 2
B = 2
C = 0
Como log_B(A) > C --> entonces la complejidad temporal del algoritmo es O(n).
*/

//Ejercicio 9 de la Guia
/*
Implementar, por división y conquista, una función que dado un arreglo y su largo, determine si el mismo se encuentra ordenado. Indicar y justificar el orden.
*/
bool verificar_orden(int arreglo[], int posicion) {
	if (posicion == 0) {
		return (arreglo[posicion] <= arreglo[posicion + 1]);
	}
	
	return ((arreglo[posicion] >= arreglo[posicion - 1]) && (arreglo[posicion] <= arreglo[posicion + 1]));
}

bool arreglo_esta_ordenado(int arreglo[], int inicio, int fin) {
	if (inicio == fin) {
		return true;
	}
	
	int medio = (inicio + fin) / 2;
	if (!arreglo_esta_ordenado(arreglo, inicio, medio)) {
		return false;
	}
	
	if (!arreglo_esta_ordenado(arreglo, medio + 1, fin)) {
		return false;
	}
	
	return verificar_orden(arreglo, medio);
}

bool arreglo_orden_ascendente(int arreglo[], int n) {
	if ((arreglo == NULL) || (n <= 0)) {
		return false;
	}
	
	return arreglo_esta_ordenado(arreglo, 0, n - 1);
}
/*
Teorema Maestro:
T(n) = A * T(n / B) + O(n ^ C)
T(n) = 2 * T(n / 2) + O(1)
A = 2
B = 2
C = 0
Como log_B(A) > C --> entonces la complejidad temporal del algoritmo es O(n).
*/

//Ejercicio 10 de la Guia
/*
Implementar, por división y conquista, una función que dado un arreglo sin elementos repetidos y casi ordenado 
(todos los elementos se encuentran ordenados, salvo uno), obtenga el elemento fuera de lugar. Indicar y justificar el orden.
*/
bool verificar_orden_correcto(int arreglo[], int posicion, int *posicion_desordenada) {
	if (posicion == 0) {
		if (arreglo[posicion] > arreglo[posicion + 1]) {
			*posicion_desordenada = posicion;
			return false;
		}
		return true;
	}
	
	if (arreglo[posicion] < arreglo[posicion - 1]) {
		*posicion_desordenada = posicion;
		return false;
	}
	
	if (arreglo[posicion] > arreglo[posicion + 1]) {
		*posicion_desordenada = posicion + 1;
		return false;
	}
	
	return true;
}

bool elemento_ordenado(int arreglo[], int inicio, int fin, int *posicion) {
	if (inicio == fin) {
		return true;
	}
	
	int medio = (inicio + fin) / 2;
	if (!elemento_ordenado(arreglo, inicio, medio, posicion)) {
		return false;
	}
	
	if (!elemento_ordenado(arreglo, medio + 1, fin, posicion)) {
		return false;
	}
	
	return verificar_orden_correcto(arreglo, medio, posicion);
}

int elemento_desordenado(int arreglo[], int n) {
	if ((arreglo == NULL) || (n <= 0)) {
		return -1;
	}
	
	int posicion = -1;
	elemento_ordenado(arreglo, 0, n - 1, &posicion);
	return posicion;
}
/*
Teorema Maestro:
T(n) = A * T(n / B) + O(n ^ C)
T(n) = 2 * T(n / 2) + O(1)
A = 2
B = 2
C = 0
Como log_B(A) > C --> entonces la complejidad temporal del algoritmo es O(n).
*/

//Ejercicio 13 de la Guia
/*
Se tiene un arreglo de N>=3 elementos en forma de pico, esto es: estrictamente creciente hasta una determinada posición p, 
y estrictamente decreciente a partir de ella (con 0<p<N-1). 
Por ejemplo, en el arreglo [1, 2, 3, 1, 0, -2] la posición del pico es p=2. Se pide:
Implementar un algoritmo de división y conquista de orden O(logn) 
que encuentre la posición p del pico: size_t posicion_pico(int v[], size_t ini, size_t fin);. 
La función será invocará inicialmente como: posicion_pico(v, 0, n-1), y tiene como pre-condición que el arreglo tenga forma de pico.
Justificar el orden del algoritmo mediante el teorema del maestro.
*/
size_t posicion_pico(int v[], size_t ini, size_t fin) {
	if (fin == 2) {
		return 1;
	} //Por las precondiciones del problema, esta parte del codigo no es necesaria. Lo agregue pensando que D&Q necesariamente debe tener caso base.
	
	size_t medio = (ini + fin) / 2;
	if ((v[medio] > v[medio - 1]) && (v[medio] > v[medio + 1])) {
		return medio;
	}
	
	if ((v[medio] >= v[medio - 1]) && (v[medio] <= v[medio + 1])) {
		return posicion_pico(v, medio + 1, fin);
	}
	
	return posicion_pico(v, ini, medio);
}
/*
Teorema Maestro:
T(n) = A * T(n / B) + O(n ^ C)
T(n) = T(n / 2) + O(1)
A = 1
B = 2
C = 0
Como log_B(A) = C --> entonces la complejidad temporal del algoritmo es O(log(n)).
*/

//Ejercicio 14 de la Guia
/*
Se quiere implementar MergeSort pero, en vez de dividir en dos partes el arreglo, dividirlo en tres, 
llamando recursivamente al algoritmo para cada una de las partes y luego uniéndolas.
Suponiendo que el merge de las tres partes se realiza en tiempo lineal, calcular el orden del algoritmo.
Si en vez de dividir en tres partes, se dividiera el arreglo en n, siendo n la cantidad de elementos del arreglo 
¿a qué otro algoritmo de ordenamiento se asemeja esta implementación? ¿Cuál es el orden de dicho algoritmo?
Dado lo obtenido en los puntos anteriores ¿tiene sentido implementar MergeSort con k separaciones, para k>2?

Analizo con el teorema maestro:
Teorema Maestro:
T(n) = A * T(n / B) + O(n ^ C)
T(n) = 3 * T(n / 3) + O(n)
A = 3
B = 3
C = 1
Como log_B(A) = C --> entonces la complejidad temporal del algoritmo es O(n * log(n)).

Para el caso de dividir en n, deja de ser un algoritmo de D&Q, se parece al algoritmo de seleccion.
La complejidad del algoritmo sera de O(n^2).

No tiene sentido implementar MergeSort con k separaciones, siendo k > 2, ya que, aunque k se mantenga despreciable, se 
complica la escritura del codigo sin obtener beneficios ni en la complejidad temporal ni la espacial.
*/

//Ejercicio 15 de la Guia
/*
Un algoritmo sencillo para multiplicar matrices de n×n demora O(n^3). El algoritmo de Strassen (que utiliza División y Conquista) 
lo hace en O(n^log_2(7)). La profesora Manterola quiere implementar un algoritmo de División y Conquista que sea aún más veloz, 
donde divida al problema en A subproblemas de tamaño de n/4, y que juntar las soluciones parciales sea O(n^2). 
¿Cuál es el máximo A para que el orden del algoritmo sea menor que el del algoritmo de Strassen? Justificar.

Analizo con el teorema maestro:
Teorema Maestro:
T(n) = A * T(n / B) + O(n ^ C)
T(n) = A * T(n / 4) + O(n^2)
A = 3
B = 4
C = 2
Si log_4(A) < 2 --> A < 16 --> O(n^2) --> Es menor que O(n^log_2(7))
Si log_4(A) = 2 --> A = 16 --> O(n^2 * log(n)) --> Es menor que O(n^log_2(7))
Si log_4(A) > 2 --> A > 16 --> Que valor de A debe tener para superar el valor de log_2(7)?
El valor tiene que ser A < 49.
*/

//Ejercicio 16 de la Guia
/*
En Bytelandia tienen un sistema monetario extraño: su divisa es el bytelandés, y existen denominaciones en moneda física… ¡para todos los valores enteros! 
(Esto es, se emiten monedas de 1, 2, 3, …, 14, 15, …, 28, 29, 30, … bytelandeses). No solo eso, cualquier moneda de valor n puede cambiarse en el banco 
por 3 monedas de menor denominación, de valores n/2, n/3 y n/4 respectivamente (no existe denominación de 0 pesos, por lo cual es posible recibir 
menos de 3 monedas en el cambio); una vez hecho el cambio, sin embargo, no pueden cambiarse de vuelta por la moneda mayor 
(e.g., no pueden cambiase una moneda de 2 y otra de 3 por una de 5).
Finalmente, también es posible intercambiar bytelandeses por pesos argentinos, a una tasa de 1 a 1. 
Se pide implementar un algoritmo que, utilizando división y conquista, reciba el valor n de una moneda en bytelandés 
y devuelva la cantidad máxima de pesos argentinos que se podría obtener realizando los intercambios arriba mencionados. 
Por ejemplo, si n=12, la cantidad máxima de pesos que se puede obtener es $13, ya que podemos dividir la moneda de 12 bytelandeses 
en monedas de 6, 4 y 3; y $6 + $4 + $3 = $13 (se podría seguir dividiendo, pero en este caso no conviene dividir ninguna de esas monedas resultantes). 
Justificar el orden del algoritmo implementado.
*/
size_t calcular_cantidad_maxima_de_pesos(size_t bytelandes, size_t* moneda) {
	if (bytelandes < 12) {
		return bytelandes;
	}
	
	size_t moneda1 = calcular_cantidad_maxima_de_pesos(bytelandes / 2, moneda);
	size_t moneda3 = 0;
	if (moneda1 < 12) {
		moneda3 = bytelandes / 4;
	} else {
		moneda3 = *moneda;
	}
	
	size_t moneda2 = calcular_cantidad_maxima_de_pesos(bytelandes / 3, moneda);
	*moneda = moneda1;
	return moneda1 + moneda2 + moneda3;
}

size_t intercambiar_bytelandes_por_pesos(size_t bytelandes) {
	size_t moneda = 0;
	
	return calcular_cantidad_maxima_de_pesos(bytelandes, &moneda);
}
/*
Teorema Maestro:
T(n) = A * T(n / B) + O(n ^ C)
T(n) = 2 * T(n / 2) + O(1)
A = 2
B = 2
C = 0
Como log_B(A) > C --> entonces la complejidad temporal del algoritmo es O(n).
*/

//Ejercicio 17 de la Guia
/*
Implementar una función (que utilice división y conquista) de orden O(n * log(n)) que dado un arreglo de n números enteros 
devuelva true o false según si existe algún elemento que aparezca más de la mitad de las veces. Justificar el orden de la solución. Ejemplos:
[1, 2, 1, 2, 3] -> false
[1, 1, 2, 3] -> false
[1, 2, 3, 1, 1, 1] -> true
[1] -> true
*/
int calcular_repeticiones(int arreglo[], size_t inicio, size_t fin, size_t posicion) {
	int repeticiones = 1;
	
	for (size_t i = inicio; i <= fin; i++) {
		if ((i != posicion) && (arreglo[i] == arreglo[posicion])) {
			repeticiones++;
		}
	}
	
	return repeticiones;
}

size_t comparar_numeros(int arreglo[], size_t inicio, size_t fin, size_t izq, size_t der, int* cantidad_repetidos) {
	int repeticiones_izq = calcular_repeticiones(arreglo, inicio, fin, izq); 
	int repeticiones_der = calcular_repeticiones(arreglo, inicio, fin, der);
	
	if (repeticiones_izq > *cantidad_repetidos) {
		*cantidad_repetidos = repeticiones_izq;
		return izq;
	}
	
	if (repeticiones_der > *cantidad_repetidos) {
		*cantidad_repetidos = repeticiones_der;
		return der;
	}
	
	if (repeticiones_izq >= repeticiones_der) {
		return izq;
	}
	
	return der;
}

size_t buscar_repetidos(int arreglo[], size_t inicio, size_t fin, int* cantidad_repetidos) {
	if (inicio == fin) {
		return fin;
	}
	
	size_t medio = (inicio + fin) / 2;
	size_t izq = buscar_repetidos(arreglo, inicio, medio, cantidad_repetidos);
	size_t der = buscar_repetidos(arreglo, medio + 1, fin, cantidad_repetidos);
	return comparar_numeros(arreglo, inicio, fin, izq, der, cantidad_repetidos);
}

bool elemento_se_repite_mas_de_la_mitad(int arreglo[], size_t n) {
	int cantidad_repetidos = 1;
	
	buscar_repetidos(arreglo, 0, n - 1, &cantidad_repetidos);
	return (cantidad_repetidos > ((int)n / 2));
}
/*
Teorema Maestro:
T(n) = A * T(n / B) + O(n ^ C)
T(n) = 2 * T(n / 2) + 2 * O(n)
A = 2
B = 2
C = 1
Como log_B(A) = C --> entonces la complejidad temporal del algoritmo es O(n * log(n)).
*/
