from grafo import Grafo
import queue

def reconstruir_camino(padres, origen, destino):
    """Reconstruye el camino efectuado desde 
    el vertice de origen hasta el de destino.
    Se recibe como parametro el diccionario de padres."""
    fin = destino
    recorrido = []
    while fin != origen:
        recorrido.append(fin)
        fin = padres.get(fin)
    recorrido.append(origen)
    recorrido.reverse()
    return camino

def camino_bfs(grafo, origen, fin, visitados, padres, cola):
    """Funcion auxiliar para obtener un camino minimo."""
    visitados.add(origen)
    padres[origen] = None
    cola.put(origen)
    while not cola.empty():
        v = cola.get()
        for w in grafo.obtener_adyacentes(v):
            if w not in visitados:
                visitados.add(w)
                padres[w] = v
                if fin and w == fin: break
                cola.put(w)

def obtener_camino(grafo, origen, fin):
    """Obtiene un camino minimo posible para grafos dirigidos y no pesados.
    Recibe un grafo, un vertice de origen y uno de fin (si no se indica fin
    se asume que se quieren obtener todos los caminos minimos desde el origen).
    Pre: el grafo existe y los vertices de origen y fin tambien.
    Retorna una lista con los vertices del camino."""
    visitados = set()
    padres = {}
    cola = queue.Queue()
    camino_bfs(grafo, origen, fin, visitados, padres, cola)
    return reconstruir_camino(padres, origen, fin)

def actualizar_grafo_residual(grafo_residual, u, v, valor):
    peso_anterior = grafo_residual.ver_peso_arista(u, v)
    if peso_anterior == valor:
        grafo_residual.eliminar_arista(u, v)
    else:
        grafo_residual.eliminar_arista(u, v)
        grafo_residual.agregar_arista(u, v, peso_anterior - valor)
    if not grafo_residual.vertices_estan_unidos(v, u):
        grafo_residual.agregar_arista(v, u, valor)
    else:
        grafo_residual.eliminar_arista(v, u)
        grafo_residual.agregar_arista(v, u, peso_anterior + valor)

def agregar_vertice_ciclo_largo_2(grafo, grafo_copia, v, w, vertice_aux):
    if v in grafo.obtener_adyacentes(w):
        if v in grafo_copia.obtener_adyacentes(w):
            grafo_copia.agregar_vertice(str(vertice_aux), False)
            grafo_copia.agregar_arista(w, str(vertice_aux), grafo_copia.ver_peso_arista(w, v))
            grafo_copia.agregar_arista(str(vertice_aux), v, grafo_copia.ver_peso_arista(w, v))
            grafo_copia.eliminar_arista(w, v)
            return vertice_aux + 1
    return vertice_aux

def modificar_ciclo_largo_2(grafo, grafo_copia):
    vertice_aux = 0
    for v in grafo.obtener_todos_los_vertices():
        for w in grafo.obtener_adyacentes(v):
            if w == v: continue
            vertice_aux = agregar_vertice_ciclo_largo_2(grafo, grafo_copia, v, w, vertice_aux)

def copiar_grafo(grafo):
    grafo_copia = Grafo(True)
    for v in grafo.obtener_todos_los_vertices():
        grafo_copia.agregar_vertice(v, grafo.ver_dato_vertice(v))
    for v in grafo.obtener_todos_los_vertices():
        for w in grafo.obtener_adyacentes(v):
            if w == v: continue #elimino bucles
            grafo_copia.agregar_arista(v, w, grafo.ver_peso_arista(v, w))
    #buscar y modificar los ciclos de largo 2.
    modificar_ciclo_largo_2(grafo, grafo_copia)
    return grafo_copia

def min_peso(grafo, camino):
    p_min = grafo.ver_peso_arista(camino[0], camino[1])
    for i in range(1, len(camino) - 1):
        peso = grafo.ver_peso_arista(camino[i], camino[i + 1])
        if peso < p_min: p_min = peso
    return p_min

def algoritmo_ford_fulkerson(grafo, s, t):
    """"""
    flujo = {}
    for v in grafo.obtener_todos_los_vertices():
        for w in grafo.obtener_adyacentes(v):
            flujo[(v, w)] = 0
    grafo_residual = copiar_grafo(grafo)
    while not (camino = obtener_camino(grafo_residual, s, t)):
        capacidad_residual_camino = min_peso(grafo, camino)
        for i in range(1, len(camino)):
            if camino[i] in grafo.obtener_adyacentes(camino[i - 1]):
                flujo[(camino[i] - 1, camino[i])] += capacidad_residual_camino
                actualizar_grafo_residual(grafo_residual, camino[i - 1], camino[i], capacidad_residual_camino)
            else:
                flujo[(camino[i], camino[i - 1])] -= capacidad_residual_camino
                actualizar_grafo_residual(grafo_residual, camino[i], camino[i - 1], capacidad_residual_camino)
    return flujo