# neo6m-controller

This is a small wrapper around SoftwareSerial and TinyGPSPlus for Arduino to read various data from a NEO 6M GPS. Requires C++17 (`-std=c++1z`).

## Setup

For this to work, one simply needs to connect the NEO 6M GPS to the specified RX and TX pins. Remember that the TX pin from the GPS needs to be connected to the RX pin on the Arduino, as they act like a sender/receiver pair.

## Usage

The following example shows how to use Neo6M::GPS through SoftwareSerial. Software serial only
works on some pins, and which of these pins works is different between different Arduinos.

```cpp
#include "neo6m_gps.hpp"

// Essentially Serial1 on Mega
#define RXPIN 19
#define TXPIN 18

Neo6M::GPS gps(RXPIN, TXPIN);

void setup() {
    Serial.begin(115200);
    gps.begin();
}

void loop() {
    gps.tryRead();

    if (gps.hasLocation()) {
        Serial.print("Latitude: ");
        Serial.print(gps.getLatitude());
        Serial.print("Longitude: ");
        Serial.print(gps.getLongitude());
    }
}
```

You can also use this wrapper with any other Stream, e.g. HardwareSerial. This can be useful, as
for example on an Arduino Mega the communication ports 14..19 do not work with SoftwareSerial.
To use these hardware ports, the following API can be used.

```cpp
Neo6M::GPS gps;

void setup() {
    Serial1.begin(Neo6M::GPS::defaultBaudrate);
    gps.useStream(&Serial1);
}
```
