#include "Calendar.h"
#include <Arduino.h> 
#include "Weather.h"

#define DHTTYPE DHT11   // DHT 11
#define DHTPIN 16
DHT dht(DHTPIN, DHTTYPE);

Weather::Weather(WiFiClass &wifir, GxEPD2_3C<GxEPD2_750c_Z08, GxEPD2_750c_Z08::HEIGHT> &displayr, struct tm &timeinfor) : wifi(wifir), display(displayr), timeinfo(timeinfor){

}

void Weather::dhtInit(){
    dht.begin();
}