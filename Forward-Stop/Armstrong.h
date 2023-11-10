#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#include <SoftwareSerial.h>
#include <IRremote.h>
#define trig 4
#define echo A3
#define buzzer 3
#define LTLeft A5
#define LTCenter A6
#define LTRight A7

#define MotorBRS 9
#define MotorBLS 5
#define MotorFLS 6
#define MotorFRS 10
#define MotorBR1 13
#define MotorBR2 A0
#define MotorBL1 8
#define MotorBL2 7
#define MotorFL1 12
#define MotorFL2 11
#define MotorFR1 A1
#define MotorFR2 A2
#define rxPin 2
#define txPin 3
int led_ring_pin =A4;
int NUMPIXELS =24;
Adafruit_NeoPixel pixels(NUMPIXELS,led_ring_pin, NEO_GRB + NEO_KHZ800);
#if defined(Bluetooth)
  SoftwareSerial mySerial=SoftwareSerial(rxPin, txPin);
#endif
int command=1;
bool Button_Pressed(){
    if(IrReceiver.decode()){
        command=IrReceiver.decodedIRData.command;
        return true;
    }
    command=1;
    return false;
}
bool one_pressed(){
  return command==69;
}
bool two_pressed(){
  return command==70;
}
bool three_pressed(){
  return command==71;
}
bool four_pressed(){
  return command==68;
}
bool five_pressed(){
  return command==64;
}
bool six_pressed(){
  return command==67;
}
bool seven_pressed(){
  return command==7;
}
bool eight_pressed(){
  return command==21;
}
bool nine_pressed(){
  return command==9;
}
bool star_pressed(){
  return command==22;
}
bool zero_pressed(){
  return command==25;
}
bool hash_pressed(){
  return command==13;
}
bool up_pressed(){
  return command==24;
}
bool right_pressed(){
  return command==90;
}
bool left_pressed(){
  return command==8;
}
bool down_pressed(){
  return command==82;
}
bool ok_pressed(){
  return command==28;
}
void resume(){
  IrReceiver.resume();
} 

