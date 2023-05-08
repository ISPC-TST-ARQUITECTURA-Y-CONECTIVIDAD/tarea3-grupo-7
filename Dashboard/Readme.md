
## $\textcolor{orange}{Descripción\ de\ la\ plataforma\ de\ Soporte:}$

![image](https://user-images.githubusercontent.com/46485082/236715490-f53f88d9-e4f2-4875-a7ad-c1c3ed129750.png)



![image](https://user-images.githubusercontent.com/46485082/236715823-a99b8eff-fbdf-485a-a5fa-393cb33b8d75.png)

![image](https://user-images.githubusercontent.com/46485082/236715887-c90cb93c-4eb6-4ac0-a10d-7dec13a6cd7c.png)



- [x] Identificación del sistema: se determina el modelo matemático del sistema a controlar, incluyendo la dinámica del proceso y las interacciones con otros sistemas.       Para ello, se pueden utilizar técnicas de identificación de sistemas como el análisis de respuesta al impulso o el análisis de frecuencia.

- [x] Diseño del controlador: se seleccionan los coeficientes del controlador PID (Kp, Ki y Kd) y se ajustan para lograr un comportamiento
      deseado del sistema  controlado. Se pueden utilizar herramientas de diseño de controladores, como el método de ajuste de 
      Ziegler-Nichols o el método de ajuste de Cohen-Coon.

- [x] Simulación y evaluación: se simula el comportamiento del sistema controlado con el controlador PID diseñado. La simulación permite evaluar el 
      rendimiento del  controlador y ajustar los coeficientes del controlador según sea necesario.


## $\textcolor{orange}{Función\ de\ transferencia\ del\ proceso:}$

Esta función es una herramienta que describe como un sistema dinámico responde a una entrada. Sirve
para representar como la salida cambia en respuesta a una entrada. En la ecuación a continuación, T(s)
es la temperatura actual en la transformada de Laplace, Td(s) es la temperatura deseada en la
transformada de Laplace, K es la ganancia del sistema (representa la relación entre la señal de entrada y
la de salida), y τ (tau) es la velocidad de respuesta del sistema a los cambios en la señal de entrada.

![image](https://user-images.githubusercontent.com/46485082/235377585-665e762b-443c-4d91-8492-78dbda22d22b.png)


## $\textcolor{orange}{Error\ del\ sistema:}$

Esto se refiere a la diferencia entre la temperatura deseada y la temperatura real del departamento. La
ecuación queda de la siguiente manera:

![image](https://user-images.githubusercontent.com/46485082/235377606-12f325b7-da8a-4e28-83c8-f1d6391b5e7e.png)


Donde E(t) corresponde al error, Td(t) corresponde a la temperatura deseada y T(t) a la temperatura real
del departamento, todo esto evaluado en el tiempo t.

## $\textcolor{orange}{Cálculo\ de\ términos\ PID:}$

- [x] Término proporcional (P): se calcula multiplicando el error por una constante proporcional (Kp).

![image](https://user-images.githubusercontent.com/46485082/235377627-fc4972aa-cbba-4578-8f7d-8654392326ee.png)


- [x] Término integral (I): se calcula sumando el error a lo largo del tiempo y multiplicándolo por una constante integral (Ki).


![image](https://user-images.githubusercontent.com/46485082/235377405-3f7a6c2e-edd5-4042-a96e-9bf8a6419b27.png)


- [x] Término derivativo (D): es el producto la tasa de cambio del error por una constante derivativa (Kd):

![image](https://user-images.githubusercontent.com/46485082/235377670-52301a6e-2dc9-4fc8-9a90-b7d48c47d518.png)

## $\textcolor{orange}{PID:}$

La suma de los tres componentes da como resultado el controlador PID, quedando de la siguiente
manera:


![image](https://user-images.githubusercontent.com/46485082/235377686-b1ec9275-2eee-4318-ade8-1a49707965bc.png)


Donde g(t) es la señal de control enviada al sistema de control de temperatura.

Un código en Python, como ejemplo, para el control del sistema es el siguiente:


```python
import numpy as np
import matplotlib.pyplot as plt

class CasaInteligente:
    def __init__(self, temperatura_inicial, K, tau):
        self.temperatura_actual = temperatura_inicial
        self.temperatura_deseada = temperatura_inicial
        self.historial_temperaturas = [temperatura_inicial]
        self.K = K
        self.tau = tau
        self.dt = 1.0 / 60 # Paso de tiempo en horas (1 minuto)
        self.error_integral = 0
        self.error_anterior = 0
        
    def actualizar_temperatura(self, nueva_temperatura):
        self.temperatura_actual = nueva_temperatura
        self.historial_temperaturas.append(nueva_temperatura)
        
    def controlador_pid(self, Kp, Ki, Kd):
        error = self.temperatura_deseada - self.temperatura_actual
        self.error_integral += error * self.dt
        error_derivada = (error - self.error_anterior) / self.dt
        u = Kp * error + Ki * self.error_integral + Kd * error_derivada
        self.error_anterior = error
        return u
    
    def simular_dia(self, temperatura_deseada, Kp, Ki, Kd):
        self.temperatura_deseada = temperatura_deseada
        for _ in range(24 * 60): # Simular durante 24 horas en intervalos de 1 minuto
            u = self.controlador_pid(Kp, Ki, Kd)
            dydt = (self.K * u - self.temperatura_actual) / self.tau
            nueva_temperatura = self.temperatura_actual + dydt * self.dt
            self.actualizar_temperatura(nueva_temperatura)
    
    def graficar_temperaturas(self):
        plt.plot(np.arange(len(self.historial_temperaturas)) / 60, self.historial_temperaturas, label="Temperatura")
        plt.axhline(self.temperatura_deseada, color="r", linestyle="--", label="Temperatura deseada")
        plt.xlabel("Hora")
        plt.ylabel("Temperatura (°C)")
        plt.title("Control de temperatura en una casa inteligente")
        plt.legend()
        plt.ylim(20,22)
        plt.xlim(0,1)
        plt.show()

def main():
    casa = CasaInteligente(25, K=7, tau=3)
    casa.simular_dia(21, Kp=8, Ki=10, Kd=0.08)
    casa.graficar_temperaturas()

if __name__ == "__main__":
    main()



```

Luego de probar valores para Kp, Ki y Kd, se concluyó que los valores adecuados son los expresados en el
código (Kp=8, Ki=10, Kd=0.08). Reduciendo el componente derivativo y aumentando los otros
parámetros, se logra el comportamiento deseado. Mostrando un comportamiento de la siguiente
manera:

![image](https://user-images.githubusercontent.com/46485082/235377484-b013c4a4-07ca-43e4-9204-27f877e42695.png)



En el plazo de una hora:

![image](https://user-images.githubusercontent.com/46485082/235377494-a79899ef-d915-4432-b451-ce53cc5147cf.png)




## $\textcolor{orange}{Descripcion\ del\ principio\ de\ funcionamiento:}$

El controlador PID (Proporcional-Integral-Derivativo) es un algoritmo utilizado para controlar sistemas en tiempo real. Para el caso de un sistema de refrigeracion, el objetivo del controlador es ajustar automáticamente la cantidad de enfriamiento suministrada por el sistema para mantener una temperatura deseada.

Para el caso de un sistema de refrigeración, el dispositivo se conforma con dos sensores de temperatura y humedad (DHT11 y DHT22) y una placa de desarrollo ESP32, los sensores miden la temperatura y la humedad ambiente, y envían esta información a la placa ESP32. La placa utiliza esta información para calcular el error entre la temperatura deseada y la temperatura actual, y luego ajusta la cantidad de enfriamiento proporcionado por el sistema de refrigeración para minimizar ese error.

El control PID utiliza tres parámetros: la ganancia proporcional, la ganancia integral y la ganancia derivativa. Estos parámetros ajustan la cantidad de corrección que se aplica al sistema en función de la magnitud y la dirección del error. En otras palabras, si el error es grande y está aumentando, el controlador aumentará la cantidad de enfriamiento proporcionada para corregirlo. Si el error es pequeño y está disminuyendo, el controlador reducirá la cantidad de enfriamiento para evitar sobrecorrección.

En resumen, el control PID  utiliza la información de los sensores para ajustar automáticamente la cantidad de enfriamiento proporcionada por el sistema para mantener una temperatura deseada, y utiliza una combinación de ganancia proporcional, ganancia integral y ganancia derivativa para minimizar el error y evitar sobrecorrección.

## $\textcolor{orange}{Esquema\ del\ control\ PID:}$

![image](https://user-images.githubusercontent.com/46485082/235324427-de49fe65-964a-44b6-a239-a0823613a980.png)








