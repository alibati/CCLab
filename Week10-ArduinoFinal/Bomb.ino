
#define DIGIT1 2
#define DIGIT2 3
#define DIGIT3 5
#define DIGIT4 6

#define SEGMENTA 7
#define SEGMENTB 8
#define SEGMENTC 9
#define SEGMENTD 10
#define SEGMENTE 11
#define SEGMENTF 12
#define SEGMENTG A0

#define COLON 4
#define AMPM A1

#define BUTTON A5

#define STOPWIRE  A2
#define SPEEDWIRE A3
#define ZEROWIRE  A4

#define ACTION 13

#define ON  HIGH
#define OFF LOW

#define DELAYTIME 50

unsigned short hours, minutes, seconds;
unsigned long lastTime; 

int buttonState;             
int lastButtonState = LOW;   
unsigned long button_down_start = 0; 
unsigned long lastDebounceTime = 0;  
unsigned long debounceDelay = 50;    

byte flash;    
byte flash_on; 
byte timer_stopped;

#define ONE_SECOND 1000
#define FLASH_TIME 100
unsigned long time_chunk;

void setup() {
  
  Serial.begin(9600);
  
  
  pinMode(DIGIT1, OUTPUT);
  pinMode(DIGIT2, OUTPUT);
  pinMode(DIGIT3, OUTPUT);
  pinMode(DIGIT4, OUTPUT);

  pinMode(SEGMENTA, OUTPUT);
  pinMode(SEGMENTB, OUTPUT);
  pinMode(SEGMENTC, OUTPUT);
  pinMode(SEGMENTD, OUTPUT);
  pinMode(SEGMENTE, OUTPUT);
  pinMode(SEGMENTF, OUTPUT);
  pinMode(SEGMENTG, OUTPUT);

  pinMode(COLON, OUTPUT);
  pinMode(AMPM, OUTPUT);
  
  
  pinMode(BUTTON, INPUT);
  
  
  pinMode(STOPWIRE, INPUT);
  pinMode(SPEEDWIRE, INPUT);
  pinMode(ZEROWIRE, INPUT);
  
  
  pinMode(ACTION, OUTPUT);
  
  
  hours = 0;
  minutes = 0;
  seconds = 10;

  flash = 0;
  flash_on = 0;
  timer_stopped = 0;

  time_chunk = ONE_SECOND;

  lastTime = millis();
}

void loop() {
  
    
  while (millis() - lastTime < time_chunk) {
        
    if (!flash || flash_on) {
      
      if (hours > 0) {
        clock_show_time(hours, minutes);
       if (seconds % 2 == 0) {
          clock_show_colon();
        }
      }
      else {
        clock_show_time(minutes, seconds);
        clock_show_colon(); 
      }
      
    }
    

    if (digitalRead(STOPWIRE) == LOW) {  
      timer_stopped = true;
    }
    else {
      timer_stopped = false;
    }
    
    if (digitalRead(SPEEDWIRE) == LOW) { 
      flash = 1;
      time_chunk = FLASH_TIME;
    }
    
    if (digitalRead(ZEROWIRE) == LOW) {  
      hours = 0;
      minutes = 0;
      seconds = 0;
      time_chunk = FLASH_TIME;
    }
    
    
    int reading = digitalRead(BUTTON);
 
     
    if (reading != lastButtonState) {
      lastDebounceTime = millis();
    }
    
    if ((millis() - lastDebounceTime) > debounceDelay) {
      if (buttonState != reading) {
        button_down_start = millis();
      }
      
      buttonState = reading;
      

      if (buttonState == HIGH) {
        flash = 0; 
        digitalWrite(ACTION, OFF); 
        time_chunk = ONE_SECOND; 
          
        
        if ((millis() % 10) == 0) {
          
          if ((millis() - button_down_start) > 5000) {
            seconds += 10;
            if (seconds > 59) seconds = 59;
          }
          
          
          incrementTime();
        }
      }
    } 
 
    lastButtonState = reading;
  }

  lastTime += time_chunk;
  
  if (!timer_stopped) {
    decrementTime();
  }
  
  if (flash) {
    flash_on = !flash_on;
  }

}

