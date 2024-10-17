# Cola by Daniel Ayala - Carlos Cardona 
# Primer Ejercicio
1. λ>μ = 165165,000...
   
![image](https://github.com/user-attachments/assets/d3a45136-f420-4ccd-9338-6b6bb113a516)

2. λ<μ = 6,46977...x10^(-213)

![WhatsApp Image 2024-10-09 at 7 43 28 PM (1)](https://github.com/user-attachments/assets/c01fc37e-d07a-4cd2-99a9-c8f8724cb481)

3. λ=μ = 375374,999...

![WhatsApp Image 2024-10-09 at 7 43 28 PM (2)](https://github.com/user-attachments/assets/8b4e6e5f-f3d6-4737-b359-62298013aca7)


# Segundo Ejercicio 

## COMPARACIÓN:

En el archivo comparacion punto se muetra la comparación 

# Tercer Ejercicio - Análisis código mesa

## Valores Iniciales:

En el primer paso (índice 0), Queue Length es 0 y Clients in System es 1. Esto indica que hay un cliente que acaba de llegar al sistema y que aún no ha comenzado su servicio (o ha sido atendido y está siendo retirado del sistema).

## Crecimiento de la Cola:

A medida que avanza la simulación (índices 1 a 4), puedes observar un aumento en la longitud de la cola. Esto indica que la tasa de llegada de nuevos clientes (λ) es mayor que la tasa de servicio (μ), lo que resulta en una acumulación de clientes en la cola.

-Longitud de la Cola Máxima:

En varios pasos (como en el índice 10), Queue Length alcanza 10, que es el máximo que se ha establecido (K = 10). Esto significa que la cola está completamente ocupada y no se aceptan más clientes hasta que algunos sean atendidos y salgan del sistema.

## Clientes en el Sistema:

La columna Clients in System muestra cómo cambia el número total de clientes en el sistema. Cuando la longitud de la cola alcanza su límite, el número de clientes en el sistema se mantiene constante hasta que algunos clientes son atendidos.

## Paso de Simulación:

En cada paso (tick), el modelo decide si un nuevo cliente llega basándose en una probabilidad relacionada con λ, y luego, el servidor atiende a los clientes en la cola.

## Recolector de datos:

El código utiliza DataCollector para medir la longitud de la cola y el número total de clientes en el sistema en cada paso de la simulación.

# Cuarto Ejercicio

El codigo se encuentra arriba es el cola_sim.cpp
