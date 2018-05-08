/*
  Pin connections
  Arduino   device
  Ground    LCD ground
  +5VDC     Vcc
  +3.3V  OLED Monitor (VCC)
  A0    input for data read (5 VDC limit)
  A1    input voltage to adjust PWM (optional used here for demo purposes)
  A2
  A3
  A4    SDA (if no SDA pin)
  A5    SCL (if not SCL pin)
  0     Left Push Button (RX0)
  1     MiddlePush Button (TX1)
  2    
  3     Momentary Switch Push button. Trigers Relay (Other end goes to ground)
  4
  5
  6
  7     Pin to 5v Relay
  8
  9     
  10
  11
  12
  13
  SDA   SDA
  SLC   SLC
*/
#include <Adafruit_SSD1306.h>
#include <Pushbutton.h>

#define OLED_RESET    4

#define LEFT_PIN      0
#define MULTI_FNC_PIN    1 
#define RIGHT_PIN     2
#define BUTTON_PIN    3
#define RELAY_PIN     7  // The pin to which the Relay Control signal is sent

Adafruit_SSD1306 display(OLED_RESET);

unsigned int interval = 0;
unsigned int tmrInterval = 0;

/*
unsigned int pulse01Interval = 1;
unsigned int pulse02Interval = 1;
unsigned int interPulseDelay = 1;
*/

unsigned int tmrPulse01Interval = 1;
unsigned int tmrPulse02Interval = 1;
unsigned int tmrDelayInterval = 1;

String  durationTitle;

int mxTimeUnits = 1000;
int intvlIncrArr[] = {10,1,1,1}; //[usec, msec, sec, min]
int tmIntvlIncr = 1;
const int BAUD_RATE = 9600;

int ledPin = 13;
volatile int buttonFlag;

int menuitem = 1;
int page = 1;
int TuPgMenuItm = 1;
String  TmUnitChosen = "msec";
String menuItemDesc[] = {"Not Used", "Pulse 1:", "Delay: ", "Pulse 2:"};

volatile boolean up = false;
volatile boolean down = false;
volatile boolean middle = false;

int downButtonState = 0;
int upButtonState = 0;
int selectButtonState = 0;
int lastDownButtonState = 0;
int lastSelectButtonState = 0;
int lastUpButtonState = 0;

//We need to track how long the momentary pushbutton is held in order to execute different commands
//This value will be recorded in seconds
float pressLength_milliSeconds = 0;

// Define the *minimum* length of time, in milli-seconds, that the button must be pressed for a particular option to occur
int optionOne_milliSeconds = 100;
int optionTwo_milliSeconds = 1000;        

Pushbutton button(BUTTON_PIN);

void setup() {
  //pinMode(BUTTON_PIN, INPUT_PULLUP); //D3
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), ISR_button, FALLING);
 
  pinMode(MULTI_FNC_PIN, INPUT_PULLUP); //D1
  pinMode(LEFT_PIN, INPUT_PULLUP);  //D0
  pinMode(RELAY_PIN, OUTPUT);

  Serial.begin(BAUD_RATE);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
}

void loop() {

  if (buttonFlag && button.getSingleDebouncedRelease())
  {
    detachInterrupt(digitalPinToInterrupt(BUTTON_PIN));
    display.clearDisplay();
    display.setTextColor(WHITE, BLACK);
    display.setCursor(35, 0);
    display.print("Pulse Active!!!");
    display.display();
    
    // Fire Pulse 01
    digitalWrite(RELAY_PIN, HIGH);
    digitalWrite(ledPin, HIGH);
    delay(tmrPulse01Interval);
    digitalWrite(RELAY_PIN, LOW);
    digitalWrite(ledPin, LOW);

    // Delay Second Pulse for intended Duration
    delay(tmrDelayInterval);

    // Fire Pulse 02
    digitalWrite(RELAY_PIN, HIGH);
    digitalWrite(ledPin, HIGH);
    delay(tmrPulse02Interval);
    digitalWrite(RELAY_PIN, LOW);
    digitalWrite(ledPin, LOW);

    buttonFlag = 0;
    digitalWrite(BUTTON_PIN, HIGH);
    attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), ISR_button, FALLING);
  }

  drawMenu();

  // set middle & down vars dependent upon time D1 pressed 
  set_middle_dwn_vars();
  
  //downButtonState = digitalRead(2);
  //selectButtonState = digitalRead(1);
  upButtonState =   digitalRead(0);

  //checkIfDownButtonIsPressed();
  checkIfUpButtonIsPressed();
  //checkIfSelectButtonIsPressed();

  if (up && page == 1 ) {
    up = false;
    menuitem--;
    if (menuitem == 0)
    {
      menuitem = 3;
    }
  } else if (up && page == 3 && interval > 0 ) {
    up = false;
    interval -= tmIntvlIncr;
    interval %= mxTimeUnits;
    interval = abs (interval); 
  }


  if (down && page == 1) {
    down = false;
    menuitem++;
    if (menuitem == 4)
    {
      menuitem = 1;
    }
  } else if (down && page == 2) {
    down = false;
    TuPgMenuItm++;
    if (TuPgMenuItm == 5)
    {
      TuPgMenuItm = 1;
    }
  
  } else if (down && page == 3 && interval == 0) {
    down = false;
    interval += tmIntvlIncr;
  } else if (down && page == 3 ) {
    down = false;
    interval += tmIntvlIncr;
    interval %= mxTimeUnits;
  }

  if (middle) {
    middle = false;

    if (page == 1) {
      durationTitle = menuItemDesc[menuitem];
     switch (menuitem) {
      case 1:
        interval = tmrPulse01Interval;
        break;
      case 2:
        interval = tmrDelayInterval;
        break;
      case 3:
        interval = tmrPulse02Interval;
        break;
      default:
        interval = 0;
     }     
      page = 3;
    } else if (page == 3) {
      if (menuitem == 1 ){
        tmrPulse01Interval = interval;
      }  else if (menuitem == 2 ) {
        tmrDelayInterval = interval;
      } else if (menuitem == 3 ){
        tmrPulse02Interval = interval;
      } 
      page = 1;
    }
  }

}

