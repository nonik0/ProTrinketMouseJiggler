#include <ProTrinketKeyboard.h> 

void wait(int millisecs_to_wait) {
  unsigned long timestamp = millis();
  while (millis() < (timestamp + millisecs_to_wait))
    TrinketKeyboard.poll();
}

void slowType(char* str) {
  while(*str != '\0') {
      TrinketKeyboard.typeChar(*str++);
      wait(100);
  }
}

void setup()
{
  TrinketKeyboard.begin();
}

void loop()
{
  wait(random(6000, 60000)); 
  switch(random(0,3)) {
    case 0: slowType("help..."); break;
    case 1: slowType("please..."); break;
    case 2: slowType("i am stuck here..."); break;
    case 3: slowType("kathy..?"); break;
  }
}
