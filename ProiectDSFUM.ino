#include <Arduino.h>
#include "PinDefinitionsAndMore.h"
#include <IRremote.hpp>
#include "pitches.h"

//pt telecomanda
#define DECODE_NEC

//pt steag
#define ENABLE 6
#define DIR_A 4
#define DIR_B 5

void raiseFlag() {
  analogWrite(ENABLE, 255);
  digitalWrite(DIR_B, LOW);
  digitalWrite(DIR_A, HIGH);
  delay(1000);
  digitalWrite(DIR_A, LOW);
  digitalWrite(ENABLE, LOW);
}

void lowerFlag() {
  analogWrite(ENABLE, 255);
  digitalWrite(DIR_A, LOW);
  digitalWrite(DIR_B, HIGH);
  delay(100);
  digitalWrite(DIR_B, LOW);
  digitalWrite(ENABLE, LOW);
}

//pt inclinare
const int ballSwitchPin = 3;

//pt melodii
int chanel = 0;
struct Melodii {
  int canal;
  void (*play_song)();
};

Melodii songs[] = {
  {0, play_godfathertheme},
  {1, play_mariotheme},
  {2, play_pinkpanthertheme},
  {3, play_romaniananthem},
};

//pt becuri
void illuminate_LED() {
  if(chanel == 3) {
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);
  } 
  else {
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(10 + chanel, HIGH);
  }
}

void change_chanel(bool forward) {
  if(chanel != 3) {
    if(forward == true) {
      if(chanel < 2) {chanel++;}
      else {chanel = 0;}

      IrReceiver.stop();
      illuminate_LED();
      tone(SOUND_PIN, NOTE_C6, 200);
      delay(200);
      noTone(SOUND_PIN);
      IrReceiver.start();
    }
    
    if(forward == false) {
      if(chanel > 0) {chanel--;}
      else {chanel = 2;}

      IrReceiver.stop();
      illuminate_LED();
      tone(SOUND_PIN, NOTE_C2, 200);
      delay(200);
      noTone(SOUND_PIN);
      IrReceiver.start();
    }
  }
}
void setup() {
  Serial.begin(9600);
  //pt led
  digitalWrite(10, HIGH);

  //pt telecomanda
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

  //pt inclinare
  pinMode(ballSwitchPin, INPUT);
  digitalWrite(ballSwitchPin, HIGH);

  //pt steag
  pinMode(ENABLE,OUTPUT);
  pinMode(DIR_A,OUTPUT);
  pinMode(DIR_B,OUTPUT);
}

void loop() {
  int digitalVal = digitalRead(ballSwitchPin);
  if(HIGH == digitalVal)
  {
    IrReceiver.stop();
    tone(SOUND_PIN, NOTE_C6, 200);
    delay(400);
    noTone(SOUND_PIN);
    IrReceiver.start();
  }

  if (IrReceiver.decode()) {
    if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
      Serial.println(F("Received noise or an unknown (or not yet enabled) protocol"));
    }

    IrReceiver.resume();
    switch(IrReceiver.decodedIRData.command) {
      case 0x45: {
        Serial.println("CH-");
        break;
      }
      case 0x46: {
        Serial.println("CH");
        if(chanel != 3) {
          chanel = 3;
          IrReceiver.stop();
          illuminate_LED();
          tone(SOUND_PIN, NOTE_C6, 200);
          delay(200);
          noTone(SOUND_PIN);
          IrReceiver.start();
        }
        else {
          chanel = 0;
          IrReceiver.stop();
          illuminate_LED();
          tone(SOUND_PIN, NOTE_C2, 200);
          delay(200);
          noTone(SOUND_PIN);
          IrReceiver.start();
        }
        
        break;
      }
      case 0x47: { 
        Serial.println("CH+");
        break;
      }
      case 0x44: { 
        Serial.println("|<<");
        change_chanel(false);
        break;
      }
      case 0x40: { 
        Serial.println(">>|");
        change_chanel(true);
        break;
      }
      case 0x43: { 
        Serial.println(">||");
        IrReceiver.stop();
        if(chanel == 3) {raiseFlag(); }
        delay(1000);

        songs[chanel].play_song();

        delay(1000);
        if(chanel == 3) {lowerFlag(); }
        IrReceiver.start();
        break;
      }
      case 0x7: { 
        Serial.println("Volume+");
        break;
      }
      case 0x15: { 
        Serial.println("Volume-");
        break;
      }
      case 0x9: { 
        Serial.print("EQ: ");
        break;
      }
      case 0x19: { 
        Serial.println("100+");
        break;
      }
      case 0xD: { 
        Serial.println("200+");
        break;
      }
      case 0x16: { 
        Serial.println("0");
        break;
      }
      case 0xC: { 
        Serial.println("1");
        break;
      }
      case 0x18: { 
        Serial.println("2");
        break;
      }
      case 0x5E: { 
        Serial.println("3");
        break;
      }
      case 0x8: { 
        Serial.println("4");
        break;
      }
      case 0x1C: { 
        Serial.println("5");
        break;
      }
      case 0x5A: { 
        Serial.println("6");
        break;
      }
      case 0x42: { 
        Serial.println("7");
        break;
      }
      case 0x52: { 
        Serial.println("8");
        break;
      }
      case 0x4A: { 
        Serial.println("9");
        break;
      }
      default: {
        
      }
    }
    //delay(1000);
  }
}
