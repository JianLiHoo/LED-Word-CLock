#include <Adafruit_NeoPixel.h>
#include <Wire.h>  //Required for RTClib.h
#include <RTClib.h>
#include <pitches.h>

// Which pin on the Arduino is connected to the NeoPixels?
#define LEDPIN            7

//Define Pins for settings
#define SETPIN            8
#define LEFTPIN           9
#define RIGHTPIN          10

//Buzzer Pin
#define BUZZER            6

//Delays
#define FASTBLINK         100
#define SLOWBLINK         600

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      121

Adafruit_NeoPixel grid = Adafruit_NeoPixel(NUMPIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);
RTC_DS1307 rtc;

int delayval = 500; // delay for half a second

/*============Colors=============*/

uint32_t colorWhite = grid.Color(150,150,150);
uint32_t colorBlack = grid.Color(0, 0, 0);
uint32_t colorRed = grid.Color(150, 0, 0);
uint32_t colorGreen = grid.Color(0, 150, 0);
uint32_t colorBlue = grid.Color(0, 0, 150);
uint32_t colorJGreen = grid.Color(50, 179, 30);
uint32_t colorPurple = grid.Color(150,0,150);

/*============Word Arrays===========*/
//End with -1 to display LEDs(as per void paintWord)

//------------Uniques-----------
int arrJIANLI[] = {104,105,106,107,108,109,110,111,112,113,114,115,-1};
int arrSMILEY[] = {83,-1};
int arrA[] = {118,-1};
int arrHAPPY[] = {99,100,101,102,103,-1};
int arrBIRTHDAY[] = {91,92,93,94,95,96,97,98,-1};
int arrTOu[] = {64,65,-1};
int arrU[] = {4,-1};
int arrDAY[] = {91,92,93,-1};

//------------Settings-----------
int arrBRIGHT[] = {98,96,49,48,47,46,-1};

//------------Headers-----------
int arrIT[] = {120,119,-1};
int arrIS[] = {117,116,-1};

//------------Bridges------------
int arrPAST[] = {55,56,57,58,-1};
int arrTO[] = {58,59,-1};
int arrO[] = {59,-1};
int arrPAS[] = {55,56,57,-1};

//-------------Minutes-----------
int arrFIVEM[] = {84,85,86,87,-1};
int arrTENM[] = {88,89,90,-1};
int arrTWENTYFIVEM[] = {77,78,79,80,81,82,83,84,85,86,87,-1};
int arrTWENTYM[] = {77,78,79,80,81,82,-1};
int arrdashFIVEM[] = {83,84,85,86,87,-1};
int arrQUARTER[] = {66,67,68,69,70,71,72,-1};
int arrHALF[] = {73,74,75,76,-1};
int arrJnM[] = {104,115,-1};
int arrInM[] = {105,114,-1};
int arrAnM[] = {106,113,-1};
int arrNnM[] = {107,112,-1};
int arrLnM[] = {108,111,-1};
int arrI2nM[] = {109,110,-1};

//-------------Hours-------------
int arrONEH[] = {23,24,25,-1};
int arrTWOH[] = {41,42,43,-1};
int arrTHREEH[] = {50,51,52,53,54,-1};
int arrFOURH[] = {60,61,62,63,-1};
int arrFIVEH[] = {18,19,20,21,-1};
int arrSIXH[] = {33,32,11,-1};
int arrSEVENH[] = {33,34,35,36,37,-1};
int arrEIGHTH[] = {46,47,48,49,50,-1};
int arrNINEH[] = {37,38,39,40,-1};
int arrTENH[] = {44,45,46,-1};
int arrELEVENH[] = {12,13,14,15,16,17,-1};
int arrTWELVEH[] = {26,27,28,29,30,31,-1};

//-------------Endings-----------
int arrOCLOCK[] = {5,6,7,8,9,10,-1};
int arrAM[] = {2,3,-1};
int arrPM[] = {0,1,-1};

//-------------Number Display-------------

int arr1[] = {2,3,4,18,25,40,47,62,69,61,-1};
int arr2[] = {2,3,4,17,26,39,40,41,46,63,68,69,70,-1};
int arr3[] = {4,3,2,19,24,41,40,39,46,63,68,69,70,-1};
int arr4[] = {2,19,24,41,46,63,68,70,61,48,39,40,-1};
int arr5[] = {68,69,70,61,48,39,40,41,24,19,2,3,4,-1};
int arr6[] = {68,69,70,61,48,39,26,17,4,3,2,19,24,41,40,39,-1};
int arr7[] = {2,19,24,41,46,63,68,69,70,-1};
int arr8[] = {70,69,68,61,63,48,46,39,40,41,26,24,17,19,4,3,2,-1};
int arr9[] = {2,19,24,41,46,63,68,70,61,48,39,40,69,-1};
int arr0[] = {70,69,68,61,63,48,46,39,41,26,24,17,19,4,3,2,-1};

int arr1Tens[] = {6,7,8,14,29,36,51,58,73,57,-1};
int arr2Tens[] = {6,7,8,13,30,35,36,37,50,59,72,73,74,-1};
int arr3Tens[] = {8,7,6,15,28,37,36,35,50,59,72,73,74,-1};

int arrsDay[] = {120,99,98,77,119,101,96,78,-1};
int arrsMonth[] = {77,98,99,119,101,96,79,117,103,94,81,-1};


/*============Time Delays==============*/

/*============Time Banks===============*/
int currMinute = 0;
int currHour = 0;

int capMillis = 0;  //Time captured by millis()
int timeTaken = 0;  //After subtracting capMillis from millis()
int timeCount = 0;  //timeCount + timeTaken

/*============Settings===================*/
boolean settingMode = false;
boolean statusLight = true;
int settingsMenu = 0;
int setHour = 0;
int setMinute = 0;

float dayBrightness = 255;
float nightBrightness = 100;
float pctBrightness = 100;
float brightness = dayBrightness;



void setup() {
/*========NeoPixels Setup=====*/
  grid.begin(); // This initializes the NeoPixel library.

/*========RTC Setup===========*/
  
  Serial.begin(57600);
#ifdef AVR
  Wire.begin();
#else
  Wire1.begin(); // Shield I2C pins connect to alt I2C bus on Arduino Due
#endif
  rtc.begin();

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  pinMode(SETPIN, INPUT);
  pinMode(LEFTPIN, INPUT);
  pinMode(RIGHTPIN, INPUT);
  
  pinMode(BUZZER, OUTPUT);
  
  colorWipe(colorBlack,0);
  
  grid.setBrightness(brightness);
  
}

