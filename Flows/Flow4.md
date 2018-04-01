# Capturar medidas de los sensores y guardarlas en InfluxDb

## Diagrama de Bloques:
![../FlowsEvol/Node-RED4.png](../FlowsEvol/Node-RED4.png)

## Detalle de Bloques:

- Crear base de datos sensors en Chronograf
- Conexión de influxDb a localhost y database sensors.
- En el nodo de influxDb out poner como measurement cada uno de los dispositivos

