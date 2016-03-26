/*
 * File:   main.c
 * Author: dillon
 *
 * Created on March 20, 2016, 2:44 AM
 */

// PIC16F88 Configuration Bit Settings

// 'C' source line config statements

#include <xc.h>
#include <stdbool.h>

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG1
#pragma config FOSC = INTOSCCLK // Oscillator Selection bits (INTRC oscillator; CLKO function on RA6/OSC2/CLKO pin and port I/O function on RA7/OSC1/CLKI pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = OFF      // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is digital I/O, MCLR internally tied to VDD)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage Programming Enable bit (RB3/PGM pin has PGM function, Low-Voltage Programming enabled)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off)
#pragma config CCPMX = RB0      // CCP1 Pin Selection bit (CCP1 function on RB0)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// CONFIG2
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal External Switchover mode enabled)


#include "utils.h"

void bres_count();
void event();
unsigned int b_count; //this is a big number, so we can use 4 bytes
unsigned char tuning;
unsigned short wheel_count;
display one;
display two;
display three;
char descimal_point=3;

void interrupt bres_count_int()
{    
    tuning=0;
    //INTCONbits.T0IF = false;
    //INTCON &= 0x04; //clear the timer over flow error bit or some shit like that.
    
    if(b_count>=(4004+tuning))
    {
        if(PORTBbits.RB0==true)
        {
            PORTBbits.RB0=false;
        }
        else
        {
            PORTBbits.RB0=true;
        }
        
        b_count=0;
    }
    else
    {
        b_count+=1;
    }
    
    if(INTCONbits.INT0IF)
    {
        INTCONbits.TMR0IF=false;
    }
}


void main() 
{
    system_init();
    wheel_count=0;
    
    //d_one=0x01;
    //d_two=0x02;
    //d_three=0x03;
    
    while(true)
    {
//        unsigned char i;
//        for(i=0;i<255;i++); //debounce 
//        
//        if(PORTAbits.RA1==true)
//        {
//            PORTBbits.RB1=true;
//        }
//        else
//        {
//            PORTBbits.RB1=false;
//        }
        
        //there may be an issue where the magnetic switch needs to be debouced.
        //if indeed it does we could probs do it on code or with a rc circit. 
        if(PORTBbits.RB6==true)
        {
            wheel_count++;
        }
        
        //update display
        //get seven segment value and set portb to that value.
        //updateDisplay(1,2,3,0);
        //char value=0x08;
        //value=getSevenSegmentNode(value);
        //PORTB=value;
        //PORTAbits.RA7=true;
        PORTB=0x00;
    }
    
    return;
}