char BluetoothRead(){
  #if defined(Bluetooth)
  while(!mySerial.available()){}
  return mySerial.read();
  #endif
  return '?';
}
void Send_via_Bluetooth(float distance){
#if defined(Bluetooth)
mySerial.println(String(distance));
#endif
}
void set_Bluetooth_password(String Pass){
#if defined(Bluetooth)
String PassCommand="AT+PSWD="+Pass;
delay(1000); 
for(int i=0;i<PassCommand.length();i++) mySerial.write(PassCommand.charAt(i));
mySerial.write('\r');
mySerial.write('\n');
#endif
}
void set_Bluetooth_name(String Name){
#if defined(Bluetooth)
String NameCommand="AT+NAME="+Name;
delay(1000);
for(int i=0;i<NameCommand.length();i++) mySerial.write(NameCommand.charAt(i));
mySerial.write('\r');
mySerial.write('\n');
#endif
}
float CharToFloat(String s){
  return float(s[0]); 
}
float Letter(String s){
  return float(s[0]);  
}
void initialize_IrReceiver(int IRpin = 2){
   IrReceiver.begin(IRpin, ENABLE_LED_FEEDBACK);
}
void initialize_Bluetooth(){
  #if defined(Bluetooth)
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  mySerial.begin(9600);
  #endif
}
void initialize_face(int PIN = led_ring_pin, int LED_COUNT = NUMPIXELS){
  pixels.setPin(PIN);
  pixels.updateLength(LED_COUNT);
  NUMPIXELS=LED_COUNT;
  led_ring_pin=PIN;
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin();
  pixels.clear();
  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(0,0,0));
  }
  pixels.show();
}
void show_pixel(int index,int red,int green,int blue){
  pixels.setPixelColor(index, pixels.Color(red,green,blue));
  pixels.show();
}
void show_levels(int level,int red,int green,int blue){

  if(level<1){
    pixels.clear();
      for(int i=0;i<NUMPIXELS;i++){    
    pixels.setPixelColor(i, pixels.Color(0,0,0));
  }
  pixels.show();
    return;
  }
  if(level>NUMPIXELS/2+1){
    pixels.clear();
      for(int i=0;i<NUMPIXELS;i++){
   
    pixels.setPixelColor(i, pixels.Color(red,green,blue));
  }
  pixels.show();
    return;
  }
  bool removed[NUMPIXELS];
  for(int i=0;i<NUMPIXELS;i++){
    removed[i]=false;
  }
     
      pixels.setPixelColor(0, pixels.Color(red,green,blue));
      removed[0]=true;
      pixels.show();
  if(level<=9&&level>1){    
  
  for(int i=1;i<level;i++){
    pixels.setPixelColor(i, pixels.Color(red,green,blue));
    pixels.setPixelColor(16-i, pixels.Color(red,green,blue)); 
    removed[i]=true;
    removed[16-i]=true;
    pixels.show();
    //delay(50);
  }
}

  if(level>9){

    for(int i=1;i<16;i++){
    pixels.setPixelColor(i, pixels.Color(red,green,blue));   
    removed[i]=true;
    pixels.show();

  }

    pixels.setPixelColor(16, pixels.Color(red,green,blue));
    pixels.setPixelColor(17, pixels.Color(red,green,blue)); 
    removed[16]=true;
    removed[17]=true;  
    pixels.show();
    //delay(50);     
  }
  if(level>=11){
    pixels.setPixelColor(18, pixels.Color(red,green,blue));
    pixels.setPixelColor(23, pixels.Color(red,green,blue));
    removed[18]=true;
    removed[23]=true;   
    pixels.show();
    //delay(50);   
  }
  if(level>=12){
    pixels.setPixelColor(19, pixels.Color(red,green,blue));
    pixels.setPixelColor(22, pixels.Color(red,green,blue));
    removed[19]=true;
    removed[22]=true;   
    pixels.show();
    //delay(50);   
  }
    if(level==13){
    pixels.setPixelColor(20, pixels.Color(red,green,blue));
    pixels.setPixelColor(21, pixels.Color(red,green,blue));
    removed[20]=true;
    removed[21]=true;   
    pixels.show();
    //delay(50);   
  }
  for(int i=0;i<NUMPIXELS;i++){
    if(removed[i]==false){
      pixels.setPixelColor(i,0,0,0);
    }
  }
  pixels.show();
}
void show_rainbow(char direction,int cycles){
      for(int i=16;i<NUMPIXELS;i++){
        pixels.setPixelColor(i, pixels.Color(10,10,10));
        pixels.show();
  }
  pixels.updateLength(16);
  if(direction=='a'){
  for(long firstPixelHue = 0; firstPixelHue < cycles*65536; firstPixelHue += 256) {
    pixels.rainbow(firstPixelHue);
    pixels.show(); 
    delay(1);  
  }
 
}
else if(direction=='c'){
  for(long firstPixelHue = cycles*65536-1; firstPixelHue >=0; firstPixelHue -= 256) {
    pixels.rainbow(firstPixelHue);
    pixels.show(); 
    delay(1);  
     }   
   }
    pixels.updateLength(NUMPIXELS);
 }
 void clear_face(){
    pixels.clear();
    for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(0,0,0));
  }
  pixels.show();
 }
void begin(){
 
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  pixels.clear();
  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(0,0,0));
  }
  pixels.show();
 
  pinMode(MotorBR1,OUTPUT);
  pinMode(MotorBR2,OUTPUT);
  pinMode(MotorBL1,OUTPUT);
  pinMode(MotorBL2,OUTPUT);
  pinMode(MotorFL1,OUTPUT);
  pinMode(MotorFL2,OUTPUT);
  pinMode(MotorFR1,OUTPUT);
  pinMode(MotorFR2,OUTPUT);

  pinMode(LTRight,INPUT);
  pinMode(LTLeft,INPUT);
  pinMode(LTCenter,INPUT);  
}


void Stop ()
{
  ///////////stop///////////
  //front left motor 
  digitalWrite(MotorFL1, LOW);
  digitalWrite(MotorFL2, LOW);
  //back right motor 
  digitalWrite(MotorBR1, LOW);
  digitalWrite(MotorBR2, LOW);
  //front right motor 
  digitalWrite(MotorFR1, LOW);
  digitalWrite(MotorFR2, LOW);
  //back left motor 
  digitalWrite(MotorBL1, LOW);
  digitalWrite(MotorBL2, LOW);   

}

