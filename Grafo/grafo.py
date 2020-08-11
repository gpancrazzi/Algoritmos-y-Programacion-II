from vertice import Vertice
from random import randint

class Grafo(object):
    def __init__(self, dirigido):
        """Se crea el Grafo, es necesario
        indicar true si el mismo es dirigido y false en el caso contrario.
        Post: el grafo esta creado."""
        self.es_dirigido = dirigido
        self.vertices = {}
        self.cantidad_aristas = 0
    
    def agregar_vertice(self, nombre, dato=None):
        """Pre: el grafo esta creado.
        Retorna true si se agrega el vertice, 
        en el caso que el vertice ya se encuentre, retorna false."""
        if nombre in self.vertices: return False
        self.vertices[nombre] = Vertice(nombre, dato)
        return True

    def agregar_arista(self, inicio, fin, peso=None):
        """Pre: el grafo fue creado.
        Retorna true si se creo la arista y false en caso contrario.
        Pos: se agrega una arista al grafo."""
        vertice1 = self.vertices.get(inicio)
        vertice2 = self.vertices.get(fin)
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

    def eliminar_arista(self, inicio, fin):
        """Pre: el grafo fue creado.
        Retorna true si se elimino la arista y false en caso que la arista no exista.
        Pos: se elimina una arista del grafo."""
        vertice1 = self.vertices.get(inicio)
        vertice2 = self.vertices.get(fin)
        if self.vertices_estan_unidos(inicio, fin):
            if self.es_dirigido:
                vertice1.eliminar_union(fin)
                self.cantidad_aristas -= 1
                return True
            vertice1.eliminar_union(fin)
            vertice2.eliminar_union(inicio)
            self.cantidad_aristas -= 1
            return True
        return False
    
    def eliminar_vertice(self, nombre):
        """Pre:el grafo esta creado.
        Elimina el vertice y todas las aristas del mismo.
        Pos: el grafo tiene un vertice menos y se eliminan las aristas del vertice."""
        if nombre in self.vertices:
            if self.es_dirigido:
                for adyacente in self.vertices:
                    self.eliminar_arista(adyacente, nombre)
                    self.eliminar_arista(nombre, adyacente)
            else:
                vertice = self.vertices.get(nombre)
                for adyacente in vertice.iterador_vertice():
                    adyacente = self.vertices.get(adyacente)
                    adyacente.eliminar_union(nombre)
                    self.cantidad_aristas -= 1
            self.vertices.pop(nombre)

    def pertenece_vertice(self, nombre):
        """Indica si el vertice se encuentra en el grafo.
        Pre: el grafo fue creado.
        Retorna true en caso que se encuentre y false en caso contrario."""
        return nombre in self.vertices

    def obtener_vertice(self, nombre):
        """Pre: el grafo fue creado.
        Si existe retorna el vertice y su dato, None en caso contrario."""
        if self.pertenece_vertice(nombre):
            return self.vertices.get(nombre)
        return None

    def vertices_estan_unidos(self, inicio, fin):
        """Indica si dos vertices se encuentran conectados.
        Pre: el grafo fue creado.
        Retorna true en caso que exista la arista o false en caso contrario."""
        if self.pertenece_vertice(inicio) and self.pertenece_vertice(fin):
            if self.es_dirigido:
                return self.vertices.get(inicio).estan_conectados(fin)    
            return self.vertices.get(inicio).estan_conectados(fin) and self.vertices.get(fin).estan_conectados(inicio)
        return False

    def ver_peso_arista(self, inicio, fin):
        """Pre: el grafo existe.
        Se retorna el peso en el caso que la arista exista, None en el caso contrario."""
        vertice1 = self.vertices.get(inicio)
        vertice2 = self.vertices.get(fin)
        if self.vertices_estan_unidos(inicio, fin):
            return vertice1.ver_peso_union(fin)    
        return None

    def obtener_todos_los_vertices(self):
        """Pre: el grafo existe.
        Retorna una lista con todos los vertices."""
        return self.vertices.keys()

    def obtener_todas_las_aristas(self):
        """Pre: el grafo existe.
        Retorna una lista de listas con todas las aristas (inicio, fin y peso).
        Retorna None en el caso que no haya aristas en el grafo."""
        if self.cantidad_aristas == 0: return None
        aristas = []
        for nombre in self.vertices:
            vertice = self.vertices.get(nombre)
            for adyacente in vertice.iterador_vertice():
                arista = []
                arista[0] = nombre
                arista[1] = adyacente
                arista[2] = vertice.ver_peso_union(adyacente)
                aristas.append(arista)
        return aristas

    def obtener_adyacentes(self, nombre):
        """Pre: el grafo existe
        Retorna los adyacentes a un vertice."""
        vertice = self.vertices.get(nombre)
        return vertice.ver_vecinos()

    def cantidad_vertices(self):
        """Pre: el grafo existe.
        Retorna la cantidad de vertices que hay en el grafo."""
        return len(self.vertices)
    
    def cantidad_uniones(self):
        """Pre: el grafo existe.
        Retorna la cantidad de aristas que hay en el grafo."""
        return self.cantidad_aristas

    def vertice_aleatorio(self):
        """Pre: el grafo existe.
        Retorna un vertice al azar, None en caso que el grafo este vacio."""
        if self.self.cantidad_vertices() == 0: return None
        vertices = self.obtener_todos_los_vertices()
        i = randint(0,self.cantidad_vertices() - 1)
        return vertices[i]

    def ver_dato_vertice(self, nombre):
        """Pre: el grafo existe.
        Retorna el dato del vertice."""
        if not nombre in self.vertices: return None
        vertice = self.vertices.get(nombre)
        return vertice.ver_dato()