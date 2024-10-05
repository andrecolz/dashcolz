#include "Calendar.h"
#include <Arduino.h>  // Include se stai usando l'ambiente Arduino

Calendar::Calendar(WiFiClass &wifir, GxEPD2_3C<GxEPD2_750c_Z08, GxEPD2_750c_Z08::HEIGHT> &displayr, struct tm &timeinfor) : wifi(wifir), display(displayr), timeinfo(timeinfor){
  
}

void Calendar::calculateDays(struct tm &timeinfo) {
  int dayInThisMonth = daysInMonth(timeinfo.tm_mon + 1, timeinfo.tm_year);
  int dayLastMonth = daysInMonth(timeinfo.tm_mon, timeinfo.tm_year); //  per tm_year se gennaio -1 se dicembre +1 (da mettere if)
  int dayNextMonth = daysInMonth(timeinfo.tm_mon + 2, timeinfo.tm_year); //  <--- (+1)   forse manco serve visto che prendo i primi giorni
  int today = timeinfo.tm_mday;
  int dayOfWeek = timeinfo.tm_wday;  

  int line = 0;
  while(true){
    if(today == 0){
      break;
    }
    if(dayOfWeek == 0){
      line++;
      dayOfWeek = 7;
    } else {
      dayOfWeek--;
      today--;
    }
  }
  Serial.println(dayLastMonth + " " + line);

  day[dayOfWeek].nday = 1;
  day[dayOfWeek].currentMonth = true;

  int dowtmp = dayOfWeek;
  while(true){
    dowtmp--;
    if(dowtmp == -1){
      break;
    }
    day[dowtmp].nday = dayLastMonth;
    day[dowtmp].currentMonth = false;
    dayLastMonth--;
  }

  int i = 2;
  while(true){
    dayOfWeek++;
    if(i == dayInThisMonth + 1){
      break;
    }
    day[dayOfWeek].nday = i;
    day[dayOfWeek].currentMonth = true;
    i++;
  }

  i = 1;
  while(true){
    if(dayOfWeek == 42){
      break;
    }
    day[dayOfWeek].nday = i;
    day[dayOfWeek].currentMonth = false;
    i++;
    dayOfWeek++;
  }
}

int Calendar::daysInMonth(int thisMonth, int thisYear){
  if((thisMonth==2) && ((thisYear%400==0) || ((thisYear%100!=0)&&(thisYear%4==0)))){
    return 29;
  }
  else if(thisMonth==2){
    return 28;
  }
  else if(thisMonth==1 || thisMonth==3 || thisMonth==5 || thisMonth==7 || thisMonth==8 || thisMonth==10 || thisMonth==12){
    return 31;
  }
  else if(thisMonth==4 || thisMonth==6 || thisMonth==9 || thisMonth==11){
    return 30;
  }
  
  return 0;
}

void Calendar::drawCalendar(){
  display.drawBitmap(0, 0, dashboardIMG, 800, 480, GxEPD_WHITE);

//   int hum = dht.readHumidity();
//   // Read temperature as Celsius (the default)
//   int tempe = dht.readTemperature();

//   Serial.print(F("Humidity: "));
//   Serial.print(hum);
//   Serial.print(F("%  Temperature: "));
//   Serial.print(tempe);
//   Serial.print(F("°C "));
//   Serial.println("");

//   display.setFont(&FreeMonoBold12pt7b);
//   display.setTextColor(GxEPD_BLACK);
//   display.setCursor(716, 267);
//   display.print(String(tempe));

//   display.setCursor(716, 300);
//   display.print(String(hum));

  int x1 = 32;
  int y1 = 245;
  int x2 = 80;
  int y2 = 277;
  int k = 0;

  for(int j = 0; j < 6; j++){
    int h1 = y2 - y1;

     for(int i = 0; i < 7; i++){
        int w1 = x2 - x1;
        int16_t tbx, tby; 
        uint16_t tbw, tbh;
        display.setFont(&FreeMonoBold12pt7b);
        display.setTextColor(GxEPD_BLACK);
        display.getTextBounds(String(day[k].nday), 0, 0, &tbx, &tby, &tbw, &tbh);

        uint16_t x = x1 + ((w1) - tbw) / 2 - tbx;
        uint16_t y = y1 + ((h1) - tbh) / 2 - tby;
        display.setCursor(x, y);
        if(i == 6){
          if(day[k].currentMonth){
            display.setTextColor(GxEPD_RED);
            if(day[k].nday == timeinfo.tm_mday){
              //display.fillCircle(x1 + (w1+1)/2, y1 + (h1+1) / 2, 15, GxEPD_BLACK);
              // display.drawLine(x1, y1, x2, y2, GxEPD_RED);
              // display.drawLine(x1, y2, x2, y1, GxEPD_RED);
              display.setFont(&FreeMonoBold18pt7b);
              display.getTextBounds(String(day[k].nday), 0, 0, &tbx, &tby, &tbw, &tbh);

              x = x1 + ((w1) - tbw) / 2 - tbx;
              y = y1 + ((h1) - tbh) / 2 - tby;
              display.setCursor(x, y);
              display.print(day[k].nday);
            } else {
              display.setFont(&FreeMonoBold12pt7b);
              display.print(day[k].nday);
            }
          } else {
            display.setTextColor(GxEPD_RED);
            display.setFont(&FreeMono12pt7b);
            display.getTextBounds(String(day[k].nday), 0, 0, &tbx, &tby, &tbw, &tbh);

            x = x1 + ((w1) - tbw) / 2 - tbx;
            y = y1 + ((h1) - tbh) / 2 - tby;
            display.setCursor(x, y);
            display.print(day[k].nday);
          }
        } else {
          if(day[k].currentMonth){
            if(day[k].nday == timeinfo.tm_mday){
              display.setFont(&FreeMonoBold18pt7b);
              display.getTextBounds(String(day[k].nday), 0, 0, &tbx, &tby, &tbw, &tbh);

              x = x1 + ((w1) - tbw) / 2 - tbx;
              y = y1 + ((h1) - tbh) / 2 - tby;
              display.setCursor(x, y);
              display.print(day[k].nday);
            } else {
              display.setFont(&FreeMonoBold12pt7b);
              display.print(day[k].nday);
            }
          } else {
            display.setFont(&FreeMono12pt7b);
            display.print(day[k].nday);
          }
        }
        


        x1 = x1 + w1 + 3;
        x2 = x2 + w1 + 3;
        k++;
    }
    x1 = 32;
    x2 = 80;
    y1 = y1 + h1 + 3;
    y2 = y2 + h1 + 3;
  }
}

void Calendar::getDay(){

}
