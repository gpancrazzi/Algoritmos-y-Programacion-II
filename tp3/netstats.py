#!/usr/bin/python3
from grafo import Grafo
from biblioteca import camino_minimo_bfs, vertices_rango_n, ciclo_largo_n
from biblioteca import componente_fuertemente_conexa, clustering, diametro_grafo
import sys
import constantes
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

###############################################################################
#                       COMANDOS DE NETSTATS                                  #
###############################################################################

def listar_operaciones():
    operaciones = ["camino", "conectados", "ciclo", "rango", "navegacion", "clustering",
    "diametro"]
    for operacion in operaciones:
        print(operacion)

def camino_mas_corto(grafo, parametros):
    """"""
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
    """"""
    origen = parametros.pop(0)
    n = int(parametros.pop(0))
    en_rango = vertices_rango_n(grafo, origen, n)
    print(en_rango)

def navegacion_primer_link(grafo, parametros):
    """"""
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
    """"""
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
        if grafo.obtener_adyacentes(articulo): print(articulo)
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