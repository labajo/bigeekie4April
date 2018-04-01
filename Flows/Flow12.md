# Enviar notificación del cambio a Telegram

## Diagrama de Bloques:
![../FlowsEvol/Node-RED12.png](../FlowsEvol/Node-RED12.png)

## Detalle de Bloques:
- Subscripción a los mensajes de los topics ```wemoslamp/out``` y ```sensors/wemos_2_out```
- Lamp Switch
  - msg.payload
  - OK =off
  - OK =rainbow
  - stopping after first match

- Relay Switch
  - msg.payload
  - 0
  - 1
  - stopping after first match

- Función SetPayload:
```js
msg.payload = {
    chatId: {{chatIdHardcoded}},
    type:'message',
    content:'Lampara apagada 🌑'}
return msg;
```

o

```js
msg.payload = {
    chatId: {{chatIdHardcoded}},
    type:'message',
    content:'Lampara encendida 🌕'}
return msg;
```