void loop() {

//==================Settings==========================
  DateTime now = rtc.now();
  setHour = now.hour();
  setMinute = now.minute();
  capMillis = millis();
  
  if(digitalRead(SETPIN)==LOW){  //Press SET to enter settings
    colorWipe(colorBlack,0);
    settingMode = true;
    Serial.println("Settings Mode");
  }
 
 if(settingMode==true){
    colorWipe(colorBlack,0);
    paintWord(arrJIANLI,colorRed);
    while(digitalRead(SETPIN)==!LOW){  //while pressed. Prevent accidental trigerring of next command
    }
    delay(500);
    while(digitalRead(SETPIN)==HIGH){  //not pressed
      if(digitalRead(LEFTPIN)==LOW){
        while(digitalRead(LEFTPIN)!=HIGH){
        }
        if(settingsMenu==0){  
          settingsMenu = 3;
        }
        else{
          settingsMenu = settingsMenu - 1;
        }
      }
      if(digitalRead(RIGHTPIN)==LOW){
        while(digitalRead(RIGHTPIN)!=HIGH){
        }
        if(settingsMenu==3){  
          settingsMenu = 0;
        }
        else{
          settingsMenu = settingsMenu + 1;
        }
        
      }
      Serial.print("Settings Menu = ");
      Serial.println(settingsMenu,DEC);
      
      switch (settingsMenu){
      
        case 0:
          paintWord(arrTHREEH,colorBlack);
          paintWord(arrONEH,colorBlack);  
          paintWord(arrBRIGHT,colorWhite); 
          break;
          
        case 1:
          paintWord(arrBRIGHT,colorBlack);
          paintWord(arrTWOH,colorBlack);
          paintWord(arrONEH,colorWhite);
          break;
          
        case 2:
          paintWord(arrONEH,colorBlack);
          paintWord(arrTHREEH,colorBlack);
          paintWord(arrTWOH,colorWhite);
          break;
          
        case 3:
          paintWord(arrTWOH,colorBlack);
          paintWord(arrBRIGHT,colorBlack);
          paintWord(arrTHREEH,colorWhite);
          break;
        default:
          break;
          
      }
    }
    
    while(digitalRead(SETPIN)!=HIGH){  //prevent accidental triggering of next command
    }
    
    switch (settingsMenu){
      
        case 0:
            
          blinkWord(arrBRIGHT,colorWhite,3);  //Para: (arrWord,color,loops)
          break;
          
        case 1:
   
          blinkWord(arrONEH,colorWhite,3);  //Para: (arrWord,color,loops)
          break;
          
        case 2:
        
          blinkWord(arrTWOH,colorWhite,3);  //Para: (arrWord,color,loops)
          break;
          
        case 3:
        
          blinkWord(arrTHREEH,colorWhite,3);  //Para: (arrWord,color,loops)
          break;
          
        default:
          break;
          
    }
    
    while(digitalRead(SETPIN)!=HIGH){  //prevent accidental triggering of next command
    }      
    
    while(digitalRead(SETPIN)==HIGH){  //not pressed
    
      switch (settingsMenu){
        
        case 0:
          Serial.println("Brightness Settings");
          paintWord(arrBRIGHT,colorWhite);
          while(digitalRead(SETPIN)==HIGH){  //Not pressed
            if(digitalRead(LEFTPIN)==LOW){
              while(digitalRead(LEFTPIN)!=HIGH){
              }
              if(pctBrightness<20){
                pctBrightness = 100;
              }
              else{
                pctBrightness = pctBrightness - 10; 
              }
            }
            if(digitalRead(RIGHTPIN)==LOW){
              while(digitalRead(RIGHTPIN)!=HIGH){
              }
              if(pctBrightness>100){
                pctBrightness = 10;
              }
              else{
                pctBrightness = pctBrightness + 10; 
              }
            }
            brightness = dayBrightness*(pctBrightness/100);
            //Serial.println(brightness,DEC);
            //Serial.print(pctBrightness,DEC);
            //Serial.println("%");
            grid.setBrightness(brightness);
            grid.show();
            //delay(500);
          }
          break;
          
        case 1:
          Serial.println("Hour");
          displayHour(setHour);
           
          while(digitalRead(SETPIN)==HIGH){  //Not pressed
            if(digitalRead(LEFTPIN)==LOW){
              while(digitalRead(LEFTPIN)!=HIGH){
              }
              if(setHour<2){
                setHour = 24;
              }
              else{
                setHour = setHour - 1; 
              }
            }
            if(digitalRead(RIGHTPIN)==LOW){
              while(digitalRead(RIGHTPIN)!=HIGH){
              }
              if(setHour>23){
                setHour = 1;
              }
              else{
                setHour = setHour + 1; 
              }
            }
            displayHour(setHour);
            rtc.adjust(DateTime(now.year(),now.month(), now.day(), setHour, now.minute(), now.second()));
            Serial.print("setHour = ");
            Serial.println(setHour,DEC);
            delay(100);
         
          }
          
          break;
          
        case 2:
          Serial.println("Minutes");
          displayMinute(setMinute);
           
          while(digitalRead(SETPIN)==HIGH){  //Not pressed
            if(digitalRead(LEFTPIN)==LOW){
              while(digitalRead(LEFTPIN)!=HIGH){
              }
              if(setMinute<2){
                setMinute = 59;
              }
              else{
                setMinute = setMinute - 1; 
              }
            }
            if(digitalRead(RIGHTPIN)==LOW){
              while(digitalRead(RIGHTPIN)!=HIGH){
              }
              if(setMinute>59){
                setMinute = 1;
              }
              else{
                setMinute = setMinute + 1; 
              }
            }
            displayMinute(setMinute);
            rtc.adjust(DateTime(now.year(),now.month(), now.day(), now.hour(), setMinute, 0));  //reset seconds to 0 as well
            Serial.print("setMinute = ");
            Serial.println(setMinute,DEC);
            delay(100);
         
          }
          break;
          
        case 3:
          Serial.println("3 Settings");
          break;
        default:
          break;
          
      }
    }
    
    while(digitalRead(SETPIN)!=HIGH){
    }
    colorWipe(colorBlack,0);
    Serial.println("End of Settings Mode");
    settingMode = false;
    buzzerBeep(30,100,2);  //buzzerBeep(int frequency,int duration, int loops)
  }
  
  int brightness = dayBrightness * (pctBrightness/100);  //Percentage of day brightness
  
  displayTime();
  checkForBirthday(8,9); //checkForBirthday(D,M)
  
  timeTaken = millis()-capMillis;
  
  timeCount = timeCount+timeTaken;
  
  if(timeCount >20000){
    colorWipe(colorBlack,0);
    paintWord(arrsDay,colorWhite);
    displayNum(now.day(),colorGreen);
    delay(5000);
    colorWipe(colorBlack,0);
    paintWord(arrsMonth,colorWhite);
    displayNum(now.month(),colorBlue);
    delay(5000);
    colorWipe(colorBlack,0);
    timeCount = 0;
  }
  

}

