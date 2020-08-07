from grafo import Grafo
from recorridos import bfs
from testing import print_test

def prueba_bfs():
    grafo1 = Grafo(True)
    vertices = ['A', 'B', 'C', 'D', 'E', 'F']
    for v in vertices:
        grafo1.agregar_vertice(v)
    grafo1.agregar_arista(vertices[0], vertices[1])
    grafo1.agregar_arista(vertices[0], vertices[2])
    grafo1.agregar_arista(vertices[1], vertices[2])
    grafo1.agregar_arista(vertices[2], vertices[3])
    grafo1.agregar_arista(vertices[3], vertices[4])
    grafo1.agregar_arista(vertices[3], vertices[5])
    grafo1.agregar_arista(vertices[4], vertices[1])
    recorrido = bfs(grafo1, vertices[0])
    padres = recorrido[0]
    orden = recorrido[1]
    print_test("Prueba BFS el padre del origen es None", not padres[vertices[0]])
    print_test("Prueba BFS el orden del origen es 0", orden[vertices[0]] == 0)
    
    print_test("Prueba BFS el padre del vertice 'B' es el correcto", padres[vertices[1]] == vertices[0])
    print_test("Prueba BFS el orden del vertice 'B' es el correcto", orden[vertices[1]] == 1)

print("~~~ PRUEBAS BFS ~~~")
prueba_bfs()