void Forward (int speed)
{
    //setting motors' speeds to 0/255
    analogWrite(MotorBLS, speed);
    analogWrite(MotorFLS, speed);
    analogWrite(MotorBRS, speed);
    analogWrite(MotorFRS, speed);

    ////////forward///////////
    //front left motor 
    digitalWrite(MotorFL1, HIGH);
    digitalWrite(MotorFL2, LOW);
    //back right motor 
    digitalWrite(MotorBR1, HIGH);
    digitalWrite(MotorBR2, LOW);
    //front right motor 
    digitalWrite(MotorFR1, HIGH);
    digitalWrite(MotorFR2, LOW);
    //back left motor 
    digitalWrite(MotorBL1, HIGH);
    digitalWrite(MotorBL2, LOW);   
}

void Backward (int speed)
{
    //setting motors' speeds to 0/255
    analogWrite(MotorBLS, speed);
    analogWrite(MotorFLS, speed);
    analogWrite(MotorBRS, speed);
    analogWrite(MotorFRS, speed);

    ////////backward///////////
    //front left motor 
    digitalWrite(MotorFL1, LOW);
    digitalWrite(MotorFL2, HIGH);
    //back right motor 
    digitalWrite(MotorBR1, LOW);
    digitalWrite(MotorBR2, HIGH);
    //front right motor 
    digitalWrite(MotorFR1, LOW);
    digitalWrite(MotorFR2, HIGH);
    //back left motor 
    digitalWrite(MotorBL1, LOW);
    digitalWrite(MotorBL2, HIGH);   
}

void rotateLeft (int speed)
{
  //setting motors' speeds to 0/255
  analogWrite(MotorBLS,speed);
  analogWrite(MotorFLS,speed);
  analogWrite(MotorBRS,speed);
  analogWrite(MotorFRS,speed);

  //Back left motor backward
  digitalWrite(MotorBL1,LOW);
  digitalWrite(MotorBL2,HIGH);
  //front left motor backward
  digitalWrite(MotorFL1,LOW);
  digitalWrite(MotorFL2,HIGH);
  //front right motor forward
  digitalWrite(MotorBR1,HIGH);
  digitalWrite(MotorBR2,LOW);
  //front right motor forward
  digitalWrite(MotorFR1,HIGH);
  digitalWrite(MotorFR2,LOW);

}
void rotateRight (int speed)
{
  //setting motors' speeds to 0/255
  analogWrite(MotorBLS,speed);
  analogWrite(MotorFLS,speed);
  analogWrite(MotorBRS,speed);
  analogWrite(MotorFRS,speed);

  digitalWrite(MotorBL1,1);
  digitalWrite(MotorBL2,0);
  digitalWrite(MotorFL1,1);
  digitalWrite(MotorFL2,0);
  digitalWrite(MotorBR1,0);
  digitalWrite(MotorBR2,1);
  digitalWrite(MotorFR1,0);
  digitalWrite(MotorFR2,1);

}

