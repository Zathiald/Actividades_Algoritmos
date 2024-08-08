import random

def calcular_dias_para_pedido(pedido, produccion_linea1, produccion_linea2):
    diasNecesarios = 0
    totalProducido = produccion_linea1 + produccion_linea2
    if totalProducido <= 0:
        return "La producción diaria debe ser mayor que 0."
    
    # Calcula los días necesarios para completar el pedido
    diasNecesarios = pedido / totalProducido
    
    # Redondea hacia arriba para obtener días completos
    diasNecesarios = int(diasNecesarios) if diasNecesarios.is_integer() else int(diasNecesarios) + 1
    return diasNecesarios

# Solicitar el pedido al usuario
pedido = int(input("Ingresa la cantidad de camisas en el pedido: "))

# Generar producción diaria aleatoria para las líneas de producción
produccionLinea1 = random.randint(50, 300)  # Producción diaria de la línea 1
produccionLinea2 = random.randint(50, 300)  # Producción diaria de la línea 2

# Mostrar la producción diaria de cada línea
print(f"Producción diaria de la línea 1: {produccionLinea1} camisas")
print(f"Producción diaria de la línea 2: {produccionLinea2} camisas")

# Calcular los días necesarios
dias = calcular_dias_para_pedido(pedido, produccionLinea1, produccionLinea2)
print(f"Se necesitarán {dias} días para completar el pedido de {pedido} camisas.")

