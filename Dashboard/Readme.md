
## $\textcolor{orange}{Descripción\ de\ la\ plataforma\ de\ Soporte:}$

Ubidots es una plataforma basada en la nube que proporciona servicios y herramientas para la gestión y visualización de datos en tiempo real. Es especialmente utilizada en el ámbito de Internet de las cosas (IoT) para recopilar, almacenar y analizar datos generados por dispositivos conectados.

Con Ubidots, los usuarios pueden crear paneles interactivos y personalizados para visualizar y monitorear datos en tiempo real, establecer alarmas y notificaciones, realizar análisis y crear informes. La plataforma es flexible y escalable, lo que permite a los usuarios adaptarla a sus necesidades específicas.

Además, Ubidots proporciona APIs y herramientas para integrar datos y funcionalidades con otras aplicaciones y sistemas, lo que facilita la conexión y el intercambio de información.

La plataforma tiene diferentes planes de servicios. Hay un plan de estudiante y una prueba gratuita por 30 dias.

## $\textcolor{orange}{Dashboard\ de\ la\ Actividad\ 3:}$

![image](https://user-images.githubusercontent.com/46485082/236715490-f53f88d9-e4f2-4875-a7ad-c1c3ed129750.png)

## $\textcolor{orange}{Imagen\ del\ prototipo\ y\ la\ AppWeb:}$

![image](https://user-images.githubusercontent.com/46485082/236715823-a99b8eff-fbdf-485a-a5fa-393cb33b8d75.png)


## $\textcolor{orange}{Pantalla\ de\ la\ App\ Ubidots:}$

![image](https://user-images.githubusercontent.com/46485082/236715887-c90cb93c-4eb6-4ac0-a10d-7dec13a6cd7c.png)

Tanto el uso de la aplicacion Web como la de la App para Smartphone tiene beneficios como los que podemos enumerar aca:

- [x] Monitoreo y control en tiempo real:

La aplicación permite acceder y visualizar datos en tiempo real, lo que facilita el monitoreo y control de dispositivos y sistemas conectados.

- [x] Visualización personalizada:

Los usuarios pueden crear paneles de control personalizados para visualizar los datos de manera intuitiva y adaptada a sus necesidades específicas. Esto facilita la comprensión de los datos y la toma de decisiones informadas.

- [x] Alertas y notificaciones:

La aplicación permite configurar alertas y notificaciones basadas en umbrales predefinidos. Esto permite recibir avisos en tiempo real cuando los datos superan ciertos límites o condiciones establecidas.

- [x] Acceso desde cualquier lugar:

La aplicación de Ubidots está basada en la nube, lo que significa que los usuarios pueden acceder a los datos y paneles desde cualquier dispositivo con conexión a Internet. Esto proporciona flexibilidad y movilidad.

- [x] Integración con otras aplicaciones y servicios:

Ubidots ofrece APIs y herramientas de integración que permiten conectar y compartir datos con otras aplicaciones y servicios, lo que facilita la interoperabilidad y el uso conjunto de información.

- [x] Escalabilidad :

La plataforma de Ubidots es escalable, lo que significa que puede adaptarse a diferentes tamaños de proyectos y necesidades cambiantes a medida que crece la cantidad de dispositivos y datos a gestionar.





## $\textcolor{orange}{:}$



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








