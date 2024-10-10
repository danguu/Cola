from mesa import Agent, Model
from mesa.time import RandomActivation
from mesa.datacollection import DataCollector
import random

# Parámetros de llegada (lambda) y servicio (mu)
LAMBDA = 1  # Tasa de llegada - Se cambia tambien a 0.20 y 2
MU = 0.67     # Tasa de servicio - Se cambia tambien a 0.33 y 0.50 
K = 10        # Capacidad máxima de la cola (Si K = INF, no hay límite)

class Cliente(Agent):
    """Agente que representa un cliente en la cola."""
    def __init__(self, unique_id, model):
        super().__init__(unique_id, model)
        self.arrival_time = model.schedule.time

class Servidor(Agent):
    """Agente que representa el servidor de la cola."""
    def __init__(self, unique_id, model):
        super().__init__(unique_id, model)
        self.serving = None
        self.service_time_left = 0

    def step(self):
        if self.serving is not None:
            self.service_time_left -= 1
            if self.service_time_left <= 0:
                # Cliente servido, retirarse del sistema
                self.serving = None  # Solo eliminar referencia al cliente
        else:
            if len(self.model.queue) > 0:
                # Si hay clientes en la cola, servir al primero
                self.serving = self.model.queue.pop(0)  # Quitar cliente de la cola
                self.service_time_left = random.expovariate(1 / self.model.mu_rate)  # Tiempo de servicio

class MM1Model(Model):
    """Modelo de simulación de la cola M/M/1/K."""
    def __init__(self, lambda_rate=LAMBDA, mu_rate=MU, max_queue=K):
        super().__init__()
        self.num_agents = 0
        self.lambda_rate = lambda_rate
        self.mu_rate = mu_rate
        self.max_queue = max_queue
        self.queue = []
        self.schedule = RandomActivation(self)

        # Inicializar el servidor
        servidor = Servidor(self.next_id(), self)
        self.schedule.add(servidor)

        # Recopilador de datos
        self.datacollector = DataCollector(
            {
                "Queue Length": lambda m: len(m.queue),
                "Clients in System": lambda m: len(m.queue) + (1 if servidor.serving else 0)
            }
        )

    def step(self):
        # Probabilidad de llegada de un nuevo cliente
        if random.random() < self.lambda_rate:
            if len(self.queue) < self.max_queue or self.max_queue == float('inf'):
                cliente = Cliente(self.next_id(), self)
                self.queue.append(cliente)

        # Pasar al siguiente paso en la simulación
        self.schedule.step()

        # Recoger los datos
        self.datacollector.collect(self)

# Ejecutar la simulación
model = MM1Model()

# Número de pasos de simulación
for i in range(10):
    model.step()

# Ver los resultados
results = model.datacollector.get_model_vars_dataframe()
print(results)
