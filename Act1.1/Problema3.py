import random

def generar_numeros_aleatorios(cantidad):
    numeros = []    
    for _ in range(cantidad):
        numero = random.randint(-100, 100)  # Genera un número aleatorio entre -100 y 100
        numeros.append(numero)
    return numeros

# Solicitar al usuario que ingrese un número
cantidad = int(input("Ingresa la cantidad de números aleatorios que deseas: "))

# Generar y mostrar los números aleatorios
numerosAleatorios = generar_numeros_aleatorios(cantidad)
print(f"Los {cantidad} números aleatorios son: {numerosAleatorios}")