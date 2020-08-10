from grafo import Grafo
import queue

#grafo pesado con pesos positivos: usar dijkstra
#grafo pesado, dirigido, con pesos negarivos: usar bellman-ford
#grafo no pesado: usar un recorrido bfs
#Orden de dijkstra O(e log(v)) siendo e la cantidad de aristas y v la cantidad de vertices.
#Orden de bellman-ford O(e * v) siendo e la cantidad de aristas y v la cantidad de vertices.

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

def bellman_ford(grafo, origen):
    """"""
    distancia = {}
    padre = {}
    INFINITO = 'INFINITO'
    for vertice in grafo:
        distancia[vertice] = INFINITO
    distancia[origen] = 0
    padre[origen] = None
    aristas = grafo.obtener_todas_las_aristas()
    for i in range(grafo.cantidad_vertices()):
        for v, w, peso in aristas:
            if distancia[v] == INFINITO: continue
            if (distancia[v] != INFINITO and distancia[w] == INFINITO) or (distancia[w] != INFINITO and distancia[v] + peso < distancia[w]):
                padre[w] = v
                distancia[w] = distancia[v] + peso
    for v, w, peso in aristas:
        if distancia[v] + peso < distancia[w]: return None #ciclo negativo
    return padre, distancia