/*
 * File:   newmain.c
 * Author: Radhika
 *
 * Created on 27 October, 2026, 2:47 PM
 */

#include <xc.h>
#include "CLCD.h"
#include "adc.h"
#include "cann.h"
#include "msg.h"
#include "newmain.h"
#include "Matrix keypad.h"
#include <stdint.h>

unsigned int count = 0, flag = 0;
unsigned int delay = 0, key = 0;
unsigned short rpm;
    uint8_t rpm_data[5];
    uint8_t indicator[6] = "      ";
    uint8_t indicator_status = 0;

void init_config(void)
{
    init_clcd();
    init_adc();
    init_matrix_keypad();
    init_can();
    

PORTB = 0x00;

TRISC = TRISC | 0x08;  // RC3 input; preserve other TRISC settings
TRISCbits.TRISC0 = 0;  // RW output
TRISCbits.TRISC1 = 0;  // RS output
TRISCbits.TRISC2 = 0;  // EN output
}

void main(void)
{
    

    init_config();

    while (1)
    {
       
         rpm = (read_adc(CHANNEL4) / 10.23) * 60;

        rpm_data[0] = ((rpm / 1000) % 10 + '0');
        rpm_data[1] = ((rpm / 100) % 10 + '0');
        rpm_data[2] = ((rpm / 10) % 10 + '0');
        rpm_data[3] = (rpm % 10 + '0');
        rpm_data[4] = '\0';


        
//        clcd_print((const unsigned char *)"RPM INDICATOR", LINE1(0));
//       clcd_print((const unsigned char *)rpm_data, LINE2(0));
       
       can_transmit(RPM_MSG_ID, rpm_data, 4);
        __delay_ms(80);
        
        
        key = read_switches(STATE_CHANGE);
        
        if(key == MK_SW3)
        {
            flag = 1;
            count = 0;
            PORTB = 0x00;
            indicator_status = 1;
            indicator[0] = 'L';
            indicator[1] = 'E';
            indicator[2] = 'F';
            indicator[3] = 'T';
            indicator[4] = '\0';
        }
        else if (key == MK_SW4)
        {
            flag = 2;
            count = 0;
            PORTB = 0x00;
            indicator_status = 2;
            indicator[0] = 'R';
            indicator[1] = 'I';
            indicator[2] = 'G';
            indicator[3] = 'H';
            indicator[4] = 'T';
            indicator[5] = '\0';
            
        }
        else if (key == MK_SW5)
        {
            flag = 0;
            count = 0;
            PORTB = 0x00;
            indicator_status = 0;
               
         indicator[0] = ' ';
         indicator[1] = ' ';
         indicator[2] = ' ';
         indicator[3] = ' ';
         indicator[4] = ' ';
         indicator[5] = '\0';
        }
        
      
        
        if(flag == 1)
        {
            if(count % 2 == 0)
            {
                PORTB = 0x03;
            }
            else
            {
                PORTB = 0x00;
            }
            count++;
            
        }
        else if(flag == 2)
        {
            
            
            if(count % 2 == 0)
            {
                PORTB = 0xC0;
            }
            else
            {
                PORTB = 0x00;
            }
            count++;
        }
        else
        {
            PORTB = 0x00;
        }
        //clcd_print( (const unsigned char *)indicator, LINE2(10) );  
        // Use your actual status variable
       can_transmit(INDICATOR_MSG_ID, &indicator_status, 1);
        __delay_ms(80);
        
    }
}