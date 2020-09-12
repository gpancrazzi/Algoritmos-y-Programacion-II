from grafo import Grafo
import heapq
from union_find import UnionFind
from operator import itemgetter

#Complejidad algoritmo de Prim: O(e log(v)) siendo e la cantidad de aristas y v la cantidad de vertices.
def mst_prim(grafo):
    """Pre: el grafo es no dirigido.
    Retorna un arbol de tendido minimo."""
    vertice = grafo.vertice_aleatorio()
    visitados = set()
    visitados.add(vertice)
    heap = []
    arbol = Grafo(False)
    for v in grafo.obtener_todos_los_vertices():
        arbol.agregar_vertice(v, grafo.ver_dato_vertice(v))
    for w in grafo.obtener_adyacentes(vertice):
        heapq.heappush(heap, (grafo.ver_peso_arista(vertice, w), vertice, w))
    while not heap.empty():
        (p, v, w) = heapq.heappop(heap)
        if w in visitados: continue
        arbol.agregar_arista(v, w, p)
        visitados.add(w)
        for e in grafo.obtener_adyacentes(w):
            if e not in visitados: heapq.heappush(heap, (grafo.ver_peso_arista(w, e), w, e))
    return arbol

#Complejidad algoritmo de Kruskal: O(e log(v)) siendo e la cantidad de aristas y v la cantidad de vertices.
#Hay posibilidad de mejorar la complejidad si se tiene información que permita ordenar las aristas mediante
#un algoritmo de ordenamiento no comparativo.
def mst_kruskal(grafo):
    """Pre: el grafo es no dirigido.
    Retorna un arbol de tendido minimo."""
    conjuntos = UnionFind(grafo.obtener_todos_los_vertices())
    #ordenar las aristas de forma ascendente por peso.
    aristas = sorted(grafo.obtener_todas_las_aristas(), key=itemgetter(2))
    arbol = Grafo(False)
    for v in grafo.obtener_todos_los_vertices():
        arbol.agregar_vertice(v, grafo.ver_dato_vertice(v))
    for v, w, p in aristas:
        if conjuntos.find(v) == conjuntos.find(w): continue
        arbol.agregar_arista(v, w, p)
        conjuntos.union(v, w)
    return arbol