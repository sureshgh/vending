

#include"stddefs.h"

char product[][13]={"Wai wai",
					"Mayos",
					"Surya",
					"Shikhar",
					"Kwiks Balls",
					"Pachak",
					"Momo",
					"Gadeula",
					"Naan"
					};

int main()
{

 char msg[128],pin[10],machine[10],item[10],success[30];
 uint8_t number;
 uint8_t motorCounter=0;

 DDRB=0xff;
 DDRD=0xf8;
 
 DDRC=0xff;
 DDRA=0b11111110;
 PORTA=0b00000001;
 PORTC=0x00;

 sei();

 initLCD();
 _delay_ms(50);
 LCDClear();
 LCDGotoXY(0,0);
 _delay_ms(50);

 if(initGSM())
  LCDPrint("Vending Machine");
 
 LCDGotoXY(0,0);

 sendCommand(ENABLE_TEXT_MODE); //Enable Text Mode

// uint8_t j=0;

 while(1)
  {
   number=isMessageNotification();

   if(number)
    {

	 readMsg(2,msg);
	 LCDGotoXY(0,0);
	 LCDPrint(msg);
	 //extractPinCode(msg,pin);
     //extractMachineCode(msg,machine);
     //extractItemCode(msg,item);
	 
	 //CDGotoXY(1,1);
	
	 if(!strcmp(machine,"vm001"))
	  {

	   //LCDGotoXY(0,0);
	   //LCDPrint("Good one");
	   //j++;
	   //LCDGotoXY(0,1);
	   //LCDData(j+48);
	  
	   /* motorCounter=item[2]-48;
	  
	   if(motorCounter<9)
	    {
	     PORTC=(1<<(motorCounter-1));
		 LCDPrint(product[motorCounter-1]);
		 LCDPrint("                ");
		}
	   else
	    {
	     PORTA|=(1<<PA7);
		 LCDPrint(product[8]);
		}
	  
	   while(!(PINA&(1<<PA0)));
	   
	   LCDGotoXY(1,1);
	   LCDPrint("Completed       ");

		PORTC=0;
		PORTA&=~(1<<PA7);
		
		strcpy(success,pin);
		strcat(success," SUCCESS");*/
		//deleteMsg();
		//_delay_ms(500);
		//sendMsg(pin);
		//_delay_ms(500);

		machine[0]=0;
		item[0]=0;
		pin[0]=0;
	  }
	}
  }
 
 return 0;

}
