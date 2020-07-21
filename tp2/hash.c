#define _POSIX_C_SOURCE 200809L
#include "hash.h"
#include <stdlib.h>
#include <string.h>

#define CAPACIDAD_INICIAL 47
#define CONSTANTE_DE_REDIMENSION 2

/* ******************************************************************
 *                        ESTRUCTURA DE DATOS
 * *****************************************************************/

typedef enum {vacio, ocupado, borrado} estado_t;

typedef struct campos {
	char* clave;
	void* valor;
	estado_t estado;
} campos_t;

struct hash {
	size_t capacidad;
	size_t cantidad;
	size_t borrados;
	campos_t* campos;
	hash_destruir_dato_t destruir_dato;
};

struct hash_iter {
	const hash_t* hash;
	size_t act;
};

/* ******************************************************************
 *                        FUNCIONES AUXILIARES
 * *****************************************************************/

void inicializar_variables (hash_t* hash, size_t capacidad) {
	hash->capacidad = capacidad;
	hash->cantidad = 0;
	hash->borrados = 0;
	
	for (size_t i = 0; i < hash->capacidad; i++) {
		hash->campos[i].estado = vacio;
	}
}

size_t funcion_hash(const char *str, size_t capacidad) {
    size_t hash = 5381;
    int c;

    while ((c = *str++)) {
    	hash = ((hash << 5) + hash) + c;
	}

    return hash % capacidad;
}

void obtener_nueva_posicion (const hash_t* hash, size_t* pos) {
	if (*pos >= (hash->capacidad - 1)) {
		*pos = 0;
	} else {
		*pos += 1;
	}
}

size_t buscar_posicion_clave (const hash_t* hash, const char* clave) {
	size_t pos = funcion_hash(clave, hash->capacidad);
	
	if (hash->campos[pos].estado == vacio) {
		return pos;
	}
	
	while (hash->campos[pos].estado != vacio) {
		if ((hash->campos[pos].estado == ocupado) && (strcmp(hash->campos[pos].clave, clave) == 0)) {
			return pos;
		}
		obtener_nueva_posicion(hash, &pos);
	}
	
	return pos;
}

void guardar_campo (hash_t* hash, char* clave, void* dato, size_t pos) {
	hash->campos[pos].clave = clave;
	hash->campos[pos].valor = dato;
	hash->campos[pos].estado = ocupado;
	hash->cantidad++;
}

bool redimensionar(hash_t *hash, size_t capacidad) {
	campos_t* temp_campos = malloc(sizeof(campos_t) * capacidad);
	
	if (!temp_campos) {
		return false;
	}
	
	size_t ant_capacidad = hash->capacidad;
	campos_t* ant_campos = hash->campos;
	hash->campos = temp_campos;
	inicializar_variables(hash, capacidad);
	size_t pos;
	for (size_t i = 0; i < ant_capacidad; i++) {
		if (ant_campos[i].estado == ocupado) {
			pos = buscar_posicion_clave(hash, ant_campos[i].clave);
			guardar_campo(hash, ant_campos[i].clave, ant_campos[i].valor, pos);
		}
	}
	
	free(ant_campos);
	return true;
}

/* ******************************************************************
 *                        PRIMITIVAS DEL HASH
 * *****************************************************************/

hash_t *hash_crear(hash_destruir_dato_t destruir_dato) {
	hash_t* hash = malloc(sizeof(hash_t));
	
	if (!hash) {
		return NULL;
	}
	
	hash->campos = malloc(sizeof(campos_t) * CAPACIDAD_INICIAL);
	if (!hash->campos) {
		free(hash);
		return NULL;
	}
	
	inicializar_variables(hash, CAPACIDAD_INICIAL);
	hash->destruir_dato = destruir_dato;
	return hash;
}

