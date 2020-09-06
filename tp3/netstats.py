#!/usr/bin/python3
from grafo import Grafo
from biblioteca import camino_minimo_bfs, vertices_rango_n, ciclo_largo_n, orden_topologico, pagerank
from biblioteca import componente_fuertemente_conexa, clustering, diametro_grafo, label_propagation
import sys
import constantes
import heapq
sys.setrecursionlimit(999999999)

###############################################################################
#                       FUNCIONES AUXILIARES                                  #
###############################################################################

def limpiar_parametros(linea):
    """Limpia de caracteres de salto de linea 
    los parametros pasados por entrada estandar."""
    parametros = linea.split(',')
    parametros_limpios = []
    for parametro in parametros:
        parametro = parametro.lstrip()
        parametro = parametro.rstrip()
        parametros_limpios.append(parametro)
    return parametros_limpios

def identificar_comando(linea):
    """Identifica el comando y los parametros 
    pasados por entrada estandar."""
    comandos = linea.split(' ', 1)
    comando = comandos.pop(0)
    if not comandos: return comando, None
    linea = "".join(comandos)
    parametros = limpiar_parametros(linea)
    return comando, parametros

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
    camino = constantes.FLECHA.join(recorrido)
    return camino

def obtener_componente(v, cfc, num_cfc):
    """Funcion auxiliar para calcular vertices conectados."""
    num = num_cfc.get(v)
    conectados = cfc.get(num)
    return conectados

def construir_grafo_auxiliar(grafo, parametros):
    """Funcion auxiliar para calcular orden valido de lectura.
    Recibe como parametro un grafo y una lista con vertices del grafo.
    Retorna un grafo con los vertices y conexiones entre los vertices pasados por parametro
    (invertidas según aparecen en el grafo original)."""
    grafo_aux = Grafo(True)
    for v in parametros:
        grafo_aux.agregar_vertice(v)
        for w in grafo.obtener_adyacentes(v):
            if w in parametros:
                grafo_aux.agregar_vertice(w)
                grafo_aux.agregar_arista(w, v)
    return grafo_aux

###############################################################################
#                       COMANDOS DE NETSTATS                                  #
###############################################################################

def listar_operaciones():
    operaciones = ["camino", "conectados", "ciclo", "rango", "navegacion", "clustering",
    "diametro", "lectura", "comunidad", "mas_importantes"]
    for operacion in operaciones:
        print(operacion)

def camino_mas_corto(grafo, parametros):
    origen = parametros.pop(0)
    destino = parametros.pop(0)
    if ((not grafo.pertenece_vertice(origen)) or 
    (not grafo.pertenece_vertice(destino))): 
        print(constantes.SIN_CAMINO)
        return 
    (padres, orden) = camino_minimo_bfs(grafo, origen, destino)
    if not destino in orden:
        print(constantes.SIN_CAMINO)
        return
    camino = reconstruir_camino(padres, origen, destino)
    print(camino)
    print(constantes.COSTO_CAMINO %orden[destino])

def todos_en_rango(grafo, parametros):
    origen = parametros.pop(0)
    n = int(parametros.pop(0))
    en_rango = vertices_rango_n(grafo, origen, n)
    print(en_rango)

def navegacion_primer_link(grafo, parametros):
    v = parametros.pop(0)
    camino = []
    camino.append(v)
    while v:
        if len(camino) == 21: break
        v = grafo.ver_dato_vertice(v)
        if not v: break
        camino.append(v)
    recorrido = constantes.FLECHA.join(camino)
    print(recorrido)

def ciclo_n_articulos(grafo, parametros):
    origen = parametros.pop(0)
    n = int(parametros.pop(0))
    ciclo = ciclo_largo_n(grafo, origen, n)
    if not ciclo:
        print(constantes.SIN_CAMINO)
        return
    ciclo.append(origen)
    recorrido = constantes.FLECHA.join(ciclo)
    print(recorrido)

def calcular_diametro(grafo):
    (origen, destino, orden) = diametro_grafo(grafo)
    (padres, ordenes) = camino_minimo_bfs(grafo, origen, destino)
    diametro = reconstruir_camino(padres, origen, destino)
    print(diametro)
    print(constantes.COSTO_CAMINO %orden)
    return diametro, orden

def calcular_conectividad(grafo, parametros, cfc, num_cfc):
    v = parametros.pop(0)
    if v in num_cfc:
        conectados = obtener_componente(v, cfc, num_cfc)
        print(conectados)
        return
    componentes = componente_fuertemente_conexa(grafo)
    for c in componentes:
        num = len(cfc)
        cfc[num] = constantes.COMA.join(c)
        aux = dict.fromkeys(c,num)
        num_cfc.update(aux)
    componente = obtener_componente(v, cfc, num_cfc)
    print(componente)

