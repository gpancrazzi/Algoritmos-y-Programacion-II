#define _POSIX_C_SOURCE 200809L
#include "lista.h"
#include "strutil.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

bool recorrer_elementos (void *dato, void *extra) {
	fprintf(stdout, "%s\n", (char*)dato);
	return true;
}

bool validar_cantidad_de_parametros(int cant_arg) {
	if ((cant_arg != 3) && (cant_arg != 4)) {
		fprintf(stderr, "Cantidad de parametros erronea\n");
		return false;
	}
	
	return true;
}

bool validar_parametro_numerico(char* num) {
	size_t i = 0;
	
	while (i < (strlen(num))) {
		if (isdigit(num[i]) == 0) {
			fprintf(stderr, "Tipo de parametro incorrecto\n");
			return false;
		}
		i++;
	}
	
	return true;
}

char* obtener_cadena_a_copiar(char* str) {
	size_t largo = strlen(str);
	
	size_t i = largo - 1;
	while ((i > 0) && ((str[i] == '\r') || (str[i] == '\n') || (str[i] == '\0'))) {
		i--;
	}
	
	largo = largo - (largo - (i + 1));
	char* str_aux = substr(str, largo);
	if (str_aux == NULL) {
		return NULL;
	}

	return str_aux;
}

void ubicar_iterador_en_ultimo_elemento(lista_iter_t* lista_iter, lista_t* lista) {
	while (lista_iter_ver_actual(lista_iter) != lista_ver_ultimo(lista)) {
		lista_iter_avanzar(lista_iter);
	}
}

void desenlistar_elementos_sobrantes(lista_iter_t* lista_iter, bool ult_elem_coincide) {
	if (ult_elem_coincide == true) {
		lista_iter_avanzar(lista_iter);
	}
	
	while ((lista_iter != NULL) && (lista_iter_al_final(lista_iter) == false)) {
		free(lista_iter_borrar(lista_iter));
	}
}

void buscar_coincidencia(FILE* archivo, char* str_a_buscar, size_t contexto) {
	lista_t* lista = lista_crear();
	if (lista == NULL) {
		return;
	}
	
	bool coincidencia = false, ult_elem_coincide = false;
	char* cadena = NULL; 
	char* cadena_aux;
	size_t TAM = 0, contexto_aux = 0;
	ssize_t fin_arch = 0;
	lista_iter_t* lista_iter = NULL;
	while (fin_arch != -1) {
		if (archivo != NULL) {
			fin_arch = getline(&cadena, &TAM, archivo);
		} else {
			fin_arch = getline(&cadena, &TAM, stdin);
		}
		if (fin_arch != -1) {
			cadena_aux = obtener_cadena_a_copiar(cadena);
		    if (cadena_aux == NULL) {
			    break;
		    }
		    if (lista_insertar_ultimo(lista, cadena_aux) == false) {
			    coincidencia = false;
			    break;
		    }
		    contexto_aux++;
		    if (strstr(cadena_aux, str_a_buscar) != 0) {
				contexto_aux = 0;
				ult_elem_coincide = true;
				if (coincidencia == false) {
					lista_iter = lista_iter_crear(lista);
				    if (lista_iter == NULL) {
				    	break;
					}
					coincidencia = true;
				}
				ubicar_iterador_en_ultimo_elemento(lista_iter, lista);
			} else if (contexto_aux > contexto) {
			    if (coincidencia == true) {
			    	if (ult_elem_coincide == true) {
			    	    lista_iter_avanzar(lista_iter);
			    		ult_elem_coincide = false;
					}
				    free(lista_iter_borrar(lista_iter));
				} else {
					free(lista_borrar_primero(lista));
				}
			}
		} else {
			desenlistar_elementos_sobrantes(lista_iter, ult_elem_coincide);
		}
	}
	
	if (coincidencia == true) {
		lista_iterar(lista, recorrer_elementos, NULL);
	}
	
	free(cadena);
	lista_iter_destruir(lista_iter);
	lista_destruir(lista, free);
}

int main (int argc, char* argv[]) {
	if (validar_cantidad_de_parametros(argc) == false) {
		return 0;
	}
	
	if (validar_parametro_numerico(argv[2]) == false) {
		return 0;
	}
	
	FILE *archivo = NULL;
	if (argc == 4) {
	    archivo = fopen(argv[3], "rt");
	    if (archivo == NULL) {
		    fprintf(stderr, "No se pudo leer el archivo indicado\n");
		    return 0;
	    }
	    rewind(archivo);
	}
	
	if (archivo != NULL) {
		buscar_coincidencia(archivo, argv[1], atoi(argv[2]));
		fclose(archivo);
	} else {
		buscar_coincidencia(NULL, argv[1], atoi(argv[2]));
	}
	
	return 0;
}
