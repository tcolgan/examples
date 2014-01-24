/* Serial.c */

#include "Serial.h"
#include "addressmap.h"

static tUByte* SerialPortAddress[] =
{
  (tUByte *)ADDR_SER0 ,
  (tUByte *)ADDR_SER1 ,
} ;

#define  UART_CRYSTAL_FREQ  33000000L /* UART Crystal frequency */

enum
{
  RCV_FIFO ,
  XMT_FIFO ,
  NUM_FIFOS
} ;

typedef enum UART_INT_TYPE {
  UART_INT_TYPE_RCV ,
  UART_INT_TYPE_XMT 
} UART_INT_TYPE ;



#define FIFO_SIZE 1024 /* must be power of 2 */

typedef struct FIFO
{
  tUByte buff[ FIFO_SIZE ] ;
  int idxWr ;
  int idxRd ;
} FIFO ;

FIFO SerialFifos[ SERIAL_NUM ][ NUM_FIFOS ] ;

/* Prototypes */
tBoolean UartClearFifo( int channel , tUByte mask ) ;
int FifoPush( FIFO* fifo , tUByte* src , int size ) ;
int FifoPop( FIFO* fifo , tUByte* dst , int maxsize ) ;
tVoid UartEnableInterrupt( int channel , UART_INT_TYPE type , tBoolean state ) ;


inline int FifoNextIdx( int idx ) 
{
  return ( idx + 1 ) & ( FIFO_SIZE - 1 ) ;
}

int FifoPush( FIFO* fifo , tUByte* src , int size )
{
  /* returns number of bytes pushed */
  int srcidx = 0 ;
  
  while( ( FifoNextIdx( fifo->idxWr ) != fifo->idxRd ) && ( srcidx < size ) )
  {
    fifo->buff[ fifo->idxWr ] = src[ srcidx ] ;
    srcidx++ ;
    fifo->idxWr = FifoNextIdx( fifo->idxWr ) ;
  }
  return srcidx ;
}


int FifoPop( FIFO* fifo , tUByte* dst , int maxsize )
{
  /* returns number of bytes popped */
  int dstidx = 0 ;
  
  while( ( fifo->idxWr != fifo->idxRd ) && ( dstidx < maxsize ) )
  {
    dst[ dstidx ] = fifo->buff[ fifo->idxRd ] ;
    fifo->idxRd = FifoNextIdx( fifo->idxRd ) ;
    dstidx++ ;
  }
  return dstidx ;
}


inline tVoid UartWriteReg( int channel , int reg , tUByte val )
{
  *( SerialPortAddress[ channel ] + reg )  = val ;
}


inline tUByte UartReadReg( int channel , int reg )
{
  return *( SerialPortAddress[ channel ] + reg ) ;
}


tVoid UartEnableInterrupt( int channel , UART_INT_TYPE type , tBoolean state )
{
  tUByte mask[] =
  {
    UART_IER_MASK_RCV ,
    UART_IER_MASK_XMT
  } ;
  
  tUByte msk  ;
  tUByte ier  ;
  
  msk = mask[ type ] ;
  ier = UartReadReg( channel , UART_IER_OFFSET ) ;
  
  ier = (tUByte)( state ? ( ier | msk ) : ( ier & ~msk ) ) ;
  
  UartWriteReg( channel , UART_IER_OFFSET , ier ) ;
}

tBoolean UartClearFifo( int channel , tUByte mask )
{
  int      count ;
  tBoolean result = TRUE ;
  
  /* Clear the FIFO. */
  UartWriteReg( channel , UART_FCR_OFFSET, (tUByte)( UartReadReg( channel , UART_FCR_OFFSET ) | mask ) ) ;

  /* Wait for FIFO to clear within time limit */
  count = 100 ;
  while( ( UartReadReg( channel ,  UART_FCR_OFFSET) & mask ) && ( count > 0 ) )    
  {
      count--;   
  }

  if ( count == 0 )           /* Did Chip reset its FIFOs? */
  {
    result = FALSE ;
  }
  
  return result ;
}

