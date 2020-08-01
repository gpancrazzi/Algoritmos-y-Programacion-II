from vertice import Vertice

class Grafo(object):
    def _init_(self, dirigido):
        self.es_dirigido = dirigido
        self.vertices = {}
        self.cantidad_aristas = 0
    def agregar_vertice(self, vertice, dato):
        if (vertice in self.vertices):