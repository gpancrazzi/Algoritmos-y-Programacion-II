from grafo import Grafo
from pila import Pila
import queue

def obtener_grados_de_entrada(grafo, grados):
    """"""
    for vertice in grafo.vertices:
        grados[vertice] = 0
    for vertice in grafo.vertices:
        for adyacente in grafo.obtener_adyacentes(vertice):
            grados[adyacente] += 1

def orden_topologico_bfs(grafo):
    """"""
    grados = {}
    obtener_grados_de_entrada(grafo, grados)
    cola = queue.Queue()
    for vertice in grafo.vertices:
        if grados[vertice] == 0:
            cola.put(vertice)
    resultado = []
    while not cola.empty():
        vertice = cola.get()
        resultado.append(vertice)
        for adyacente in grafo.obtener_adyacentes(vertice):
            grados[adyacente] -= 1
            if grados[vertice] == 0:
                cola.put(adyacente)
    if len(resultado) == grafo.cantidad_vertices():
        return resultado
    return None

def orden_topologico_recursivo(grafo, vertice, pila, visitados):
    """"""
    visitados.add(vertice)
    for adyacente in grafo.obtener_adyacentes(vertice):
        if adyacente not in visitados:
            orden_topologico_recursivo(grafo, vertice, pila, visitados)
    pila.apilar(vertice)

def orden_topologico_dfs(grafo):
    """"""
    visitados = set()
    pila = Pila()
    for vertice in grafo.vertices:
        if vertice not in visitados:
            orden_topologico_recursivo(grafo, vertice, pila, visitados)
    return pila