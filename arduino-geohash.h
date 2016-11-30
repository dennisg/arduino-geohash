#ifndef _ARDUINO_GEOHASH_H
#define _ARDUINO_GEOHASH_H

#include <Arduino.h>


class GeoHash {

public:

    GeoHash();
    GeoHash(uint8_t precision);

    const char* encode(float lat, float lng);

private: 
    const char* base32;
    uint8_t m_precision;
    char* geohash;

};

#endif