from grafo import Grafo
from pila import Pila

def minimo(orden1, orden2):
    if orden1 <= orden2: return orden1
    return orden2

def armar_nueva_cfc(pila, apilados, nueva_cfc):
    v = pila.desapilar()
    apilados.remove(v)
    nueva_cfc.append(v)
    return v

def algoritmo_tarjan(grafo, v, visitados, pila, apilados, orden, mas_bajo, componentes):
    visitados.add(v)
    pila.apilar(v)
    apilados.add(v)
    mas_bajo[v] = orden[v]
    for w in grafo.obtener_adyacentes(v):
        if w not in visitados:
            orden[w] = orden[v] + 1
            algoritmo_tarjan(grafo, w, visitados, pila, apilados, orden, mas_bajo, componentes)
            mas_bajo[v] = minimo(mas_bajo[v], mas_bajo[w])
        else if w in apilados:
            mas_bajo[v] = minimo(mas_bajo[v], mas_bajo[w])
    if mas_bajo[v] == orden[v]:
        nueva_cfc = []
        w = armar_nueva_cfc(pila, apilados, nueva_cfc)
        while w != v:
            w = armar_nueva_cfc(pila, apilados, nueva_cfc)
        componentes.append(nueva_cfc)

def componente_fuertemente_conexa(grafo):
    """Calcula las componentes fuertemente conexas de todo el grafo.
    Pre: el grafo existe.
    Retorna una lista de listas, donde cada lista representa una componente."""
    visitados = set()
    pila = Pila()
    apilados = set()
    mas_bajo = {}
    orden = {}
    cfc = []
    for v in grafo.obtener_todos_los_vertices(): 
        orden[v] = 0
        if v not in visitados: algoritmo_tarjan(grafo, v, visitados, pila, apilados, orden, mas_bajo, cfc)
    return cfc