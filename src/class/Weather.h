#ifndef WEATHER_H
#define WEATHER_H

#include <WiFi.h>
#include <Adafruit_GFX.h>
#include "epd3c/GxEPD2_750c_Z08.h"
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMono12pt7b.h>
#include <Fonts/FreeMonoBold18pt7b.h>
#include "img/dashboard.h"
#include <GxEPD2_3C.h>

class Weather{
    public:
        Weather(WiFiClass &wifir, GxEPD2_3C<GxEPD2_750c_Z08, GxEPD2_750c_Z08::HEIGHT> &displayr, struct tm &timeinfor);
        void drawInternalInfo();
        void drawExternalInfo();
        void drawLocalWeather();
        void drawTemperature();

    private:
        WiFiClass &wifi;  // Variabile privata
        GxEPD2_3C<GxEPD2_750c_Z08, GxEPD2_750c_Z08::HEIGHT> &display;
        struct tm &timeinfo;
};

#endif