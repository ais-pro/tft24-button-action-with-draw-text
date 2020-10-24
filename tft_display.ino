#include <SPFD5408_Adafruit_GFX.h>    // Core graphics library
#include <SPFD5408_Adafruit_TFTLCD.h> // Hardware-specific library
#include <SPFD5408_TouchScreen.h>     // Touch library

#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

Adafruit_TFTLCD tft(LCD_CS, LCD_CD,  LCD_WR, LCD_RD, LCD_RESET); 

uint16_t buttons_y = 0;

#define YP A1 
#define XM A2 
#define YM 7  
#define XP 6 
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

#define BUTTONS 3
Adafruit_GFX_Button buttons[BUTTONS];

uint16_t identifier = 0x9341;


#define BUTTON_CLEAR 0
#define BUTTON_SHOW 1
#define BUTTON_RESET 2

TSPoint p;

short TS_MINX=106;
short TS_MINY=228;
short TS_MAXX=886;
short TS_MAXY=1007;


// Calibrates value
#define SENSIBILITY 300
#define MINPRESSURE 10
#define MAXPRESSURE 1000



void setup() {

  Serial.begin(9600);

  
  tft.reset();
  
  
  tft.begin(identifier);

  tft.setRotation(0);

  
 tft.fillScreen(WHITE);





  initializeButtons();   

  
  for (uint8_t i=0; i<3; i++) {
      buttons[i].drawButton();
  }


}


void initializeButtons() {

  uint16_t x = 38;
  uint16_t y = tft.height() - 38;
  uint16_t w = 75;
  uint16_t h = 38;

  
  uint8_t spacing_x = 5;
  
  uint8_t textSize = 1;

  char buttonlabels[3][20] = {"Clear", "Show", "Recalib."};
  uint16_t buttoncolors[15] = {RED, BLUE, RED};

  for (uint8_t b=0; b<3; b++) {
    buttons[b].initButton(&tft,                           // TFT object
                  x+b*(w+spacing_x),  y,                  // x, y,
                  w, h, WHITE, buttoncolors[b], WHITE,    // w, h, outline, fill, 
                  buttonlabels[b], textSize);             // text
  }

}

void loop()
{
  // Test of calibration
  
  TSPoint p;

  // Wait a touch
  
  digitalWrite(13, HIGH);
  
  p = ts.getPoint();

  if(p.z < MINPRESSURE || p.z > MAXPRESSURE)return;
  
    pinMode(XM, OUTPUT); //Pins configures again for TFT control
    pinMode(YP, OUTPUT);
  
  digitalWrite(13, LOW);

  // Map of values
  
  p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
  p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());


  
  // Buttons

  // Go thru all the buttons, checking if they were pressed
  
  for (uint8_t b=0; b<BUTTONS; b++) {
    
    if (buttons[b].contains(p.x, p.y)) {

      
              tft.setTextColor(RED);
              // Clear
              tft.setCursor (10, 10);
              tft.println("Clear to proceed");

        // Action

        switch  (b) {

          case BUTTON_CLEAR:

  tft.setTextColor(RED);
              // Clear
              tft.setCursor (40, 50);
              tft.println("Clear to proceed");


              break;
              
          case BUTTON_SHOW:

              // Clear


  tft.setTextColor(RED);
              tft.setCursor (40, 100);
              tft.println("Touch to proceed");

              
              break;
              
          case BUTTON_RESET:

  tft.setTextColor(RED);
              tft.setCursor (40, 150);
              // New calibration
              tft.println("calibra to proceed");


              break;
        }
    }
  }





  
  

}
