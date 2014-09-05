//simple Tx on pin D12
//Written By : Mohannad Rawashdeh
// 3:00pm , 13/6/2013
//http://www.genotronex.com/
//..................................
#include <VirtualWire.h>
void setup()
{
    Serial.begin(9600);	  // Debugging only
    Serial.println("setup");
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_set_rx_pin(12);
    vw_setup(4000);  // Bits per sec
    pinMode(13, OUTPUT);

    vw_rx_start();       // Start the receiver PLL running
}
    void loop()
{
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;

    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
      int i;
      char letra;
      if(buf[0]=='1'){ 
        digitalWrite(13,0);
      }  
     if(buf[0]=='0'){
        digitalWrite(13,1);
      }
      Serial.print("Got: ");
	
	for (i = 0; i < buflen; i++)
	{
	    Serial.print(buf[i], HEX);
            Serial.print(" ");
            letra=hexNibbleToChar(buf[i]);
            Serial.print(letra);
	    Serial.println(" ");
	}
	Serial.println("");
    }
}

char hexNibbleToChar(char nibble)
{
  if (nibble >= '0' && nibble <= '9')
    return nibble - '0';
  else if (nibble >= 'a' && nibble <= 'f')
    return 10 + nibble - 'a';
  else
    return 10 + nibble - 'A';
}
