int R = 9; //Red Leds
int G = 10; //Green LEDs
int B = 11; //Blue LEDs
int Rpot = A0;
int Gpot = A1;
int Bpot = A2;
int button = 7;  //Switch
int setting = 0;  //LED Mode
int x[2]= {
  1,1};
int RGB[3] = {
  0,0,0};
int RGBpot[3] = {
  A0,A1,A2};
int Rclr = 0;
int Gclr = 0;
int Bclr = 0;
int Rclr2 = 0;
int Gclr2 = 0;
int Bclr2 = 0;
int Rchange = 5;
int Gchange = 5;
int Bchange = 5;
int timedelay = 100;
int flag = 0;





void setup(){
  pinMode(R,OUTPUT);
  pinMode(G,OUTPUT);
  pinMode(B,OUTPUT);
  pinMode(button,INPUT_PULLUP);
  // Serial.begin(9600);
}


void loop(){
  x[1] = digitalRead(button);
  if(x[1] == 0 && x[0] == 1){
    setting = setting++;
  }

  if (setting >= 10){
    setting = 0;
  }




  switch(setting){
  case 0: //White
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
      delay(500);
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

  case 8:  //  Christmas Setting
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
  case 9:
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
  x[0] = x[1];
}

//  Functions

void PressedButton(){
  x[1] = digitalRead(button);
  if(x[1] == 0 && x[0] == 1){
    flag = 1;
  }
  x[0] = x[1];

}

void Initialize(){
  Rclr = 0;
  Gclr = 0;
  Bclr = 0; 
  analogWrite(R, 0);
  analogWrite(G, 0);
  analogWrite(B, 0);
}

void TurnOnBlue(){
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


void TurnOffBlue(){
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

void TurnOnRed(){
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

void TurnOffRed(){
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

void TurnOnGreen(){
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

void TurnOffGreen(){
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

void TurnOffAll(){
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