void checkIfDownButtonIsPressed()
{
  if (downButtonState != lastDownButtonState)
  {
    if (downButtonState == 0)
    {
      down = true;
    }
    delay(50);
  }
  lastDownButtonState = downButtonState;
}

void checkIfUpButtonIsPressed()
{
  if (upButtonState != lastUpButtonState)
  {
    if (upButtonState == 0) {
      up = true;
    }
    delay(50);
  }
  lastUpButtonState = upButtonState;
}

void checkIfSelectButtonIsPressed()
{
  if (selectButtonState != lastSelectButtonState)
  {
    if (selectButtonState == 0) {
      middle = true;
    }
    delay(50);
  }
  lastSelectButtonState = selectButtonState;
}


void drawMenu()
{

  if (page == 1)
  {
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(WHITE, BLACK);
    display.setCursor(15, 0);
    display.print("PULSE MENU");
    display.drawFastHLine(0, 10, 83, WHITE);
    display.setCursor(0, 15);

    if (menuitem == 1)
    {
      display.setTextColor(BLACK, WHITE);
    }
    else
    {
      display.setTextColor(WHITE, BLACK);
    }
    String intStr;
    intStr += tmrPulse01Interval;
    display.print(">"+ menuItemDesc[1] + intStr + " " + TmUnitChosen);
    
    display.setCursor(0, 25);

    if (menuitem == 2)
    {
      display.setTextColor(BLACK, WHITE);
    }
    else
    {
      display.setTextColor(WHITE, BLACK);
    }
    String intStr2;
    intStr2 += tmrDelayInterval;   
    display.print(">"+ menuItemDesc[2] + intStr2 + " " + TmUnitChosen);

    display.setCursor(0, 35);

    if (menuitem == 3)
    {
      display.setTextColor(BLACK, WHITE);
    }
    else
    {
      display.setTextColor(WHITE, BLACK);
    }
    String intStr3;
    intStr3 += tmrPulse02Interval;
    display.print(">"+ menuItemDesc[3] + intStr3 + " " + TmUnitChosen);
    display.display();
  }
  else if (page == 3)
  {

    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(WHITE, BLACK);
    display.setCursor(15, 0);
    display.print(durationTitle);
    display.drawFastHLine(0, 10, 83, WHITE);
    display.setCursor(5, 15);
    display.print("Value in: " +  TmUnitChosen);
    display.setTextSize(2);
    display.setCursor(5, 25);
    display.print(interval);

    display.setTextSize(2);
    display.display();
  }  
}

void resetDefaults()
{
  interval = 0;
  tmrInterval = 0;
  mxTimeUnits = 0;
  tmIntvlIncr = 1;
  TmUnitChosen = "msec";
}

void ISR_button()
{
    // Just a handler for the pin interrupt.
    buttonFlag = 1;
}

void set_middle_dwn_vars()
{

  //Record *roughly* the tenths of seconds the button in being held down
  while (digitalRead(MULTI_FNC_PIN) == LOW ){ 

    delay(100);  //if you want more resolution, lower this number 
    pressLength_milliSeconds = pressLength_milliSeconds + 100;

  }//close while


  //Different if-else conditions are triggered based on the length of the button press
  //Start with the longest time option first

  //Option 2 - Execute the second option if the button is held for the correct amount of time
  if (pressLength_milliSeconds >= optionTwo_milliSeconds){

    middle = true;     

  } 

  //option 1 - Execute the first option if the button is held for the correct amount of time
  else if(pressLength_milliSeconds >= optionOne_milliSeconds){

    down = true;  

  }//close if options


  //every time through the loop, we need to reset the pressLength_Seconds counter
  pressLength_milliSeconds = 0;
}
