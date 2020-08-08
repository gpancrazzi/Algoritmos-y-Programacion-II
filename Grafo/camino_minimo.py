from grafo import Grafo
import queue

#grafo pesado
#grafo no pesado: usar un recorrido bfs

def dijkstra(grafo, origen):
    """"""
    distancia = {}
    padre = {}
    INFINITO = -1
    for vertice in grafo:
        distancia[vertice] = INFINITO
    distancia[origen] = 0
    padre[origen] = None
    heap = queue.PriorityQueue()
    heap.put(origen, distancia[origen])
    while not heap.empty():
        vertice = heap.get()
        for adyacente in grafo.obtener_adyacentes(vertice):
            if distancia[adyacente] == INFINITO or distancia[vertice] + grafo.ver_peso_arista(vertice, adyacente) < distancia[adyacente]:
                distancia[adyacente] = distancia[vertice] + grafo.ver_peso_arista(vertice, adyacente)
                padre[adyacente] = vertice
                heap.put(adyacente, distancia[adyacente])
    return padre, distancia