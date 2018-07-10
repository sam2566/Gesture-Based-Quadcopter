volatile byte data[20],L1,L2,checksum;
volatile int x,i,j,L,M,ack, b[4];
volatile float a[4];

void setup() 
{
  // setup code, to run once:
  
  // Serial Communication at 115200 Baud rate
  Serial.begin(115200);
  
  //Setup Complete
  Serial.println("Setup Done");
  delay(1000);
}


void loop() 
{
  //main code, to run repeatedly:
  
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
    
  //Discard any buffer data present
  Serial.flush();
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
  else 
    return 0;
}
