# Generar Dashboard

## Diagrama de Bloques:
![../FlowsEvol/Node-RED2.png](../FlowsEvol/Node-RED2.png)

## Detalle de Bloques:

- Bloque función GetTemp

```js
msg.payload = msg.payload.temp;
return msg;
```

