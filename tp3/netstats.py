#!/usr/bin/python3
from grafo import Grafo
from biblioteca import camino_minimo_bfs
import sys
import constantes

def construir_grafo(archivo):
    """Recibe un archivo, con formato tsv, abierto para lectura.
    Retorna un grafo con las conexiones especificadas en el archivo."""
    grafo = Grafo(True)
    for linea in archivo:
        linea_limpia = linea.strip()
        titulos = linea_limpia.split('\t')
        articulo = titulos.pop(0)
        grafo.agregar_vertice(articulo)
        for link in titulos:
            grafo.agregar_vertice(link)
            grafo.agregar_arista(articulo, link)
    return grafo

def listar_operaciones():
    """"""
    operaciones = ["camino", "mas_importantes", "conectados", "ciclo", "lectura", 
    "diametro", "rango", "comunidad", "navegacion", "clustering"]
    for operacion in operaciones:
        print(operacion)

def reconstruir_camino(padres, origen, destino):
    """"""
    fin = destino
    recorrido = []
    while fin != origen:
        recorrido.append(fin)
        fin = padres.get(fin)
    recorrido.append(origen)
    recorrido.reverse()
    camino = constantes.FLECHA.join(recorrido)
    return camino

def camino_mas_corto(grafo, parametros):
    """"""
    origen = parametros.pop(0)
    destino = parametros.pop(0)
    if not grafo.pertenece_vertice(origen) or not grafo.pertenece_vertice(destino): 
        print(constantes.SIN_CAMINO)
        return 
    (padres, orden) = camino_minimo_bfs(grafo, origen, destino)
    if not destino in orden:
        print(constantes.SIN_CAMINO)
        return
    camino = reconstruir_camino(padres, origen, destino)
    print(camino)
    print(constantes.COSTO_CAMINO %orden[destino])

def limpiar_parametros(linea):
    """"""
    parametros = linea.split(',')
    parametros_limpios = []
    for parametro in parametros:
        parametro = parametro.lstrip()
        parametro = parametro.rstrip()
        parametros_limpios.append(parametro)
    return parametros_limpios

def identificar_comando(linea):
    """"""
    comandos = linea.split(' ', 1)
    comando = comandos.pop(0)
    if not comandos: return comando, None
    linea = "".join(comandos)
    parametros = limpiar_parametros(linea)
    return comando, parametros

def procesar_entrada(grafo):
    """"""
    comando = constantes.LISTAR_OPERACIONES
    while comando:
        try: linea = input()
        except EOFError: break
        (comando, parametros) = identificar_comando(linea)
        if comando == constantes.LISTAR_OPERACIONES: listar_operaciones()
        elif comando == constantes.CAMINO: camino_mas_corto(grafo, parametros)
        elif comando == constantes.RANGO: todos_en_rango(parametros)

#abrir el archivo pasado por terminal.
archivo = open(sys.argv[1], 'r')
#leer cada linea.
#limpiar la linea de caracteres de espacio o salto de linea.
#separar en cadenas con split (por tabulador o espacio).
#agregar en el grafo cada vertice y cada arista.
red = construir_grafo(archivo)
print("OK")
#cerrar el archivo.
archivo.close()
#listar los comandos a llamar.
procesar_entrada(red)
#esperar la entrada de comandos.
#procesar los comandos.
#finalizar.