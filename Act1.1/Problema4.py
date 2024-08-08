'''
Se muestren todos los números, la suma y el promedio de la siguiente serie
3, 6, 9, 12,… 99. 
'''
# Se muestran los números
for i in range(3, 100, 3):
    print(i)

# Se calcula la suma de los números
suma = 0
for i in range(3, 100, 3):
    suma += i
print(f"La suma de los numeros es: {suma}")

# Se calcula el promedio de los números
contador = 0
for i in range(3, 100, 3):
    contador += 1
promedio = suma / contador
print(f"El promedio de los numeros es: {promedio}")
