#include <CATALEX_SerialMp3V1.h>


CATALEX_SerialMp3V1 MP3(6,5);


void setup() {
  MP3.begin();

  MP3.setVolume(10);

  MP3.playSong(1);
}

void loop() {
  MP3.getStatus();

  if (MP3.songFinished == true){

  MP3.playSong(2);
  }
}