//======================Functions=======================

void displayTime(void){
 
  DateTime now = rtc.now();
  
  Serial.print(now.hour(),DEC);
  Serial.println("hr");
  Serial.print(now.minute(),DEC);
  Serial.println("mins");
  Serial.print(now.second(),DEC);
  Serial.println("secs");
  Serial.print(now.day(),DEC);
  Serial.println("day");
  
  
  //paintWord(arrJIANLI,colorBlue);
  paintWord(arrIT, colorWhite);
  paintWord(arrIS, colorWhite);
  
  //=================Past/To======================
  
  
  
  //==================Minutes======================
  displayMinute(now.minute());
  
  //====================Hours=====================
  
  if(now.minute()<35){
    
    if((now.hour()>0)&&(now.hour()<2)){  //Display ONE
      paintWord(arrTWELVEH,colorBlack);
      paintWord(arrONEH,colorBlue);
    }    
    if((now.hour()>1)&&(now.hour()<3)){  //Display TWO
      paintWord(arrONEH,colorBlack);
      paintWord(arrTWOH,colorBlue);
    }
    if((now.hour()>2)&&(now.hour()<4)){  //Display THREE
      paintWord(arrTWOH,colorBlack);
      paintWord(arrTHREEH,colorBlue);
    }
    if((now.hour()>3)&&(now.hour()<5)){  //Display FOUR
      paintWord(arrTHREEH,colorBlack);
      paintWord(arrFOURH,colorBlue);
    }
    if((now.hour()>4)&&(now.hour()<6)){  //Display FIVE
      paintWord(arrFOURH,colorBlack);
      paintWord(arrFIVEH,colorBlue);
    }
    if((now.hour()>5)&&(now.hour()<7)){  //Display SIX
      paintWord(arrFIVEH,colorBlack);
      paintWord(arrSIXH,colorBlue);
    }
    if((now.hour()>6)&&(now.hour()<8)){  //Display SEVEN
      paintWord(arrSIXH,colorBlack);
      paintWord(arrSEVENH,colorBlue);
    }
    if((now.hour()>7)&&(now.hour()<9)){  //Display EIGHT
      paintWord(arrSEVENH,colorBlack);
      paintWord(arrEIGHTH,colorBlue);
    }
    if((now.hour()>8)&&(now.hour()<10)){  //Display NINE
      paintWord(arrEIGHTH,colorBlack);
      paintWord(arrNINEH,colorBlue);
    }
    if((now.hour()>9)&&(now.hour()<11)){  //Display TEN
      paintWord(arrNINEH,colorBlack);
      paintWord(arrTENH,colorBlue);
    }
    if((now.hour()>10)&&(now.hour()<12)){  //Display ELEVEN
      paintWord(arrTENH,colorBlack);
      paintWord(arrELEVENH,colorBlue);
    }
    if((now.hour()>11)&&(now.hour()<13)){  //Display TWELVE
      paintWord(arrELEVENH,colorBlack);
      paintWord(arrTWELVEH,colorBlue);
    }
    if((now.hour()>12)&&(now.hour()<14)){  //Display ONE PM
      paintWord(arrTENH,colorBlack);
      paintWord(arrONEH,colorBlue);
    }    
    if((now.hour()>13)&&(now.hour()<15)){  //Display TWO PM
      paintWord(arrONEH,colorBlack);
      paintWord(arrTWOH,colorBlue);
    }
    if((now.hour()>14)&&(now.hour()<16)){  //Display THREE PM
      paintWord(arrTWOH,colorBlack);
      paintWord(arrTHREEH,colorBlue);
    }
    if((now.hour()>15)&&(now.hour()<17)){  //Display FOUR PM
      paintWord(arrTHREEH,colorBlack);
      paintWord(arrFOURH,colorBlue);
    }
    if((now.hour()>16)&&(now.hour()<18)){  //Display FIVE PM
      paintWord(arrFOURH,colorBlack);
      paintWord(arrFIVEH,colorBlue);
    }
    if((now.hour()>17)&&(now.hour()<19)){  //Display SIX PM
      paintWord(arrFIVEH,colorBlack);
      paintWord(arrSIXH,colorBlue);
    }
    if((now.hour()>18)&&(now.hour()<20)){  //Display SEVEN PM
      paintWord(arrSIXH,colorBlack);
      paintWord(arrSEVENH,colorBlue);
    }
    if((now.hour()>19)&&(now.hour()<21)){  //Display EIGHT PM
      paintWord(arrSEVENH,colorBlack);
      paintWord(arrEIGHTH,colorBlue);
    }
    if((now.hour()>20)&&(now.hour()<22)){  //Display NINE PM
      paintWord(arrEIGHTH,colorBlack);
      paintWord(arrNINEH,colorBlue);
    }
    if((now.hour()>21)&&(now.hour()<23)){  //Display TEN PM
      paintWord(arrNINEH,colorBlack);
      paintWord(arrTENH,colorBlue);
    }
    if((now.hour()>22)&&(now.hour()<=23)){  //Display ELEVEN PM
      paintWord(arrTENH,colorBlack);
      paintWord(arrELEVENH,colorBlue);
    }
    if(now.hour()>23){  //Display TWELVE PM
      paintWord(arrELEVENH,colorBlack);
      paintWord(arrTWELVEH,colorBlue);
    }  
    
    
  
  }
  else{

    if((now.hour()>11)&&(now.hour()<1)){  //Display ONE
      paintWord(arrTWELVEH,colorBlack);
      paintWord(arrONEH,colorBlue);
    }    
    if((now.hour()>0)&&(now.hour()<2)){  //Display TWO
      paintWord(arrONEH,colorBlack);
      paintWord(arrTWOH,colorBlue);
    }
    if((now.hour()>1)&&(now.hour()<3)){  //Display THREE
      paintWord(arrTWOH,colorBlack);
      paintWord(arrTHREEH,colorBlue);
    }
    if((now.hour()>2)&&(now.hour()<4)){  //Display FOUR
      paintWord(arrTHREEH,colorBlack);
      paintWord(arrFOURH,colorBlue);
    }
    if((now.hour()>3)&&(now.hour()<5)){  //Display FIVE
      paintWord(arrFOURH,colorBlack);
      paintWord(arrFIVEH,colorBlue);
    }
    if((now.hour()>4)&&(now.hour()<6)){  //Display SIX
      paintWord(arrFIVEH,colorBlack);
      paintWord(arrSIXH,colorBlue);
    }
    if((now.hour()>5)&&(now.hour()<7)){  //Display SEVEN
      paintWord(arrSIXH,colorBlack);
      paintWord(arrSEVENH,colorBlue);
    }
    if((now.hour()>6)&&(now.hour()<8)){  //Display EIGHT
      paintWord(arrSEVENH,colorBlack);
      paintWord(arrEIGHTH,colorBlue);
    }
    if((now.hour()>7)&&(now.hour()<9)){  //Display NINE
      paintWord(arrEIGHTH,colorBlack);
      paintWord(arrNINEH,colorBlue);
    }
    if((now.hour()>8)&&(now.hour()<10)){  //Display TEN
      paintWord(arrNINEH,colorBlack);
      paintWord(arrTENH,colorBlue);
    }
    if((now.hour()>9)&&(now.hour()<11)){  //Display ELEVEN
      paintWord(arrTENH,colorBlack);
      paintWord(arrELEVENH,colorBlue);
    }
    if((now.hour()>10)&&(now.hour()<12)){  //Display TWENTY
      paintWord(arrELEVENH,colorBlack);
      paintWord(arrTWELVEH,colorBlue);
    }
    if((now.hour()>11)&&(now.hour()<13)){  //Display ONE PM
      paintWord(arrTENH,colorBlack);
      paintWord(arrONEH,colorBlue);
    }    
    if((now.hour()>12)&&(now.hour()<14)){  //Display TWO PM
      paintWord(arrONEH,colorBlack);
      paintWord(arrTWOH,colorBlue);
    }
    if((now.hour()>13)&&(now.hour()<15)){  //Display THREE PM
      paintWord(arrTWOH,colorBlack);
      paintWord(arrTHREEH,colorBlue);
    }
    if((now.hour()>14)&&(now.hour()<16)){  //Display FOUR PM
      paintWord(arrTHREEH,colorBlack);
      paintWord(arrFOURH,colorBlue);
    }
    if((now.hour()>15)&&(now.hour()<17)){  //Display FIVE PM
      paintWord(arrFOURH,colorBlack);
      paintWord(arrFIVEH,colorBlue);
    }
    if((now.hour()>16)&&(now.hour()<18)){  //Display SIX PM
      paintWord(arrFIVEH,colorBlack);
      paintWord(arrSIXH,colorBlue);
    }
    if((now.hour()>17)&&(now.hour()<19)){  //Display SEVEN PM
      paintWord(arrSIXH,colorBlack);
      paintWord(arrSEVENH,colorBlue);
    }
    if((now.hour()>18)&&(now.hour()<20)){  //Display EIGHT PM
      paintWord(arrSEVENH,colorBlack);
      paintWord(arrEIGHTH,colorBlue);
    }
    if((now.hour()>19)&&(now.hour()<21)){  //Display NINE PM
      paintWord(arrEIGHTH,colorBlack);
      paintWord(arrNINEH,colorBlue);
    }
    if((now.hour()>20)&&(now.hour()<22)){  //Display TEN PM
      paintWord(arrNINEH,colorBlack);
      paintWord(arrTENH,colorBlue);
    }
    if((now.hour()>21)&&(now.hour()<23)){  //Display ELEVEN PM
      paintWord(arrTENH,colorBlack);
      paintWord(arrELEVENH,colorBlue);
    }
    if(now.hour()>22){  //Display TWELVE PM
      paintWord(arrELEVENH,colorBlack);
      paintWord(arrTWELVEH,colorBlue);
    }

  }
  
  
  paintWord(arrOCLOCK,colorWhite);
  
  delay(1000);
  
}

