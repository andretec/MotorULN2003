/*
  Motor Control
  Motor de Passo + Driver ULN2003 Arduino
  
*/

byte wave_step[4] = {0x01,0x02,0x04,0x08}; // low torque, (1)
byte full_step[4] = {0x09,0x03,0x06,0x0C}; // high torque,(2)

byte motor1 = 1; // Variables
byte motor2 = 1;
byte motor3 = 1;

bool motor1_d = false; // Directions
bool motor2_d = false;
bool motor3_d = false;

unsigned int delayTime = 3; // Time between steps; 2 <- min value

int Str;          // Receive instructions from USB
String sdata="";  // Used to concatenate the numbers

bool LoopUSB = true;


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

  PORTB = 0; // Turn off motors
  PORTC = 0;
  PORTD = 0;
                 
}

// the loop function runs over and over again forever
void loop() {


  while (Serial.available() > 0 ) {

    Str = Serial.read();

    // "M" move motor 
    if (Str == 'M' ) {

        LoopUSB = true;
        Serial.println("OK");
        delay(10);
        
        byte ch = "";
        // ----------------------------------------------------
        while ( LoopUSB ) {
            if ( Serial.available() > 0 ){
              ch = Serial.read();
              if (ch=='E') {
                Serial.print("valor = ");
                Serial.println(sdata);
                
                LoopUSB = false;
                unsigned int valor = sdata.toInt();
                Serial.println(valor+1);

                sdata = ""; // Clear the string ready for the next command.
              }
              else
              {
                Serial.println(ch);
                sdata += (char)ch;
              }  
            } // if

            delay(10);
         } // while ( LoopUSB )
         // ----------------------------------------------------
      } // if (Str.equals("move"))
  } // while (Serial.available() > 0 )
  

  
  move_motor(1,2048,true,2); // high torque,(2)

  //delay(1000);
  Serial.println("Hello !!!");
  
}

// Move motor routine
void move_motor(byte motor,unsigned int n_steps,bool directions,byte kind_wave){
  
  for (int i = 0; i <= n_steps; i++) {
    // -------------------------------------------------------- Motor #1  
    if (motor == 1) {  
      if (motor1 > 4) { motor1 = 1; }
      if (motor1 < 1) { motor1 = 4; } 
      // ---------------------------
      if (kind_wave == 1){
        PORTD = wave_step[motor1-1] * 16; // Write data in the Port
      }else{
        PORTD = full_step[motor1-1] * 16; // Write data in the Port
      }
      // ---------------------------
      if (directions) {
        motor1 = motor1 + 1;
      }else{
        motor1 = motor1 - 1;
      }
    }
    // -------------------------------------------------------- Motor #2
    if (motor == 2) {  
      if (motor2 > 4) { motor2 = 1; }
      if (motor2 < 1) { motor2 = 4; } 
      // ---------------------------
      if (kind_wave == 1){
        PORTB = wave_step[motor2-1]; // Write data in the Port
      }else{
        PORTB = full_step[motor2-1]; // Write data in the Port
      }
      // --------------------------- 
      if (directions) {
        motor2 = motor2 + 1;
      }else{
        motor2 = motor2 - 1;
      }
    }
    // -------------------------------------------------------- Motor #3
    if (motor == 3) {  
      if (motor3 > 4) { motor3 = 1; }
      if (motor3 < 1) { motor3 = 4; } 
      // ---------------------------
      if (kind_wave == 1){
        PORTC = wave_step[motor3-1]; // Write data in the Port
      }else{
        PORTC = full_step[motor3-1]; // Write data in the Port
      }
      // ---------------------------
      if (directions) {
        motor3 = motor3 + 1;
      }else{
        motor3 = motor3 - 1;
      }
    }
    // --------------------------------------------------------
    delay(delayTime); // Time between steps
    
  } // For loop

    // Turn off motor
    if (motor == 1) { PORTD = 0; }
    if (motor == 2) { PORTB = 0; }
    if (motor == 3) { PORTC = 0; }
    
}
