class Vertice(object):
    """Representa un vertice de un grafo: sus atributos son:
    nombre, peso y vertices vecinos."""
    def _init_(self, nombre, peso=None):
        """Crea un vertice
        nombre y peso son cadenas, peso es optativo"""
        self.nombre = nombre
        self.peso = peso
        self.vecinos = {}
    
    def ver_nombre(self):
        """Muestra la denominación del vertice"""
        return self.nombre

    def ver_peso(self):
        """Muestra la ponderación del vertice"""
        return self.peso

    def ver_vecinos(self):
        """Muestra los adyacentes del vertice"""
        return self.vecinos.keys()
    
    def agregar_union(self, vertice, peso=None):
        """Agrega un adyacente al vertice"""
        self.vecinos[vertice] = peso

    def eliminar_union(self, vertice):
        """Elimina un adyacente"""
        self.vecinos.pop(vertice)

    def cantidad_uniones(self):
        """"""
        return len(self.vecinos)

    def estan_conectados(self, vertice):
        """"""
        return vertice in self.vecinos

    def iterador_vertice(self):
        """"""
        iterador = iter(self.vecinos)
        return iterador