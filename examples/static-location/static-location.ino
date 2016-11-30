
#include <arduino-geohash.h>



GeoHash hasher(8);


float latitude, longitude;

void setup() {
    Serial.begin(9600);
    
    latitude  = 51.9509;
    longitude = 6.0143;
}


void loop() {
    
    const char* geohash = hasher.encode(latitude, longitude);
    Serial.println(geohash);

    delay(2000);
}
