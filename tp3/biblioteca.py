import queue
from grafo import Grafo

def bfs(grafo, origen, fin, visitados, padres, orden, cola):
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
    bfs(grafo, origen, fin, visitados, padres, orden, cola)
    if fin: return padres, orden
    for vertice in grafo.obtener_todos_los_vertices():
        if vertice not in visitados:
            bfs(grafo, vertice, visitados, padres, orden, cola)
    return padres, orden