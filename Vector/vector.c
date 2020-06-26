#include "vector.h"

/* ******************************************************************
 *                        ESTRUCTURA DE DATOS
 * *****************************************************************/
 
struct vector {
    size_t tam;
    int* datos;
};

/* ******************************************************************
 *                        FUNCIONES AUXILIARES
 * *****************************************************************/

bool rango_valido(vector_t* vector, size_t pos) {
	if ((vector_largo(vector) == 0) || (pos > (vector_largo(vector) - 1))) {
		return false;
	}
	
	return true;
}

 /* ******************************************************************
 *                        PRIMITIVAS DEL VECTOR
 * *****************************************************************/

void vector_destruir(vector_t* vector) {
	free(vector->datos);
	free(vector);
}

size_t vector_largo(vector_t* vector) {
	return vector->tam;
}

bool vector_obtener(vector_t* vector, size_t pos, int* valor) {
	if (rango_valido(vector, pos)) {
		*valor = vector->datos[pos];
		return true;
	}
	
	return false;
}

bool vector_guardar(vector_t* vector, size_t pos, int valor) {
	if (rango_valido(vector, pos)) {
		vector->datos[pos] = valor;
		return true;
	}
	
	return false; 
}

vector_t* vector_crear(size_t tam) {
    vector_t* vector = malloc(sizeof(vector_t));

    if (!vector) {
        return NULL;
    }
    vector->datos = malloc(tam * sizeof(int));

    if (tam > 0 && !vector->datos) {
        free(vector);
        return NULL;
    }
    vector->tam = tam;
    return vector;
}

bool vector_redimensionar(vector_t* vector, size_t tam_nuevo) {
    int* datos_nuevo = realloc(vector->datos, tam_nuevo * sizeof(int));

    if (tam_nuevo > 0 && !datos_nuevo) {
        return false;
    }

    vector->datos = datos_nuevo;
    vector->tam = tam_nuevo;
    return true;
}
