#include <SoftwareSerial.h> // import the serial library

#define switch1 7
#define switch2 6
#define switch3 5

bool switch1Status, switch2Status, switch3Status;

SoftwareSerial BtSerial(10, 11); // RX, TX

void setup() 
{
  switch1Status = false;
  switch2Status = false;
  switch3Status = false;
  
  Serial.begin(9600);
  BtSerial.begin(9600);
  
  pinMode(switch1, OUTPUT);
  digitalWrite(switch1, switch1Status);
  pinMode(switch2, OUTPUT);
  digitalWrite(switch2, switch1Status);
  pinMode(switch3, OUTPUT);
  digitalWrite(switch3, switch3Status);
}

void loop() 
{
  char bluetoothData = 'a';
  if (BtSerial.available() > 0)
  {
    bluetoothData=BtSerial.read();
    switch(bluetoothData)
    {
      case '1':
        if(!switch1Status)
        {
          switch1Status = true;
          digitalWrite(switch1, HIGH); 
        }
        else if(switch1Status)
        {
          switch1Status = false;
          digitalWrite(switch1, LOW); 
        }
        break;
        
      case '2':
        if(!switch2Status)
        {
          switch2Status = true;
          digitalWrite(switch2, HIGH); 
        }
        else if(switch2Status)
        {
          switch2Status = false;
          digitalWrite(switch2, LOW); 
        }
        break;       
    
      case '3':
        if(!switch3Status)
        {
          switch3Status = true;
          digitalWrite(switch3, HIGH); 
        }
        else if(switch3Status)
        {
          switch3Status = false;
          digitalWrite(switch3, LOW); 
        }
        break;                  
    }    
  }
}