void RightCurveForward (int speed)
{
  //setting motors' speeds to 0/255
  analogWrite(MotorBLS,speed * 0.8);
  analogWrite(MotorFLS,speed * 0.9);
  analogWrite(MotorBRS,speed * 0.5);
  analogWrite(MotorFRS,speed * 0.5);

  //front left motor 
  digitalWrite(MotorFL1, LOW);
  digitalWrite(MotorFL2, HIGH);
  //back right motor 
  digitalWrite(MotorBR1, LOW);
  digitalWrite(MotorBR2, HIGH);
  //front right motor 
  digitalWrite(MotorFR1, LOW);
  digitalWrite(MotorFR2, HIGH);
  //back left motor 
  digitalWrite(MotorBL1, LOW);
  digitalWrite(MotorBL2, HIGH); 

}
void LeftCurveForward (int speed)
{
  //setting motors' speeds to 0/255
  analogWrite(MotorBLS,speed * 0.5);
  analogWrite(MotorFLS,speed * 0.5);
  analogWrite(MotorBRS,speed * 0.8);
  analogWrite(MotorFRS,speed * 0.9);
  
  //front left motor 
  digitalWrite(MotorFL1, LOW);
  digitalWrite(MotorFL2, HIGH);
  //back right motor 
  digitalWrite(MotorBR1, LOW);
  digitalWrite(MotorBR2, HIGH);
  //front right motor 
  digitalWrite(MotorFR1, LOW);
  digitalWrite(MotorFR2, HIGH);
  //back left motor 
  digitalWrite(MotorBL1, LOW);
  digitalWrite(MotorBL2, HIGH);

}
void LeftCurveBackward (int speed)
{
  //setting motors' speeds to 0/255
  analogWrite(MotorBLS,speed * 0.5);
  analogWrite(MotorFLS,speed * 0.5);
  analogWrite(MotorBRS,speed * 0.9);
  analogWrite(MotorFRS,speed * 0.8);

  ////////backward///////////
  //front left motor 
  digitalWrite(MotorFL1, LOW);
  digitalWrite(MotorFL2, HIGH);
  //back right motor 
  digitalWrite(MotorBR1, LOW);
  digitalWrite(MotorBR2, HIGH);
  //front right motor 
  digitalWrite(MotorFR1, LOW);
  digitalWrite(MotorFR2, HIGH);
  //back left motor 
  digitalWrite(MotorBL1, LOW);
  digitalWrite(MotorBL2, HIGH);

}
void RightCurveBackward (int speed)
{
  //setting motors' speeds to 0/255
  analogWrite(MotorBLS,speed * 0.9);
  analogWrite(MotorFLS,speed * 0.8);
  analogWrite(MotorBRS,speed * 0.5);
  analogWrite(MotorFRS,speed * 0.5);
  
  ////////backward///////////
  //front left motor 
  digitalWrite(MotorFL1, LOW);
  digitalWrite(MotorFL2, HIGH);
  //back right motor 
  digitalWrite(MotorBR1, LOW);
  digitalWrite(MotorBR2, HIGH);
  //front right motor 
  digitalWrite(MotorFR1, LOW);
  digitalWrite(MotorFR2, HIGH);
  //back left motor 
  digitalWrite(MotorBL1, LOW);
  digitalWrite(MotorBL2, HIGH);

}

