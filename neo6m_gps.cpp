// #ifdef DEBUG
#define NEO6M_DEBUG
// #endif

#include "neo6m_gps.hpp"

constexpr bool stringsEqual(char const * a, char const * b) {
    return *a == *b && (*a == '\0' || stringsEqual(a + 1, b + 1));
}

// This was made to target TinyGPSPlus 1.0.2.
static_assert(stringsEqual(_GPS_VERSION, "1.0.2"));

// Neo6M::GPS
Neo6M::GPS::GPS() : tgps(), ss(), stream(nullptr) {}

Neo6M::GPS::GPS(uint8_t rx, uint8_t tx) {
    ss = new SoftwareSerial(rx, tx);
    stream = ss;
}

Neo6M::GPS::~GPS() {
    if (ss)
        free(ss);
}

void Neo6M::GPS::begin() {
    ss->begin(defaultBaudrate);
}

void Neo6M::GPS::useStream(Stream* stream) {
    this->stream = stream;
}

void Neo6M::GPS::tryRead() {
    if (!stream) {
#ifdef NEO6M_DEBUG
        Serial.println("No valid stream available.");
#endif
        return;
    }

    if (stream->available()) {
        auto val = stream->read();
#ifdef NEO6M_DEBUG
        Serial.print(char(val));
#endif
        tgps << val;
    }
}

bool Neo6M::GPS::hasLocation() {
    return tgps.location.isValid();
}

double Neo6M::GPS::getLatitude() {
    return tgps.location.lat();
}

double Neo6M::GPS::getLongitude() {
    return tgps.location.lng();
}
