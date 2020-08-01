from vertice import Vertice

class Grafo(object):
    def _init_(self, dirigido):
        """"""
        self.es_dirigido = dirigido
        self.vertices = {}
        self.cantidad_aristas = 0
    
    def agregar_vertice(self, nombre, dato):
        """"""
        if (nombre in self.vertices): return false
        self.vertices[nombre] = Vertice(nombre, dato)
        return true
    
    def eliminar_vertice(self, nombre):
        """"""
        vertice = self.vertices.pop(nombre)
        if vertice:
            if (self.es_dirigido):
                for adyacente in self.vertices:
                    if adyacente.estan_conectados(vertice):
                        adyacente.eliminar_union(vertice)
                        self.cantidad_aristas -= 1
            else:
                for adyacente in vertice.iterador_vertice():
                    adyacente.eliminar_union(vertice)
                    self.cantidad_aristas -= 1
            self.cantidad_aristas -= vertice.cantidad_uniones()

    def agregar_arista():
        """"""

    def eliminar_arista():
        """"""

    def pertenece_vertice():
        """"""

    def vertices_unidos():
        """"""

    def vertice_al_azar():
        """"""

    def obtener_todos_los_vertices():
        """"""

    def obtener_adyacentes():
        """"""