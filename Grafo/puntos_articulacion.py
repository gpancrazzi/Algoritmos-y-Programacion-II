from grafo import Grafo

#recordar inicializar mas_bajo con el diccionario de orden obtenido con el recorrido dfs o bfs

def minimo(orden1, orden2):
    """"""
    if orden1 <= orden2:
        return orden1
    return orden2

def puntos_articulacion(grafo, vertice, visitados, es_raiz, orden, mas_bajo, p_articulacion):
    """"""
    visitados.add(vertice)
    hijos = 0
    for adyacente in grafo.obtener_adyacentes(vertice):
        if adyacente not in visitados:
            orden[adyacente] = orden[vertice] + 1
            hijos += 1
            puntos_articulacion(grafo, adyacente, visitados, False, orden, mas_bajo, p_articulacion)
            if mas_bajo[adyacente] >= orden[vertice]:
                p_articulacion.add(vertice)
            mas_bajo[vertice] = minimo(mas_bajo[vertice], mas_bajo[adyacente])
        else:
            mas_bajo[vertice] = minimo(mas_bajo[vertice], mas_bajo[adyacente])
    if es_raiz and hijos > 1:
        p_articulacion.add(vertice)