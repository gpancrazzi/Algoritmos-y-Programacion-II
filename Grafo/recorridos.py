import queue
from grafo import Grafo

def bfs(grafo, origen):
    """Recorrido de un grafo en ancho.
    Se recibe el grafo y un vertice de origen.
    Retorna un diccionario con los padres de cada vertice y
    un diccionario con el orden de cada vertice en relación al origen indicado."""
    visitados = set()
    padres = {}
    orden = {}
    cola = queue.Queue()
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
                cola.put(adyacente)
    return padres, orden

def recorrido_dfs(grafo, vertice, visitados, padres, orden):
    visitados.add(vertice)
    for adyacente in grafo.obtener_adyacentes(vertice):
        if adyacente not in visitados:
            padres[adyacente] = vertice
            orden[adyacente] = orden[vertice] + 1
            recorrido_dfs(grafo, adyacente, visitados, padres, orden)

def dfs(grafo):
    """"""
    visitados = set()
    padres = {}
    orden = {}
    for vertice in grafo.vertices:
        if vertice not in visitados:
            padre[vertice] = None
            orden[vertice] = 0
            recorrido_dfs(grafo, vertice, visitados, padres, orden)
    return padres, orden