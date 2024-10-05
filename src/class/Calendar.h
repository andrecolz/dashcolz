#ifndef CALENDAR_H
#define CALENDAR_H

#include <WiFi.h>
#include <Adafruit_GFX.h>
#include "epd3c/GxEPD2_750c_Z08.h"
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMono12pt7b.h>
#include <Fonts/FreeMonoBold18pt7b.h>
#include "img/dashboard.h"
#include <GxEPD2_3C.h>

class Calendar {
  public:
    Calendar(WiFiClass &wifir, GxEPD2_3C<GxEPD2_750c_Z08, GxEPD2_750c_Z08::HEIGHT> &displayr, struct tm &timeinfor);  // Costruttore
    void calculateDays(struct tm &timeinfo);  // Metodo pubblico
    int daysInMonth(int thisMonth, int thisYear);
    void drawCalendar();
    void getDay();

  private:
    WiFiClass &wifi;  // Variabile privata
    GxEPD2_3C<GxEPD2_750c_Z08, GxEPD2_750c_Z08::HEIGHT> &display;
    struct tm &timeinfo;
    struct Dayc {
        int nday;
        bool currentMonth;
    };
    Dayc day[42];
    

};

#endif