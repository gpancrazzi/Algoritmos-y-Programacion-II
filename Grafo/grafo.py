from vertice import Vertice

class Grafo(object):
    def __init__(self, dirigido):
        """"""
        self.es_dirigido = dirigido
        self.vertices = {}
        self.cantidad_aristas = 0
    
    def agregar_vertice(self, nombre, dato):
        """"""
        if nombre in self.vertices: return False
        self.vertices[nombre] = Vertice(nombre, dato)
        return True
    
    def eliminar_vertice(self, nombre):
        """"""
        vertice = self.vertices.pop(nombre)
        if vertice:
            if self.es_dirigido:
                for adyacente in self.vertices:
                    if adyacente.estan_conectados(nombre):
                        adyacente.eliminar_union(nombre)
                        self.cantidad_aristas -= 1
            else:
                for adyacente in vertice.iterador_vertice():
                    adyacente.eliminar_union(nombre)
                    self.cantidad_aristas -= 1
            self.cantidad_aristas -= vertice.cantidad_uniones()

    def agregar_arista(self, inicio, fin, peso=None):
        """"""
        vertice1 = self.get(inicio)
        vertice2 = self.get(fin)
        if not self.vertices_estan_unidos(inicio, fin):
            if self.es_dirigido:
                vertice1.agregar_union(fin, peso)
                self.cantidad_aristas += 1
                return True
            vertice1.agregar_union(fin, peso)
            vertice2.agregar_union(inicio, peso)
            self.cantidad_aristas += 1
            return True
        return False

    def eliminar_arista(self, nombre1, nombre2):
        """"""
        vertice1 = self.get(nombre1)
        vertice2 = self.get(nombre2)
        if self.vertices_estan_unidos(nombre1, nombre2):
            if self.es_dirigido:
                vertice1.eliminar_union(nombre2) or vertice2.eliminar_union(nombre1)
                return True
            vertice1.eliminar_union(nombre2)
            vertice2.eliminar_union(nombre1)
            return True
        return False

    def pertenece_vertice(self, nombre):
        """Indica si el vertice se encuentra en el grafo.
        Pre: el grafo fue creado.
        Retorna true en caso que se encuentre y false en caso contrario."""
        return nombre in self.vertices

    def vertices_estan_unidos(self, nombre1, nombre2):
        """Indica si dos vertices se encuentran conectados.
        Pre: el grafo fue creado.
        Retorna true en caso que exista la arista o false en caso contrario."""
        if self.pertenece_vertice(nombre1) and self.pertenece_vertice(nombre2):
            return self.vertices.get(nombre1).estan_conectados(nombre2) or self.vertices.get(nombre2).estan_conectados(nombre1)
        return False

    def obtener_todos_los_vertices(self):
        """"""
        return self.vertices.keys()

    def obtener_adyacentes(self, nombre):
        """"""
        vertice = self.vertices.get(nombre)
        return vertice.ver_vecinos(nombre)

    def ver_peso_vertice(self, nombre):
        """"""
        vertice = self.get(nombre)
        if vertice: return vertice.ver_peso()
        return None