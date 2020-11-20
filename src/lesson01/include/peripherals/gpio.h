#ifndef	_P_GPIO_H
#define	_P_GPIO_H

#include "peripherals/base.h"

// Address      | Field Name  |  Description             |  Size  |  Read/Write
#define GPFSEL1         (PBASE+0x00200004)
// ----------------------------------------------------------------------------
// 0x 7E20 0004 | GPFSEL1     |  GPIO Function Select 1  |  32    |  R/W
#define GPSET0          (PBASE+0x0020001C)
// ----------------------------------------------------------------------------
// 0x 7E20 001C | GPSET0      |  GPIO Pin Output Set 0   |  32    |  W
#define GPCLR0          (PBASE+0x00200028)
// ----------------------------------------------------------------------------
// 0x 7E20 0028 | GPCLR0      |  GPIO Pin Output Clear 0 |  32    |  W
#define GPPUD           (PBASE+0x00200094)
// ----------------------------------------------------------------------------
// 0x 7E20 0094 | GPPUD       |  GPIO Pin Pull-up/down Enable  |  32    |  R/W
#define GPPUDCLK0       (PBASE+0x00200098)
// ----------------------------------------------------------------------------
// 0x 7E20 0098 | GPPUDCLK0   |  GPIO Pin Pull-up/down Enable Clock 0  |  32    |  R/W

/*
    GPIO中peripheral registers的一些解释:
    GPFSELn (n = {0,1,2,3,4,5}), 第n个GPIO Function Select寄存器, 负责确定GPIO某个pin的功能,
    具体来讲: 
        GPFSEL0: pin0~9
        GPFSEL1: pin10~19
        GPFSEL2: pin20~29
        GPFSEL3: pin30~39
        GPFSEL4: pin40~49
        GPFSEL5: pin50~53
    每个pin的功能选择用3bit表示:
        000 = GPIO Pin is an input
        001 = GPIO Pin is an output
        100 = GPIO Pin takes alternate function 0
        101 = GPIO Pin takes alternate function 1
        110 = GPIO Pin takes alternate function 2
        111 = GPIO Pin takes alternate function 3
        011 = GPIO Pin takes alternate function 4
        010 = GPIO Pin takes alternate function 5
    具体pin x对应的GPFSELn地哪3bit这里不赘述.

    GPPUD和GPPUDCLK0, GPPUDCLK1的功能参考BCM2837-ARM-Peripherals.-.Revised.-.V2-1.pdf Page100-101
*/

#endif  /*_P_GPIO_H */