void paintWord(int arrWord[], uint32_t color){
  for(int i = 0; i < grid.numPixels() + 1; i++){
    if(arrWord[i] == -1){
      grid.show();
      break;
    }else{
      grid.setPixelColor(arrWord[i],color);
    }
  }
}
void colorWipe(uint32_t color, uint16_t wait){  //Fills entire Display with colour. Set to Black to clear
  for(int i = 0; i < grid.numPixels() + 1; i++){
      grid.setPixelColor(i,color);
  }
  grid.show();
  delay(wait);
}

void wordTest(void){  //Test all Words
  
  paintWord(arrJIANLI, colorBlue);
  delay(1000);
  paintWord(arrSMILEY, colorBlue);
  delay(1000);
  paintWord(arrHAPPY, colorBlue);
  delay(1000);
  paintWord(arrBIRTHDAY, colorBlue);
  delay(1000);
  paintWord(arrIT, colorBlue);
  delay(1000);
  paintWord(arrIS, colorBlue);
  delay(1000);
  paintWord(arrPAST, colorBlue);
  delay(1000);
  paintWord(arrTO, colorBlue);
  delay(1000);
  paintWord(arrFIVEM, colorBlue);
  delay(1000);
  paintWord(arrTENM, colorBlue);
  delay(1000);
  paintWord(arrTWENTYM, colorBlue);
  delay(1000);
  paintWord(arrQUARTER, colorBlue);
  delay(1000);
  paintWord(arrHALF,colorBlue);
  delay(1000);
  paintWord(arrONEH, colorBlue);
  delay(1000);
  paintWord(arrTWOH, colorBlue);
  delay(1000);
  paintWord(arrTHREEH, colorBlue);
  delay(1000);
  paintWord(arrFOURH, colorBlue);
  delay(1000);
  paintWord(arrFIVEH, colorBlue);
  delay(1000);
  paintWord(arrSIXH, colorBlue);
  delay(1000);
  paintWord(arrSEVENH, colorBlue);
  delay(1000);
  paintWord(arrEIGHTH, colorBlue);
  delay(1000);
  paintWord(arrNINEH, colorBlue);
  delay(1000);
  paintWord(arrTENH, colorBlue);
  delay(1000);  
  paintWord(arrELEVENH, colorBlue);
  delay(1000);
  paintWord(arrJIANLI, colorBlue);
  delay(1000);  
  paintWord(arrTWELVEH, colorBlue);
  delay(1000); 
  paintWord(arrOCLOCK, colorBlue);
  delay(1000);  
  paintWord(arrAM, colorBlue);
  delay(1000);
  paintWord(arrPM, colorBlue);
  delay(1000);
 
  
  delay(5000);
  
  paintWord(arrJIANLI, colorBlue);
  delay(1000);
  colorWipe(colorBlack,0);
  paintWord(arrSMILEY, colorBlue);
  delay(1000);
  colorWipe(colorBlack,0);
  paintWord(arrHAPPY, colorBlue);
  delay(1000);
  colorWipe(colorBlack,0);
  paintWord(arrBIRTHDAY, colorBlue);
  delay(1000);
  colorWipe(colorBlack,0);
  paintWord(arrIT, colorBlue);
  delay(1000);
  colorWipe(colorBlack,0);
  paintWord(arrIS, colorBlue);
  delay(1000);
  colorWipe(colorBlack,0);
  paintWord(arrPAST, colorBlue);
  delay(1000);
  colorWipe(colorBlack,0);
  paintWord(arrTO, colorBlue);
  delay(1000);
  colorWipe(colorBlack,0);
  paintWord(arrFIVEM, colorBlue);
  delay(1000);
  colorWipe(colorBlack,0);
  paintWord(arrTENM, colorBlue);
  delay(1000);
  colorWipe(colorBlack,0);
  paintWord(arrTWENTYM, colorBlue);
  delay(1000);
  colorWipe(colorBlack,0);
  paintWord(arrQUARTER, colorBlue);
  delay(1000);
  colorWipe(colorBlack,0);
  paintWord(arrHALF,colorBlue);
  delay(1000);
  colorWipe(colorBlack,0);
  paintWord(arrONEH, colorBlue);
  delay(1000);
  colorWipe(colorBlack,0);
  paintWord(arrTWOH, colorBlue);
  delay(1000);
  colorWipe(colorBlack,0);
  paintWord(arrTHREEH, colorBlue);
  delay(1000);
  colorWipe(colorBlack,0);
  paintWord(arrFOURH, colorBlue);
  delay(1000);
  colorWipe(colorBlack,0);
  paintWord(arrFIVEH, colorBlue);
  delay(1000);
  colorWipe(colorBlack,0);
  paintWord(arrSIXH, colorBlue);
  delay(1000);
  colorWipe(colorBlack,0);
  paintWord(arrSEVENH, colorBlue);
  delay(1000);
  colorWipe(colorBlack,0);
  paintWord(arrEIGHTH, colorBlue);
  delay(1000);
  colorWipe(colorBlack,0);
  paintWord(arrNINEH, colorBlue);
  delay(1000);
  colorWipe(colorBlack,0);
  paintWord(arrTENH, colorBlue);
  delay(1000);
  colorWipe(colorBlack,0);
  paintWord(arrELEVENH, colorBlue);
  delay(1000);
  colorWipe(colorBlack,0);
  paintWord(arrJIANLI, colorBlue);
  delay(1000);
  colorWipe(colorBlack,0);
  paintWord(arrTWELVEH, colorBlue);
  delay(1000);
  colorWipe(colorBlack,0);
  paintWord(arrOCLOCK, colorBlue);
  delay(1000);
  colorWipe(colorBlack,0);
  paintWord(arrAM, colorBlue);
  delay(1000);
  colorWipe(colorBlack,0);
  paintWord(arrPM, colorBlue);
  delay(1000);
  colorWipe(colorBlack,0);
 
}

