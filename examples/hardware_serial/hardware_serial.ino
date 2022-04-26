#include "neo6m_gps.hpp"
#include <HardwareSerial.h>

// These empty template definitions use the default debug parameter, which is false.
// Using GPS<true> would enable debug output which may or may not clutter your serial monitor.
Neo6M::GPS<> gps;

void setup() {
    // This is if you want to use the Serial1 hardware stream. If you otherwise want to
    // use a software serial, likely because your board does not have enough hardware serials,
    // use the other constructor specifying the two pins:
    //
    //     Neo6M::GPS<> gps(RXPIN, TXPIN);
    //
    // Using that constructor, one simple needs to call gps.begin() here instead.
    
    // Note that on boards like the Uno Serial1 does not exist and will actually make this program
    // not compile. On those small boards its likely you will need to use software serial.
    Serial1.begin(Neo6M::defaultBaudrate);
    gps.useStream(&Serial1);
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
