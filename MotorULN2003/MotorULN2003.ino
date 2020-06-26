/*
  Motor Control
  Motor de Passo + Driver ULN2003 Arduino
  
*/

unsigned int motor1 = 8;
unsigned int motor2 = 8;
unsigned int motor3 = 8;

unsigned int motor1_d = 0; // Directions
unsigned int motor2_d = 0;
unsigned int motor3_d = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  // set pins 4..7 as output (1),
  // leave pin 0,1,2,3 as input (0)
  // but leave pin 0 (serial receive) as input (0)
  // (otherwise serial port will stop working!) ...
  DDRD = B11110000;  // digital pins 4,5,6,7
  
  // set pins 0..3 as output (1)
  DDRB = B00001111;  // digital pins 8,9,10,11

  // set pins 0..3 as output (1)
  DDRC = B00001111;  // digital pins A0,A1,A2,A3

  PORTB = 1;
  PORTC = 1;
  PORTD = 1;
                    
}

// the loop function runs over and over again forever
void loop() {
  
  // Motor1
  // --------------------------------
  PORTD = motor1 * 16;
  if (motor1_d == 0) {
    motor1 = motor1 >> 1;
  }else{
    motor1 = motor1 << 1;
  }
  if (motor1 > 8) { motor1 = 1; }
  if (motor1 < 1) { motor1 = 8; }
  // --------------------------------

  // Motor2
  // --------------------------------
  PORTB = motor2;
  if (motor2_d == 0) {
    motor2 = motor2 >> 1;
  }else{
    motor2 = motor2 << 1;
  }
  if (motor2 > 8) { motor2 = 1; }
  if (motor2 < 1) { motor2 = 8; }
  // --------------------------------

  // Motor3
  // --------------------------------
  PORTC = motor3;
  if (motor3_d == 0) {
    motor3 = motor3 >> 1;
  }else{
    motor3 = motor3 << 1;
  }
  if (motor3 > 8) { motor3 = 1; }
  if (motor3 < 1) { motor3 = 8; }
  // --------------------------------
  
  
  //delay(1);
  //PORTD = B00000000; // sets digital pins 7,5,3 HIGH
  //delay(10);

  delay(500);
  //Serial.println("Hello !!!");
  
}
