from grafo import Grafo

def prueba_grafo_crear():
    grafo1 = Grafo(False)
    if grafo1: print('Prueba grafo crear... Ok')
    if not grafo1.es_dirigido: print('Prueba grafo no es dirigido... Ok')
    grafo1.es_dirigido = True
    if grafo1.es_dirigido: print('Prueba grafo es dirigido... Ok')

def prueba_grafo_dirigido():
    grafo1 = Grafo(True)
    equipos = ['River', 'Boca', 'Independiente', 'San Lorenzo', 'Racing']
    for equipo in equipos:
        grafo1.agregar_vertice(equipo, None)
    if not grafo1.vertices_estan_unidos(equipos[0], equipos[2]): print('Prueba grafo no hay arista entre dos vertices... Ok')
    grafo1.agregar_arista(equipos[0], equipos[2], None)
    if grafo1.vertices_estan_unidos(equipos[0], equipos[2]) and grafo1.vertices_estan_unidos(equipos[2], equipos[0]): 
        print('Prueba grafo se agrega una arista... Ok')
    if grafo1.cantidad_aristas == 1: print('Prueba grafo la cantidad de aristas es la correcta... Ok')
    if grafo1.cantidad_vertices() == 5: print('Prueba grafo la cantidad de vertices es la correcta... Ok')

prueba_grafo_crear()
prueba_grafo_dirigido()