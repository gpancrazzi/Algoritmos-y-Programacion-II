#ifndef ABB_H
#define ABB_H

#include <stdbool.h>
#include <stddef.h>

struct abb;
struct abb_iter;

typedef struct abb abb_t;
typedef struct abb_iter abb_iter_t;

// tipo de funcion para destruir comparar claves.
typedef int (*abb_comparar_clave_t) (const char *, const char *);
// tipo de funcion para destruir dato.
typedef void (*abb_destruir_dato_t) (void *);

/* Crea el arbol binario de busqueda.
*/
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato);

/* Guarda un elemento en el abb, si la clave ya se encuentra en la
 * estructura, la reemplaza. De no poder guardarlo devuelve false.
 * Pre: La estructura abb fue inicializada
 * Post: Se almacena el par (clave, dato).
 */
bool abb_guardar(abb_t *arbol, const char *clave, void *dato);

/* Borra un elemento del abb y devuelve el dato asociado.  Devuelve
 * NULL si el dato no estaba.
 * Pre: La estructura abb fue inicializada
 * Post: El elemento fue borrado de la estructura y se lo devolvia,
 * en el caso de que estuviera guardado.
 */
void *abb_borrar(abb_t *arbol, const char *clave);

/* Obtiene el valor de un elemento del abb, si la clave no se encuentra
 * devuelve NULL.
 * Pre: La estructura abb fue inicializada
 */
void *abb_obtener(const abb_t *arbol, const char *clave);

/* Determina si la clave pertenece o no al abb.
 * Pre: La estructura abb fue inicializada
 */
bool abb_pertenece(const abb_t *arbol, const char *clave);

/* Devuelve la cantidad de elementos del abb.
 * Pre: La estructura abb fue inicializada
 */
size_t abb_cantidad(abb_t *arbol);

/* Destruye la estructura liberando la memoria pedida y llamando a la funcion
 * destruir para cada par (clave, dato).
 * Pre: La estructura abb fue inicializada
 * Post: La estructura abb fue destruida
 */
void abb_destruir(abb_t *arbol);

/* Recorre cada elemento del abb, desde el primero hasta el ultimo o hasta el indicado por la funcion visitar  
 * y realiza las acciones que se especifiquen en dicha funcion. 
 * Pre: la estructura abb fue inicializada, extra es una variable o NULL segun el caso.
 */
void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra);

/* Iterador del abb */

// Crea iterador
abb_iter_t *abb_iter_in_crear(const abb_t *arbol);

// Avanza iterador
bool abb_iter_in_avanzar(abb_iter_t *iter);

// Devuelve clave actual, esa clave no se puede modificar ni liberar.
const char *abb_iter_in_ver_actual(const abb_iter_t *iter);

// Comprueba si termino la iteracion
bool abb_iter_in_al_final(const abb_iter_t *iter);

// Destruye iterador
void abb_iter_in_destruir(abb_iter_t* iter);

#endif // ABB_H
