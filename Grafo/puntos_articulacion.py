from grafo import Grafo

def minimo(orden1, orden2):
    if orden1 <= orden2: return orden1
    return orden2

def calcular_puntos_articulacion(grafo, v, visitados, es_raiz, orden, mas_bajo, p_articulacion):
    visitados.add(v)
    mas_bajo[v] = orden[v]
    hijos = 0
    for w in grafo.obtener_adyacentes(v):
        if w not in visitados:
            orden[w] = orden[v] + 1
            hijos += 1
            calcular_puntos_articulacion(grafo, w, visitados, False, orden, mas_bajo, p_articulacion)
            if mas_bajo[w] >= orden[v]:
                p_articulacion.add(v)
            mas_bajo[v] = minimo(mas_bajo[v], mas_bajo[w])
        else:
            mas_bajo[v] = minimo(mas_bajo[v], mas_bajo[w])
    if es_raiz and hijos > 1:
        p_articulacion.add(v)

def puntos_articulacion(grafo):
    """Calcula los puntos de articulación de un grafo.
    Un punto de articulación es un vertice que, si lo quitamos del grafo, 
    separa en dos o mas componentes conexas dicho grafo.
    Retorna un conjunto con los vertices o None en caso que no haya puntos de articulación."""
    visitados = set()
    mas_bajo = {}
    p_articulacion = set()
    orden = {}
    for v in grafo.obtener_todos_los_vertices():
        if v not in visitados:
            orden[v] = 0
            calcular_puntos_articulacion(grafo, v, visitados, True, orden, mas_bajo, p_articulacion)
    if p_articulacion: return p_articulacion        
    return None