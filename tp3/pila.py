class Pila:
     def __init__(self):
        """Crea una pila."""
        self.items = []

     def esta_vacia(self):
        """Pre: la pila fue creada.
        Retorna True si la pila esta vacia.
        False en caso contrario."""
        return self.items == []

     def apilar(self, item):
        """Pre: la pila fue creada.
        Apila un elemento en el tope de la pila."""
        self.items.append(item)

     def desapilar(self):
        """Pre: la pila fue creada.
        Desapila el elemento al tope de la pila.
        Retorna el elemento."""
        return self.items.pop()

     def ver_tope(self):
        """Pre: la pila fue creada.
        Retorna el elemento al tope de la pila."""
        return self.items[len(self.items)-1]

     def tamano(self):
        """Pre: la pila fue creada.
        Retorna la cantidad de elementos apilados."""
        return len(self.items)