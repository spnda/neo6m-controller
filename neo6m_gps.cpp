#include "neo6m_gps.hpp"

// So that we can keep the function definitions within this TU.
template class Neo6M::GPS<true>;
template class Neo6M::GPS<false>;

constexpr bool stringsEqual(char const * a, char const * b) {
    return *a == *b && (*a == '\0' || stringsEqual(a + 1, b + 1));
}

// This was made to target TinyGPSPlus 1.0.2.
static_assert(stringsEqual(_GPS_VERSION, "1.0.2"));

template<bool debug>
Neo6M::GPS<debug>::GPS() : tgps(), ss(nullptr), stream(nullptr) {}

template<bool debug>
Neo6M::GPS<debug>::GPS(uint8_t rx, uint8_t tx) {
    ss = new SoftwareSerial(rx, tx);
    stream = ss;
}

template<bool debug>
Neo6M::GPS<debug>::~GPS() {
    if (ss)
        free(ss);
}

template<bool debug>
void Neo6M::GPS<debug>::begin() {
    ss->begin(defaultBaudrate);
}

template<bool debug>
void Neo6M::GPS<debug>::useStream(Stream* stream) {
    this->stream = stream;
}

template<bool debug>
void Neo6M::GPS<debug>::tryRead() {
    if (!stream) {
        if constexpr (debug) {
            Serial.println("No valid stream available.");
        }
        return;
    }

    if (stream->available()) {
        auto val = stream->read();
        if constexpr (debug) {
            Serial.print(char(val));
        }
        tgps << val;
    }
}

template<bool debug>
bool Neo6M::GPS<debug>::hasLocation() {
    return tgps.location.isValid();
}

template<bool debug>
double Neo6M::GPS<debug>::getLatitude() {
    return tgps.location.lat();
}

template<bool debug>
double Neo6M::GPS<debug>::getLongitude() {
    return tgps.location.lng();
}

template<bool debug>
bool Neo6M::GPS<debug>::GPS::hasSatellites() {
    return tgps.satellites.isValid();
}

template<bool debug>
uint32_t Neo6M::GPS<debug>::GPS::getSatelliteCount() {
    return tgps.satellites.value();
}

template<bool debug>
bool Neo6M::GPS<debug>::GPS::hasAltitude() {
    return tgps.altitude.isValid();
}

template<bool debug>
double Neo6M::GPS<debug>::GPS::getAltitudeMeters() {
    return tgps.altitude.meters();
}
