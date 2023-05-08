## $\textcolor{orange}{Componentes:}$

- [x] ESP32
- [x] DHT11
- [x] Resistencia de 220 ohm
- [x] LED
- [x] Protoboard 
- [x] Jumper´s MM

## $\textcolor{orange}{Circuito:}$

![image](https://user-images.githubusercontent.com/108508184/236831526-d5ece466-05bd-4e8f-b1ce-cf9924bc9ad5.png)


## $\textcolor{orange}{Imagenes :}$

![image](https://user-images.githubusercontent.com/46485082/236805358-f15cbe61-282d-487f-bda9-99db11c0d57f.png)


![image](https://user-images.githubusercontent.com/46485082/236805941-31e3cf1e-91b3-48f1-9eda-5f7c787ac94b.png)


![image](https://user-images.githubusercontent.com/46485082/236806138-6c823215-2776-43cf-8202-bb6f2a442ce2.png)


![image](https://user-images.githubusercontent.com/46485082/236806395-d8d50341-a1fb-4cde-ab2f-6bbe04764e87.png)


## $\textcolor{orange}{Codigo:}$

Código en C++.


```C++

/*Incluimos primero las librerías instaladas*/

#include <DHTesp.h>
#include <Wire.h>
#include "UbidotsEsp32Mqtt.h"
#include <UbiConstants.h>
#include <UbiTypes.h>

/*Definimos que el LED estará conectado al pin 2 del ESP32*/

#define LED_PIN 2

/*Definimos que el tipo de sensor que estamos utilizando es un DHT11*/

DHTesp dht11_1;

/*Definimos el pin donde datos del DHT11*/

const int pin1 = 26;


/*Definimos primero el Token que nos brinda la plataforma Ubidots para hacer la conexión*/
  
  const char *UBIDOTS_TOKEN = "TOKEN DE UBIDOTS;

/*Definimos SSID y PASSWORD de nuestra red WiFi*/

  const char *WIFI_SSID = "NOMBRE DEL WIFI";      
  const char *WIFI_PASS = "PASSWORD";     

/*Definimos el nombre de nuestro dispositivo, el cual aparecerá en la plataforma Ubidots*/

  const char *DEVICE_LABEL = "ESP32";

/*Definimos las variables que se medirán y que serán publicadas en la plataforma Ubidots*/
  
  const char *VARIABLE_LABEL_1 = "temperatura"; 
  const char *VARIABLE_LABEL_2 = "humedad"; 

/*Definimos la frecuencia de publicación de 5 segundos*/
  
  const int PUBLISH_FREQUENCY = 5000; 

/*Definimos unas variables extra, que incluye la librería*/
 
  unsigned long timer;
  uint8_t analogPin = 34; 

/*Definimos que las variables de la librería UBIDOTS trabajarán con el Token*/

  Ubidots ubidots(UBIDOTS_TOKEN);

/*codigo para LED*/

void handleMessage(char *topic, byte *payload, unsigned int length) {

  char ledValue = (char)payload[0];

  if (ledValue == '1') {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }

}



/*La librería nos da una función de Subscripción para mensajes de regreso desde la plataforma Ubidots hacia nuestro circuito*/

void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}


/*Definimos la función Setup() para iniciar nuestro circuito*/

void setup()
{
  /*Iniciamos el terminal Serial a 115200*/
  Serial.begin(115200);     
  /*Imprimimos el siguiente texto para asegurar el encendido del circuito*/
  Serial.println("Medición inciada");
  Serial.println("DHT11 Encendido");
  /*Iniciamos nuestro sensor DHT11*/
  dht11_1.setup(pin1, DHTesp::DHT11);
   
   pinMode(LED_PIN, OUTPUT); // codigo para el LED
   digitalWrite(LED_PIN, LOW);// codigo para el LED
  
  
  /*Incluimos un retardo de 1 segundo*/

  delay(1000);

  /*Ahora, se incluye las funciones de conexión de la Plataforma, como la conexión a internet con las credenciales de WiFi*/
  // ubidots.setDebug(true);  //Descomentar esto para que los mensajes de depuración estén disponibles
  
  ubidots.connectToWifi(WIFI_SSID, WIFI_PASS);
  
  /*Se inicia la función de subscripción para los mensajes de retorno, que se definió líneas arriba*/
  
  ubidots.setCallback(handleMessage);//linea de LED
  
  /*Se incluye las funciones de Setup y Reconnect, predefinidas de la librería*/
  
  ubidots.setup();
  ubidots.reconnect();
  ubidots.subscribeLastValue("esp32", "led");//codigo para el LED
    timer = millis();
}

/*Iniciamos el bucle de la función Loop()*/

void loop()
{
  
  /*Definimos que, si no se conecta a la plataforma Ubidots, se pasa la función Reconnect() para volver a establecer la conexión*/

  if (!ubidots.connected())
  {
    ubidots.reconnect();
    ubidots.subscribeLastValue("esp32", "led");//codigo para el LED
    return; // CODIGO PARA LED
  }
  
  /*En esta condicional, iniciamos la medición de Temperatura y Humedad del sensor, y la información será enviada a la Plataforma*/
  
  if (abs(millis() - timer) > PUBLISH_FREQUENCY) 
  {
    /*Hacemos la medición de Temperatura y Humedad del sensor, y lo definimos en variables Float */
    
    float h = dht11_1.getHumidity();
    float t = dht11_1.getTemperature();
    
       
    /*Definimos que el valor de Temperatura será enviado por la variable 1, a la plataforma Ubidots*/
    
    ubidots.add(VARIABLE_LABEL_1, t);
    
    /*Definimos que el valor de Humedad será enviado por la variable 2, a la plataforma Ubidots*/
    
    ubidots.add(VARIABLE_LABEL_2, h);
    
    /*Hacemos la publicación de los datos en el dispositivo definido*/
    
    ubidots.publish(DEVICE_LABEL);
    
    /*Para mostrar los datos, los imprimimos en el terminal Serial*/
    
    Serial.println("Enviando los datos a Ubidots: ");
    Serial.println("Temperatura: " + String(t));
    Serial.println("Humedad: " + String(h));
    Serial.println("-----------------------------------------");
    timer = millis();
  }
  
  /*Agregamos un delay de 10 segundos para el envío, y que luego de este tiempo, se proceda a reiniciar el bucle*/

  delay(1000);  
  ubidots.loop();
}

```

## $\textcolor{orange}{Monitor\ Serial:}$


![image](https://user-images.githubusercontent.com/46485082/236807524-09760537-c8e4-41c9-9681-c01122d89df9.png)


