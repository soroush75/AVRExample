/*****************************************************
This program was produced by the
CodeWizardAVR V2.05.3 Standard
Project :
Version :
Date    : 2/20/2013
Author  : Sarmast
Company : 
Comments:
Chip type               : ATmega16A
Program type            : Application
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*****************************************************/
// ___***IN THE NAME OF GOD***____
#include <mega16a.h>
# include <stdlib.h>
#include <delay.h>
#include <spi.h>
#include <mega16a.h>
#include <stdio.h>
// Alphanumeric LCD functions
#include <alcd.h>
#define ADC_VREF_TYPE 0x40
#define c1 PIND.4
#define c2 PIND.5
#define c3 PIND.6
#define ADC_VREF_TYPE 0x40
#asm
.equ __lcd_port=0x1B ;PORTC
#endasm
unsigned char scan[4]={0XFE,0XFD,0XFB,0XF7};
unsigned char arrkey[12]={1,2,3,4,5,6,7,8,9,25,0,15};
unsigned char key=19;
unsigned char red[2],counter=0;
unsigned char keypad()
{
    unsigned char r,b,t;
    for (r=0; r<4; r++){
        b=4;
        t=r;
        c1=1;
        c2=1;
        c3=1;
        PORTD=scan[r];
        if(c1==0) {b=1; t--; }
        if(c2==0) b=2;
        if(c3==0) b=3;



        if (!(b==4)){
            key=arrkey[((t*3)+(b-1))];
            while(c1==0);
            while(c2==0);
            while(c3==0);
            delay_ms(30);

            return key;

        }
    }
    key=19;
}

// Read the AD conversion result
unsigned int read_adc(unsigned char adc_input)
{
ADMUX=adc_input | (ADC_VREF_TYPE & 0xff);
// Delay needed for the stabilization of the ADC input voltage
delay_us(10);
// Start the AD conversion
ADCSRA|=0x40;
// Wait for the AD conversion to complete
while ((ADCSRA & 0x10)==0);
ADCSRA|=0x10;
return ADCW;
}

// Declare your global variables here
char r[4];
char* x;
int p;
char lcd_buffer[33],g;
void main(void)
{  char buffer[16];
int i=0,k=0,w=1;
int m1=0;
float v;                    //jerm cold
int m2=0;               //jerm hot
int c=4200;           //zarfiat garmaee water
int p=1000;         //chegali water
int q1=0;           //damaye cold water
int q2=0;         //damaye hot water
float t=2.4;     //zaman baz shodan kole ab
int q3=0;       //damaye karbar
int q4=0;       //nesbat bazshodan cold
int j=0;
char lcd_buff[10];
char lcd_buffe[33],zu[20];
char lcd_buffes[33];
int adc_in;
float temp,temps;
char str[10],lcd[10];
float tf;
int d,z;
// Declare your local variables here

// Input/Output Ports initialization
// Port A initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T
PORTA=0x00;
DDRA=0x00;

// Port B initialization
// Func7=In Func6=In Func5=In Func4=In Func3=Out Func2=In Func1=In Func0=In
// State7=T State6=T State5=T State4=T State3=0 State2=T State1=T State0=T
PORTB=0x00;
DDRB=0xFF;

// Port C initialization
// Func7=Out Func6=Out Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out
// State7=0 State6=0 State5=0 State4=0 State3=0 State2=0 State1=0 State0=0
PORTC=0x00;
DDRC=0xFF;

// Port D initialization
// Func7=Out Func6=In Func5=In Func4=In Func3=Out Func2=Out Func1=Out Func0=Out
// State7=0 State6=T State5=T State4=T State3=0 State2=0 State1=0 State0=0
PORTD=0x00;
DDRD=0x8F;

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
// Mode: Fast PWM top=0xFF
// OC0 output: Disconnected
TCCR0=0x3B;
TCNT0=0x00;
  OCR0=0x255;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: Timer1 Stopped
// Mode: Normal top=0xFFFF
// OC1A output: Discon.
// OC1B output: Discon.
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=0x00;
TCCR1B=0x00;
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;

// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: 125.000 kHz
// Mode: Fast PWM top=0xFF
// OC2 output: Disconnected
ASSR=0x00;
TCCR2=0x4C;
TCNT2=0x00;
OCR2=0x255;

// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
// INT2: Off
MCUCR=0x00;
MCUCSR=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=0x00;

// USART initialization
// USART disabled
UCSRB=0x00;

// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
ACSR=0x80;
SFIOR=0x00;

// ADC initialization
// ADC Clock frequency: 1000.000 kHz
// ADC Voltage Reference: AVCC pin
// ADC Auto Trigger Source: Free Running
ADMUX=ADC_VREF_TYPE & 0xff;
ADCSRA=0x86;
SFIOR&=0x1F;

// SPI initialization
// SPI disabled
SPCR=0x00;

// TWI initialization
// TWI disabled
TWCR=0x00;

// Alphanumeric LCD initialization
// Connections are specified in the
// Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
// RS - PORTC Bit 0
// RD - PORTC Bit 1
// EN - PORTC Bit 2
// D4 - PORTC Bit 4
// D5 - PORTC Bit 5
// D6 - PORTC Bit 6
// D7 - PORTC Bit 7
// Characters/line: 16
lcd_init(16);
#asm("sei")
while (1)
      {
      // Place your code here
        i++;
        q1=read_adc(0);
        temp = ((q1 * 5000.0) / 1023 - 273);
        lcd_gotoxy(0,0);
        sprintf(lcd_buffe,"t=%3.2f",temp);
        lcd_puts(lcd_buffe);
        delay_ms(100);
        q2=read_adc(1);
        temps = ((q2 * 5000.0) / 1023 - 273);
        lcd_gotoxy(8,0);
        sprintf(lcd_buffes,"t=%3.2f",temps);
        lcd_puts(lcd_buffes);
        delay_ms(100);
        keypad();



        if (key!=19)
        {
                 if (key!=15)
                {
                red[counter]=key;
                counter++;
                if (counter==3)
                counter=0;
                }
            if (key==15)
            {     k++;
            counter=0;
            q3=red[1]*10+red[0];
                itoa(q3,x);
                              // m1(q3-q1)=m2(q2-q3)
                q4=((q2-q3)/(q3-q1))*1516;      //q4=nesbat baz shodan ab sard
            v=t/j;
            PORTB.0=0;
            PORTB.1=1;
            delay_ms(q4);
            PORTB.1=0;

            PORTB.6=1; if(q3>25){
            delay_ms(1516);
            PORTB.6=0;}
                else if(q3<=25){  delay_ms(29);
                PORTB.6=0;}
            PORTB.7=0;
            }

              if((key==0)&&(w==k))
            {   w++;
            PORTB.0=1;
            PORTB.1=0;
            PORTB.6=0;
            PORTB.7=1;
            delay_ms(1600);
            PORTB.0=0;
            PORTB.1=0;
            PORTB.6=0;
            PORTB.7=0;

             }





            //matne keypad
        sprintf(buffer,"%d",red[1]);
        lcd_gotoxy(6,1);
        lcd_puts(buffer);
        sprintf(buffer,"%d",red[0]);
        lcd_puts(buffer);
        lcd_gotoxy(8,1);
         }






      }
}