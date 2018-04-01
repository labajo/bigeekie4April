# Preguntar al bot por las últimas medidas

## Diagrama de Bloques:
![../FlowsEvol/Node-RED8.png](../FlowsEvol/Node-RED8.png)

## Detalle de Bloques:

- Bloque Save chatProps tipo Function:

```js
msg.chat = msg.payload;
return msg;
```

- Bloque Get last temp and hum:

```sql
SELECT last("temp") AS "last_temp", last("hum") AS "last_hum" FROM "sensors"."autogen"."wemos_1" WHERE time > now() - 1h
```

- Bloque Recover chatProps tipo de function:

```js
msg.data = msg.payload[0];
msg.payload.chatId = msg.chat.chatId;
msg.payload.messageId = msg.chat.messageId;
msg.payload.type = msg.chat.type;
return msg;
```

- Bloque Message Render tipo Template:
  - Set property msg.payload.content

```
La temperatura es de {{data.last_temp}} ºC y hay una humedad del {{data.last_hum}}% a las {{data.time}}
```