void checkForBirthday(int bDay, int bMonth){
  
  DateTime now = rtc.now();
  
  if((now.month()==bMonth)&&(now.day()==bDay)){
    paintWord(arrA,colorPurple);
    paintWord(arrHAPPY,colorPurple);
    paintWord(arrBIRTHDAY,colorPurple);
    paintWord(arrTOu,colorPurple);
    paintWord(arrU,colorPurple);
  }
}

void displayHour(int currHour){  //currHour refers to currHour selected as in settings mode
  switch (currHour){
            
            case 1:
              paintWord(arrTWOH,colorBlack);
              paintWord(arrTWELVEH,colorBlack);
              paintWord(arrONEH,colorWhite);
              paintWord(arrAM,colorWhite);
              paintWord(arrPM,colorBlack);
              break;
              
            case 2:
              paintWord(arrTHREEH,colorBlack);
              paintWord(arrONEH,colorBlack);
              paintWord(arrTWOH,colorWhite);
              paintWord(arrAM,colorWhite);
              paintWord(arrPM,colorBlack);
              break;
              
            case 3:
              paintWord(arrTWOH,colorBlack);
              paintWord(arrFOURH,colorBlack);
              paintWord(arrTHREEH,colorWhite);
              paintWord(arrAM,colorWhite);
              paintWord(arrPM,colorBlack);
              break;
             
            case 4:
              paintWord(arrTHREEH,colorBlack);
              paintWord(arrFIVEH,colorBlack);
              paintWord(arrFOURH,colorWhite);
              paintWord(arrAM,colorWhite);
              paintWord(arrPM,colorBlack);
              break;
            
            case 5:
              paintWord(arrFOURH,colorBlack);
              paintWord(arrSIXH,colorBlack);
              paintWord(arrFIVEH,colorWhite);
              paintWord(arrAM,colorWhite);
              paintWord(arrPM,colorBlack);
              break;
             
            case 6:
              paintWord(arrFIVEH,colorBlack);
              paintWord(arrSEVENH,colorBlack);
              paintWord(arrSIXH,colorWhite);
              paintWord(arrAM,colorWhite);
              paintWord(arrPM,colorBlack);
              break;
             
            case 7:
              paintWord(arrSIXH,colorBlack);
              paintWord(arrEIGHTH,colorBlack);
              paintWord(arrSEVENH,colorWhite);
              paintWord(arrAM,colorWhite);
              paintWord(arrPM,colorBlack);
              break;
             
            case 8:
              paintWord(arrSEVENH,colorBlack);
              paintWord(arrNINEH,colorBlack);
              paintWord(arrEIGHTH,colorWhite);
              paintWord(arrAM,colorWhite);
              paintWord(arrPM,colorBlack);
              break;
             
            case 9:
              paintWord(arrEIGHTH,colorBlack);
              paintWord(arrTENH,colorBlack);
              paintWord(arrNINEH,colorWhite);
              paintWord(arrAM,colorWhite);
              paintWord(arrPM,colorBlack);
              break;
             
            case 10:
              paintWord(arrNINEH,colorBlack);
              paintWord(arrELEVENH,colorBlack);
              paintWord(arrTENH,colorWhite);
              paintWord(arrAM,colorWhite);
              paintWord(arrPM,colorBlack);
              break;
             
            case 11:
              paintWord(arrTWELVEH,colorBlack);
              paintWord(arrTENH,colorBlack);
              paintWord(arrELEVENH,colorWhite);
              paintWord(arrAM,colorWhite);
              paintWord(arrPM,colorBlack);
              break; 
              
            case 12:
              paintWord(arrELEVENH,colorBlack);
              paintWord(arrONEH,colorBlack);
              paintWord(arrTWELVEH,colorWhite);
              paintWord(arrAM,colorWhite);
              paintWord(arrPM,colorBlack);
              break;
              
            case 13:
              paintWord(arrTWOH,colorBlack);
              paintWord(arrTWELVEH,colorBlack);
              paintWord(arrONEH,colorWhite);
              paintWord(arrPM,colorWhite);
              paintWord(arrAM,colorBlack);
              break;
              
            case 14:
              paintWord(arrTHREEH,colorBlack);
              paintWord(arrONEH,colorBlack);
              paintWord(arrTWOH,colorWhite);
              paintWord(arrPM,colorWhite);
              paintWord(arrAM,colorBlack);
              break;
              
            case 15:
              paintWord(arrTWOH,colorBlack);
              paintWord(arrFOURH,colorBlack);
              paintWord(arrTHREEH,colorWhite);
              paintWord(arrPM,colorWhite);
              paintWord(arrAM,colorBlack);
              break;
             
            case 16:
              paintWord(arrTHREEH,colorBlack);
              paintWord(arrFIVEH,colorBlack);
              paintWord(arrFOURH,colorWhite);
              paintWord(arrPM,colorWhite);
              paintWord(arrAM,colorBlack);
              break;
            
            case 17:
              paintWord(arrFOURH,colorBlack);
              paintWord(arrSIXH,colorBlack);
              paintWord(arrFIVEH,colorWhite);
              paintWord(arrPM,colorWhite);
              paintWord(arrAM,colorBlack);
              break;
             
            case 18:
              paintWord(arrFIVEH,colorBlack);
              paintWord(arrSEVENH,colorBlack);
              paintWord(arrSIXH,colorWhite);
              paintWord(arrPM,colorWhite);
              paintWord(arrAM,colorBlack);
              break;
             
            case 19:
              paintWord(arrSIXH,colorBlack);
              paintWord(arrEIGHTH,colorBlack);
              paintWord(arrSEVENH,colorWhite);
              paintWord(arrPM,colorWhite);
              paintWord(arrAM,colorBlack);
              break;
             
            case 20:
              paintWord(arrSEVENH,colorBlack);
              paintWord(arrNINEH,colorBlack);
              paintWord(arrEIGHTH,colorWhite);
              paintWord(arrPM,colorWhite);
              paintWord(arrAM,colorBlack);
              break;
             
            case 21:
              paintWord(arrEIGHTH,colorBlack);
              paintWord(arrTENH,colorBlack);
              paintWord(arrNINEH,colorWhite);
              paintWord(arrPM,colorWhite);
              paintWord(arrAM,colorBlack);
              break;
             
            case 22:
              paintWord(arrNINEH,colorBlack);
              paintWord(arrELEVENH,colorBlack);
              paintWord(arrTENH,colorWhite);
              paintWord(arrPM,colorWhite);
              paintWord(arrAM,colorBlack);
              break;
             
            case 23:
              paintWord(arrTWELVEH,colorBlack);
              paintWord(arrTENH,colorBlack);
              paintWord(arrELEVENH,colorWhite);
              paintWord(arrPM,colorWhite);
              paintWord(arrAM,colorBlack);
              break; 
              
            case 24:
              paintWord(arrELEVENH,colorBlack);
              paintWord(arrONEH,colorBlack);
              paintWord(arrTWELVEH,colorWhite);
              paintWord(arrPM,colorWhite);
              paintWord(arrAM,colorBlack);
              break;
              
            default:
              break;
  }
}

