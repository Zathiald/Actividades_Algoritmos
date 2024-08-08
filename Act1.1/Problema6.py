def calcular_factorial(numero):
    factorial = 0
    if numero < 0:
        return "El factorial no está definido para números negativos."
    elif numero == 0 or numero == 1:
        return 1
    else:
        factorial = 1
        for i in range(2, numero + 1):
            factorial *= i
        return factorial

# Solicitar al usuario que ingrese un número
numero = int(input("Ingresa un número: "))

# Calcular y mostrar el factorial
resultado = calcular_factorial(numero)
print(f"El factorial de {numero} es: {resultado}")