void decrementTime() {

      if (seconds == 0) {
      
        if (minutes == 0) {
        
          if (hours == 0) {          
            flash = 1;
            time_chunk = FLASH_TIME;
            do_action();
          }
          else {
            minutes = 59;
            hours--;
          }
        }
        else {
          seconds = 59;
          minutes--;
        }
        
      }
      else {
        seconds--;  
      }
}


void incrementTime() {
  
  if (seconds == 59) {
    seconds = 0;
    
    if (minutes == 59) {
      minutes = 0;
      
      if (hours == 12) {          
        hours = 1;
      }
      else {
        hours++;
      }
    }
    else {
      minutes++;
    }
  }
  else {
    seconds++;  
  }
}


void clock_show_time(unsigned short hours, unsigned short minutes) {
  unsigned short i;
  unsigned short delaytime;
  unsigned short num_leds[10] = { 6, 2, 5, 5, 4, 5, 6, 3, 7, 6 };
  unsigned short digit[4];
  unsigned short hide_leading_hours_digit;
    

  if (hours > 99) hours = 99;
  if (minutes > 59) minutes = 59;
  

  if (hours < 10 && hours > 0) {
    hide_leading_hours_digit = 1;
  }
  else {
    hide_leading_hours_digit = 0;
  }
  
  digit[0] = hours / 10;
  digit[1] = hours % 10; // remainder
  digit[2] = minutes / 10;
  digit[3] = minutes % 10; // remainder  

  for (i = hide_leading_hours_digit; i < 4; i++) {
    clock_all_off();
    clock_show_digit(i, digit[i]);
    delaytime = num_leds[digit[i]] * DELAYTIME;   
    delayMicroseconds(delaytime);
  }
    
  clock_all_off();
}


void clock_all_off(void) {
  
  
  digitalWrite(DIGIT1, OFF);
  digitalWrite(DIGIT2, OFF);
  digitalWrite(DIGIT3, OFF);
  digitalWrite(DIGIT4, OFF);
  
  
  digitalWrite(SEGMENTA, ON);
  digitalWrite(SEGMENTB, ON);
  digitalWrite(SEGMENTC, ON);
  digitalWrite(SEGMENTD, ON);
  digitalWrite(SEGMENTE, ON);
  digitalWrite(SEGMENTF, ON);
  digitalWrite(SEGMENTG, ON);
  
  
  digitalWrite(COLON, OFF);
  digitalWrite(AMPM, OFF);
}


void clock_show_digit(unsigned short position, unsigned short value) {
  byte a;
  byte b;
  byte c;
  byte d;
  byte e;
  byte f;
  byte g;

  switch (position) {
    case 0:
      digitalWrite(DIGIT1, ON);
      break;
    case 1:
      digitalWrite(DIGIT2, ON);
      break;
    case 2:
      digitalWrite(DIGIT3, ON);
      break;
    case 3:
      digitalWrite(DIGIT4, ON);
      break;
  }

  a = !(value == 1 || value == 4);
  b = !(value == 5 || value == 6);
  c = !(value == 2);
  d = !(value == 1 || value == 4 || value == 7);
  e =  (value == 0 || value == 2 || value == 6 || value == 8);
  f = !(value == 1 || value == 2 || value == 3 || value == 7);
  g = !(value == 0 || value == 1 || value == 7);
  
  if (a) digitalWrite(SEGMENTA, OFF);
  if (b) digitalWrite(SEGMENTB, OFF);
  if (c) digitalWrite(SEGMENTC, OFF);
  if (d) digitalWrite(SEGMENTD, OFF);
  if (e) digitalWrite(SEGMENTE, OFF);
  if (f) digitalWrite(SEGMENTF, OFF);
  if (g) digitalWrite(SEGMENTG, OFF);
}


void clock_show_colon(void) {
  unsigned short delaytime;

  digitalWrite(COLON, ON);  
                             
  delaytime = DELAYTIME * 2;  
  delayMicroseconds(delaytime);
  digitalWrite(COLON, OFF);
}


void clock_show_ampm(void) {
  unsigned short delaytime;

  digitalWrite(AMPM, ON);
                      
  delaytime = DELAYTIME;  
  delayMicroseconds(delaytime); 
  digitalWrite(AMPM, OFF);
}


static void do_action(void) {
  digitalWrite(ACTION, ON);
  Serial.println("ACTION!");
}
