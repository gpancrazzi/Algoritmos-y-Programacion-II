from colorama import Fore

def print_test(texto, condicion):
    """Recibe una cadena de texto y una condicion a cumplir.
    Si la condicion es true retorna el texto y un mensaje Ok.
    Si la condicion es false retorna el texto y un mensaje de error."""
    if condicion:
        return print(Fore.WHITE+texto+Fore.WHITE+'... '+Fore.GREEN+'OK'+Fore.RESET)
    return print(Fore.WHITE+texto+Fore.WHITE+'... '+Fore.RED+'ERROR'+Fore.RESET)