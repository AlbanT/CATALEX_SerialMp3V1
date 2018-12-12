/*
  CATALEX_SerialMp3V1.cpp - Library controlling the Catalex UART MP3 Player.
  Created by AlbanT, 2018/12/05.
  Released into the public domain.
  Based on the code found on: https://create.arduino.cc/projecthub/javier-munoz-saez/arduino-mp3-player-catalex-2effef
*/

#ifndef CATALEX_SerialMp3V1_h
#define CATALEX_SerialMp3V1_h

#include "Arduino.h"
#include <SoftwareSerial.h>

class CATALEX_SerialMp3V1
{
  public:
  	CATALEX_SerialMp3V1(byte RX, byte TX);
	void begin();
    void playSong(int index);
	void setVolume(int volume);
	void nextSong();
	void previousSong();
	void volumeUp();
	void volumeDown();
	void singleCyclePlay();
	void sleepMode();
	void wakeUp();
	void playResume();
	void playPause();
	void playStop();
	void getStatus();
	bool songFinished;
  private:
	SoftwareSerial *UART;
	void sendCommand(int8_t command, int16_t dat);
};

#endif