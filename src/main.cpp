#include <GxEPD2_3C.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMono12pt7b.h>
#include <Fonts/FreeMonoBold18pt7b.h>
#include <SPI.h>
#include "img/dashboard.h"
#include "img/loading.h"
#include "img/wificon.h"
#include <Wire.h>
#include <Time.h>
#include <WiFi.h>
#include <Adafruit_GFX.h>
#include "epd3c/GxEPD2_750c_Z08.h"
#include "class/Calendar.h"

GxEPD2_3C<GxEPD2_750c_Z08, GxEPD2_750c_Z08::HEIGHT> display(GxEPD2_750c_Z08(/*CS=D8*/ SS, /*DC=D3*/ 21, /*RST=D4*/ 3, /*BUSY=D2*/ 2));

const char* ssid = "TIM-62244755_2.4GEXT";
const char* password = "RDe7AYX3SRf3F4zH4RKfUtc6";

struct tm timeinfo;

// const char* ssid = "GalaxyA53";
// const char* password = "aaaaaaaa";


void setup() {
  Serial.begin(9600);
  display.init(115200, true, 2, false);

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  
  // Init and get the time
  configTime(3600, 3600, "pool.ntp.org");
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  //calculateDays(timeinfo);

  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_BLACK);
    //drawBitmapFromProgmem(0, 0, dashboardIMG, 800, 480, timeinfo); // Adatta le coordinate e le dimensioni dell'immagine
    
    // display.fillRect(418, 276, 349, 3, GxEPD_BLACK);

    // display.fillRect(487, 209, 3, 67, GxEPD_BLACK);
    // display.fillRect(558 +2, 209, 3, 67, GxEPD_BLACK);
    // display.fillRect(628 +2, 209, 3, 67, GxEPD_BLACK);
    // display.fillRect(698 +2, 209, 3, 67, GxEPD_BLACK);
  } while (display.nextPage());
}

void loop() {



  delay(30000);
}