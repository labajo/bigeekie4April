# Bigeekie - Node RED, domótica en casa


## Índice:

- Gateway

  ![Gateway.png](Gateway.png)
  
  Ejemplos: https://www.google.es/search?q=gateway+domotica

- Instalar node-red

  - https://nodered.org/docs/getting-started/installation
  - https://nodered.org/docs/security
  - Interfaces: MQTT, HTTP, Websockets, TCP, UDP, BLE, GPIO, etc….
  - Muchísimos plugins
  - Finalidad
    - Centralización.
    - Ayuda a dispositivos ligeros al procesamiento.
    - Cacheo en caso de caída de red.
    - Multi interfaz.
    - Conectividad desde el exterior.

- MQTT (Message Queuing Telemetry Transport) https://en.wikipedia.org/wiki/MQTT
  Publish/subscribe. Comunicación bidireccional fácil.

- Sensores MQTT con DeepSleep

  ![MQTTSensor.png](MQTTSensor.png)

- Actuadores MQTT

  ![MQTTActuator.png](MQTTActuator.png)


  Programas en la carpeta ArduinoProjects. ESP8266 y ESP32


- TimeSeries Database, Graphic tool and alarm management (InfluxDb, Chronograf, Kapacitor) 
  - https://en.wikipedia.org/wiki/InfluxDB

- Flows

  - [Escuchar MQTT](Flows/Flow1.md)
  - [Generar Dashboard](Flows/Flow2.md)
  - [Poner un botón en el dashboard](Flows/Flow3.md)
  - [Capturar medidas de los sensores y guardarlas en InfluxDb](Flows/Flow4.md)
  - [Averiguar el chatId de tu conversación con el bot de telegram](Flows/Flow5.md)
  - [Configuración del bot de telegram](Flows/Flow6.md)
  - [Preguntar al bot por las últimas medidas](Flows/Flow7.md)
  - [Enlazar el botón del dashboard con el bot](Flows/Flow8.md)
  - [Añadir botón de AWS IoT](Flows/Flow9.md)
  - [Activar y desactivar la TupperLamp](Flows/Flow10.md)
  - [Activar relé en base a alarmas de Kapacitor](Flows/Flow11.md)
  - [Enviar notificación del cambio a Telegram](Flows/Flow12.md)

![FlowsEvol/Node-RED12.png](FlowsEvol/Node-RED12.png)


- Ejemplo gráficos Chronograf:
  - Gráfico de líneas:
![FlowsEvol/Chronograf1.png](FlowsEvol/Chronograf1.png)
  - Gauge:
![FlowsEvol/Chronograf2.png](FlowsEvol/Chronograf2.png)


- Ejemplo alertas Kapacitor:
  - Temp alert:
    - Threshold
    - Seleccionar base de datos y medida, 0 functions
    - temp, less than 16
    - add handler: Telegram con bot token y chatId
    - Message: {{ if eq .Level "OK" }}Problema de temperatura arreglado 😀.{{ else }}La temperatura ha bajado de 16ºC 💩.{{ end }} Valor actual:  {{ index .Fields "value" }} ºC, fecha:  {{.Time}}

  - Relay alert:
    - Threshold
    - Seleccionar base de datos y medida, 0 functions
    - temp, less than 16
    - add handler: http://localhost:1880/api/relay
    - Message: {{ if eq .Level "OK" }}0{{ else }}1{{ end }}


## Recetas:
  [Recetas.md](Recetas.md)