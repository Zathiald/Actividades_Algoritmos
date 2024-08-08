'''
Resulta que ha llegado una nueva máquina embotelladora de refrescos, el contenedor principal de la
máquina tiene forma cilíndrica. Se sabe que cada envase de refresco debe contener M mililitros. Se
desea saber cuántos refrescos puede llenar la máquina de una sola vez, sin recargar el contenedor
Solo se tienen los datos del radio de la base y la altura medidos en metros.
'''

import math

def calcular_refrescos(radio, altura, volumenEnvase):
    # Volumen de la maquina
    volumenCilindro_m3 = math.pi * (radio ** 2) * altura
    volumenCilindro_ml = volumenCilindro_m3 * 1000000
    
    numeroEnvases = volumenCilindro_ml / volumenEnvase
    
    return numeroEnvases

# Ejemplo
radio = 0.5 
altura = 1.0 
volumen_envase = 500  # en mililitros

print(calcular_refrescos(radio, altura, volumen_envase))