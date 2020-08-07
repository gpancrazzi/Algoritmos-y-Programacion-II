from grafo import Grafo
import queue

def obtener_grados_de_entrada(grafo, grados):
    """"""
    for vertice in grafo.vertices:
        grados[vertice] = 0
    for vertice in grafo.vertices:
        for adyacente in grafo.obtener_adyacentes(vertice):
            grados[adyacente] += 1

def orden_topologico(grafo):
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