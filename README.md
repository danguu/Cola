# Cola

Segundo Ejercicio 

Comparación de lo simulado vs lo teórico

-COMPARACIÓN:

-Si
λ<μ, deberías ver que los valores simulados tienden a aproximarse a los resultados teóricos una vez que el sistema alcanza un estado estacionario.

-Si
λ>μ, observarás que la simulación muestra una tendencia de crecimiento continuo en el número de clientes en la cola, mientras que la teoría predice que no hay un estado estacionario.

-Si
λ=μ, la simulación reflejará una acumulación lenta pero constante de clientes, lo que coincide con la predicción teórica de un crecimiento indefinido en un sistema crítico.

Tercer Ejercicio

-Análisis de los Resultados

-Valores Iniciales:

En el primer paso (índice 0), Queue Length es 0 y Clients in System es 1. Esto indica que hay un cliente que acaba de llegar al sistema y que aún no ha comenzado su servicio (o ha sido atendido y está siendo retirado del sistema).

-Crecimiento de la Cola:

A medida que avanza la simulación (índices 1 a 4), puedes observar un aumento en la longitud de la cola. Esto indica que la tasa de llegada de nuevos clientes (λ) es mayor que la tasa de servicio (μ), lo que resulta en una acumulación de clientes en la cola.
-Longitud de la Cola Máxima:

En varios pasos (como en el índice 10), Queue Length alcanza 10, que es el máximo que se ha establecido (K = 10). Esto significa que la cola está completamente ocupada y no se aceptan más clientes hasta que algunos sean atendidos y salgan del sistema.

-Clientes en el Sistema:

La columna Clients in System muestra cómo cambia el número total de clientes en el sistema. Cuando la longitud de la cola alcanza su límite, el número de clientes en el sistema se mantiene constante hasta que algunos clientes son atendidos.

-Comportamiento Observado
λ > μ:

Si la tasa de llegada (λ) es mayor que la tasa de servicio (μ), como parece ser el caso aquí, se puede esperar que la cola se llene y se mantenga llena, ya que los nuevos clientes llegan más rápido de lo que se pueden atender. Este comportamiento se puede observar en la longitud de la cola y en el número de clientes en el sistema.

-Cola Estable:

Una vez que la cola se llena, el sistema tiende a estabilizarse. Los valores en la columna Clients in System se mantienen en un rango, indicando que se está alcanzando un equilibrio donde la llegada de nuevos clientes es igual a la salida de clientes atendidos, a pesar de que la cola ya esté en su capacidad máxima.
