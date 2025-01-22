//Note: This is a not clean code, this is only a pratical test
//where we don't want use any library or dependence of other's code blocks!!!

//The idea is to make the code so basic that you can let it change and see what happens!

#define VFD_in 5// 
#define VFD_clk 6 // 
#define VFD_cs 7 // 
#define VFD_rst 11 //
#define VFD_led 12 //This pin is to polarize the base of transistor of LED of Power 

#define delay_tcsh _delay_us(16)

unsigned char char0, char1, char2;

void send_data(unsigned char a) {
  unsigned char data = 170; //value to transmit, binary 10101010
  unsigned char mask = 1; //our bitmask

  data = a;
  //This don't send the strobe signal, to be used in burst data send
  for (mask = 00000001; mask > 0; mask <<= 1) { //iterate through bit mask
    PIND = (0 << VFD_clk);
    if (data & mask) { // if bitwise AND resolves to true
      PORTD = (1 << VFD_in);
      //Serial.print(bitRead(PORTD,5));
    }
    else { //if bitwise and resolves to false
      PORTD = (0 << VFD_in); // send 0
      //Serial.print(bitRead(PORTD,5));
    }
    _delay_us(48); //delay
    PIND = (1 << VFD_clk);
    _delay_us(48); //delay
  //    PIND &= ~(0 << VFD_clk);
  }
  //Serial.println();
  delayMicroseconds(5);
}
void sendCommandVFD(unsigned char a) {
  unsigned char data = 0x00;
  unsigned char mask = 1; //our bitmask

  data = a;
  PIND = (1 << VFD_clk);
  PIND &= ~(1 << VFD_cs);
  _delay_us(48); //delay
          for (mask = 00000001; mask > 0; mask <<= 1) { //iterate through bit mask
            PIND = (0 << VFD_clk);
                  if (data & mask) { // if bitwise AND resolves to true
                    PORTD = (1 << VFD_in);
                  }
                  else { //if bitwise and resolves to false
                    PORTD = (0 << VFD_in); // send 0
                  }
            _delay_us(48); //delay
            PIND = (1 << VFD_clk);
            _delay_us(48); //delay
  //            PIND &= ~(0 << VFD_clk);
  //            _delay_us(48); //delay
            }
  _delay_us(48); //delay         
  PIND = (1 << VFD_cs);
}
void M35500_init(void) {
  digitalWrite(VFD_rst, LOW); //Reset happen at Low value!
  delay(300);
  digitalWrite(VFD_rst, HIGH); //Reset happen at Low value!
  delayMicroseconds(800); //power_up delay
  //
  // Configure VFD display (grids)
  sendCommandVFD(0b11101101);//     (Command 0) Display data setting 111x1100 is 10 digits and 16 or less segments(This means send 2Bytes or 3Bytes).
  _delay_us(48); //delay
  sendCommandVFD(0b11000111);//     (Command 1) Display ON and 15/16 duty setting.
 _delay_us(48); //delay
  sendCommandVFD(0b10101010);//     (Command 2) Digit start pin setting. (1010:D7-0000:D17) ????
  _delay_us(48); //delay
  sendCommandVFD(0b10000000);//     (Command 3) Port data settings Port selection: 0: P3-P0 & 1: P7-P4 Last four bits is output port.
  _delay_us(48); //delay  
}
void allOn(){
    //char0 = (animChars[0] | char0);
  //char1 = (animChars[1] | char1);
  //char2 = (animChars[2] | char2);
  char0 = 0xff;   //Here we send all "1". Is necessary 13 bits by digit, I sent 16 to be more easy, but you can specify it by correct way.
  char1 = 0xff;
  char2 = 0xff;
 sendCommandVFD(0b10101001);//     (Command 2) Digit start pin setting. (1010:D7-0000:D17) ????
  _delay_us(50); //delay
  PIND = (1 << VFD_clk);
  _delay_us(50); //delay 
  PIND &= ~(1 << VFD_cs); 
  _delay_us(50); //delay 

  send_data(0b11100101); //cmd 0 Each grid use 3 bytes here define the 1º
  _delay_us(8); //delay
  //send_data(animChars[0] | char0);_delay_us(8);   send_data(animChars[1] | char1);_delay_us(8);   //send_data(animChars[2] | char2);  // 17-24;   9-16;    1-8;
  //send_data(animChars[0] | char0);_delay_us(48);   send_data(animChars[1] | char1);_delay_us(48);   //send_data(animChars[2] | char2);  // 17-24;   9-16;    1-8;

  send_data(char0);   send_data(char1);  send_data(char2);  // 17-24;   9-16;    1-8;
  send_data(char0);   send_data(char1);  send_data(char2);  // 17-24;   9-16;    1-8;
  send_data(char0);   send_data(char1);  send_data(char2);  // 17-24;   9-16;    1-8;
  send_data(char0);   send_data(char1);  send_data(char2);  // 17-24;   9-16;    1-8;
  send_data(char0);   send_data(char1);  send_data(char2);  // 17-24;   9-16;    1-8;
  send_data(char0);   send_data(char1);  send_data(char2);  // 17-24;   9-16;    1-8;
  send_data(char0);   send_data(char1);  send_data(char2);  // 17-24;   9-16;    1-8;
  send_data(char0);   send_data(char1);  send_data(char2);  // 17-24;   9-16;    1-8;
  send_data(char0);   send_data(char1);  send_data(char2);  // 17-24;   9-16;    1-8;
  send_data(char0);   send_data(char1);  send_data(char2);  // 17-24;   9-16;    1-8;
  //
  delayMicroseconds(45);
  PIND = (1 << VFD_cs);
}
void M35500clear(){
    //char0 = (animChars[0] | char0);
  //char1 = (animChars[1] | char1);
  //char2 = (animChars[2] | char2);
  char0 = 0x00;
  char1 = 0x00;
  char2 = 0x00;
 sendCommandVFD(0b10101001);//     (Command 2) Digit start pin setting. (1010:D7-0000:D17) ????
  _delay_us(50); //delay
  PIND = (1 << VFD_clk);
  _delay_us(50); //delay 
  PIND &= ~(1 << VFD_cs); 
  _delay_us(50); //delay 

  send_data(0b11100101); //cmd 0 Each grid use 3 bytes here define the 1º
  _delay_us(8); //delay
  //
  //send_data(animChars[0] | char0);_delay_us(8);   send_data(animChars[1] | char1);_delay_us(8);   //send_data(animChars[2] | char2);  // 17-24;   9-16;    1-8;
  //send_data(animChars[0] | char0);_delay_us(48);   send_data(animChars[1] | char1);_delay_us(48);   //send_data(animChars[2] | char2);  // 17-24;   9-16;    1-8;

  send_data(char0);   send_data(char1);  send_data(char2);  // 17-24;   9-16;    1-8;
  send_data(char0);   send_data(char1);  send_data(char2);  // 17-24;   9-16;    1-8;
  send_data(char0);   send_data(char1);  send_data(char2);  // 17-24;   9-16;    1-8;
  send_data(char0);   send_data(char1);  send_data(char2);  // 17-24;   9-16;    1-8;
  send_data(char0);   send_data(char1);  send_data(char2);  // 17-24;   9-16;    1-8;
  send_data(char0);   send_data(char1);  send_data(char2);  // 17-24;   9-16;    1-8;
  send_data(char0);   send_data(char1);  send_data(char2);  // 17-24;   9-16;    1-8;
  send_data(char0);   send_data(char1);  send_data(char2);  // 17-24;   9-16;    1-8;
  send_data(char0);   send_data(char1);  send_data(char2);  // 17-24;   9-16;    1-8;
  send_data(char0);   send_data(char1);  send_data(char2);  // 17-24;   9-16;    1-8;
  //
  delayMicroseconds(45);
  PIND = (1 << VFD_cs);
}
void msgHELLO(){
  //char0 = (animChars[0] | char0);
  //char1 = (animChars[1] | char1);
  //char2 = (animChars[2] | char2);
  char0 = 0xFF;
  char1 = 0xFF;
  char2 = 0xFF;
 sendCommandVFD(0b10101001);//     (Command 2) Digit start pin setting. (1010:D7-0000:D17) ????
  _delay_us(50); //delay
  PIND = (1 << VFD_clk);
  _delay_us(50); //delay 
  PIND &= ~(1 << VFD_cs); 
  _delay_us(50); //delay 

  send_data(0b11100101); //cmd 0 Each grid use 3 bytes here define the 1º
  _delay_us(8); //delay
  //
  //send_data(animChars[0] | char0);_delay_us(8);   send_data(animChars[1] | char1);_delay_us(8);   //send_data(animChars[2] | char2);  // 17-24;   9-16;    1-8;
  //send_data(animChars[0] | char0);_delay_us(48);   send_data(animChars[1] | char1);_delay_us(48);   //send_data(animChars[2] | char2);  // 17-24;   9-16;    1-8;
  char0=0b00000000;
  char1=0b00010000;
  send_data(0b00000000);   send_data(0b00000000);  send_data(0b00000000);   //  digito 1
  send_data(0b11110000);   send_data(0b00000011);  send_data(0b00000000);   //  digito H
  send_data(0b11100001);   send_data(0b00100010);  send_data(0b00000000);   //  digito E
  send_data(0b00100000);   send_data(0b00100010);  send_data(0b00000000);   //  digito L
  send_data(0b00100000);   send_data(0b00100010);  send_data(0b00000000);   //  digito L
  send_data(0b00110001);   send_data(0b00100011);  send_data(0b00000000);   //  digito O
  send_data(0b00110001);   send_data(0b00100011);  send_data(0b00000000);   //  digito 7
  send_data(0b00000000);   send_data(0b00000000);  send_data(0b00000000);   //  digito 8
  send_data(0b00000000);   send_data(0b00000000);  send_data(0b00000000);   //  digito 9
  send_data(0b00000000);   send_data(0b00000000);  send_data(0b00000000);   //  digito 10
  //
  delayMicroseconds(15);
  PIND = (1 << VFD_cs);
}
void msgHI(){
  //char0 = (animChars[0] | char0);
  //char1 = (animChars[1] | char1);
  //char2 = (animChars[2] | char2);
  char0 = 0xFF;
  char1 = 0xFF;
  char2 = 0xFF;
 sendCommandVFD(0b10101001);//     (Command 2) Digit start pin setting. (1010:D7-0000:D17) ????
  _delay_us(50); //delay
  PIND = (1 << VFD_clk);
  _delay_us(50); //delay 
  PIND &= ~(1 << VFD_cs); 
  _delay_us(50); //delay 

  send_data(0b11100101); //cmd 0 Each grid use 3 bytes here define the 1º
  _delay_us(8); //delay
  //
  //send_data(animChars[0] | char0);_delay_us(8);   send_data(animChars[1] | char1);_delay_us(8);   //send_data(animChars[2] | char2);  // 17-24;   9-16;    1-8;
  //send_data(animChars[0] | char0);_delay_us(48);   send_data(animChars[1] | char1);_delay_us(48);   //send_data(animChars[2] | char2);  // 17-24;   9-16;    1-8;
  char0=0b00000000;
  char1=0b00010000;
  send_data(0b00000000);   send_data(0b00000000);  send_data(0b00000000);   //  digito 1
  send_data(0b11110000);   send_data(0b00000011);  send_data(0b00000000);   //  digito H
  send_data(0b00000101);   send_data(0b00101000);  send_data(0b00000000);   //  digito I
  send_data(0b00000000);   send_data(0b00000000);  send_data(0b00000000);   //  digito 4
  send_data(0b00000000);   send_data(0b00000000);  send_data(0b00000000);   //  digito 5
  send_data(0b00000000);   send_data(0b00000000);  send_data(0b00000000);   //  digito 6
  send_data(0b00000000);   send_data(0b00000000);  send_data(0b00000000);   //  digito 7
  send_data(0b00000000);   send_data(0b00000000);  send_data(0b00000000);   //  digito 8
  send_data(0b00000000);   send_data(0b00000000);  send_data(0b00000000);   //  digito 9
  send_data(0b00000000);   send_data(0b00000000);  send_data(0b00000000);   //  digito 10
  //
  delayMicroseconds(15);
  PIND = (1 << VFD_cs);
}
void msgFOLKS(){
 sendCommandVFD(0b10101001);//     (Command 2) Digit start pin setting. (1010:D7-0000:D17) ????
  delay(2);
  PIND = (1 << VFD_clk);
  delay(2);
  PIND &= ~(1 << VFD_cs); 
  delay(2);
  send_data(0b11100101); //cmd 0 Each grid use 3 bytes here define the 1º
  delay(2);
  send_data(0b00000000);   send_data(0b00000000);  send_data(0b00000000);   //  digito 1
  send_data(0b11100001);   send_data(0b00000010);  send_data(0b00000000);   //  digito F
  send_data(0b00110001);   send_data(0b00100011);  send_data(0b00000000);   //  digito O
  send_data(0b00100000);   send_data(0b00100010);  send_data(0b00000000);   //  digito L
  send_data(0b10101000);   send_data(0b00010010);  send_data(0b00000000);   //  digito K
  send_data(0b11100001);   send_data(0b00100001);  send_data(0b00000000);   //  digito S
  send_data(0b00000000);   send_data(0b00000000);  send_data(0b00000000);   //  digito 7
  send_data(0b00000000);   send_data(0b00000000);  send_data(0b00000000);   //  digito 8
  send_data(0b00000000);   send_data(0b00000000);  send_data(0b00000000);   //  digito 9
  send_data(0b00000000);   send_data(0b00000000);  send_data(0b00000000);   //  digito 10
  //
  delayMicroseconds(15);
  PIND = (1 << VFD_cs);
}
void msgWheels(uint8_t word0, uint8_t word1){
 sendCommandVFD(0b10101001);//     (Command 2) Digit start pin setting. (1010:D7-0000:D17) ????
  _delay_us(50); //delay
  PIND = (1 << VFD_clk);
  _delay_us(50); //delay 
  PIND &= ~(1 << VFD_cs); 
  _delay_us(50); //delay 

  send_data(0b11100101); //cmd 0 Each grid use 3 bytes here define the 1º
  _delay_us(8); //delay
  //
  //send_data(animChars[0] | char0);_delay_us(8);   send_data(animChars[1] | char1);_delay_us(8);   //send_data(animChars[2] | char2);  // 17-24;   9-16;    1-8;
  //send_data(animChars[0] | char0);_delay_us(48);   send_data(animChars[1] | char1);_delay_us(48);   //send_data(animChars[2] | char2);  // 17-24;   9-16;    1-8;
  char0=0b00000000;
  char1=0b00010000;
  send_data(word0);   send_data(word1);  send_data(0b00000000);   //  digito 1
  // send_data(0b00000000);   send_data(0b00000000);  send_data(0b00000000);   //  digito H
  // send_data(0b00000000);   send_data(0b00000000);  send_data(0b00000000);   //  digito I
  // send_data(0b00000000);   send_data(0b00000000);  send_data(0b00000000);   //  digito 4
  // send_data(0b00000000);   send_data(0b00000000);  send_data(0b00000000);   //  digito 5
  // send_data(0b00000000);   send_data(0b00000000);  send_data(0b00000000);   //  digito 6
  // send_data(0b00000000);   send_data(0b00000000);  send_data(0b00000000);   //  digito 7
  // send_data(0b00000000);   send_data(0b00000000);  send_data(0b00000000);   //  digito 8
  // send_data(0b00000000);   send_data(0b00000000);  send_data(0b00000000);   //  digito 9
  // send_data(0b00000000);   send_data(0b00000000);  send_data(0b00000000);   //  digito 10
  //
  delayMicroseconds(15);
  PIND = (1 << VFD_cs);
}
void animeWheels(){
  short wheels = 0x0080; // This active bit 7 of firt byte of short(short have 16 bits on arduino)
  uint8_t wheelA = 0x00;
  uint8_t wheelB = 0x00;
  for(uint8_t i = 0x00; i < 7; i++){
    // ((x=v << 0) & 0x00FF);
    //word4 = (mask0 & 0xff000000) >>  24; // remaning segments 
    (wheels = (wheels << 1));
    Serial.println(wheels, BIN);
    wheelA = ((wheels & 0x00FF) >> 0);
    wheelB = ((wheels & 0xFF00) >> 8);
    wheelB = (wheelB | 0b01000000);
    switch (i){
      case 6: wheelA = (wheelA | 0x00);
              wheelB = (wheelB | 0b01000000); break;
      case 7: wheelA = (wheelA | 0x00);
              wheelB = (wheelB | 0b01100000); break;
    }
    
  Serial.print(wheelA, BIN);Serial.print(" =A; ");Serial.print(wheelB, BIN);Serial.print(" =B; ");
  msgWheels(wheelA, wheelB);
  delay(100);
  }
}
void clearVFD(void) {
  /*
    Here I clean all registers
    Could be done only on the number of grid
    to be more fast. The 12 * 3 bytes = 36 registers
  */
  sendCommandVFD(0b11101101); // cmd 0
  PIND = (1 << VFD_clk);
  _delay_us(50); //delay 
  PIND &= ~(1 << VFD_cs); 
  _delay_us(50); //delay 

  for (int i = 0; i < 30; i++) {
    send_data(0b00000000); // data
  }

  PIND = (1 << VFD_cs);
  delayMicroseconds(4);
}
void setup() {
  pinMode( VFD_in, OUTPUT);// 8: If 0 write LCD, if 1 read of LCD
  pinMode( VFD_clk, OUTPUT);// 9: if 0 is a command, if 1 is a data0
  pinMode( VFD_cs, OUTPUT);// 10: Must be pulsed to LCD fetch data of bus
  pinMode( VFD_rst, OUTPUT);// 11: if 0 is a command, if 1 is a data0
  pinMode( VFD_led, OUTPUT);// 12

  digitalWrite(VFD_rst, HIGH);

  pinMode( 13, OUTPUT); //Pin of pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);

  M35500_init();
}
void loop() {
  msgHELLO();
  delay(1500);
  digitalWrite(12, HIGH);
      for (uint8_t i = 0; i<3; i++){
        allOn();
        delay(1000);
        M35500clear();
        delay(200);
      }
  digitalWrite(12, LOW); 
  for(uint8_t i = 0x00; i < 4; i++){
    msgHI();
    animeWheels();
  }
  for(uint8_t i = 0x00; i < 8; i++){
    msgFOLKS();
    animeWheels();
  }
  sendCommandVFD(0b11000111);//     (Command 1) Display ON and 15/16 duty setting. Change bright of segments!
  delay(500);
  sendCommandVFD(0b11000011);//     (Command 1) Display ON and 15/16 duty setting. 
  delay(1500);
  sendCommandVFD(0b11000111);//     (Command 1) Display ON and 15/16 duty setting.
  delay(500);
}
