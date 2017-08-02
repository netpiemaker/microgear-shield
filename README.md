# ESP8266 MICROGEAR SHIELD

This is ESP8266 Firmware based on FREERTOS SDK. 

Main objective is to build hardware microgear board to support NETPIE IOT platform and to liberate microgear from various platform compatible issue.

You can find latest version of FREERTOS SDK here -> [Espressif FreeRTOS](https://github.com/espressif/ESP8266_RTOS_SDK)


To use this board effectively use it with NETPIE IoT Platform -> [Netpie platform](https://netpie.io/)

**_Please Check on [wiki page](https://github.com/moun1234/FreeRTOSMicrogear/wiki) for an API DOC!!!_**

## Features

**1. Real time base firmware**

**2. 2 modes support (Standalone and MCU-compatible) with **AT COMMAND Based****

**3. Support Library Arduino Mega, Uno and other MCU**

**4. MQTT MODULE (Only Netpie compatible):**
- Subscribing
- Publish up to 1024 Bytes
- Key, Secret and Token Authentication
- Easy to setup and use
    
**5. TCP MODULE:**
- **Support multiple connection (up to 2 clients)**
- Support ALL mandatory functions eg.connect, print, flush 
- Easy to use API

## Installations

**1. Install a [toolchain](https://github.com/esp8266/esp8266-wiki/wiki/Toolchain)**

**2. Install [FreeRTOS](https://github.com/espressif/ESP8266_RTOS_SDK)**

**3. Clone this project:**
```
git clone https://github.com/moun1234/Microgear-Shield-RTOS
```
**4. Enter the directory and flash TO ESP8266 USING _MAKE COMMAND_ OR [ESPTOOL](https://github.com/espressif/esptool):**
```
make clean
make 
make flash
```
## Circumstance

   **1. Baud rate has to be 9600 due to the uncertainty of serial communication**
