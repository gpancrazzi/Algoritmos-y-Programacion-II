from grafo import Grafo

def dfs_ciclo_largo_n(grafo, v, origen, n, visitados, camino_actual):
    """"""
    visitados.add(v)
    if len(camino_actual) == n:
        if origen in grafo.obtener_adyacentes(v): return camino_actual
        return None
    for w in grafo.obtener_adyacentes(v):
        if w in visitados: continue
        solucion = dfs_ciclo_largo_n(grafo, w, origen, n, visitados, camino_actual + [w])
        if solucion: return solucion
    visitados.remove(v)
    return None