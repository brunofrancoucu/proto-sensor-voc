# ti3-e5-p2
Banner

Utilizando una unidad de procesamiento (Arduino UNO luego ESP32), combinamos diferentes sensores (TODO: citar memoria).

## Inicializacion Dispositivo (Build y Upload)
Pre isntalar librerias, drivers, requisitos, [pasos](main/README.md/#instalacion)

```bash
# reemplazar puerto y core
arduino-cli compile --fqbn espressif:esp32:esp32 ./firmware/firmware.ino
arduino-cli upload -p /dev/ttyAMA0 --fqbn espressif:esp32:esp32 ./firmware/firmware.ino
arduino-cli monitor -p /dev/cu.wchusbserial5A770373911 --fqbn espressif:esp32:esp32 -c baudrate=115200
```

## Inicializacion Frontend

Next Mdwl

## Inicializacion Backend

Python api mySql reciclado

## Proceso

Fotos, evolucions