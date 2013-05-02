
#include"stddefs.h"
#include"gsm.h"

uint8_t initGSM()
{
 uint8_t i=0,j=0;
 char gsmMsg[20];

 USARTInit(BAUD_PRESCALE);

 sendCommand("AT");

 while(i<10)
  {
    
   if(UDataAvailable()<6)
    {
	 i++;
	 _delay_ms(10);
	}
	else
	{
	 
	 for(j=0;j<6;j++)
	  {
	   gsmMsg[j]=UReadData();
	  }

	 if(gsmMsg[2]=='O' && gsmMsg[3]=='K')
	  {
	   UFlushBuffer();
	   return 1;
	  }
	}
  }

 return 0; //initialization failed
}

void sendCommand(char *command)
{
  UWriteCharArray(command);
  UWriteData(ENTER);
}

uint8_t isMessageNotification()
{
 uint8_t timeout=0;

 while(UDataAvailable()<20 && timeout<10) //timeout at 1 second
  {
   timeout++;
   _delay_ms(100);
  }

  if(timeout>=10)
   {
	return 0;
   }
  
  UFlushBuffer();

  return 1;
}

void deleteMsg()
{
 sendCommand("AT+CMGD=1");
}

void sendMsg(char *msg)
{
	sendCommand("AT+CMGS=\"+9779808855727\"");
	_delay_ms(100);

	sendCommand(msg);
	UWriteData(0x1A);
}

uint8_t readMsg(uint8_t i,char *msg)
{

 char ch[16]="AT+CMGR=";
 char num[3];
 uint8_t j=8,k=0;
 uint8_t cnt=0;
 uint8_t timeout=0;
 uint8_t semi=0;
 char gsmMsg[128];

 itoa(i,num,10);

 while(num[k])
  {
   ch[j++]=num[k++];
  }

 ch[j]=0;

 UFlushBuffer();
 _delay_ms(10);

 sendCommand(ch);

 while(UDataAvailable()<120 && timeout<20)
  {
   timeout++;
   _delay_ms(100);
  }

 for(i=0;i<120;i++)
   gsmMsg[cnt++]=UReadData();
 
 gsmMsg[cnt]=0;
 LCDGotoXY(0,0);

 for(i=0;i<120;i++)
  {
   if(gsmMsg[i]=='"')
    semi++;
   if(semi>=6)
    break;
  }

  i+=3;
  k=0;

  for(j=i;j<120;j++)
   {
    if(gsmMsg[j]=='O')
	 break;
	msg[k++]=gsmMsg[j];
   }
   

   msg[k-2]=0;

   //for(i=62;i<78;i++)
    //LCDData(gsmMsg[i]);
 
/*
 for(i=0;i<120;i++)
  {
   if(gsmMsg[i]=='\n' && i>2)
    break;
  }
 
 k=0;
 for(j=i;j<120;j++)
  {
   if(gsmMsg[j]=='\n' || gsmMsg[j]=='\r')
    break;

   msg[k++]=gsmMsg[j];
  }
 
 msg[k]=0;
 i=0;
 j=0;
*/

/*for(i=62;i<78;i++)
  msg[j++]=gsmMsg[i];
 
 msg[j]=0;
*/

 return 0;
}

void extractPinCode(char* msg,char *pin)
{
  uint8_t i=0;

  while(msg[i]!=' ' && msg[i])
   {
    pin[i]=msg[i];
	i++;
   }
	
  pin[i]=0;
}

void extractMachineCode(char *msg,char *machine)
{
  uint8_t i=0,j=0;

  while(msg[i]!=' '  && msg[i]) i++;
  i++;

  while(msg[i]!=' ')
   {
    machine[j++]=msg[i++];
   }

   machine[j]=0;
}

void extractItemCode(char *msg,char *item)
{
 uint8_t i=0,j=0;

  while(msg[i]!=' ' && msg[i]) i++;
  i++;
  while(msg[i]!=' ' && msg[i]) i++;
  i++;
  while(msg[i]!=' ' && msg[i])
   {
    item[j++]=msg[i++];
   }

   item[j]=0;
}
