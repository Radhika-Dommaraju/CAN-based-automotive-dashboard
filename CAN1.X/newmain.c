/*
 * File:   newmain.c
 * Author: Radhika
 *
 * Created on 27 October, 2026, 1:57 PM
 */


#include <xc.h>
#include "newmain.h"
#include "adc.h"
#include "CLCD.h"
#include "cann.h"
#include "msg.h"
#include "Matrix keypad.h"
#include <stdint.h>



unsigned int  key, ind = 0, speed;
unsigned char speed_str[3];
unsigned short adc_value,rpm;
char rpm_data[5];

unsigned char gear[9][3] = { "ON", "GN", "G1", "G2", "G3", "G4", "G5", "GR", "C_"};


void init_config()
{
    init_clcd();
    init_matrix_keypad();
    init_adc();
    init_can();
    
}





//void main(void) 
//{
//    init_config();
//    
//    while(1)
//    {
//    adc_value = read_adc(CHANNEL4);
//        speed = ((unsigned long)adc_value * 99UL) / 1023UL;
//        
//        speed_str[0] =  (unsigned char)(speed / 10) + '0';
//        speed_str[1] =  (unsigned char)(speed % 10) + '0';
//        speed_str[2] = '\0';
//        
//        uint8_t data[2];
//
//       data[0] = (uint8_t)(speed >> 8);
//       data[1] = (uint8_t)(speed & 0xFF);
//
//can_transmit(SPEED_MSG_ID, data, 2);
//       // rpm = (read_adc(CHANNEL4) / 10.23) * 60;
//
//        //rpm_data[0] = ((rpm / 1000) % 10 + '0');
//        //rpm_data[1] = ((rpm / 100) % 10 + '0');
//        //rpm_data[2] = ((rpm / 10) % 10 + '0');
//        //rpm_data[3] = (rpm % 10 + '0');
//        //rpm_data[4] = '\0';
//
//        /* Display labels */
//        clcd_print((const unsigned char *)"GEAR  SPD ", LINE1(0));
//
//        /* Next: format and display time, event and speed */
//
////        clcd_print(gear[ind], LINE2(2));
////       clcd_print(speed_str, LINE2(6));
//        //clcd_print(rpm_data, LINE2(8));
//        
//       // check_matrix_keypad();
//        can_transmit(SPEED_MSG_ID, speed, 2);
//    __delay_ms(80);
//        
//        
//        key = read_switches(STATE_CHANGE);
//  
//        if(key == MK_SW1)
//        {
//            if(ind == 8)
//            {
//                ind = 1;
//            }
//            else if(ind < 7)
//            {
//            ind++;
//            }
//        }
//        if(key == MK_SW2)
//        {
//            
//            if(ind > 0)
//            {
//            ind--;
//            }
//            
//        }
//        if(key == MK_SW3)
//        {
//            ind = 8;
//        }
//        
//       can_transmit(GEAR_MSG_ID, gear[ind], 2);
//        __delay_ms(80);
//        
//    }
//    return;
//}