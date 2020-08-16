import queue
from grafo import Grafo

def camino_bfs(grafo, origen, fin, visitados, padres, orden, cola):
    visitados.add(origen)
    padres[origen] = None
    orden[origen] = 0
    cola.put(origen)
    while not cola.empty():
        v = cola.get()
        for w in grafo.obtener_adyacentes(v):
            if w not in visitados:
                visitados.add(w)
                padres[w] = v
                orden[w] = orden[v] + 1
                if fin and w == fin: break
                cola.put(w)

def camino_minimo_bfs(grafo, origen, fin=None):
    """"""
    visitados = set()
    padres = {}
    orden = {}
    cola = queue.Queue()
    camino_bfs(grafo, origen, fin, visitados, padres, orden, cola)
    return padres, orden

def recorrido_bfs(grafo, origen, n, visitados, orden, cola):
    visitados.add(origen)
    orden[origen] = 0
    cola.put(origen)
    while not cola.empty():
        v = cola.get()
        for w in grafo.obtener_adyacentes(v):
            if w not in visitados:
                visitados.add(w)
                orden[w] = orden[v] + 1
                if orden.get(w) > n: continue
                cola.put(w)

def vertices_rango_n(grafo, origen, n):
    """"""
    visitados = set()
    orden = {}
    cola = queue.Queue()
    recorrido_bfs(grafo, origen, n, visitados, orden, cola)
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

def camino_maximo(ordenes):
    destino = None
    orden = None
    for v in ordenes:
        if not orden or ordenes.get(v) > orden:
            orden = ordenes.get(v)
            destino = v
    return destino, orden

def diametro_grafo(grafo):
    """"""
    origen_max = None
    destino_max = None
    orden_max = None
    padres_max = {}
    for v in grafo.obtener_todos_los_vertices():
        (padres, ordenes) = camino_minimo_bfs(grafo, v)
        (destino, orden) = camino_maximo(ordenes)
        if not orden_max or orden > orden_max:
            origen_max = v
            destino_max = destino
            orden_max = orden
            padres_max = padres.copy()
    return padres_max, origen_max, destino_max, orden_max