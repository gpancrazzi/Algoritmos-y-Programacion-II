#!/usr/bin/python3
from grafo import Grafo
import sys

def construir_grafo(archivo):
    """Recibe un archivo, con formato tsv, abierto para lectura.
    Retorna un grafo con las conexiones especificadas linea a linea."""
    grafo = Grafo(False)
    for linea in archivo:
        linea_limpia = linea.strip()
        titulos = linea_limpia.split('\t')
        articulo = titulos.pop(0)
        grafo.agregar_vertice(articulo)
        for link in titulos:
            grafo.agregar_vertice(link)
            grafo.agregar_arista(articulo, link)
    return grafo

#abrir el archivo pasado por terminal.
archivo = open(sys.argv[1], 'r')
#leer cada linea.
#limpiar la linea de caracteres de espacio o salto de linea.
#separar en cadenas con split (por tabulador o espacio).
#agregar en el grafo cada vertice y cada arista.
grafo = construir_grafo(archivo)
#cerrar el archivo.
archivo.close()
#listar los comandos a llamar.
#esperar la entrada de comandos.
#finalizar.