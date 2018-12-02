//decode_results results;
#include <SoftwareSerial.h>            
#include <TimerOne.h>
SoftwareSerial BTserial(9, 11); // RX, TX
           
volatile int i=0;               // Variable to use as a counter
int LED_PIN = 13;
int intensity = 127;
volatile boolean zero_cross=0;  // Boolean to store a "switch" to tell us if we have crossed zero
int AC_pin = 10;                 // Output to Opto Triac

int dim2 = 0;                   // led control
int dim = 128;                  // Dimming level (0-128)  0 = on, 128 = 0ff                  
int freqStep = 75;    // This is the delay-per-brightness step in microseconds.

void setup() {   
  pinMode(AC_pin, OUTPUT);                          // Set the Triac pin as output
  pinMode(LED_PIN, OUTPUT);
    BTserial.begin(9600);
    Serial.begin(9600);
  attachInterrupt(0, zero_cross_detect, RISING);    // Attach an Interupt to Pin 2 (interupt 0) for Zero Cross Detection
  Timer1.initialize(freqStep);                      // Initialize TimerOne library for the freq we need
  Timer1.attachInterrupt(dim_check, freqStep);    
  Serial.println("Ready");  
  digitalWrite(LED_PIN, HIGH);
}

void zero_cross_detect() 
{    
  zero_cross = true;               // set the boolean to true to tell our dimming function that a zero cross has occured
  i=0;
  digitalWrite(AC_pin, LOW);
}                                 
// Turn on the TRIAC at the appropriate time

void dim_check() 
{                   
  if(zero_cross == true) {              
    if(i>=dim) {                     
      digitalWrite(AC_pin, HIGH);  // turn on light  
//      delayMicroseconds(10);     
      i=0;  // reset time step counter                         
      zero_cross=false;    // reset zero cross detection
    } 
    else {
      i++;  // increment time step counter                     
}}}                                      


void translateIR(char a) // takes action based on IR code received
{
  switch(a)
  {
  case 'x':  
    {
   Serial.println(a);
    if (dim<127)  
   {
    dim = dim + 8;
    if (dim>127) 
    {
      dim=128; // in vechiul sketch era 127
    }
    }}
    
    break;

  case 'y':  
    {
    Serial.println(a);
      {
  if (dim>5)  
  {
     dim = dim - 8;
  if (dim<0) 
    {
      dim=0;  // in vechiul sketch era 1
    } }}}
    break;
  }}
  
void loop() 
{
//  dim = map(analogRead(A0), 0, 1023, 5, 124);
  dim = intensity;
  Serial.println(dim);
  
  char c;

  if(BTserial.available() > 0)
  {
     c = (char)BTserial.read();
     if(c == '1')
     { 
        digitalWrite(LED_PIN, HIGH);
        Serial.println("LED ON");
     }
     else if(c == '2')
     {
       digitalWrite(LED_PIN, LOW);
       Serial.println("LED OFF");
     }
     else if(c == '3')
     {
        intensity = 127;
        Serial.println("BULB OFF");
     }
     else if(c == '4')
     {
       intensity = 100;
       Serial.println("BULB LOW 100");
     }
     else if(c == '5')
     {
       intensity = 70;
       Serial.println("BULB LOW 70");
     }
     else if(c == '6')
     {
       intensity = 40;
       Serial.println("BULB LOW 40");
     }
     else if(c == '7')
     {
       intensity = 10;
       Serial.println("BULB LOW 10");
     }
     else if(c == '8')
     {
       intensity = 0;
       Serial.println("BULB OFF");
     }
  }
}
