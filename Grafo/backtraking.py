from grafo import Grafo

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
    """Calcula un ciclo de largo especificado n.
    Pre: el grafo existe.
    Retorna una lista con los vertices que forman el ciclo."""
    if not origen in grafo.obtener_todos_los_vertices(): return None
    visitados = set()
    camino = []
    camino.append(origen)
    return dfs_ciclo_largo_n(grafo, origen, origen, n, visitados, camino)

def es_compatible(grafo, v, colores):
    for w in grafo.obtener_adyacentes(v):
        if w in colores and colores[w] == colores[v]: return False
    return True

def coloreo(grafo, v, colores, color, k):
    """Verifica si es posible colorear los vertices del grafo con la paleta pasada por parametro.
    Retorna True si es posible y False en caso contrario."""
    colores[v] = color
    if len(colores) == grafo.cantidad_vertices():
        if es_compatible(grafo, v, colores): return True
        colores.remove(v)
        return False
    if not es_compatible(grafo, v, colores):
        colores.remove(v)
        return False
    for w in grafo.obtener_adyacentes(v):
        if w in colores: continue
        for color_opcion in range(k):
            if coloreo(grafo, w, colores, color_opcion, k): return True
    colores.remove(v)
    return False

def camino_hamiltoniano_dfs(grafo, v, visitados, camino):
    visitados.add(v)
    camino.append(v)
    if len(visitados) == grafo.cantidad_vertices(): return True
    for w in grafo.obtener_adyacentes(v):
        if w not in visitados:
            if camino_hamiltoniano_dfs(grafo, w, visitados, camino): return True
    visitados.remove(v)
    camino.pop()
    return False

def camino_hamiltoniano(grafo):
    """Obtiene un camino hamiltoniano.
    Un camino hamiltoniano, es un camino de un grafo, una sucesión de aristas adyacentes, 
    que visita todos los vértices del grafo una sola vez. 
    Si además el último vértice visitado es adyacente al primero, el camino es un ciclo hamiltoniano. 
    Retorna una lista con el camino."""
    camino = []
    visitados = set()
    for v in grafo.obtener_todos_los_vertices():
        if camino_hamiltoniano_dfs(grafo, v, visitados, camino): return camino
    return None