void FrontLeftDiagonal (int speed)
{
  //setting front right & back left motors' speeds to 0/255
  analogWrite(MotorFRS,speed);
  analogWrite(MotorBLS,speed);

  //front right motor forward
  digitalWrite(MotorFR1,HIGH);
  digitalWrite(MotorFR2,LOW);
  //back left motor forward
  digitalWrite(MotorBL1,HIGH);
  digitalWrite(MotorBL2,LOW);

}
void BackRightDiagonal (int speed)
{
  //setting front right & back left motors' speeds to 0/255
  analogWrite(MotorFRS,speed);
  analogWrite(MotorBLS,speed);

  //front right motor backward
  digitalWrite(MotorFR1,LOW);
  digitalWrite(MotorFR2,HIGH);
  //back left motor forward
  digitalWrite(MotorBL1,LOW);
  digitalWrite(MotorBL2,HIGH);

}
void FrontRightDiagonal (int speed)
{
  //setting front left & back righ motors' speeds to 0/255
  analogWrite(MotorFLS,speed);
  analogWrite(MotorBRS,speed);
  
  //front left motor forward
  digitalWrite(MotorFL1,HIGH);
  digitalWrite(MotorFL2,LOW);
  //front left motor forward
  digitalWrite(MotorBR1,HIGH);
  digitalWrite(MotorBR2,LOW);

}
void BackLeftDiagonal (int speed)
{
  //setting front left & back righ motors' speeds to 0/255
  analogWrite(MotorFLS,speed);
  analogWrite(MotorBRS,speed);
  
  //front left motor backward
  digitalWrite(MotorFL1,LOW);
  digitalWrite(MotorFL2,HIGH);
  //back right motor backward
  digitalWrite(MotorBR1,LOW);
  digitalWrite(MotorBR2,HIGH);

}
void Right (int speed)
{
  //setting motors' speeds to 0/255
  analogWrite(MotorBLS,speed);
  analogWrite(MotorFLS,speed);
  analogWrite(MotorBRS,speed);
  analogWrite(MotorFRS,speed);

  //front left motor forward
  digitalWrite(MotorFL1,HIGH);
  digitalWrite(MotorFL2,LOW);
  //back right motor forward
  digitalWrite(MotorBR1,HIGH);
  digitalWrite(MotorBR2,LOW);

  //front right motor backward
  digitalWrite(MotorFR1,LOW);
  digitalWrite(MotorFR2,HIGH);
  //back left motor backward
  digitalWrite(MotorBL1,LOW);
  digitalWrite(MotorBL2,HIGH);

}
void Left (int speed)
{
  //setting motors' speeds to 0/255
  analogWrite(MotorBLS,speed);
  analogWrite(MotorFLS,speed);
  analogWrite(MotorBRS,speed);
  analogWrite(MotorFRS,speed);

  //front right motor forward
  digitalWrite(MotorFR1,HIGH);
  digitalWrite(MotorFR2,LOW);
  //back left motor forward
  digitalWrite(MotorBL1,HIGH);
  digitalWrite(MotorBL2,LOW);

  //front left motor backward
  digitalWrite(MotorFL1,LOW);
  digitalWrite(MotorFL2,HIGH);
  //back right motor backward
  digitalWrite(MotorBR1,LOW);
  digitalWrite(MotorBR2,HIGH);

}
float getDistance(){
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  float duration = pulseIn(echo, HIGH);
  return  duration * 0.034 / 2;
}
void distance_ring(){
  int distance=getDistance();
    if(distance>30){
    for(int i=0;i<NUMPIXELS;i++){
      pixels.setPixelColor(i, pixels.Color(0,255,0));
    }
      pixels.show();
  }
  else if(distance<4){
     for(int i=0;i<NUMPIXELS;i++){
      pixels.setPixelColor(i, pixels.Color(255,0,0));
    } 
      pixels.show();  
  }
  else{
    int level=map(distance,30,4,1,NUMPIXELS/2+1);
    show_levels(level,map(distance,30,4,0,255),map(distance,4,30,0,255),0);
  }
  delay(100);
}

void obstacleAvoidance(){
  if(getDistance()<15){
    Stop();
    delay(50);
    Backward(100);
    delay(100);
    Stop();
    delay(50);
    rotateRight(150);
    delay(100);
  }
  else{
    Forward(100);
  }

}
void lineFollower(){
  bool left=analogRead(LTLeft)>100;
  bool center=analogRead(LTCenter)>100;
  bool right=analogRead(LTRight)>100;
  if(!left&&!center&&right){
    rotateRight(70);
   delay(100);
   Forward(100);
   delay(50);
 }
   if(!left&&center&&!right){
   Forward(100);
   delay(100);
 }
   if(!left&&center&&right){
      rotateRight(70);
      delay(100);
      Forward(100);
      delay(50);
 }
   if(left&&!center&&!right){

   rotateLeft(70);
   delay(100);
   Forward(100);
   delay(50);
 }
   if(left&&!center&&right){
   Forward(100);
 }
   if(left&&center&&!right){

   rotateLeft(70);
   delay(100);
    Forward(100);
    delay(50);
 }if(left&&center&&right){

   Forward(100);
 }
  if(!left&&!center&&!right){
    rotateRight(70);
    delay(100);
  }
}
void prisoner(){
  bool left=analogRead(LTLeft)>100;
  bool center=analogRead(LTCenter)>100;
  bool right=analogRead(LTRight)>100;
  if(left||center||right){
    Stop();
    delay(50);
    rotateRight(150);
    delay(500);
  }
  else{
    Forward(100);
    delay(100);
  }
}
void Square(){
  for(int i=0;i<4;i++){
  Forward(150);
  delay(1500);
  Stop();
  delay(50);
  rotateRight(150);
  delay(1500);
  Stop();
  delay(50);
  }

}
