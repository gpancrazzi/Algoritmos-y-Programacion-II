from grafo import Grafo

def prueba_grafo_crear():
    grafo1=Grafo(False)
    if grafo1: print('Prueba grafo crear... Ok')
    if not grafo1.es_dirigido: print('Prueba grafo no es dirigido... Ok')
    grafo1.es_dirigido = True
    if grafo1.es_dirigido: print('Prueba grafo es dirigido... Ok')

prueba_grafo_crear()

