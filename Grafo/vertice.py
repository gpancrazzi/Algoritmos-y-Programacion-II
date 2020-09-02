class Vertice(object):
    """Representa un vertice de un grafo: sus atributos son:
    nombre, dato y vertices vecinos."""
    def __init__(self, nombre, dato=None):
        """Crea un vertice
        nombre y dato son cadenas, dato es optativo"""
        self.nombre = nombre
        self.dato = dato
        self.vecinos = {}
    
    def ver_nombre(self):
        """Pre: el vertice existe.
        Muestra la denominación del vertice"""
        return self.nombre

    def ver_dato(self):
        """Pre: el vertice existe.
        Muestra el dato del vertice"""
        return self.dato

    def ver_vecinos(self):
        """Pre: el vertice existe.
        Muestra los adyacentes del vertice"""
        return self.vecinos.keys()
    
    def agregar_union(self, vertice, peso=None):
        """Pre: el vertice existe.
        Agrega un adyacente al vertice"""
        self.vecinos[vertice] = peso

    def eliminar_union(self, vertice):
        """Pre: el vertice existe y la arista existen.
        Elimina un adyacente"""
        self.vecinos.pop(vertice)

    def ver_peso_union(self, vertice):
        """Pre: el vertice y la arista existen.
        Muestra el dato de la unión de los vertices."""
        return self.vecinos.get(vertice)

    def cantidad_uniones(self):
        """Pre: el vertice existe.
        Se muestran la cantidad de adyacentes que tiene el vertice."""
        return len(self.vecinos)

    def estan_conectados(self, vertice):
        """Pre: los vertices existen.
        Retorna true si existe una arista entre ambos vertices y false en caso contrario."""
        return vertice in self.vecinos

    def cambiar_dato(self, dato):
        """Pre: el vertice existe.
        Modifica el dato del vertice."""
        self.dato = dato

    def iterador_vertice(self):
        """Pre: el vertice existe.
        Retorna un iterador para recorrer los adyacentes al vertice."""
        return iter(self.vecinos)