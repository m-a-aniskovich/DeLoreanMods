#include "src/HT16K33.h"

#define MATRIX_ADDRESS 0x70
#define BRIGHTNESS 5
#define RX 4
#define TX 1
#define SYNC_PIN 3
#define RANDOM_INPUT PIN_PB5

#define DELAY 200 //из FluxCapacitor
#define TIMES 70  //из FluxCapacitor
#define CLK_DELTA 0 //в миллисекундах. Насколько замедлить цикл работы для точной синхронизации, может быть отрицательным чтобы ускорить

HT16K33 matrix = HT16K33();
int randBits(int from, int to) {
  if (from < 0) from = 0;
  if (to > 16) to = 16;
  if (from >= to) return to;
  return int(random(from, to + 1));
}

void setup() {
  pinMode(SYNC_PIN, OUTPUT);
  digitalWrite(SYNC_PIN, LOW);

  bool i2c_success = TinyI2C.start(MATRIX_ADDRESS, 0);
  while (!i2c_success) {
    delay(DELAY * 10);
    i2c_success = matrix.init(MATRIX_ADDRESS);
  }
  TinyI2C.stop();
  matrix.init(MATRIX_ADDRESS);
  matrix.setBrightness(BRIGHTNESS);

  pinMode(RANDOM_INPUT, INPUT);
  int seed = analogRead(RANDOM_INPUT);
  randomSeed(seed);
}
void all_off() {
  matrix.clear();
  matrix.write();
  digitalWrite(SYNC_PIN, LOW);
  delay(20);
  digitalWrite(SYNC_PIN, HIGH);
  delay(DELAY);
}
void setup_travel() {
  int rounds = 16;
  for (int t = 0; t < rounds; t++) {
    int level = t / 4 + 1;
    for (uint8_t row = 0; row < 8; row++)
      if (row % 2 == 0) matrix.setRow(row, randBits(level - 1, level + 1));
      else         matrix.setRow(row, randBits(level - 2, level));
    matrix.write();
    delay(DELAY + (CLK_DELTA / rounds));
  }
}
void faster() {
  long all_time = 0;
  int delay_time = DELAY;
  int delay_delta = delay_time / TIMES;
  for (int t = 0; t < TIMES; t++) {
    all_time += delay_time * 5;
    delay_time -= delay_delta;
  }

  long loop_count = all_time / DELAY;
  int start_level = 5;
  for (long t = 0; t < loop_count; t++) {
    int max_level = start_level + (t * 12.0) / loop_count;
    int min_level = max_level - max_level / 2;
    int off_level = max_level / 2;

    int speed_up = 1;
    if (max_level >= 15) speed_up = 2;
    for (int t = 0; t < speed_up; t++) {
      for (uint8_t row = 0; row <= 7; row++)
        if (row == 2 || row == 5)
          matrix.setRow(row, randBits(0, off_level));
        else
          matrix.setRow(row, randBits(min_level, max_level));
      matrix.write();
      delay(DELAY / speed_up);
    }
  }
  delay(all_time - loop_count * DELAY);
}
void mph88() {
  int maxLevel[8] = { 16, 16, 10, 15, 16, 8, 16, 14 };
  for (int i = 0; i <= 16; i++) {
    for (uint8_t row = 0; row < 8; row++) {
      int rowValue = matrix.getRow(row);
      if (rowValue > maxLevel[row])
        matrix.setRow(row, rowValue - 1);
      if (rowValue < maxLevel[row])
        matrix.setRow(row, rowValue + 1);
    }
    matrix.write();
    delay(DELAY / 3);
  }
  delay(DELAY * 5);
}
void slower() {
  for (int i = 0; i < 16; i++) {
    for (uint8_t row = 0; row < 8; row++)
      matrix.setRow(row, matrix.getRow(row) - 1);
    matrix.write();
    delay(DELAY / 16);
  }
}

void loop()
{
  all_off();
  setup_travel();
  faster();
  mph88();
  slower();
}
