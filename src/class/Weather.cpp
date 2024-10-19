#include "Calendar.h"
#include <Arduino.h> 
#include "Weather.h"
#include "DHT.h"

#define DHTTYPE DHT11   // DHT 11
#define DHTPIN 16
DHT dht(DHTPIN, DHTTYPE);

Weather::Weather(WiFiClass &wifir, GxEPD2_3C<GxEPD2_750c_Z08, GxEPD2_750c_Z08::HEIGHT> &displayr, struct tm &timeinfor) : wifi(wifir), display(displayr), timeinfo(timeinfor){

}

void Weather::drawInternalInfo(){
    Serial.print("inizio temp");
    dht.begin();
    int hum = dht.readHumidity();
    int tempe = dht.readTemperature();

    Serial.println(tempe);
    int16_t tbx, tby; 
    uint16_t tbw, tbh;

    display.setFont(&FreeMonoBold12pt7b);
    display.setTextColor(GxEPD_BLACK);

    display.getTextBounds(String(tempe), 0, 0, &tbx, &tby, &tbw, &tbh);
    int x = 716; //715 + ((53) - tbw) / 2 - tbx;
    int y = 245 + ((23) - tbh) / 2 - tby;
    Serial.println(x);
    Serial.println(y);
    display.setCursor(x, y);
    display.print(String(tempe) + "C");

    display.getTextBounds(String(hum), 0, 0, &tbx, &tby, &tbw, &tbh);
    x = 716;
    y = 280 + ((23) - tbh) / 2 - tby;
    display.setCursor(x, y);
    display.print(String(hum) + "%");
}

void Weather::drawExternalInfo(){

}

void Weather::drawTemperature(int t, int h){

}

void Weather::drawLocalWeather(){

}