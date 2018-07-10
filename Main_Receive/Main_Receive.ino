volatile byte data[20],L1,L2,checksum;
volatile int x,i,j,L,M,ack, b[4];
volatile float a[4];

#include <Servo.h>

Servo m1, m2, m3,m4;


void setup() {
  
  // Serial Communication at 115200 Baud rate
  Serial.begin(115200);
  
  // Attachment of Motors to PWM pins of Nano
  m1.attach(3);
  m2.attach(5);
  m3.attach(6);
  m4.attach(9);
  
  //Arming of Motors
  delay(1);
  m1.write(40);
  delay(1);
  m2.write(40);
  delay(1);
  m3.write(40);
  delay(1);
  m4.write(40);
  
  //Setup Complete
  Serial.println("Setup Done");
  delay(1000);

}

void loop() {
  
  //Initialisation of values
  L1=0;L2=0;
  L=0;
  ack=0;
  
  //Read data recieved through XBEE  
  IncomingData();

  //Discard any buffer data present at Serial
  Serial.flush();

  //move forward only if ack=1
  if (ack==1)
    ack = disco();
  
  //Serial.println(ack);
  //Serial.println(L2,HEX);

  //delay of 20 ms
  delay(20);
  if (ack==3)
    hello();

  //Discard any buffer data present
  Serial.flush();

}


// This function calculates the sum of all the data and verifies it for data integrity
int disco()
{
  x=0;
  for (i=0;i<L;i++)
  {
    x=x+(int)data[i];
  }

  //obtain last two bytes and substract with 0xffh
  x=x%256;
  x=x-255;

  //Serial.println(x);
  int y;
  y= (x+checksum)%256;
  
  //if the checksum equals x value send 3 as acknowledge else 0
  if (x==-(checksum))
   {
    return 3;
   }
  else return 0;

}

//fuction to obtain data through serial port 
void IncomingData()
{
  if (Serial.available())
  {
    if (Serial.read() == 0x7E)
    {   
      L1=Serial.read();
      L2=Serial.read();
        for (i=0;i<16;i++)
        {
         data[i]=Serial.read();
        }      
      checksum=(int)Serial.read();
    }
 delay(25);
  }
      L=(int)L1*256+(int)L2;
      //if the length of incoming data equals 16 then generate acknowlegement as 1
      if (L==16)
        ack=1; 
}

//run the motors based on the data acquired
void hello()
{
  j=0;
  //assigning data to a new array
  for (i=12;i<L;i++)
   {
    j=i-12;   
    a[j]=data[i];
   }
        //calculation of angles from data acquired
       for (int j=0; j<4; j++)
      {
        //a[j]=data[12+j];
        a[j]=a[j]/255*180;
        b[j]=(int)a[j];
        Serial.println(b[j]); 
        //Serial.print('\n');
      }
      //write data to the motors
      m1.write(b[0]);
      m2.write(b[1]);
      m3.write(b[2]);
      m4.write(b[3]);
    
 
}
