# Cola by Daniel Ayala - Carlos Cardona 
# Primer Ejercicio
1. λ>μ = 165165,000...
   
![image](https://github.com/user-attachments/assets/d3a45136-f420-4ccd-9338-6b6bb113a516)

2. λ<μ = 6,46977...x10^(-213)

![WhatsApp Image 2024-10-09 at 7 43 28 PM](https://github.com/user-attachments/assets/182844fe-c039-49e8-88b8-9ac3eb758870)

3. λ=μ = 375374,999...

![WhatsApp Image 2024-10-09 at 7 43 28 PM](https://github.com/user-attachments/assets/b94d1b47-6621-4534-851b-f9f206439c33)


# Segundo Ejercicio 

## COMPARACIÓN:

-Si
λ<μ, Podemos calcular los valores teóricos. Aquí el sistema es estable y deberíamos observar resultados consistentes entre la simulación y la teoría.

-Si
λ>μ, El sistema no puede estabilizarse, lo que significa que los tiempos y las colas crecerán indefinidamente. Aún así, podemos analizar el comportamiento teórico inicial, aunque en este caso la teoría nos dice que el sistema es inestable.

-Si
λ=μ, El sistema está en una condición crítica y no se estabiliza; sin embargo, teóricamente, podemos observar una acumulación lenta de clientes en la cola.

# Tercer Ejercicio - Análisis de los Resultados

## Valores Iniciales:

En el primer paso (índice 0), Queue Length es 0 y Clients in System es 1. Esto indica que hay un cliente que acaba de llegar al sistema y que aún no ha comenzado su servicio (o ha sido atendido y está siendo retirado del sistema).

## Crecimiento de la Cola:

A medida que avanza la simulación (índices 1 a 4), puedes observar un aumento en la longitud de la cola. Esto indica que la tasa de llegada de nuevos clientes (λ) es mayor que la tasa de servicio (μ), lo que resulta en una acumulación de clientes en la cola.
-Longitud de la Cola Máxima:

En varios pasos (como en el índice 10), Queue Length alcanza 10, que es el máximo que se ha establecido (K = 10). Esto significa que la cola está completamente ocupada y no se aceptan más clientes hasta que algunos sean atendidos y salgan del sistema.

## Clientes en el Sistema:

La columna Clients in System muestra cómo cambia el número total de clientes en el sistema. Cuando la longitud de la cola alcanza su límite, el número de clientes en el sistema se mantiene constante hasta que algunos clientes son atendidos.

## Comportamiento Observado
λ > μ:

Si la tasa de llegada (λ) es mayor que la tasa de servicio (μ), como parece ser el caso aquí, se puede esperar que la cola se llene y se mantenga llena, ya que los nuevos clientes llegan más rápido de lo que se pueden atender. Este comportamiento se puede observar en la longitud de la cola y en el número de clientes en el sistema.

## Cola Estable:

Una vez que la cola se llena, el sistema tiende a estabilizarse. Los valores en la columna Clients in System se mantienen en un rango, indicando que se está alcanzando un equilibrio donde la llegada de nuevos clientes es igual a la salida de clientes atendidos, a pesar de que la cola ya esté en su capacidad máxima.
