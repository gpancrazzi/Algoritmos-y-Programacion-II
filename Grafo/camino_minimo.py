from grafo import Grafo
import heapq

#grafo pesado con pesos positivos: usar dijkstra
#grafo pesado, dirigido, con pesos negarivos: usar bellman-ford
#grafo no pesado: usar un recorrido bfs
#Orden de dijkstra O(e log(v)) siendo e la cantidad de aristas y v la cantidad de vertices.
#Orden de bellman-ford O(e * v) siendo e la cantidad de aristas y v la cantidad de vertices.

def dijkstra(grafo, origen):
    """Permite obtener todos los caminos minimos desde el origen 
    pasado por parametro a todos los vertices del grafo.
    Retorna un diccionario con los padres de cada vertice y otro con la distancia de cada vertice al origen."""
    distancia = {}
    padres = {}
    INFINITO = -1
    for v in grafo.obtener_todos_los_vertices():
        distancia[v] = INFINITO
    distancia[origen] = 0
    padres[origen] = None
    heap = []
    heapq.heappush(heap, (distancia[origen], origen))
    while not heap.empty():
        (d, v) = heapq.heappop(heap)
        for w in grafo.obtener_adyacentes(v):
            if distancia[w] == INFINITO or distancia[v] + grafo.ver_peso_arista(v, w) < distancia[w]:
                distancia[w] = distancia[v] + grafo.ver_peso_arista(v, w)
                padres[w] = v
                heapq.heappush(heap, (distancia[w], w))
    return padres, distancia

def bellman_ford(grafo, origen):
    """Permite obtener todos los caminos minimos desde el origen 
    pasado por parametro a todos los vertices del grafo.
    Retorna un diccionario con los padres de cada vertice y otro con la distancia de cada vertice al origen."""
    distancia = {}
    padres = {}
    INFINITO = 'INFINITO'
    for v in grafo.obtener_todos_los_vertices():
        distancia[v] = INFINITO
    distancia[origen] = 0
    padres[origen] = None
    aristas = grafo.obtener_todas_las_aristas()
    for i in range(grafo.cantidad_vertices()):
        for v, w, peso in aristas:
            if distancia[v] == INFINITO: continue
            if (distancia[v] != INFINITO and distancia[w] == INFINITO) or (distancia[w] != INFINITO and distancia[v] + peso < distancia[w]):
                padres[w] = v
                distancia[w] = distancia[v] + peso
    for v, w, peso in aristas:
        if distancia[v] + peso < distancia[w]: return None #ciclo negativo
    return padres, distancia