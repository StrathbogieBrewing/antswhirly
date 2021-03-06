// ATMEL ATMEGA8 & 168 / ARDUINO
//
//                  +-\/-+
//            PC6  1|    |28  PC5 (AI 5)
//      (D 0) PD0  2|    |27  PC4 (AI 4)
//      (D 1) PD1  3|    |26  PC3 (AI 3)
//      (D 2) PD2  4|    |25  PC2 (AI 2)
// PWM+ (D 3) PD3  5|    |24  PC1 (AI 1)
//      (D 4) PD4  6|    |23  PC0 (AI 0)
//            VCC  7|    |22  GND
//            GND  8|    |21  AREF
//            PB6  9|    |20  AVCC
//            PB7 10|    |19  PB5 (D 13)
// PWM+ (D 5) PD5 11|    |18  PB4 (D 12)
// PWM+ (D 6) PD6 12|    |17  PB3 (D 11) PWM
//      (D 7) PD7 13|    |16  PB2 (D 10) PWM
//      (D 8) PB0 14|    |15  PB1 (D 9) PWM
//                  +----+

#define SSR (11)
#define PEDAL_1 (13)
#define PEDAL_2 (12)

void setup()
{
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(SSR, OUTPUT);

  pinMode(PEDAL_1, INPUT_PULLUP);
  pinMode(PEDAL_2, INPUT_PULLUP);

  // digitalWrite(SSR, HIGH);

  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop()
{
  static int debounce = 0;
  static int counter = 0;
  static bool speed = 0;
  static bool run = 0;

  counter++;
  delay(20); // 20 ms mains period

  int pot_one = (analogRead(A0) >> 7) + 10;
  int pot_two = (analogRead(A1) >> 7) + 10;

  if (digitalRead(PEDAL_1) == LOW)
  {
    debounce++;
  }
  else if (digitalRead(PEDAL_2) == LOW)
  {
    debounce--;
  }
  else
  {
    debounce = 0;
  }

  if (debounce == 3)
  {
    speed = !speed;
    if (debounce >= 4)
      debounce = 4;
  }

  if (debounce == -3)
  {
    run = !run;
    if (debounce <= -4)
      debounce = -4;
  }

  int drive = 0;
  if (run)
  {
    if (speed)
    {
      drive = pot_one;
    }
    else
    {
      drive = pot_two;
    }
  }

  // print out the value you read:
  if ((counter & 0x3F) == 32)
  {
    // Serial.println(pot_one);
    Serial.println(drive);
  }

  if ((counter & 0x0F) < drive)
  {
    digitalWrite(SSR, HIGH);
  }
  else
  {
    digitalWrite(SSR, LOW);
  }

  if ((counter & 0x03F) < 32)
  {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);
  }
}
