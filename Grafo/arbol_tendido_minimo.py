from grafo import Grafo
import queue

def mst_prim(grafo):
    """"""
    vertice = grafo.vertice_aleatorio()
    visitados = set()
    visitados.add(vertice)
    heap = queue.PriorityQueue()
    arbol = Grafo(False)
    for v in grafo.obtener_todos_los_vertices():
        arbol.agregar_vertice(v, grafo.ver_dato_vertice(v))
    for w in grafo.obtener_adyacentes(vertice):
        heap.put((vertice, w), grafo.ver_peso_arista(vertice, w))
    while not heap.empty():
        (v, w) = heap.get()
        if w in visitados: continue
        arbol.agregar_arista(v, w, grafo.ver_peso_arista(v, w))
        visitados.add(w)
        for u in grafo.obtener_adyacentes(w):
            if u not in visitados: heap.put((w, u), grafo.ver_peso_arista(w, u))
    return arbol