#ifndef	_P_MINI_UART_H
#define	_P_MINI_UART_H

#include "peripherals/base.h"

// Address Register  |  Name3           |  Description                 |  Size  |
#define AUX_ENABLES     (PBASE+0x00215004)
// ------------------------------------------------------------------------------
// 0x7E21_5004       |  AUX_ENABLES     |  Auxiliary enables           |  3     |
#define AUX_MU_IO_REG   (PBASE+0x00215040)
// ------------------------------------------------------------------------------
// 0x7E21_5040       |  AUX_MU_IO_REG   |  Mini Uart I/O Data          |  8     | 
#define AUX_MU_IER_REG  (PBASE+0x00215044)
// ------------------------------------------------------------------------------
// 0x7E21_5044       |  AUX_MU_IER_REG  |  Mini Uart Interrupt Enable  |  3     |
#define AUX_MU_IIR_REG  (PBASE+0x00215048)
#define AUX_MU_LCR_REG  (PBASE+0x0021504C)
// ------------------------------------------------------------------------------
// 0x7E21_504C       |  AUX_MU_LCR_REG  |  Mini Uart Line Control      |  8     |
#define AUX_MU_MCR_REG  (PBASE+0x00215050)
// ------------------------------------------------------------------------------
// 0x7E21_5050       |  AUX_MU_MCR_REG  |  Mini Uart Modem Control     |  8     |
#define AUX_MU_LSR_REG  (PBASE+0x00215054)
// ------------------------------------------------------------------------------
// 0x7E21_5054       |  AUX_MU_LSR_REG  |  Mini Uart Line Status       |  8     |
#define AUX_MU_MSR_REG  (PBASE+0x00215058)
#define AUX_MU_SCRATCH  (PBASE+0x0021505C)
#define AUX_MU_CNTL_REG (PBASE+0x00215060)
// ------------------------------------------------------------------------------
// 0x7E21_5060       |  AUX_MU_CNTL_REG |  Mini Uart Extra Control     |  8     |
#define AUX_MU_STAT_REG (PBASE+0x00215064)
#define AUX_MU_BAUD_REG (PBASE+0x00215068)
// ------------------------------------------------------------------------------
// 0x7E21_5068       |  AUX_MU_BAUD_REG |  Mini Uart Baudrate          |  16    |

#endif  /*_P_MINI_UART_H */
