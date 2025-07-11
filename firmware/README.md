# ESP32 Dev Module (Instalacion)

## Requisitios

- VScode extension Arduino por moozzyk
- Serial port arduino esp32 mac
- arduino-cli ([instalacion](https://docs.arduino.cc/arduino-cli/installation/))
- PlatformIO (cli/onWin:vscodeExtension)
- CP2102 / 04, by silicon labs, drivers: [CP210x VCP Drivers](https://www.silabs.com/developer-tools/usb-to-uart-bridge-vcp-drivers?tab=downloads)
- CH9102 (micro) / CH340 (usb-c), by WCH, drivers: [Spark](https://sparks.gogo.co.nz/ch340.html)

## Instalacion

### PlatformIO
Instalar e iniciar terminal desde vsc `command palette`
```bash
pio project init --board esp32dev --project-option="framework=arduino"
# IntelliSense libraries c_cpp
pio init --ide vscode
```
```bash
# Compile
pio run
# Upload & compile
pio run -t upload
# Compiles and uploads a LittleFS image of /data
pio run --target uploadfs 
pio device monitor
pio device list
``` 
gzip files
```bash
gzip -k data/index.html
mv data/index.html.gz data/index.html
pio run --target uploadfs
```
### Librerias 

```bash
# Librerias
arduino-cli lib install "Adafruit GFX Library"
arduino-cli lib install "Adafruit SSD1306"
arduino-cli lib install "DHT sensor library"
arduino-cli lib install "Adafruit Unified Sensor"
```

## Build y Upload

```bash
# reemplazar puerto y core
arduino-cli compile --fqbn espressif:esp32:esp32 .
arduino-cli upload -p /dev/ttyAMA0 --fqbn espressif:esp32:esp32 .
arduino-cli monitor -p /dev/cu.wchusbserial5A770373911 --fqbn espressif:esp32:esp32 -c baudrate=115200
```

### Core FQBN

```bash
# # Listado de cores
# arduino-cli core search esp32

# Instalar core (FQBN: `espressif:esp32:esp32`)
arduino-cli core install esp32:esp32

# o
    
mkdir -p ~/Arduino/hardware/espressif
cd ~/Arduino/hardware/espressif
git clone https://github.com/espressif/arduino-esp32.git esp32
cd esp32
git submodule update --init --recursive # no tiene? creoq no
python3 tools/get.py # > 3.11
```

## Arduino pasos (no cloud ide)

```bash
arduino-cli sketch new MyFirstSketch

# Actualizar cache local
arduino-cli core update-index

# Verificar placa reconocida ono
arduino-cli board list

# Listado de placas y sus cadenas FQBN
arduino-cli board listall mkr

# Instalar nucleo de palca
arduino-cli core install arduino:samd

# Verificar nucleo
arduino-cli core list

# Compilar y cargar el boceto
arduino-cli compile --fqbn arduino:samd:mkr1000 MyFirstSketch
# puerto serial correcto
arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:samd:mkr1000 MyFirstSketch

# Instalar y buscar librerias
arduino-cli lib search debouncer
arduino-cli lib install FTDebouncer
```
[source](https://arduino-github-io.translate.goog/arduino-cli/0.35/getting-started/?_x_tr_sl=en&_x_tr_tl=es&_x_tr_hl=es&_x_tr_pto=tc)