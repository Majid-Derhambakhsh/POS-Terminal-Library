/*
------------------------------------------------------------------------------
~ File   : pos_terminal.h
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

#ifndef __POS_TERMINAL_H_
#define __POS_TERMINAL_H_

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Include ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "pos_terminal_conf.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Defines ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ------------------------------ POS ------------------------------ */
/* .................. TLV - Tag ................... */
#define POS_TLV_TAG_START                          0x72

#define POS_TLV_TAG_FEE                            0x8E
#define POS_TLV_TAG_TRACKING_NUMBER                0x8C
#define POS_TLV_TAG_REFERENCE_NUMBER               0x8B
#define POS_TLV_TAG_CARD_NUMBER                    0x8A
#define POS_TLV_TAG_TERMINAL_ID                    0x89
#define POS_TLV_TAG_DATE_TIME                      0x87

/* ................. TLV - Length ................. */
#define POS_TLV_LEN_CARD_NUMBER                    16
#define POS_TLV_LEN_TRACKING_NUMBER                12
#define POS_TLV_LEN_REFERENCE_NUMBER               12
#define POS_TLV_LEN_MERCHANT_ID                    6
#define POS_TLV_LEN_TERMINAL_ID                    8

/* ................. TLV - Value .................. */
#define POS_TLV_VAL_TRANSACTION_OK                 0x31
#define POS_TLV_VAL_TRANSACTION_CANCEL             0x03
#define POS_TLV_VAL_TRANSACTION_WRONG_PASSWORD     0x37
#define POS_TLV_VAL_TRANSACTION_NETWORK_ERROR      0x05
#define POS_TLV_VAL_TRANSACTION_INSUFFICIENT_FUNDS 0x33
#define POS_TLV_VAL_TRANSACTION_TIMEOUT            0x01

/* .................... Timing .................... */
#define POS_UART_TX_TIMEOUT                        1000
#define POS_UART_RX_TIMEOUT                        100

/* .................... Common .................... */
#define __POS_ASCII_TO_NUM(ch)                     ((ch) - 48)

/* .................... Macro ..................... */
/* ----------------------- Define by compiler ---------------------- */
#ifdef __CODEVISIONAVR__  /* Check compiler */
	
	#ifndef POS_GetTick
		#error GetTick function not found
	#endif
	
	#ifndef POS_UART_Transmit
		#error UART_Transmit function not found
	#endif

/* ------------------------------------------------------------------ */
#elif defined(__GNUC__) && !defined(USE_HAL_DRIVER)  /* Check compiler */
	
	#ifndef POS_GetTick
		#error GetTick function not found
	#endif
	
	#ifndef POS_UART_Transmit
		#error UART_Transmit function not found
	#endif
	
/* ------------------------------------------------------------------ */
#elif defined(USE_HAL_DRIVER)  /* Check driver */
	
	#define POS_GetTick()                           HAL_GetTick()
	#define POS_UART_Transmit(UARTx, uData, Size)   HAL_UART_Transmit((UARTx), (uData), (Size), POS_UART_TX_TIMEOUT)
	
#endif /* __CODEVISIONAVR__ */

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Types ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* -------------------------- Transaction -------------------------- */
typedef enum 
{
	
	TRANSACTION_SUCCESS             = 0x31,
	TRANSACTION_CANCEL              = 0x03,
	TRANSACTION_WRONG_PASSWORD      = 0x37,
	TRANSACTION_POS_TIMEOUT         = 0x01,
	TRANSACTION_NETWORK_ERROR       = 0x05,
	TRANSACTION_INSUFFICIENT_FUNDS  = 0x33,
	TRANSACTION_TIMEOUT             = 0x08,
	TRANSACTION_WRONG_RESULT        = 0xFF,
	TRANSACTION_PACKET_ERROR        = 0xFE,
	
}POS_TransactionResultTypeDef;

typedef enum 
{
	
	POS_SEND_TRANSACTION_ENDED   = 0,
	POS_SEND_TRANSACTION_STARTED = 1,
	
}POS_TransactionStatusTypeDef;

typedef struct 
{

	/* ...... Transaction Date ..... */
	uint16_t Year;
	uint8_t  Month;
	uint8_t  Day;
	
	/* ...... Transaction Time ..... */
	uint8_t  Hour;
	uint8_t  Minute;
	uint8_t  Second;
	
	/* ............................. */
	uint32_t Fee;
	
	char CardNumber[POS_TLV_LEN_CARD_NUMBER + 1];
	char ReferenceNumber[POS_TLV_LEN_REFERENCE_NUMBER + 1];
	char TrackingNumber[POS_TLV_LEN_TRACKING_NUMBER + 1];
	char MerchantID[POS_TLV_LEN_MERCHANT_ID + 1];
	char TerminalID[POS_TLV_LEN_TERMINAL_ID + 1];
	
}POS_TransactionInfoTypeDef;

