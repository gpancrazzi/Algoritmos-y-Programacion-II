from grafo import Grafo
from pila import Pila

def minimo(orden1, orden2):
    """"""
    if orden1 <= orden2:
        return orden1
    return orden2

def componente_fuertemente_conexa(grafo, vertice, visitados, pila, apilados, orden, mas_bajo, componentes):
    """"""
    visitados.add(vertice)
    pila.apilar(vertice)
    apilados.add(vertice)
    mas_bajo[vertice] = orden[vertice]
    for adyacente in grafo.obtener_adyacentes(vertice):
        if adyacente not in visitados:
            orden[adyacente] = orden[vertice] + 1
            componente_fuertemente_conexa(grafo, adyacente, visitados, pila, apilados, orden, mas_bajo, componentes)
            mas_bajo[vertice] = minimo(mas_bajo[vertice], mas_bajo[adyacente])
        else if adyacente in apilados:
            mas_bajo[vertice] = minimo(mas_bajo[vertice], mas_bajo[adyacente])
    if mas_bajo[vertice] == orden[vertice]:
        nueva_cfc = []
        componente = pila.desapilar()
        apilados.remove(componente)
        nueva_cfc.append(componente)
        while componente != vertice:
            componente = pila.desapilar()
            apilados.remove(componente)
            nueva_cfc.append(componente)
        componentes.append(nueva_cfc)