def calcular_coeficiente_clustering(grafo, parametros):
    pagina = None
    if parametros: pagina = parametros.pop(0)
    coeficiente = clustering(grafo, pagina)
    print(constantes.COEFICIENTE_CLUSTERING %coeficiente)

def calcular_lectura_2_am(grafo, parametros):
    grafo_aux = construir_grafo_auxiliar(grafo, parametros)
    orden = orden_topologico(grafo_aux)
    if not orden: 
        print(constantes.SIN_LECTURA)
        return
    orden_lectura = constantes.COMA.join(orden)
    print(orden_lectura)

def calcular_comunidad(grafo, parametros, comunidades, num_comunidad):
    pagina = parametros.pop(0)
    if not pagina in comunidades:
        grupos = label_propagation(grafo)
        comunidades.update(grupos)
        for v in comunidades:
            label = comunidades.get(v)
            if not label in num_comunidad:
                comunidad = []
                comunidad.append(v)
                num_comunidad[label] = comunidad
            else:
                grupo = num_comunidad.get(label)
                grupo.append(v)
    num = comunidades.get(pagina)
    conjunto = constantes.COMA.join(num_comunidad.get(num))
    print(conjunto)

def calcular_mas_importantes(grafo, parametros, page_rank, rank_page):
    n = int(parametros.pop(0))
    if not page_rank:
        articulos_importantes = pagerank(grafo)
        page_rank.update(articulos_importantes)
        rank_page.update(dict(zip(articulos_importantes.values(), articulos_importantes.keys())))
    heap = []
    for v in page_rank:
        if not heap or len(heap) < n: 
            heapq.heappush(heap, page_rank.get(v))
            continue
        minimo = heap[0]
        if page_rank.get(v) > minimo:
            heapq.heappop(heap)
            heapq.heappush(heap, page_rank.get(v))
    paginas = []
    while heap:
        coeficiente = heapq.heappop(heap)
        v = rank_page.get(coeficiente)
        paginas.append(v)
    paginas.reverse()
    paginas_importantes = constantes.COMA.join(paginas)
    print(paginas_importantes)

###############################################################################
#                       FUNCIONES PRINCIPALES                                 #
###############################################################################

def procesar_entrada(grafo):
    """Procesa los comandos pasados por entrada estandar."""
    comando = constantes.LISTAR_OPERACIONES
    cfc = {}
    num_cfc = {}
    diametro = None
    costo = 0
    comunidades = {}
    num_comunidad = {}
    rank_page = {}
    page_rank = {}
    while comando:
        try: linea = input()
        except EOFError: break
        (comando, parametros) = identificar_comando(linea)
        if comando == constantes.LISTAR_OPERACIONES: listar_operaciones()
        elif comando == constantes.CAMINO: camino_mas_corto(grafo, parametros)
        elif comando == constantes.RANGO: todos_en_rango(grafo, parametros)
        elif comando == constantes.NAVEGACION: navegacion_primer_link(grafo, parametros)
        elif comando == constantes.CICLO: ciclo_n_articulos(grafo, parametros)
        elif comando == constantes.CONECTADOS: calcular_conectividad(grafo, parametros, cfc, num_cfc)
        elif comando == constantes.CLUSTERING: calcular_coeficiente_clustering(grafo, parametros)
        elif comando == constantes.LECTURA: calcular_lectura_2_am(grafo, parametros)
        elif comando == constantes.COMUNIDAD: calcular_comunidad(grafo, parametros, comunidades, num_comunidad)
        elif comando == constantes.MAS_IMPORTANTES: calcular_mas_importantes(grafo, parametros, page_rank, rank_page)
        elif comando == constantes.DIAMETRO: 
            if not diametro: (diametro, costo) = calcular_diametro(grafo)
            else:
                print(diametro)
                print(constantes.COSTO_CAMINO %costo)

def construir_grafo(archivo):
    """Recibe un archivo, con formato tsv, abierto para lectura.
    Retorna un grafo con las conexiones especificadas en el archivo."""
    grafo = Grafo(True)
    for linea in archivo:
        linea_limpia = linea.strip()
        titulos = linea_limpia.split('\t')
        articulo = titulos.pop(0)
        link1 = None
        if titulos: link1 = titulos.pop(0)
        if grafo.pertenece_vertice(articulo): grafo.actualizar_dato(articulo, link1)
        else: grafo.agregar_vertice(articulo, link1)
        if link1:
            grafo.agregar_vertice(link1)
            grafo.agregar_arista(articulo, link1)
        for link in titulos:
            grafo.agregar_vertice(link)
            grafo.agregar_arista(articulo, link)
    return grafo

archivo = open(sys.argv[1], 'r')
red = construir_grafo(archivo)
archivo.close()
procesar_entrada(red)