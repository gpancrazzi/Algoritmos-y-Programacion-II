import queue
from grafo import Grafo
from pila import Pila

###############################################################################
#                       FUNCIONES AUXILIARES                                  #
###############################################################################

def camino_bfs(grafo, origen, fin, visitados, padres, orden, cola):
    """Funcion auxiliar para obtener un camino minimo."""
    visitados.add(origen)
    padres[origen] = None
    orden[origen] = 0
    cola.put(origen)
    while not cola.empty():
        v = cola.get()
        for w in grafo.obtener_adyacentes(v):
            if w not in visitados:
                visitados.add(w)
                padres[w] = v
                orden[w] = orden[v] + 1
                if fin and w == fin: break
                cola.put(w)

def rango_bfs(grafo, origen, n, visitados, orden, cola):
    """Funcion auxiliar para ser utilizada para obtener vertices en rango."""
    visitados.add(origen)
    orden[origen] = 0
    cola.put(origen)
    while not cola.empty():
        v = cola.get()
        for w in grafo.obtener_adyacentes(v):
            if w not in visitados:
                visitados.add(w)
                orden[w] = orden[v] + 1
                if orden.get(w) > n: continue
                cola.put(w)

def dfs_ciclo_largo_n(grafo, v, origen, n, visitados, camino_actual):
    """Funcion auxiliar para obtener un ciclo de largo n."""
    visitados.add(v)
    if len(camino_actual) == n:
        if origen in grafo.obtener_adyacentes(v): return camino_actual
        visitados.remove(v)
        return None
    for w in grafo.obtener_adyacentes(v):
        if w in visitados: continue
        solucion = dfs_ciclo_largo_n(grafo, w, origen, n, visitados, camino_actual + [w])
        if solucion: return solucion
    visitados.remove(v)
    return None

def minimo(orden1, orden2):
    """Funcion auxiliar para calcular componentes fuertemente conexas."""
    if orden1 <= orden2:
        return orden1
    return orden2

def armar_nueva_cfc(pila, apilados, nueva_cfc):
    """Funcion auxiliar para calcular componentes fuertemente conexas."""
    v = pila.desapilar()
    apilados.remove(v)
    nueva_cfc.append(v)
    return v

def algoritmo_tarjan(grafo, v, visitados, pila, apilados, orden, mas_bajo, cfc):
    visitados.add(v)
    pila.apilar(v)
    apilados.add(v)
    mas_bajo[v] = orden[v]
    for w in grafo.obtener_adyacentes(v):
        if w not in visitados:
            orden[w] = orden[v] + 1
            algoritmo_tarjan(grafo, w, visitados, pila, apilados, orden, mas_bajo, cfc)
            mas_bajo[v] = minimo(mas_bajo[v], mas_bajo[w])
        elif w in apilados:
            mas_bajo[v] = minimo(mas_bajo[v], mas_bajo[w])
    if mas_bajo[v] == orden[v]:
        nueva_cfc = []
        w = armar_nueva_cfc(pila, apilados, nueva_cfc)
        while w != v:
            w = armar_nueva_cfc(pila, apilados, nueva_cfc)
        cfc.append(nueva_cfc)

def calcular_arista_de_arista(grafo, vertice):
    """Funcion auxiliar para calcular el coeficiente de clustering."""
    cant_aristas = 0
    bucle = 0
    for v in grafo.obtener_adyacentes(vertice):
        if v == vertice: 
            bucle += 1
            continue
        for w in grafo.obtener_adyacentes(v):
            if w == v: continue
            if w == vertice: continue
            if grafo.vertices_estan_unidos(vertice, w): cant_aristas += 1
    return cant_aristas, bucle

###############################################################################
#                       FUNCIONES A USAR POR TDA GRAFO                        #
###############################################################################

def camino_minimo_bfs(grafo, origen, fin=None):
    """Obtiene un camino minimo posible para grafos dirigidos y no pesados.
    Recibe un grafo, un vertice de origen y uno de fin (si no se indica fin
    se asume que se quieren obtener todos los caminos minimos desde el origen).
    Pre: el grafo existe y los vertices de origen y fin tambien.
    Retorna dos diccionarios, uno con la distancia de cada vertice al origen
    y otro con los padres de cada vertice."""
    visitados = set()
    padres = {}
    orden = {}
    cola = queue.Queue()
    camino_bfs(grafo, origen, fin, visitados, padres, orden, cola)
    return padres, orden

