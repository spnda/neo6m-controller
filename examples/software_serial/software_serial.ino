#include "neo6m_gps.hpp"

// These are specific to your board and your wiring, be careful that you get these right!
// IMPORTANT: Always remember that the RX pin on your board connects to the TX pin on your GPS,
//            while the TX pin on your board connects to the RX pin on your GPS!!
#define RXPIN 10
#define TXPIN 9

// These empty template definitions use the default debug parameter, which is false.
// Using GPS<true> would enable debug output which may or may not clutter your serial monitor.
Neo6M::GPS<> gps(RXPIN, TXPIN);

void setup() {
    // This shows how you can simply use a software serial stream. Note that this only works on
    // some pins on every board and it is usually recommended to use hardware serial instead.
    gps.begin();
}

void loop() {
    // This tries reading and updating values from the GPS, if connected properly. If the debug
    // setting is enabled through the template parameters, this will also print debug information.
    gps.tryRead();

    // The location might not be available, therefore, you need to verify its presence using
    // the hasLocation function. Only then can you print values from getLatitude and getLongitude.
    if (gps.hasLocation()) {
        Serial.print("Latitude: ");
        Serial.print(gps.getLatitude());
        Serial.print("Longitude: ");
        Serial.print(gps.getLongitude());
        Serial.println();
    }
}
