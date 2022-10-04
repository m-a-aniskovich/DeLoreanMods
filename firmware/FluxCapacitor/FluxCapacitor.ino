//#define board_MEGA true

#ifdef board_MEGA
  #define L1 9
  #define L2 8
  #define L3 13
  #define L4 12
  #define LC 10
#else
  #define L1 4
  #define L2 3
  #define L3 0
  #define L4 1
  #define LC 2
#endif

#define DELAY 210
#define TIMES 90

const int LEDS[] = {L1, L2, L3, L4, LC};

#ifdef board_MEGA
  void on(int pin) {
    analogWrite(pduhin, 32);
  }
  void off(int pin) {
    analogWrite(pin, 0);
  }
#else
  void on(int pin) {
    digitalWrite(pin, HIGH);
  }
  void off(int pin) {
    digitalWrite(pin, LOW);
  }
#endif

void setup() {
  for (int p = 0; p < 5; p++) pinMode(p, OUTPUT);
}

void all_off() {
  for (int p = 0; p < 5; p++) off(p);
}
void one_from_center() {
  for (int i = 4; i >= 0; i--) {
    on(LEDS[i]);
    delay(DELAY);
    off(LEDS[i]);
  }
}
void one_from_center(int delay_time) {
  for (int i = 4; i >= 0; i--) {
    on(LEDS[i]);
    delay(delay_time);
    off(LEDS[i]);
  }
}
void one_to_center() {
  for (int i = 0; i <= 4; i++) {
    on(LEDS[i]);
    delay(DELAY);
    off(LEDS[i]);
  }
}
void one_to_center(int delay_time) {
  for (int i = 0; i <= 4; i++) {
    on(LEDS[i]);
    delay(delay_time);
    off(LEDS[i]);
  }
}
void faster() {
  int delay_time = DELAY;
  int delay_delta = delay_time / TIMES;
  for (int i = 0; i < TIMES; i++) {
    one_to_center(delay_time);
    delay_time -= delay_delta;
  }
}
void on_to_center() {
  for (int i = 0; i <= 4; i++) {
    on(LEDS[i]);
    delay(DELAY / 4);
  }
}
void off_to_center() {
  for (int i = 0; i <= 4; i++) {
    off(LEDS[i]);
    delay(DELAY / 4);
  }
}
void loop() {
  all_off();
  one_from_center();
  faster();
  all_off();
  on_to_center();
  delay(DELAY * 25);
  off_to_center();
  on(LC);
  delay(DELAY);
}