int SerialRead( int channel , tUByte* buffer , int maxbytes ) 
{
  return FifoPop( &SerialFifos[ channel ][ RCV_FIFO ] , buffer , maxbytes ) ;
}

int SerialWrite( int channel , tUByte* buffer , int maxbytes )
{
  int byteswritten = FifoPush( &SerialFifos[ channel ][ XMT_FIFO ] , buffer , maxbytes ) ;
  
  UartEnableInterrupt( channel , UART_INT_TYPE_XMT , TRUE ) ;
  
  return byteswritten ;
}

tBoolean SerialInit( int channel , int baud )
{
  tBoolean result ;
  tUWord   baudval ;
  
  result = TRUE ;
  
  /* Set DLAB bit to enable the alternate registers on the chip. This allows us to write to the DLL and DLH */
  /* registers instead of the THR and IER registers which share the same memory address */
  UartWriteReg( channel , UART_LCR_OFFSET , UART_LCR_DL_ENABLE ) ;

  /* The DLL register holds the 8 LSBs while the DLH holds the 8 MSBs of the divisor number. */          
  /* NOTE: we are not using the divide by 4 feature! */
  baudval = ( tUWord )( UART_CRYSTAL_FREQ / 16 / baud ) ;
  UartWriteReg( channel , UART_DLL_OFFSET , (tUByte)( baudval & 0xFF ) ) ;
  UartWriteReg( channel , UART_DLH_OFFSET , (tUByte)( baudval >> 8   ) ) ;

  /* Set the transmission byte protocol to 8 bits, 1 stop bit, no parity */
  UartWriteReg( channel , UART_LCR_OFFSET , UART_LCR_8BITS_1STP_NOPAR ) ; 
  
  /* Enable the Rx and Tx FIFOs */
  UartWriteReg( channel , UART_FCR_OFFSET , UART_FCR_ENABLE_FIFOS ) ;     

  result =  
  UartClearFifo( channel , FIFO_RESET_MASK ) ;
  
  /* enable receive interrupt */
  
  UartWriteReg( channel , UART_MCR_OFFSET , (tUByte)( UartReadReg( channel , UART_MCR_OFFSET ) | UART_MCR_ENABLE_INTS ) ) ;
  UartEnableInterrupt( channel , UART_INT_TYPE_RCV , TRUE ) ;
  
  return result ;
}

tVoid SerialISR( tVoid )
{
  tUByte iir ;           
  int    channel ;
  tUByte ch ;

  /* Check IIR register to see whether there was an interrupt on this channel */
  for( channel = SERIAL_0 ; channel < SERIAL_NUM ; channel++ )
  {
    /* check if interrupt for this channel */
    
    iir = UartReadReg( channel , UART_IIR_OFFSET ) ;
    
    if( iir & UART_IIR_MASK_INT ) /* one => no interrupt */
    {
      continue ;
    }

    iir &= UART_IIR_MASK_SRC ; 
    
    /* determine interrupt type (xmt/rcv) */
    
    if( iir == UART_IIR_SRC_THR ) /* transmitter interrupt */
    {
      /* interrupt source = TRANSMITTER HOLDING REGISTER */
      if( FifoPop( &SerialFifos[ channel ][ XMT_FIFO ] , &ch , 1 ) )
      {
        UartWriteReg( channel , UART_THR_OFFSET , ch ) ;
      }
      else
      {
        UartEnableInterrupt( channel , UART_INT_TYPE_XMT , FALSE ) ;
      }
      
    }
    else if( ( iir == UART_IIR_SRC_RCVTIMEOUT ) || ( iir == UART_IIR_SRC_RHR ) )  /* receiver interrupt */
    {
      /* interrupt source = RECEIVER HOLDING REGISTER */
      while( UartReadReg( channel , UART_LSR_OFFSET ) & RHR_FULL )
      {
        ch = (tUByte)( UartReadReg( channel , UART_RHR_OFFSET ) ) ;
        FifoPush( &SerialFifos[ channel ][ RCV_FIFO ] , &ch , 1 ) ;
      }
    }
    else
    {
      /* shouldn't get here */
      static int count = 0 ;
      count++ ;
    }
  }
}