void blinkWord(int arrWord[], uint32_t color, int loops){
  
  for(int i=0;i<loops;i++){  
    paintWord(arrWord,color);
    delay(FASTBLINK);
    paintWord(arrWord,colorBlack);
    delay(FASTBLINK);
  }
}

void displayMinute(int currMinute){
  if(currMinute<35){
    if((currMinute>0)&&(currMinute<5)){  //When under 5 mins from hour
       paintWord(arrTO,colorBlack);
       paintWord(arrPAST,colorBlack);
     }
     else{  //Display PAST
       paintWord(arrO,colorBlack);
       paintWord(arrPAST,colorGreen);
     }
    
  }
  else if(currMinute==60){
    paintWord(arrTO,colorBlack);
    paintWord(arrPAST,colorBlack);
  }
  else{
    paintWord(arrPAS,colorBlack);
    paintWord(arrTO,colorGreen);
  }
  
  
  if((currMinute>0)&&(currMinute<5)){  //Clear FIVEM
    paintWord(arrFIVEM,colorBlack);
    paintWord(arrTENM, colorBlack);
  }
  if((currMinute>4)&&(currMinute<10)){  //Display FIVEM
    paintWord(arrFIVEM,colorBlue);
    paintWord(arrTENM, colorBlack);
  }
  if((currMinute>9)&&(currMinute<15)){  //Display TENM
    paintWord(arrFIVEM,colorBlack);
    paintWord(arrTENM,colorBlue);
    paintWord(arrQUARTER, colorBlack);
  }
  if((currMinute>14)&&(currMinute<20)){  //Display QUARTERM
    paintWord(arrTENM,colorBlack);
    paintWord(arrQUARTER,colorBlue);
    paintWord(arrTWENTYM, colorBlack);
  }
  if((currMinute>19)&&(currMinute<25)){  //Display TWENTYM
    paintWord(arrQUARTER,colorBlack);
    paintWord(arrTWENTYM,colorBlue);
    paintWord(arrdashFIVEM, colorBlack);
  }
  if((currMinute>24)&&(currMinute<30)){  //Display TWENTYFIVEM
    //paintWord(arrTWENTYM,colorBlack);
    paintWord(arrTWENTYFIVEM,colorBlue);
    paintWord(arrHALF, colorBlack);
  }
  if((currMinute>29)&&(currMinute<35)){  //Display HALF
    paintWord(arrTWENTYFIVEM,colorBlack);
    paintWord(arrHALF,colorBlue);
    paintWord(arrQUARTER, colorBlack);
  }
  if((currMinute>34)&&(currMinute<40)){  //Display QUARTER
    paintWord(arrHALF,colorBlack);
    paintWord(arrTWENTYFIVEM,colorBlue);
    //paintWord(arrTWENTYM, colorBlack);
  }
  if((currMinute>39)&&(currMinute<45)){  //Display TWENTYM
    paintWord(arrdashFIVEM,colorBlack);
    paintWord(arrTWENTYM,colorBlue);
    paintWord(arrQUARTER, colorBlack);
  }
  if((currMinute>44)&&(currMinute<50)){  //Display QUARTER
    paintWord(arrTWENTYM,colorBlack);
    paintWord(arrQUARTER,colorBlue);
    paintWord(arrTENM, colorBlack);
  }
  if((currMinute>49)&&(currMinute<55)){  //Display TENM
    paintWord(arrQUARTER,colorBlack);
    paintWord(arrTENM,colorBlue);
    paintWord(arrFIVEM, colorBlack);
  }
  if((currMinute>54)&&(currMinute<60)){  //Display FIVEM
    paintWord(arrTENM,colorBlack);
    paintWord(arrFIVEM,colorBlue);
  }
  if(currMinute==60){
    paintWord(arrFIVEM,colorBlack);  //Clear FIVEM
  }    
  
  if((currMinute==0)||(currMinute==5)||(currMinute==10)||(currMinute==15)||(currMinute==20)||(currMinute==25)||(currMinute==30)||(currMinute==35)||(currMinute==40)||(currMinute==45)||(currMinute==50)||(currMinute==55)||(currMinute==60)){
  paintWord(arrJIANLI,colorBlue);
  }
  if((currMinute==1)||(currMinute==6)||(currMinute==11)||(currMinute==16)||(currMinute==21)||(currMinute==26)||(currMinute==31)||(currMinute==36)||(currMinute==41)||(currMinute==46)||(currMinute==51)||(currMinute==56)){
    paintWord(arrJnM,colorGreen);
    paintWord(arrInM,colorBlue);
    paintWord(arrAnM,colorBlue);
    paintWord(arrNnM,colorBlue);
    paintWord(arrLnM,colorBlue);
    paintWord(arrI2nM,colorBlue);
  }
  if((currMinute==2)||(currMinute==7)||(currMinute==12)||(currMinute==17)||(currMinute==22)||(currMinute==27)||(currMinute==32)||(currMinute==37)||(currMinute==42)||(currMinute==47)||(currMinute==52)||(currMinute==57)){
    paintWord(arrJnM,colorGreen);
    paintWord(arrInM,colorGreen);
    paintWord(arrAnM,colorBlue);
    paintWord(arrNnM,colorBlue);
    paintWord(arrLnM,colorBlue);
    paintWord(arrI2nM,colorBlue);
  }
  if((currMinute==3)||(currMinute==8)||(currMinute==13)||(currMinute==18)||(currMinute==23)||(currMinute==28)||(currMinute==33)||(currMinute==38)||(currMinute==43)||(currMinute==48)||(currMinute==53)||(currMinute==58)){
    paintWord(arrJnM,colorGreen);
    paintWord(arrInM,colorGreen);
    paintWord(arrAnM,colorGreen);
    paintWord(arrNnM,colorBlue);
    paintWord(arrLnM,colorBlue);
    paintWord(arrI2nM,colorBlue);
  }
  if((currMinute==4)||(currMinute==9)||(currMinute==14)||(currMinute==19)||(currMinute==24)||(currMinute==29)||(currMinute==34)||(currMinute==39)||(currMinute==44)||(currMinute==49)||(currMinute==54)||(currMinute==59)){
    paintWord(arrJnM,colorGreen);
    paintWord(arrInM,colorGreen);
    paintWord(arrAnM,colorGreen);
    paintWord(arrNnM,colorGreen);
    paintWord(arrLnM,colorBlue);
    paintWord(arrI2nM,colorBlue);
  }  
  
}
void displayNum(int num, uint32_t color){
  if(num==0){
    paintWord(arr3Tens,colorBlack);
    paintWord(arr2Tens,colorBlack);
    paintWord(arr1Tens,colorBlack);
    paintWord(arr9,colorBlack);
    paintWord(arr1,colorBlack);
    
    paintWord(arr0,color);
  }
  if(num==1){
    paintWord(arr3Tens,colorBlack);
    paintWord(arr2Tens,colorBlack);
    paintWord(arr1Tens,colorBlack);
    paintWord(arr0,colorBlack);
    paintWord(arr2,colorBlack);

    paintWord(arr1,color);
  }
  if(num==2){
    paintWord(arr3Tens,colorBlack);
    paintWord(arr2Tens,colorBlack);
    paintWord(arr1Tens,colorBlack);
    paintWord(arr1,colorBlack);
    paintWord(arr3,colorBlack);
    
    paintWord(arr2,color);
  }
  if(num==3){
    paintWord(arr3Tens,colorBlack);
    paintWord(arr2Tens,colorBlack);
    paintWord(arr1Tens,colorBlack);
    paintWord(arr2,colorBlack);
    paintWord(arr4,colorBlack);
    
    paintWord(arr3,color);
  }
  if(num==4){
    paintWord(arr3Tens,colorBlack);
    paintWord(arr2Tens,colorBlack);
    paintWord(arr1Tens,colorBlack);
    paintWord(arr3,colorBlack);
    paintWord(arr5,colorBlack);
    
    paintWord(arr4,color);
  }
  if(num==5){
    paintWord(arr3Tens,colorBlack);
    paintWord(arr2Tens,colorBlack);
    paintWord(arr1Tens,colorBlack);
    paintWord(arr4,colorBlack);
    paintWord(arr6,colorBlack);
    
    paintWord(arr5,color);
  }
  if(num==6){
    paintWord(arr3Tens,colorBlack);
    paintWord(arr2Tens,colorBlack);
    paintWord(arr1Tens,colorBlack);
    paintWord(arr5,colorBlack);
    paintWord(arr7,colorBlack);
    
    paintWord(arr6,color);
  }
  if(num==7){
    paintWord(arr3Tens,colorBlack);
    paintWord(arr2Tens,colorBlack);
    paintWord(arr1Tens,colorBlack);
    paintWord(arr6,colorBlack);
    paintWord(arr8,colorBlack);
    
    paintWord(arr7,color);
  }
  if(num==8){
    paintWord(arr3Tens,colorBlack);
    paintWord(arr2Tens,colorBlack);
    paintWord(arr1Tens,colorBlack);
    paintWord(arr7,colorBlack);
    paintWord(arr9,colorBlack);
    
    paintWord(arr8,color);
  }
  if(num==9){
    paintWord(arr3Tens,colorBlack);
    paintWord(arr2Tens,colorBlack);
    paintWord(arr1Tens,colorBlack);
    paintWord(arr8,colorBlack);
    paintWord(arr0,colorBlack);
    
    paintWord(arr9,color);
  }
  if(num==10){
    paintWord(arr2Tens,colorBlack);
    paintWord(arr3Tens,colorBlack);
    paintWord(arr9,colorBlack);
    paintWord(arr1,colorBlack);
    
    paintWord(arr1Tens,color);
    paintWord(arr0,color);
  }
  if(num==11){
    paintWord(arr2Tens,colorBlack);
    paintWord(arr3Tens,colorBlack);
    paintWord(arr0,colorBlack);
    paintWord(arr2,colorBlack);
    
    paintWord(arr1Tens,color);
    paintWord(arr1,color);
  }
  if(num==12){
    paintWord(arr2Tens,colorBlack);
    paintWord(arr3Tens,colorBlack);
    paintWord(arr1,colorBlack);
    paintWord(arr3,colorBlack);
    
    paintWord(arr1Tens,color);
    paintWord(arr2,color);
  }
  if(num==13){
    paintWord(arr2Tens,colorBlack);
    paintWord(arr3Tens,colorBlack);
    paintWord(arr2,colorBlack);
    paintWord(arr4,colorBlack);
    
    paintWord(arr1Tens,color);
    paintWord(arr3,color);
  }
  if(num==14){
    paintWord(arr2Tens,colorBlack);
    paintWord(arr3Tens,colorBlack);
    paintWord(arr3,colorBlack);
    paintWord(arr5,colorBlack);
    
    paintWord(arr1Tens,color);
    paintWord(arr4,color);
  }
  if(num==15){
    paintWord(arr2Tens,colorBlack);
    paintWord(arr3Tens,colorBlack);
    paintWord(arr4,colorBlack);
    paintWord(arr6,colorBlack);
    
    paintWord(arr1Tens,color);
    paintWord(arr5,color);
  }
  if(num==16){
    paintWord(arr2Tens,colorBlack);
    paintWord(arr3Tens,colorBlack);
    paintWord(arr5,colorBlack);
    paintWord(arr7,colorBlack);
    
    paintWord(arr1Tens,color);
    paintWord(arr6,color);
  }
  if(num==17){
    paintWord(arr2Tens,colorBlack);
    paintWord(arr3Tens,colorBlack);
    paintWord(arr6,colorBlack);
    paintWord(arr8,colorBlack);
    
    paintWord(arr1Tens,color);
    paintWord(arr7,color);
  }
  if(num==18){
    paintWord(arr2Tens,colorBlack);
    paintWord(arr3Tens,colorBlack);
    paintWord(arr7,colorBlack);
    paintWord(arr9,colorBlack);
    
    paintWord(arr1Tens,color);
    paintWord(arr8,color);
  }
  if(num==19){
    paintWord(arr2Tens,colorBlack);
    paintWord(arr3Tens,colorBlack);
    paintWord(arr8,colorBlack);
    paintWord(arr0,colorBlack);
    
    paintWord(arr1Tens,color);
    paintWord(arr9,color);
  }
  if(num==20){
    paintWord(arr1Tens,colorBlack);
    paintWord(arr3Tens,colorBlack);
    paintWord(arr9,colorBlack);
    paintWord(arr1,colorBlack);
    
    paintWord(arr2Tens,color);
    paintWord(arr0,color);
  }
  if(num==21){
    paintWord(arr1Tens,colorBlack);
    paintWord(arr3Tens,colorBlack);
    paintWord(arr0,colorBlack);
    paintWord(arr2,colorBlack);
    
    paintWord(arr2Tens,color);
    paintWord(arr1,color);
  }
  if(num==22){
    paintWord(arr1Tens,colorBlack);
    paintWord(arr3Tens,colorBlack);
    paintWord(arr1,colorBlack);
    paintWord(arr3,colorBlack);
    
    paintWord(arr2Tens,color);
    paintWord(arr2,color);
  }
  if(num==23){
    paintWord(arr1Tens,colorBlack);
    paintWord(arr3Tens,colorBlack);
    paintWord(arr2,colorBlack);
    paintWord(arr4,colorBlack);
    
    paintWord(arr2Tens,color);
    paintWord(arr3,color);
  }
  if(num==24){
    paintWord(arr1Tens,colorBlack);
    paintWord(arr3Tens,colorBlack);
    paintWord(arr3,colorBlack);
    paintWord(arr5,colorBlack);
    
    paintWord(arr2Tens,color);
    paintWord(arr4,color);
  }
  if(num==25){
    paintWord(arr1Tens,colorBlack);
    paintWord(arr3Tens,colorBlack);
    paintWord(arr4,colorBlack);
    paintWord(arr6,colorBlack);
    
    paintWord(arr2Tens,color);
    paintWord(arr5,color);
  }
  if(num==26){
    paintWord(arr1Tens,colorBlack);
    paintWord(arr3Tens,colorBlack);
    paintWord(arr5,colorBlack);
    paintWord(arr7,colorBlack);
    
    paintWord(arr2Tens,color);
    paintWord(arr6,color);
  }
  if(num==27){
    paintWord(arr1Tens,colorBlack);
    paintWord(arr3Tens,colorBlack);
    paintWord(arr6,colorBlack);
    paintWord(arr8,colorBlack);
    
    paintWord(arr2Tens,color);
    paintWord(arr7,color);
  }
  if(num==28){
    paintWord(arr1Tens,colorBlack);
    paintWord(arr3Tens,colorBlack);
    paintWord(arr7,colorBlack);
    paintWord(arr9,colorBlack);
    
    paintWord(arr2Tens,color);
    paintWord(arr8,color);
  }
  if(num==29){
    paintWord(arr1Tens,colorBlack);
    paintWord(arr3Tens,colorBlack);
    paintWord(arr8,colorBlack);
    paintWord(arr0,colorBlack);
    
    paintWord(arr2Tens,color);
    paintWord(arr9,color);
  }
  if(num==30){
    paintWord(arr2Tens,colorBlack);
    paintWord(arr1Tens,colorBlack);
    paintWord(arr9,colorBlack);
    paintWord(arr1,colorBlack);
    
    paintWord(arr3Tens,color);
    paintWord(arr0,color);
  }
  if(num==31){
    paintWord(arr2Tens,colorBlack);
    paintWord(arr1Tens,colorBlack);
    paintWord(arr0,colorBlack);
    paintWord(arr2,colorBlack);
    
    paintWord(arr3Tens,color);
    paintWord(arr1,color);
  }
}

void buzzerBeep(int frequency,int duration, int loops){ 
  for(int i=0;i<loops;i++){  
    tone(BUZZER, frequency);
    delay(duration);
    noTone(BUZZER);
    delay(duration);
  }
}
