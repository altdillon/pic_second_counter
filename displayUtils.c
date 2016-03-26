/*
 * File:   displayUtils.c
 * Author: dillon
 *
 * Created on March 21, 2016, 4:07 AM
 */


#include <xc.h>
#include <stdbool.h>
#include "utils.h"

char lookup_table[]={0x3f,0x0b,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

char getSevenSegmentNode(char bcd)
{
    if(bcd > 9)
    {
        return -1;
    }
    else
    {
        return ~lookup_table[bcd]; //this is for a common cathode, b/c we're lazy
    }
}

void updateDisplay(char d_one,char d_two,char d_three,char dec_point)
{
    char buffer[3];
    unsigned char i;
   
    //figure out what the actual digits are going to be
    buffer[0]=getSevenSegmentNode(d_one);
    buffer[1]=getSevenSegmentNode(d_two);
    buffer[2]=getSevenSegmentNode(d_three);
    buffer[dec_point]=buffer[dec_point] | 0b00000001;
    
    //do the display multiplexing.
    PORTB=buffer[0];
    PORTAbits.RA7=true;
    for(i=0;i<0xff;i++);
    PORTAbits.RA7=false;
    PORTB=buffer[1];
    PORTAbits.RA0=true;
    for(i=0;i<0xff;i++);
    PORTAbits.RA0=false;
    PORTB=buffer[2];
    PORTAbits.RA1=true;
    for(i=0;i<0xff;i++);
    PORTAbits.RA1=false;
 
}