def vertices_rango_n(grafo, origen, n):
    """Obtiene la cantidad de vertices que se encuentran
    a exacta distancia n del vertice de origen.
    Pre: el grafo existe y el origen es un vertice del grafo.
    Retorna la cantidad de vertices en rango."""
    visitados = set()
    orden = {}
    cola = queue.Queue()
    rango_bfs(grafo, origen, n, visitados, orden, cola)
    en_rango = list(orden.values())
    return en_rango.count(n)

def ciclo_largo_n(grafo, origen, n):
    """Calcula un ciclo de largo especificado n.
    Pre: el grafo existe.
    Retorna una lista con los vertices que forman el ciclo."""
    if not origen in grafo.obtener_todos_los_vertices(): return None
    visitados = set()
    camino = []
    camino.append(origen)
    return dfs_ciclo_largo_n(grafo, origen, origen, n, visitados, camino)
            
def componente_fuertemente_conexa(grafo):
    """Calcula las componentes fuertemente conexas de todo el grafo.
    Pre: el grafo existe.
    Retorna una lista de listas, donde cada lista representa una componente."""
    visitados = set()
    pila = Pila()
    apilados = set()
    mas_bajo = {}
    orden = {}
    cfc = []
    for v in grafo.obtener_todos_los_vertices(): 
        orden[v] = 0
        if v not in visitados: algoritmo_tarjan(grafo, v, visitados, pila, apilados, orden, mas_bajo, cfc)
    return cfc

def clustering(grafo, vertice=None):
    """Calcula el coeficiente de clustering de un vertice para un grafo dirigido.
    Si no se especifica vertice, se calcula el clustering promedio de todo el grafo.
    Pre: el grafo y el vertice existen.
    Retorna el coeficiente."""
    cant_ady = 0
    if vertice: cant_ady = len(grafo.obtener_adyacentes(vertice))
    if vertice and cant_ady < 2: return 0
    if vertice:
        cant_aristas_aristas, bucle = calcular_arista_de_arista(grafo, vertice)
        cant_ady = cant_ady - bucle
        if cant_ady < 2: return 0
        max_ady = cant_ady * (cant_ady - 1)
        return float(cant_aristas_aristas) / float(max_ady)
    cant_vertices = grafo.cantidad_vertices()
    sum_clustering = 0
    for v in grafo.obtener_todos_los_vertices():
        sum_clustering += clustering(grafo, v)
    return sum_clustering / float(cant_vertices)

def obtener_grados_de_entrada(grafo):
    """Permite obtener el grado de entrada de cada vertice en el grafo.
    Retorna un diccionario con los vertices como clave y como valor el grado de entrada."""
    grados = {}
    for v in grafo.obtener_todos_los_vertices():
        grados[v] = 0
    for v in grafo.obtener_todos_los_vertices():
        for w in grafo.obtener_adyacentes(v):
            grados[w] += 1
    return grados

def orden_topologico(grafo):
    """Permite obtener un orden topologico posible.
    Retorna una lista con el orden.
    En caso que haya un ciclo, retorna None."""
    grados = obtener_grados_de_entrada(grafo)
    cola = queue.Queue()
    for v in grafo.obtener_todos_los_vertices():
        if grados[v] == 0: cola.put(v)
    resultado = []
    while not cola.empty():
        v = cola.get()
        resultado.append(v)
        for w in grafo.obtener_adyacentes(v):
            grados[w] -= 1
            if grados[w] == 0: cola.put(w)
    if len(resultado) == grafo.cantidad_vertices():
        return resultado
    return None
    
def diametro_grafo(grafo):
    """Permite calcular el camino mínimo más grande del grafo para grafos no pesados.
    Retorna el vertice de origen, de fin y el numero total de vertices en el diametro."""
    orden_max = 0
    origen_max = None
    destino_max = None
    caminos = {}
    for v in grafo.obtener_todos_los_vertices():
        (padres, ordenes) = camino_minimo_bfs(grafo, v)
        caminos[v] = ordenes
    for v in caminos:
        camino = caminos.get(v)
        for w in camino:
            distancia = camino.get(w)
            if distancia > orden_max:
                orden_max = distancia
                origen_max = v
                destino_max = w
    return origen_max, destino_max, orden_max