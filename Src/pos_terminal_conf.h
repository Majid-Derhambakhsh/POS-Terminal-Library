/*
------------------------------------------------------------------------------
~ File   : pos_terminal_conf.h
~ Author : Majid Derhambakhsh
~ Version: V1.0.0
~ Created: 01/10/2024 03:00:00 PM
~ Brief  :
~ Support: 
           E-Mail : Majid.Derhambakhsh@Outlook.com (subject : Embedded Library Support)
		   
           Github : https://github.com/Majid-Derhambakhsh
------------------------------------------------------------------------------
~ Description:    

~ Attention  :    

~ Changes    :
------------------------------------------------------------------------------
*/

#ifndef __POS_TERMINAL_CONF_H_
#define __POS_TERMINAL_CONF_H_

/* ~~~~~~~~~~~~~~~~~~~~ Note ~~~~~~~~~~~~~~~~~~~ */
// Default POS UART Baud Rate : 19200

/* ~~~~~~~~~~~~~~ Required Headers ~~~~~~~~~~~~~ */
/* Driver-library for AVR */

/* Driver-library for STM32 */
//#include "main.h"
//#include "usart.h"

/* ~~~~~~~~~~~ User Defined Functions ~~~~~~~~~~ */
/* If you are not using STM32, uncomment the following defines and specify your own timer and serial functions */
//#define POS_GetTick()                                GetTick()
//#define POS_UART_Transmit(uData, Size, Timeout)      UART_Transmit((uData), (Size), (Timeout))

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#endif /* __POS_TERMINAL_CONF_H_ */
