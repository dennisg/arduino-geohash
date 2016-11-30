#include "arduino-geohash.h"

GeoHash::GeoHash() : base32("0123456789bcdefghjkmnpqrstuvwxyz"), m_precision(8) {
    geohash = new char[m_precision + 1];
}

GeoHash::GeoHash(uint8_t precision) : base32("0123456789bcdefghjkmnpqrstuvwxyz"), m_precision(precision) {
    geohash = new char[m_precision + 1];
}

const char* GeoHash::encode(float lat, float lng) {

    uint32_t LatitudeBinary  = ((lat  +  90.0) * 0xFFFFFFFF / 180.0);
    uint32_t LongitudeBinary = ((lng  + 180.0) * 0xFFFFFFFF / 360.0);

    uint32_t latMin = 0, latMax =  0xFFFFFFFF;
    uint32_t lonMin = 0, lonMax =  0xFFFFFFFF;

    uint8_t i   = 0; // index into geohash
    uint8_t idx = 0; // index into base32 map
    uint8_t bit = 0; // each char holds 5 bits
    boolean evenBit = true;

    while (i <= m_precision) {
        if (evenBit) {
            // bisect E-W longitude
            uint32_t lonMid = (lonMin/2 + lonMax/2);
            
            if (LongitudeBinary >= lonMid) {
                idx = idx * 2 + 1;
                lonMin = lonMid;
            } else {
                idx = idx * 2;
                lonMax = lonMid;
            }
        } else {
            // bisect N-S latitude
            uint32_t latMid = (latMin/2 + latMax/2);

            if (LatitudeBinary >= latMid) {
                idx = idx * 2 + 1;
                latMin = latMid;
            } else {
                idx = idx * 2;
                latMax = latMid;
            }
        }
        evenBit = !evenBit;

        if (++bit == 5) {
            // 5 bits gives us a character: append it and start over
            geohash[i++] = base32[idx];
            bit = 0;
            idx = 0;
        }
    }

    geohash[m_precision] = 0;
    return geohash;
}

