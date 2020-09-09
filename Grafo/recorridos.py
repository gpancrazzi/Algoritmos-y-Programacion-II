import queue
from grafo import Grafo

def recorrido_bfs(grafo, origen, visitados, padres, orden, cola):
    visitados.add(origen)
    padres[origen] = None
    orden[origen] = 0
    cola.put(origen)
    while not cola.empty():
        v = cola.get()
        for w in grafo.obtener_adyacentes(v):
            if w not in visitados:
                visitados.add(w)
                padres[w] = v
                orden[w] = orden[v] + 1
                cola.put(w)

def bfs(grafo, origen):
    """Recorrido de un grafo en ancho.
    Se recibe el grafo y un vertice de origen.
    Retorna un diccionario con los padres de cada vertice y
    un diccionario con el orden de cada vertice en relación al origen indicado."""
    visitados = set()
    padres = {}
    orden = {}
    cola = queue.Queue()
    recorrido_bfs(grafo, origen, visitados, padres, orden, cola)
    for v in grafo.obtener_todos_los_vertices():
        if v not in visitados:
            recorrido_bfs(grafo, v, visitados, padres, orden, cola)
    return padres, orden

def recorrido_dfs(grafo, v, visitados, padres, orden):
    visitados.add(v)
    for w in grafo.obtener_adyacentes(v):
        if w not in visitados:
            padres[w] = v
            orden[w] = orden[v] + 1
            recorrido_dfs(grafo, w, visitados, padres, orden)

def dfs(grafo):
    """Recorrido de un grafo en profundidad.
    Se recibe el grafo y un vertice de origen.
    Retorna un diccionario con los padres de cada vertice y
    un diccionario con el orden de cada vertice en relación al origen indicado."""
    visitados = set()
    padres = {}
    orden = {}
    for v in grafo.obtener_todos_los_vertices():
        if v not in visitados:
            padres[v] = None
            orden[v] = 0
            recorrido_dfs(grafo, v, visitados, padres, orden)
    return padres, orden