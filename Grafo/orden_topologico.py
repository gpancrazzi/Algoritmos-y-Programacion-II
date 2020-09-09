from grafo import Grafo
from pila import Pila
import queue

def obtener_grados_de_entrada(grafo, grados):
    for v in grafo.obtener_todos_los_vertices():
        grados[v] = 0
    for v in grafo.obtener_todos_los_vertices():
        for w in grafo.obtener_adyacentes(v):
            grados[w] = grados[w] + 1

def orden_topologico_bfs(grafo):
    """Retorna una lista con un orden topologico posible.
    En caso de hallar un ciclo, retorna None."""
    grados = {}
    obtener_grados_de_entrada(grafo, grados)
    cola = queue.Queue()
    for v in grafo.obtener_todos_los_vertices():
        if grados[v] == 0:
            cola.put(v)
    resultado = []
    while not cola.empty():
        v = cola.get()
        resultado.append(v)
        for w in grafo.obtener_adyacentes(v):
            grados[w] -= 1
            if grados[w] == 0:
                cola.put(w)
    if len(resultado) == grafo.cantidad_vertices():
        return resultado
    return None

def orden_topologico_recursivo(grafo, v, pila, visitados):
    visitados.add(v)
    for w in grafo.obtener_adyacentes(v):
        if w not in visitados:
            orden_topologico_recursivo(grafo, v, pila, visitados)
    pila.apilar(v)

def orden_topologico_dfs(grafo):
    """Retorna una lista con un orden topologico posible.
    En caso de hallar un ciclo, retorna None."""
    visitados = set()
    pila = Pila()
    for v in grafo.obtener_todos_los_vertices():
        if v not in visitados:
            orden_topologico_recursivo(grafo, v, pila, visitados)
    return pila