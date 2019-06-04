#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 80000000UL
void main()
{
	DDRA=0x00;
	usartini();
	while(1)
	{
		if(PINA==0x01)
		sms();
	}
}
void usartini()
{
	UBRRL=51;
	UCSRC|=(1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);
	UCSRB|=(1<<TXEN);
}
void tx(char x)
{
	UDR=x;
	while((UCSRA&(1<<UDRE))==0);
}
void text(char *s)
{
	while(*s)
	{
		tx(*s);
		s++;
	}
}
void sms()
{
	text("AT\r");
	_delay_ms(1000);
	tx(0x22);//ascii value of "
	text("AT+CMGF=1");
	_delay_ms(1000);
	tx(0x22);
	text("AT+CMGS");
	_delay_ms(1000);
	tx(0x22);
	text("8896379952");
	_delay_ms(1000);
	tx(0x22);
	text("Intruder Alert");
	_delay_ms(1000);
	tx(0x02);
	tx(26);
}