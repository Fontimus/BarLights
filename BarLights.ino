/*
BarLights!
 C.Font 27 October 2014
 Using a momentary button, an LED strip and 3 potentiometers to 
 make the LEDs enter one of 9 settings
 Feel free to use/modify this code for all your project needs!
 */

int R = 9; //Red Pin
int G = 10; //Green Pin
int B = 11; //Blue Pin
int Rpot = A0;  // Potentiometer pin for Red
int Gpot = A1;  // Potentiometer pin for Green
int Bpot = A2;  // Potentiometer pin for Blue
int button = 7;  // Switch Pin
int setting = 0;  // LED setting
int x[2]= {     // To Check if button went from HIGH to LOW
  1,1};
int RGB[3] = {
  0,0,0};
int Rclr = 0;     // Default Red amount for fade setting
int Gclr = 0;     // Default Green amount for fade setting
int Bclr = 0;     // Default Blue amount for fade setting
int Rchange = 5;    // Amount the Red LED will change each iteration in fade setting
int Gchange = 5;    // Amount the Green LED will change each iteration in fade setting
int Bchange = 5;    // Amount the Blue LED will change each iteration in fade setting
int timedelay = 100;  // milliseconds between each color change in fade
int flag = 0;

void setup(){
  pinMode(R,OUTPUT);
  pinMode(G,OUTPUT);
  pinMode(B,OUTPUT);
  pinMode(button,INPUT_PULLUP);
}


void loop(){
  x[1] = digitalRead(button);   // Checks current button state
  if(x[1] == 0 && x[0] == 1){
    setting = setting++;
  }

  if (setting >= 10){ // Restarts the setting cycle after last one
    setting = 0;
  }

  switch(setting){  // Checks the variable setting and performs the case that matches it
  case 0: // White 
    analogWrite(R,255);
    analogWrite(G,255);
    analogWrite(B,255);
    break;
  case 1:  // Red
    analogWrite(R,255);
    analogWrite(G,0);
    analogWrite(B,0);
    break;
  case 2:  // Green
    analogWrite(R,0);
    analogWrite(G,255);
    analogWrite(B,0);
    break;    
  case 3:  //  Blue
    analogWrite(R,0);
    analogWrite(G,0);
    analogWrite(B,255);
    break;  
  case 4:  //  Cyan
    analogWrite(R,0);
    analogWrite(G,255);
    analogWrite(B,255);
    break;  
  case 5:  //  Yellow
    analogWrite(R,255);
    analogWrite(G,255);
    analogWrite(B,0);
    break;  
  case 6:  //  Purple
    analogWrite(R,255);
    analogWrite(G,0);
    analogWrite(B,255);
    break;
  case 7:  // Fade
    while(flag == 0){
      delay(500); // Without this delay case 7 would get skipped from previous button press
      Initialize();
      TurnOnBlue();
      TurnOnGreen();
      TurnOffBlue();
      TurnOnRed();
      TurnOffGreen();
      TurnOnBlue();
      TurnOffRed();
      TurnOnGreen();
      TurnOnRed();
      TurnOffBlue();
      TurnOffGreen();
      TurnOnGreen();
      TurnOffRed();
      TurnOnBlue();
      TurnOffGreen();
      TurnOnRed();
      TurnOnGreen();
      TurnOffBlue();
      TurnOffRed();
      TurnOffGreen();
      Initialize();
    }
    setting++;
    Rclr = 0;
    Gclr = 0;
    Bclr = 0;
    flag = 0;
    break;

  case 8:  //  Christmas Setting: Red & Green alternate ON/OFF every 1/2 second
    while(digitalRead(button) == HIGH){
      if(digitalRead(button) == LOW){
        setting++;
        break;
      }
      digitalWrite(R,HIGH);
      delay(500);
      digitalWrite(R,LOW);
      digitalWrite(G,HIGH);
      delay(500);
      digitalWrite(G,LOW);
    }
  case 9: // Custom color setting using potentiometers
    while(digitalRead(button) == HIGH){
      if(digitalRead(button) == LOW){
        setting++;
        break;
      }        
      RGB[1] = map(analogRead(Rpot),0,1023,0,250);
      RGB[2] = map(analogRead(Gpot),0,1023,0,250);
      RGB[3] = map(analogRead(Bpot),0,1023,0,250); 
      analogWrite(R, RGB[1]);
      analogWrite(G, RGB[2]);
      analogWrite(B, RGB[3]);
    }

  }
  x[0] = x[1];  // stores previous button state
}

//  Functions

void Initialize(){  // Starts with all LEDs off
  Rclr = 0;
  Gclr = 0;
  Bclr = 0; 
  analogWrite(R, 0);
  analogWrite(G, 0);
  analogWrite(B, 0);
}

void TurnOnBlue(){  // Turn on Blue as long as button hasn't been pressed
  if (flag == 1){
    Bclr = 251;
  }    
  while(Bclr <= 250){
    Bclr2 = Bclr;
    if(digitalRead(button) == LOW){
      flag = 1;
      //setting++;
      break;
    }
    Bclr = Bclr + Bchange;
    analogWrite(B, Bclr);
    delay(timedelay);
  }
}


void TurnOffBlue(){ // Turn off Blue as long as button hasn't been pressed
  if (flag == 1){
    Bclr = 4;
  }
  while(Bclr >= 5){
    if(digitalRead(button) == LOW){
      flag = 1;
      // setting++;
      break;
    }
    Bclr = Bclr - Bchange;
    analogWrite(B, Bclr);
    delay(timedelay);
  }
}

void TurnOnRed(){ // Turn on Red as long as button hasn't been pressed
  if (flag == 1){
    Rclr = 251;
  }
  while(Rclr <= 250){
    if(digitalRead(button) == LOW){
      flag = 1;
      //setting++;
      break;
    }
    Rclr = Rclr + Rchange;
    analogWrite(R, Rclr);
    delay(timedelay);
  }
}

void TurnOffRed(){  // Turn off Red as long as button hasn't been pressed
  if (flag == 1){
    Rclr = 4;
  }
  while(Rclr >= 5){
    if(digitalRead(button) == LOW){
      flag = 1;
      // setting++;
      break;
    }
    Rclr = Rclr - Rchange;
    analogWrite(R, Rclr);
    delay(timedelay);
  }
}

void TurnOnGreen(){ // Turn on Green as long as button hasn't been pressed
  if (flag == 1){
    Gclr = 251;
  }
  while(Gclr <= 250){
    if(digitalRead(button) == LOW){
      flag = 1;
      //setting++;
      break;
    }
    Gclr = Gclr + Gchange;
    analogWrite(G, Gclr);
    delay(timedelay);
  }
}

void TurnOffGreen(){  // Turn off Green as long as button hasn't been pressed
  if (flag == 1){
    Gclr = 4;
  }
  while(Gclr >= 5){
    if(digitalRead(button) == LOW){
      flag = 1;
      //setting++;
      break;
    }
    Gclr = Gclr - Gchange;
    analogWrite(G, Gclr);
    delay(timedelay);
  }
}

void TurnOffAll(){  // Turn off all as long as button hasn't been pressed
  if (flag == 1){
    Bclr = 4;
  }
  while(Bclr >= 5){
    if(digitalRead(button) == LOW){
      flag = 1;
      //setting++;
      break;
    }
    Rclr = Rclr - Rchange;  
    Gclr = Gclr - Gchange;
    Bclr = Bclr - Bchange;
    analogWrite(R, Rclr);
    analogWrite(G, Gclr);
    analogWrite(B, Bclr);
    delay(timedelay);
  }
}

