import queue
from grafo import Grafo
from pila import Pila

def camino_bfs(grafo, origen, fin, visitados, padres, orden, cola):
    visitados.add(origen)
    padres[origen] = None
    orden[origen] = 0
    cola.put(origen)
    while not cola.empty():
        vertice = cola.get()
        for adyacente in grafo.obtener_adyacentes(vertice):
            if adyacente not in visitados:
                visitados.add(adyacente)
                padres[adyacente] = vertice
                orden[adyacente] = orden[vertice] + 1
                if fin and adyacente == fin: break
                cola.put(adyacente)

def camino_minimo_bfs(grafo, origen, fin=None):
    """"""
    visitados = set()
    padres = {}
    orden = {}
    cola = queue.Queue()
    camino_bfs(grafo, origen, fin, visitados, padres, orden, cola)
    if fin: return padres, orden
    for vertice in grafo.obtener_todos_los_vertices():
        if vertice not in visitados:
            camino_bfs(grafo, vertice, visitados, padres, orden, cola)
    return padres, orden

def recorrido_bfs(grafo, origen, visitados, orden, cola):
    visitados.add(origen)
    orden[origen] = 0
    cola.put(origen)
    while not cola.empty():
        v = cola.get()
        for w in grafo.obtener_adyacentes(v):
            if w not in visitados:
                visitados.add(w)
                orden[w] = orden[v] + 1
                cola.put(w)

def vertices_rango_n(grafo, origen, n):
    """"""
    visitados = set()
    orden = {}
    cola = queue.Queue()
    recorrido_bfs(grafo, origen, visitados, orden, cola)
    en_rango = list(orden.values())
    return en_rango.count(n)

def dfs_ciclo_largo_n(grafo, v, origen, n, visitados, camino_actual):
    visitados.add(v)
    if len(camino_actual) == n:
        if origen in grafo.obtener_adyacentes(v): return camino_actual
        visitados.remove(v)
        return None
    for w in grafo.obtener_adyacentes(v):
        if w in visitados: continue
        solucion = dfs_ciclo_largo_n(grafo, w, origen, n, visitados, camino_actual + [w])
        if solucion: return solucion
    visitados.remove(v)
    return None

def ciclo_largo_n(grafo, origen, n):
    """"""
    if not origen in grafo.obtener_todos_los_vertices(): return None
    visitados = set()
    camino = []
    camino.append(origen)
    return dfs_ciclo_largo_n(grafo, origen, origen, n, visitados, camino)