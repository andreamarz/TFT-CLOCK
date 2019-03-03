#include <FishinoFlash.h>
#include <FishinoRTC.h>

#define DEBUG_LEVEL_INFO
#include <FishinoDebug.h>

#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h> 
#define LCD_CS A3   // Chip Select goes to Analog 3
#define LCD_CD A2   // Command/Data goes to Analog 2
#define LCD_WR A1   // LCD Write goes to Analog 1
#define LCD_RD A0   // LCD Read goes to Analog 0

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define PURPLE  0xF0ED
#define BLUETTO 0x867D 
#define VERDIN  0xA708

MCUFRIEND_kbv tft;

void setup()
{
	Serial.begin(115200);
	while(!Serial)
		;
	
	if (!RTC.isrunning()) {
		DateTime now(__DATE__, __TIME__);
		RTC.adjust(now);
	}

  tft.reset();
  uint16_t identifier = tft.readID();
  tft.begin(identifier); 
  tft.setRotation(3);
  tft.fillScreen(BLACK);
  unsigned long start = micros();
}

void loop()
{
	DateTime now = RTC.now();

  tft.setTextColor(WHITE, BLACK);
  int textSize = 4;
  tft.setTextSize(textSize);
  //String testo = "Oggi è " + String(daysOfTheWeek[now.dayOfTheWeek()]);
  String testo = "Oggi ";
  testo += String(char(130));
  testo += " ";
  switch (now.dayOfTheWeek()) {
    case 0:
      testo += "Domenica";
      break;
    case 1:
      testo += "Luned";
      testo += String(char(141));
      break;
    case 2:
      testo += "Marted";
      testo += String(char(141));
      break;
    case 3:
      testo += "Mercoled";
      testo += String(char(141));
      break;
    case 4:
      testo += "Gioved";
      testo += String(char(141));
      break;
    case 5:
      testo += "Venerd";
      testo += String(char(141));
      break;
    case 6:
      testo += "Sabato";
      break;
  }
  int x = (480 - (testo.length() * (6 * textSize))) / 2;
  int y = 10;
  tft.setCursor(x, y);
  tft.print(testo);

  textSize = 4;
  tft.setTextSize(textSize);
  testo = String(now.year()) + '-';
  if (now.month() < 10) {
    testo += ('0');
  }
  testo += String(now.month()) + '-';
  if (now.day() < 10) {
    testo += '0';
  }
  testo += String(now.day());
  x = (480 - (testo.length() * (6 * textSize))) / 2;
  y += (6 * textSize) + 20;
  tft.setCursor(x, y);
  tft.print(testo);

  textSize = 8;
  tft.setTextSize(textSize);
  testo = "";
  if (now.hour() < 10) {
    testo += '0';
  }
  testo += String(now.hour()) + ':';
  if (now.minute() < 10) {
    testo += '0';
  }
  testo += String(now.minute()) + ':';
  if (now.second() < 10) {
    testo += '0';
  }
  testo += String(now.second());
  x = (480 - (testo.length() * (6 * textSize))) / 2;
  y += (6 * textSize) + 15;
  tft.setCursor(x, y);
  tft.print(testo);

  tft.setTextColor(PURPLE, BLACK);
  testo = String(char(123));
  x = ((480 - (testo.length() * (6 * textSize))) / 2) - (6 * textSize) - 20 ;
  y += (6 * textSize) + 30;
  tft.setCursor(x, y);
  tft.print(testo);

  tft.setTextColor(BLUETTO, BLACK);
  testo = "AM";
  x = (480 - (testo.length() * (6 * textSize))) / 2;
  tft.setCursor(x, y);
  tft.print(testo);

  tft.setTextColor(VERDIN, BLACK);
  testo = String(char(125));
  x = ((480 - (testo.length() * (6 * textSize))) / 2) + (6 * textSize) + 20 ;
  tft.setCursor(x, y);
  tft.print(testo);

  tft.setTextColor(WHITE, BLACK);
  textSize = 2;
  tft.setTextSize(textSize);
  testo = "Software;";
  x = 480 / 2;
  y += (6 * textSize) + 50;
  tft.setCursor(x, y);
  tft.print(testo);
  
	delay(1000);
}
