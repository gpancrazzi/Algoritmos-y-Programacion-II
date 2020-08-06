from vertice import Vertice

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
    
    def eliminar_vertice(self, nombre):
        """Pre:el grafo esta creado.
        Elimina el vertice y todas las aristas del mismo.
        Pos: el grafo tiene un vertice menos y se eliminan las aristas del vertice."""
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

    def agregar_arista(self, inicio, fin, dato=None):
        """Pre: el grafo fue creado.
        Retorna true si se creo la arista y false en caso contrario.
        Pos: se agrega una arista al grafo."""
        vertice1 = self.vertices.get(inicio)
        vertice2 = self.vertices.get(fin)
        if not self.vertices_estan_unidos(inicio, fin):
            if self.es_dirigido:
                vertice1.agregar_union(fin, dato)
                self.cantidad_aristas += 1
                return True
            vertice1.agregar_union(fin, dato)
            vertice2.agregar_union(inicio, dato)
            self.cantidad_aristas += 1
            return True
        return False

    def eliminar_arista(self, nombre1, nombre2):
        """Pre: el grafo fue creado.
        Retorna true si se elimino la arista y false en caso que la arista no exista.
        Pos: se elimina una arista del grafo."""
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

    def obtener_todos_los_vertices(self):
        """Pre: el grafo existe.
        Retorna una lista con todos los vertices."""
        return self.vertices.keys()

    def obtener_adyacentes(self, nombre):
        """Pre: el grafo existe
        Retorna los adyacentes a un vertice."""
        vertice = self.vertices.get(nombre)
        return vertice.ver_vecinos()

    def ver_dato_arista(self, inicio, fin):
        """Pre: el grafo existe.
        Se retorna el dato en el caso que la arista exista, None en el caso contrario."""
        vertice1 = self.vertices.get(inicio)
        vertice2 = self.vertices.get(fin)
        if self.vertices_estan_unidos(inicio, fin):
            return vertice1.ver_dato_union(fin)    
        return None

    def cantidad_vertices(self):
        """Pre: el grafo existe.
        Retorna la cantidad de vertices que hay en el grafo."""
        return len(self.vertices)