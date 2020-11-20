#ifndef	_P_BASE_H
#define	_P_BASE_H

#define PBASE 0x3F000000

/*
    Video Core 是一个由Alphamosaic Ltd开发并且现在被Broadcom拥有的低功耗移动多媒体指令集架构.
    VC CPU Bus Addresses 表示的正是在Video Core下的寻址空间. ARM Physical Addresses 和 
    ARM Virtual Addresses 是通过 ARM MMU 来实现映射的

    Physical addresses range from 0x3F00_0000 to 0x3FFF_FFFF for peripherals
    
    Virtual addresses in kernel mode will range between 0xC0000000 and 0xEFFFFFFF. Virtual
    addresses in user mode (i.e. seen by processes running in ARM Linux) will range
    between 0x00000000 and 0xBFFFFFFF. 

    Peripherals (at physical address 0x3F00_0000 on) are mapped into the kernel virtual address
    space starting at address 0xF200_0000. Thus a peripheral advertised here at bus address
    0x7Ennnnnn is available in the ARM kenel at virtual address 0xF2nnnnnn

    由此可知, PBASE是物理地址中的外设起始地址.
*/

#endif  /*_P_BASE_H */
