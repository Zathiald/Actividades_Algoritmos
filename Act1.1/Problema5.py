def calcular_sumatoria(n):
    termino = 0
    exponente = 0
    suma = 0
    for i in range(1, n + 1):
        if i % 2 == 0:
            exponente = 2
        else:
            exponente = i
        termino = 1 / (i ** exponente)
        suma += termino
    return suma

# Calcular los primeros 15 términos de la sumatoria
n = 15
resultado = calcular_sumatoria(n)
print(f"La sumatoria de los primeros {n} términos es: {resultado:.6f}")
