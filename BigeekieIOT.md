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

  - ​Escuchar MQTT:
![FlowsEvol/Node-RED1.png](FlowsEvol/Node-RED1.png)
  - Generar Dashboard:
![FlowsEvol/Node-RED2.png](FlowsEvol/Node-RED2.png)
  - Poner un botón en el dashboard:
![FlowsEvol/Node-RED3.png](FlowsEvol/Node-RED3.png)
  - Capturar medidas de los sensores y guardarlas en InfluxDb:
![FlowsEvol/Node-RED4.png](FlowsEvol/Node-RED4.png)
  - Averiguar el chatId de tu conversación con el bot de telegram:
![FlowsEvol/Node-RED6.png](FlowsEvol/Node-RED6.png)
  - Configuración del bot de telegram:
![FlowsEvol/Node-RED7.png](FlowsEvol/Node-RED7.png)
  - Preguntar al bot por las últimas medidas:
![FlowsEvol/Node-RED8.png](FlowsEvol/Node-RED8.png)
  - Enlazar el botón del dashboard con el bot:
![FlowsEvol/Node-RED9.png](FlowsEvol/Node-RED9.png)
  - Añadir botón de AWS IoT:
![FlowsEvol/Node-RED10.png](FlowsEvol/Node-RED10.png)
  - Activar y desactivar la TupperLamp:
![FlowsEvol/Node-RED11.png](FlowsEvol/Node-RED11.png)
  - Activar relé en base a alarmas de Kapacitor:
![FlowsEvol/Node-RED12.png](FlowsEvol/Node-RED12.png)
  - Enviar notificación del cambio a Telegram:
![FlowsEvol/Node-RED12.png](FlowsEvol/Node-RED12.png)


- Ejemplo gráficos Chronograf:
  - Gráfico de líneas:
![FlowsEvol/Chronograf1.png](FlowsEvol/Chronograf1.png)
  - Gauge:
![FlowsEvol/Chronograf2.png](FlowsEvol/Chronograf2.png)


- Ejemplo alertas Kapacitor:
  - Temp alert:
    - Threshold
    - Seleccionar base de datos y medida
    - temp, less than 16
    - add handler: Telegram con bot token y chatId
    - Message: {{ if eq .Level "OK" }}Problema de temperatura arreglado 😀.{{ else }}La temperatura ha bajado de 16ºC 💩.{{ end }} Valor actual:  {{ index .Fields "value" }} ºC, fecha:  {{.Time}}

  - Relay alert:
    - Threshold
    - Seleccionar base de datos y medida
    - temp, less than 16
    - add handler: http://localhost:1880/api/relay
    - Message: {{ if eq .Level "OK" }}OFF{{ else }}ON{{ end }}


## Recetas:
  [Recetas.md](Recetas.md)