#include <ProTrinketKeyboard.h>

#define DEBUG 1
#define LED_PIN 13

void setup()
{
  TrinketKeyboard.begin();
  pinMode(LED_PIN, OUTPUT);
}

void loop()
{
  unsigned long seconds = millis() / 1000;
  
  // calculate min and max time to wait, which decreases linearly over a week
  int min_wait_time, max_wait_time;
#if DEBUG
  if (seconds <= 60) { // if less than a minute since epoch  
    min_wait_time = int(-(09.0/60.0)*seconds + 10.0);
    max_wait_time = int(-(18.0/60.0)*seconds + 20.0);
  }
  else {
    min_wait_time = 1; 
    max_wait_time = 2;
  }
#else
  if (seconds < 7*24*60*60) { // if less than a week since epoch  
    min_wait_time = int(-(19.0/672.00)*seconds + 17280.0);
    max_wait_time = int(-(95.0/2016.0)*seconds + 28800.0);
  }
  else {
    min_wait_time = 3 * 60;
    max_wait_time = 5 * 60;
  }
#endif

  unsigned long secs_to_wait = random(min_wait_time, max_wait_time);
  unsigned long timestamp = millis();
  unsigned int count = 0;
  unsigned heartbeat = false;
  while (millis() < (timestamp + (secs_to_wait * 1000))) {
    TrinketKeyboard.poll();

    if (count % 100000 == 0) {
        heartbeat = !heartbeat;
        if (heartbeat)
          digitalWrite(LED_PIN, HIGH);
        else
          digitalWrite(LED_PIN, LOW); 
    }
    count++;
  }

  //digitalWrite(LED_PIN, HIGH);
 #if DEBUG
  switch(5) {
 #else
  switch(random(0,6)) {
 #endif
    case 0: // press insert key
    case 1:
    case 2:
      TrinketKeyboard.pressKey(0, KEYCODE_INSERT); 
      TrinketKeyboard.pressKey(0, 0);
      break;
    case 3: // randomly press an arrow key
      unsigned int keyToPress;
      switch(random(0, 4)) {
        case 0: keyToPress = KEYCODE_ARROW_UP; break;
        case 1: keyToPress = KEYCODE_ARROW_DOWN; break;
        case 2: keyToPress = KEYCODE_ARROW_LEFT; break;
        case 3: keyToPress = KEYCODE_ARROW_RIGHT; break;
        default: break;
      }   
      TrinketKeyboard.pressKey(0, keyToPress);
      TrinketKeyboard.pressKey(0, 0);
      break;
    case 4: // press space
      TrinketKeyboard.pressKey(0, KEYCODE_SPACE); 
      TrinketKeyboard.pressKey(0, 0);
      break;
    case 5: // press ctrl+v
      TrinketKeyboard.pressKey(KEYCODE_MOD_LEFT_CONTROL, KEYCODE_V);
      TrinketKeyboard.pressKey(0, 0);
      break;
    default:
      break;
  }
  //heartbeatheartbeat heartbeatte(LED_PIN, LOW);
}


