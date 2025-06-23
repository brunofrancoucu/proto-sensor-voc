# ti3-e5-p2

# ESP32 Dev Module (Instalacion)

## Requisitios

- VScode extension Arduino por moozzyk
- Serial port arduino esp32 mac
- arduino-cli ([instalacion](https://docs.arduino.cc/arduino-cli/installation/))

## Instalacion

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