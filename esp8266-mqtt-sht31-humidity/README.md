### ESP8266 SHT31 Humidity sensor

Sending humidity and temperature data to an MQTT broker waiting with deep sleep for the next cycle.
Using ESP8266 D1 Mini

## Requirements

 - Arduino: Library Manager
    - ESP8266
    - Adafruit SHT31 Library
    - Adafruit MQTT Library
- D1 Mini Pins
    - Deep Sleep requires RST and D0 connected
        - in case you keep them connected during flashing you need to manually start it by pressing the button
    - SHT31 SCL pin with ESP D1 pin
    - SHT31 SDA pin with ESP D2 pin
    - SHT31 GND pin with ESP GND pin
    - SHT31 VIN pin with ESP 3V3 pin 

## Problems with VS Code Setup

 - "Warning] Failed to generate IntelliSense configuration." VS Code was not helpful here, but starting the same project in the arduino IDE told me it requires a sketch folder, after which the include paths were correctly populated and my local header file could be included as well