from grafo import Grafo
from testing import print_test

def prueba_grafo_crear():
    grafo1 = Grafo(False)
    print_test('Prueba grafo crear', grafo1)
    print_test('Prueba grafo no es dirigido', not grafo1.es_dirigido)
    grafo1.es_dirigido = True
    print_test('Prueba grafo es dirigido', grafo1.es_dirigido)

def prueba_grafo_dirigido():
    grafo1 = Grafo(True)
    equipos = ['River', 'Boca', 'Independiente', 'San Lorenzo', 'Racing']
    for equipo in equipos:
        grafo1.agregar_vertice(equipo, None)
    print_test('Prueba grafo dirigido no hay arista entre dos vertices', not grafo1.vertices_estan_unidos(equipos[0], equipos[2]))
    for i in [2,3,4]:
        grafo1.agregar_arista(equipos[0], equipos[i], None)
    for i in [0,2,4]:
        grafo1.agregar_arista(equipos[1], equipos[i], None)
    for i in [3,4]:
        grafo1.agregar_arista(equipos[2], equipos[i], None)
    grafo1.agregar_arista(equipos[3], equipos[1], None)
    grafo1.agregar_arista(equipos[4], equipos[3], None)
    print_test('Prueba grafo dirigido se agregan aristas y la cantidad de aristas es la correcta', grafo1.cantidad_aristas == 10)
    print_test('Prueba grafo dirigido la cantidad de vertices es la correcta', grafo1.cantidad_vertices() == 5)
    hijos_river = grafo1.obtener_adyacentes(equipos[0])
    river_padre = {'Independiente', 'San Lorenzo', 'Racing'}
    ok = True
    for hijo in hijos_river:
        ok = hijo in river_padre
    print_test('Prueba grafo dirigido obtener adyacentes a un vertice retorna los valores correctos', ok)
    grafo1.eliminar_vertice(equipos[4])
    print_test('Prueba grafo dirigido se elimina un vertice', not grafo1.pertenece_vertice(equipos[4]))
    print_test('Prueba grafo dirigido se elimina un vertice y la cantidad de aristas es la correcta', grafo1.cantidad_uniones() == 6)
    print_test('Prueba grafo dirigido arista ya no existe', not grafo1.vertices_estan_unidos(equipos[4], equipos[3]))
    print_test('Prueba grafo dirigido arista ya no existe', not grafo1.vertices_estan_unidos(equipos[0], equipos[4]))

def prueba_grafo_no_dirigido():
    grafo1 = Grafo(False)
    paises = ['Argentina', 'Brasil', 'Chile', 'Bolivia', 'Paraguay', 'Uruguay']
    for pais in paises:
        grafo1.agregar_vertice(pais, None)
    for i in [1,2,3,4,5]:
        grafo1.agregar_arista(paises[0], paises[i])
    print_test('Prueba grafo no dirigido', not grafo1.es_dirigido)
    print_test('Prueba grafo no dirigido la cantidad de vertices es la correcta', grafo1.cantidad_vertices() == 6)
    print_test('Prueba grafo no dirigido la cantidad de aristas es la correcta', grafo1.cantidad_uniones() == 5)
    grafo1.eliminar_vertice(paises[0])
    print_test('Prueba grafo no dirigido se elimina un vertice', not grafo1.pertenece_vertice(paises[0]))
    print_test('Prueba grafo no dirigido se elimina un vertice y la cantidad de aristas es la correcta', grafo1.cantidad_uniones() == 0)
    print_test('Prueba grafo no dirigido arista ya no existe', not grafo1.vertices_estan_unidos(paises[0], paises[3]))

print("~~~ PRUEBAS ALUMNO ~~~")
prueba_grafo_crear()
prueba_grafo_dirigido()
prueba_grafo_no_dirigido()