/* --------------------------- Callback ---------------------------- */
/* ---------------------------- Common ----------------------------- */
#ifdef USE_HAL_DRIVER

typedef enum 
{
	
	POS_ERROR = HAL_ERROR,
	POS_OK    = HAL_OK,
	
}POS_StatusTypeDef;

#elif

typedef enum
{
	
	POS_ERROR = 0,
	POS_OK    = 1,
	
}POS_StatusTypeDef;

#endif // USE_HAL_DRIVER

typedef struct
{
	
	#ifdef USE_HAL_DRIVER
	
	UART_HandleTypeDef *UARTx;
	
	#endif
	
	/* .......... Status ........... */
	POS_TransactionStatusTypeDef TransactionStatus;
	
	/* ..... POS Serial Buffer ..... */
	uint8_t RxBuffer[300];
	volatile uint16_t RxCounter;
	uint16_t PreRxCounter;
	
	/* .......... Timing ........... */
	uint32_t RxUpdateTime;
	uint32_t RespTimeout;
	
}POS_TypeDef;

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Enum ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Struct ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Prototype ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ..................... POS - Transaction ..................... */
/*
 * Function: POS_SendTransaction
 * -----------------------------
 * The POS_SendTransaction function transmit a transaction to a POS terminal.
 *
 * Param  : 
 *         POS: A pointer to the POS structure containing relevant information about the terminal.
 *         TotalFee: A string representing the total transaction fee.
 *         Timeout: The timeout value in milliseconds for waiting for a response.
 *         
 * Returns: 
 *         POS_OK / POS_ERROR
 *         
 * Example:
 *         uint8_t data;
 *         char TotalFee[] = "10000";
 *         
 *         POS_TypeDef MainPOS;
 *         
 *         void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
 *         {
 *               POS_UART_ISRHandle(&MainPOS, data);
 *               HAL_UART_Receive_IT(&huart2, &data, 1); 
 *         }
 *
 *         int main(void)
 *         {
 *               MainPOS.UARTx = &huart2;
 *               
 *               HAL_UART_Receive_IT(&huart2, &data, 1);
 *               
 *               POS_SendTransaction(&MainPOS, TotalFee, 30000);
 *               
 *               while(1)
 *               {
 *                      POS_TimingHandle(&MainPOS);
 *               }
 *         }
 *
 */
POS_StatusTypeDef POS_SendTransaction(POS_TypeDef *POS, char *TotalFee, uint32_t Timeout);

/* ..................... POS - ISR Handler ..................... */
/*
 * Function: POS_UART_ISRHandler
 * -----------------------------
 * UART Rx IRQ handling
 *
 * Param  : 
 *         POS: Pointer to POS Device Type
 *         uData: Received byte from UART
 *         
 * Returns: 
 *         -
 *         
 * Example: 
 *         uint8_t data;
 *         POS_TypeDef MainPOS;
 *
 *         void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
 *         {
 *               POS_UART_ISRHandle(&MainPOS, data);
 *               HAL_UART_Receive_IT(&huart2, &data, 1);
 *         }
 *         
 */
void POS_UART_ISRHandler(POS_TypeDef *POS, uint8_t uData);

/*
 * Function: POS_TimingHandler
 * ---------------------------
 * The POS_TimingHandler function manages the timeout and response handling for a transaction initiated with the POS_SendTransaction function. It checks for response data within a specified timeout, processes the received data, and triggers a callback function with the transaction result.
 *
 * Param  : 
 *         POS: Pointer to POS Device Type
 *         
 * Returns: 
 *         -
 *         
 * Example: 
 *         uint8_t data;
 *         char TotalFee[] = "10000";
 *
 *         POS_TypeDef MainPOS;
 *
 *         void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
 *         {
 *               POS_UART_ISRHandle(&MainPOS, data);
 *               HAL_UART_Receive_IT(&huart2, &data, 1);
 *         }
 *
 *         int main(void)
 *         {
 *               MainPOS.UARTx = &huart2;
 *
 *               HAL_UART_Receive_IT(&huart2, &data, 1);
 *
 *               POS_SendTransaction(&MainPOS, TotalFee, 30000);
 *
 *               while(1)
 *               {
 *                      POS_TimingHandle(&MainPOS);
 *               }
 *         }
 *         
 */
void POS_TimingHandler(POS_TypeDef *POS);

/* ...................... POS - Callback ....................... */
void POS_TransactionCallback(POS_TransactionResultTypeDef TransactionResult, POS_TransactionInfoTypeDef TransactionInfo);

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ End of the program ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#endif
