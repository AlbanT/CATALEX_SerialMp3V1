/*
  CATALEX_SerialMp3V1.cpp - Library controlling the Catalex UART MP3 Player.
  Created by AlbanT, 2018/12/05.
  Released into the public domain.
  Based on the code found on: https://create.arduino.cc/projecthub/javier-munoz-saez/arduino-mp3-player-catalex-2effef
*/

#include "Arduino.h"
#include "CATALEX_SerialMp3V1.h"





CATALEX_SerialMp3V1::CATALEX_SerialMp3V1(byte RX, byte TX)
{
  UART = new SoftwareSerial(RX, TX);
}

void CATALEX_SerialMp3V1::begin()
{
	Serial.begin(9600);
	Serial.println("CATALEX_SerialMp3V1 started");
  UART->begin(9600);
  delay(500);
  sendCommand(0x09, 0x02);//select the TF card 
  delay(200);//wait for 200ms
  songFinished = true;
}


void CATALEX_SerialMp3V1::getStatus()
{
  int c =UART->read();
  if (c != 0xFFFFFFFF) {
    if (c == 0xEF){
      Serial.println(c, HEX);
    }
    else {
      Serial.print(c, HEX);Serial.print(" ");
      if (c==0x3D){
        songFinished = true;
      }
    }
  }
 	
}

void CATALEX_SerialMp3V1::playSong(int index)
{
  songFinished = false;
 	sendCommand(0x03, index);
}

void CATALEX_SerialMp3V1::setVolume(int volume)
{
  sendCommand(0x06, volume);
}

void CATALEX_SerialMp3V1::nextSong()
{
 	sendCommand(0x01, 0x00);
}

void CATALEX_SerialMp3V1::previousSong()
{
 	sendCommand(0x02, 0x00);
}

void CATALEX_SerialMp3V1::volumeUp()
{
 	sendCommand(0x04, 0x00);
}

void CATALEX_SerialMp3V1::volumeDown()
{
 	sendCommand(0x05, 0x00);
}

void CATALEX_SerialMp3V1::singleCyclePlay()
{
 	sendCommand(0x08, 0x01);
}

void CATALEX_SerialMp3V1::sleepMode()
{
 	sendCommand(0x0A, 0x00);
}

void CATALEX_SerialMp3V1::wakeUp()
{
 	sendCommand(0x0B, 0x00);
}

void CATALEX_SerialMp3V1::playResume()
{
 	sendCommand(0x0D, 0x00);
}

void CATALEX_SerialMp3V1::playPause()
{
 	sendCommand(0x0E, 0x00);
}

void CATALEX_SerialMp3V1::playStop()
{
 	sendCommand(0x16, 0x00);
}





void CATALEX_SerialMp3V1::sendCommand(int8_t command, int16_t dat)
{
  int8_t Send_buf[8] = {0} ;
  delay(20);
  Send_buf[0] = 0x7e; //starting byte
  Send_buf[1] = 0xff; //version
  Send_buf[2] = 0x06; //the number of bytes of the command without starting byte and ending byte
  Send_buf[3] = command; //
  Send_buf[4] = 0x00;//0x00 = no feedback, 0x01 = feedback
  Send_buf[5] = (int8_t)(dat >> 8);//datah
  Send_buf[6] = (int8_t)(dat); //datal
  Send_buf[7] = 0xef; //ending byte
  for(uint8_t i=0; i<8; i++)//
  {
    UART->write(Send_buf[i]) ;
  }
}