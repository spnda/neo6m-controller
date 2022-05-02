#ifndef NEO6M_GPS_H
#define NEO6M_GPS_H

#include <stdint.h>

#include "Arduino.h"
#include <SoftwareSerial.h>

// We use the TinyGPSPlus library to parse NMEA sentences from the GPS module. Of course, the
// TinyGPS library could be re-implemented with ease, but with TinyGPS++ it allows us to easily
// add custom NMEA term handlers.
#include <TinyGPS++.h>

namespace Neo6M {
    constexpr static const auto defaultBaudrate = 9600;

    constexpr static const auto GPGSV = "GPGSV";

    template<bool debug = false>
    class GPS {
        TinyGPSPlus tgps = {};
        SoftwareSerial* ss;
        Stream* stream;

        TinyGPSCustom satellitesInView = { tgps, GPGSV, 4 };

    public:
        GPS();

        // This creates a new GPS object backed by a SoftwareSerial. By using this constructor, you
        // are required to call the begin() method during setup.
        // Remember, that the RX and TX pins serve as input/output channels. That means that the TX
        // pin should be connected to the RX pin and vice-versa.
        GPS(uint8_t rx, uint8_t tx);

        ~GPS();

        void begin();
        void useStream(Stream* stream);

        // This tries reading and updating any data the GPS might have outputted. If any warnings
        // or other messages are generated, this function will print them to the Serial Monitor.
        void tryRead();

        // The GPS might not have given location data. If hasLocation is false, the longitude and
        // latitude will be invalid.
        bool hasLocation();
        double getLatitude();
        double getLongitude();

        bool hasSatellites();
        uint32_t getSatelliteCount();
        uint32_t getSatelliteInViewCount();

        bool hasAltitude();
        double getAltitudeMeters();
    };
}

#endif
