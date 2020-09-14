#!/usr/bin/python3
# coding: utf-8

# # Ejemplo codigo de resolución de sudoku por backtracking

# ## Funciones auxiliares

# In[ ]:


import sys

def fila(cant_elem):
    return cant_elem//9

def columna(cant_elem):
    return cant_elem%9

# Funcio que verifica si puede poner el numero pasado (num) en la posicion pasado (cant_elem)
def puedo_poner(num, cant_elem, M):
    # Se fija si no esta el mismo numero en la fila
    fil = fila(cant_elem)
    for c in range(0,9):
        if M[fil][c] == num:
            return False
    
    # Se fija si no esta el mismo numero en la columna
    col = columna(cant_elem)
    for f in range(0,9):
        if M[f][col] == num:
            return False
    
    # Se fija si no esta el mismo numero en el cuadrante
    c_corner = (col//3) * 3
    f_corner = (fil//3) * 3
    for f_c in range(f_corner, f_corner+3):
        for c_c in range(c_corner, c_corner+3):
            if M[f_c][c_c] == num:
                return False
    return True
    
def sig_pos_a_usar(cant_elem, M):
    for x in range(cant_elem, 9*9):
        if M[fila(x)][columna(x)] == 0:
            return x
    return 9*9

def print_matrix(M):
    for pos_l, l in enumerate(M):
        if pos_l == 0: print('------------'*3)        
        for pos_c, c in enumerate(l):
            if pos_c==0: print('|', end='  ')
            if c == 0:
                print ('.', end='  ')
            else:
                print(c, end='  ')
            if (pos_c+1)%3==0: print('|', end='  ')
        print('')
        if (pos_l+1)%3==0: print('------------'*3)        
        


# ## Funcion backtraking sudoku

# In[ ]:


def sudoku(cant_elem, M):
    
    if cant_elem >= 9*9:
        return True
    
    cant_elem = sig_pos_a_usar(cant_elem, M)
    
    if cant_elem >= 9*9:
        return True
    
    for num in range (1, 10):
        if puedo_poner(num, cant_elem, M):
            M[fila(cant_elem)][columna(cant_elem)] = num
            if sudoku(cant_elem, M):
                return True
            M[fila(cant_elem)][columna(cant_elem)] = 0
    
    return False


# In[ ]:


M = [[6,0,0,0,1,0,0,9,0],
     [0,0,0,7,0,9,2,0,0],
     [0,0,7,0,0,0,8,0,0],
     [0,0,2,0,7,1,0,6,0],
     [0,0,6,0,4,0,9,0,7],
     [0,0,1,0,5,3,0,2,0],
     [0,0,9,0,0,0,3,0,0],
     [0,0,0,5,0,7,1,0,0],
     [4,0,0,0,3,0,0,7,0]]


print("Antes")
print_matrix(M)


encontro_solucion = sudoku(0, M)
print("Encontro sulucion? ", encontro_solucion)


print("Despues")
print_matrix(M)


# ## Version que muestra en consola el progreso

# In[ ]:


def borrar_consola(cant_lineas=14):
    input('')
    for x in range(cant_lineas):
        print("\033[K", end='') #clear line
        sys.stdout.write("\033[F") #go back line


def sudoku_v2(cant_elem, M):
    if cant_elem >= 9*9:
        return True
    
    cant_elem = sig_pos_a_usar(cant_elem, M)
    
    if cant_elem >= 9*9:
        return True
    
    for num in range (1, 10):
        if puedo_poner(num, cant_elem, M):
            M[fila(cant_elem)][columna(cant_elem)] = num
            
            borrar_consola()
            print_matrix(M)
            
            if sudoku_v2(cant_elem, M):
                return True
            M[fila(cant_elem)][columna(cant_elem)] = 0
            
            borrar_consola()
            print_matrix(M)
            
        else:
            M[fila(cant_elem)][columna(cant_elem)] = num
            
            borrar_consola()
            print_matrix(M)
            
            M[fila(cant_elem)][columna(cant_elem)] = 'X'
            
            borrar_consola()
            print_matrix(M)
            
            M[fila(cant_elem)][columna(cant_elem)] = 0
            
            borrar_consola()
            print_matrix(M)
    
    return False


# In[ ]:


print('Ejemplo simple de seguimiento \n\n')

M = [[0,0,0,0,1,0,0,0,0],
     [0,0,0,0,0,0,0,0,0],
     [0,0,0,0,0,0,0,0,0],
     [0,0,0,0,0,0,0,0,0],
     [0,0,0,0,0,0,0,0,0],
     [0,0,0,0,0,0,0,0,0],
     [0,0,0,0,0,0,0,0,0],
     [0,0,0,0,0,0,0,0,0],
     [0,0,0,0,0,0,0,0,0]]

print_matrix(M)
print('\nProcesando....\n')
print_matrix(M)
print('Encontro solucion?', sudoku_v2(0, M))

