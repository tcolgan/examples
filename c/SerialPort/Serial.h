/* Serial.h */

#ifndef SERIAL_H
#define SERIAL_H

#include "IssDefs.h"


#define SERIAL_0    0
#define SERIAL_1    1
#define SERIAL_NUM  2

#define BAUD_9600   9600
#define BAUD_19200  19200
#define BAUD_38400  38400
#define BAUD_115200 115200

#define     UART_RHR_OFFSET           0x00    /* UART receive holding register */
#define     UART_THR_OFFSET           0x00    /* UART transmit holding register */
#define     UART_DLL_OFFSET           0x00    /* UART divisor LSB */
#define     UART_DLH_OFFSET           0x08    /* UART divisor MSB */
#define     UART_IER_OFFSET           0x08    /* UART interrupt enable register */
#define     UART_FCR_OFFSET           0x10    /* FIFO Control Register */
#define     UART_IIR_OFFSET           0x10    /* UART interrupt identification register */
#define     UART_LCR_OFFSET           0x18    /* UART line control register */
#define     UART_MCR_OFFSET           0x20    /* Modem Control Register */
#define     UART_LSR_OFFSET           0x28    /* UART line status register */
#define     UART_MSR_OFFSET           0x30    /* UART line status register */
#define     UART_FRR_OFFSET           0x38    /* FIFO Ready Register */

#define     UART_LCR_DL_ENABLE          (tUByte)0x80    /* Data Latch enable value */
#define     UART_LCR_8BITS_1STP_NOPAR   (tUByte)0x03    /* 8 bits, 1 stop bit, no parity */
#define     UART_FCR_ENABLE_FIFOS       (tUByte)0x01    /* enable UART rx and tx FIFOs */
#define     UART_MCR_ENABLE_INTS        (tUByte)0x08    

/* ier masks */
#define     UART_IER_MASK_RCV           (tUByte)0x01   /* enable UART Receive  interrupt */
#define     UART_IER_MASK_XMT           (tUByte)0x02   /* enable UART Transmit interrupt */

/* iir masks */
#define     UART_IIR_MASK_INT           (tUByte)0x01  /* Interrupt pending mask */
#define     UART_IIR_MASK_SRC           (tUByte)0x0e  /* Interrupt source mask  */

#define UART_IIR_SRC_THR         0x02
#define UART_IIR_SRC_RHR         0x04
#define UART_IIR_SRC_RCVTIMEOUT  0x0c

/* LSR Masks */
#define     RHR_FULL            ((tUByte)0x01)        /* Receive Hold Register full */
#define     THR_EMPTY           ((tUByte)0x20)        /* Transmit Holding Register Empty */
#define     LSR_RECEIVE_ERROR   ((tUByte)0x1E)        /* Line Status error bits: Overrun, Framing, Parity and Break */
#define     LSR_FIFO_ERROR      ((tUByte)0x80)        /* Receive FIFO error */
#define     LSR_OVERRUN_ERROR   ((tUByte)0x02)        /* Transmit Overrun error */

#define     RX_FIFO_RESET_MASK  ((tUByte)0x02)        /* Resets only the Rx FIFO */
#define     TX_FIFO_RESET_MASK  ((tUByte)0x04)        /* Resets only the Tx FIFO */
#define     FIFO_RESET_MASK     ((tUByte)0x06)        /* Resets both Rx and Tx FIFOs */

extern int SerialRead( int channel , tUByte* buffer , int maxbytes ) ;
extern int SerialWrite( int channel , tUByte* buffer , int maxbytes ) ;
extern tBoolean SerialInit( int channel , int baud ) ;

extern tVoid SerialISR( tVoid ) ;

extern tVoid SerialTest( tVoid ) ;

#endif /* SERIAL_H */
