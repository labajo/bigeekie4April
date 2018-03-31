
## Datos
- Wifi: risquetos/*******
- InfluxDb: 8086
- Chronograf: 8888
- Mosquitto: 1883
- Node Red: 1880
- AWS IOT Button: {{aws_mac}}
- Topics:
  - sensors/wemos_1
  - sensors/esp8266_1
  - sensors/esp32_1
- MQTT QoS: 0 (https://www.hivemq.com/blog/mqtt-essentials-part-6-mqtt-quality-of-service-levels)

## Nodes instalados en Node Red
- node-red-contrib-influxdb
- node-red-contrib-md5
- node-red-contrib-pcap (error en la librería, instalar pcap2 en el node_modules de node-red, instalar también ```brew install libpcap``` o ```apt-get install libpcap-dev```)
- node-red-contrib-splitter
- node-red-contrib-telegrambot
- node-red-dashboard
- node-red-node-openweathermap
- node-red-contrib-influxdb

## Obtener api key para telegram
- Comenzar converasción con Botfather.
- Introducir comando ```/newbot```.
- Introducir un prettyName. ```bigeekieIot```
- Introducir un username acabado en ```-bot```. ```bigeekieIot_bot```

## Instalación Mosquitto:
- brew install mosquitto

## Instalación InfluxDb Mac
- brew install influxdb
- brew install chronograf
- brew install kapacitor
- brew install grafana (reemplazaría a chronograf y kapacitor en temas de gráficas y alarmas)

## InfluxDb Queries
#### Obtener el último dato en una medida
```SELECT last("temp") AS "last_temp" FROM "sensors"."autogen"."wemos_1" WHERE time > :dashboardTime:```

#### Obtener varias últimas medidas
```SELECT last("temp") AS "last_temp", last("hum") AS "last_hum" FROM "sensors"."autogen"."wemos_1" WHERE time > now() - 1h```

#### Graficar una medida
```SELECT "hum" FROM "sensors"."autogen"."wemos_1" WHERE time > :dashboardTime:```


#### Mensaje Kapacitor
```{{ if eq .Level "OK" }}Problema de temperatura arreglado 😀.{{ else }}La temperatura ha bajado de 16ºC 💩.{{ end }} Valor actual:  {{ index .Fields "value" }} ºC, fecha:  {{.Time}}```


#### Configuración Pcap Node:
- Network bridge100?
- ```(arp and ether src {{aws_mac}})```
- Decoded pcap Object
- Path: payload.shost


## Obtener estado de la lampara:
- GET http://wemoslamp.local/get_switch

## Ejemplo información Sensor:
```{"temp": 27.45, "hum": 36.21, "volt": 3.96}```

## Ayuda botón AWS IoT:
https://docs.aws.amazon.com/iot/latest/developerguide/configure-iot.html
