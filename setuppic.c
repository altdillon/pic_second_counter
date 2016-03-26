/*
 * File:   setuppic.c
 * Author: dillon
 *
 * Created on March 20, 2016, 2:49 AM
 */


#include "utils.h"

void system_init()
{
    OSCCON=0b01101100;
    ANSEL=0x00;
    TRISB=0x00;
    TRISA=0xff;
    
    TRISAbits.TRISA7=0;
    TRISAbits.TRISA0=0;
    TRISAbits.TRISA1=0;
    
    OPTION_REG=0b10001111;
    INTCON=0b10100000; //we may not need this
}
