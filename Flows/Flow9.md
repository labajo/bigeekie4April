# Añadir botón de AWS IoT

## Diagrama de Bloques:
![../FlowsEvol/Node-RED10.png](../FlowsEvol/Node-RED10.png)

## Detalle de Bloques:

- pcap node, captura arp y mac
  - interfaz (brigde100 mac en modo hostspot)
  - Decoded pcap Object
  - (arp and ether src {{dashbutton_mac}})
  - Path: payload.shost

- switch
  - == {{dashbutton_mac}}
  - stopping after first match
- Función SetPayload:

```js
msg.payload = {
    chatId: {{chatIdHardcoded}},
    type:'message',
    content:'Amazon IOT pulsado 😎'};
return msg;
```