bool hash_guardar(hash_t *hash, const char *clave, void *dato) {
	char* clave_aux = strdup(clave);
	
	if (!clave_aux) {          
		return false;
	}
	
	if ((hash->cantidad + hash->borrados) == ((hash->capacidad * 70) / 100)){
		if (!redimensionar(hash, hash->capacidad * CONSTANTE_DE_REDIMENSION)) {
			free(clave_aux);
			return false;
		}
	}
	
	size_t pos = buscar_posicion_clave(hash, clave);
	if (hash->campos[pos].estado == ocupado) {
		if (hash->destruir_dato) {
			hash->destruir_dato(hash->campos[pos].valor);
		}
		free(clave_aux);
		hash->campos[pos].valor = dato;
		return true;
	}
	
	guardar_campo(hash, clave_aux, dato, pos);
	return true;
}

void *hash_borrar(hash_t *hash, const char *clave) {
	if ((hash->capacidad > CAPACIDAD_INICIAL) && (((hash->capacidad * 20) / 100) == hash->cantidad)) {
		size_t prox_capacidad;
		if ((hash->capacidad / CONSTANTE_DE_REDIMENSION) <= CAPACIDAD_INICIAL) {
			prox_capacidad = CAPACIDAD_INICIAL;
		} else {
			prox_capacidad = hash->capacidad / CONSTANTE_DE_REDIMENSION; 
		}
		redimensionar(hash, prox_capacidad);
	}
	
	size_t pos = buscar_posicion_clave(hash, clave);
	if (hash->campos[pos].estado != ocupado) {
		return NULL;
	}
	
	hash->campos[pos].estado = borrado;
	hash->borrados++;
	hash->cantidad--;
	free(hash->campos[pos].clave);
	return hash->campos[pos].valor;
}

void *hash_obtener(const hash_t *hash, const char *clave) {
	size_t pos = buscar_posicion_clave(hash, clave);
	
	if (hash->campos[pos].estado == ocupado) {
		return hash->campos[pos].valor;
	}
	
	return NULL;
}

bool hash_pertenece(const hash_t *hash, const char *clave) {
	return (hash->campos[buscar_posicion_clave(hash, clave)].estado == ocupado);
}

size_t hash_cantidad(const hash_t *hash) {
	return hash->cantidad;
}

void hash_destruir(hash_t *hash) {
	size_t pos = 0;
	
	while (hash->cantidad > 0) {
		if (hash->campos[pos].estado == ocupado) {
			if (hash->destruir_dato) {
				hash->destruir_dato(hash_borrar(hash, hash->campos[pos].clave));
			} else {
				hash_borrar(hash, hash->campos[pos].clave);
			}
		}
		obtener_nueva_posicion(hash, &pos);
	}
	
	free(hash->campos);
	free(hash);
}

/* ******************************************************************
 *                        PRIMITIVAS DEL HASH ITERADOR
 * *****************************************************************/

hash_iter_t *hash_iter_crear(const hash_t *hash) {
	hash_iter_t* iter = malloc(sizeof(hash_iter_t));
	
	if (!iter) {
		return NULL;
	}
	
	iter->hash = hash;
	iter->act = 0;
	
	while (iter->act < hash->capacidad) {
		if (hash->campos[iter->act].estado == ocupado) {
			return iter;
		}
		iter->act++;
	}
	
	return iter;
}

bool hash_iter_avanzar(hash_iter_t *iter) {
	if (iter->act == iter->hash->capacidad) {
		return false;
	}
	
	while (iter->act < iter->hash->capacidad) {
		iter->act++;
		if ((iter->act < iter->hash->capacidad) && (iter->hash->campos[iter->act].estado == ocupado)) {
			return true;
		}
	}
	
	return true;
}

const char *hash_iter_ver_actual(const hash_iter_t *iter) {
	if (hash_iter_al_final(iter)) {
		return NULL;
	}
	
	return iter->hash->campos[iter->act].clave;
}

bool hash_iter_al_final(const hash_iter_t *iter) {
	return (iter->act == iter->hash->capacidad);
}

void hash_iter_destruir(hash_iter_t* iter) {
	free(iter);
}
