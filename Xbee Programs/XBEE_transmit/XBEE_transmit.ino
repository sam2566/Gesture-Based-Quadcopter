/*The given below code was developed by Saurabh Mehta for the packet data generation to be used with XBEE.
 * 
 */

volatile int i;

void setup()                            //Main Setup Code
{
  Serial.begin(115200);
}

void loop()                             //Main Loop Code
{
    Sabziwala();                        //Function to make and send packet data to XBEE module
}

void Sabziwala()                        // This program generates Packet data and sends it to XBEE module
{
  byte sabzi[16],SUM=0,checksum=0;      // Initial variables
   
  sabzi[0]=0x90;                        // Setting up values to the variable
  sabzi[1]=(byte)0x0;
  sabzi[2]=0x13;
  sabzi[3]=0xA2;
  sabzi[4]=(byte)0x0;
  sabzi[5]=(byte)0x0;
  sabzi[6]=(byte)0x0;
  sabzi[7]=0xFF;
  sabzi[8]=0XFF;
  sabzi[9]=0XFF;
  sabzi[10]=0XFE;
  sabzi[11]=0X01;
  sabzi[12]=0X11;
  sabzi[13]=0X11;
  sabzi[14]=0X11;
  sabzi[15]=0X11;

  for(i=0;i<16;i++)                     // Calculating SUM
  {
    SUM = SUM +sabzi[i];
  }
  checksum = 0xFF - (SUM & 0XFF);       // Calculate Checksum
  //Serial.println(checksum,HEX);
  Serial.flush();
  Serial.write(0x7E);                   // Send start delimiter
  delay(5);
  Serial.write((byte)0x0);              // Send Length - 1
  delay(5);
  Serial.write(0x10);                   // Send Length - 2
  delay(5);
  for(i=0; i<16; i++)                   // Send the values
  {
    Serial.write((byte)sabzi[i]);
    delay(5);
  }
  Serial.write((byte)checksum);         // Send the checksum
  delay(100);
  Serial.flush();                       // Flush the buffer data, if present.
}
