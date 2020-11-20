#include "utils.h"
#include "peripherals/mini_uart.h"
#include "peripherals/gpio.h"

void uart_send ( char c )
{
	while(1) {
		if(get32(AUX_MU_LSR_REG)&0x20) 
			break;
	}
	put32(AUX_MU_IO_REG,c);
}

char uart_recv ( void )
{
	while(1) {
		if(get32(AUX_MU_LSR_REG)&0x01) 
			break;
	}
	return(get32(AUX_MU_IO_REG)&0xFF);
}

/*
    以上两个操作(即send和recv)仅涉及两个寄存器AUX_MU_LSR_REG和AUX_MU_IO_REG, 放在这里解释一下:
	The AUX_MU_LSR_REG register:
		Shows the data status. 该寄存器第0bit为1时, 表示receive FIFO保存了至少一个符号, 所以
		get32(AUX_MU_LSR_REG)&0x01 == 1说明接收到数据了.; 该寄存第5bit为1时, 表示transmit FIFO
		可以接受至少1byte的数据, 所以get32(AUX_MU_LSR_REG)&0x20 == 1说明可以发送了.
	The AUX_MU_IO_REG register:
		is primary used to write data to and read data from the UART FIFOs.
		由此可见, 本进程能直接读写的寄存器AUX_MU_IO_REG并不是UART接受和发送数据的寄存器, 本进程通过
		访问AUX_MU_IO_REG间接和"UART FIFOs"通信. 而我推测, Raspberry Pi的硬件走线就决定了GPIO的
		pin14 和 pin15 可以与 UART FIFOs 相连, 相连的设置就在 GPFSEL1 里.
*/

void uart_send_string(char* str)
{
	for (int i = 0; str[i] != '\0'; i ++) {
		uart_send((char)str[i]);
	}
}

void uart_init ( void )
{
	unsigned int selector;

	selector = get32(GPFSEL1);
	// GPFSEL1定义在gpio.h中(PBASE+0x00200004), 实际值为  0x3F000000 + 0x00200004 = 0x3F200004
	// get32函数定义在utils.S中, 功能为获取地址GPFSEL1中的值并赋值给selector
	selector &= ~(7<<12);                   // clean gpio14
	// 位移位运算符是将数据看成二进制数, 对其进行向左或向右移动若干位的运算. 位移位运算符分为左移和右移两种, 均为双目运算符.
	// 第一运算对象是移位对象, 第二个运算对象是所移的二进制位数
	// ~ 按位求反运算, 即1变0, 0变1
	selector |= 2<<12;                      // set alt5 for gpio14
	selector &= ~(7<<15);                   // clean gpio15
	selector |= 2<<15;                      // set alt5 for gpio15
	put32(GPFSEL1,selector);
	// 将selector的值赋值给GPFSEL1地址处的外设的寄存器

	put32(GPPUD,0);
	delay(150);
	put32(GPPUDCLK0,(1<<14)|(1<<15));
	delay(150);
	put32(GPPUDCLK0,0);

    /*
		It is also recommended that the correct GPIO function mode is selected before enabling the mini Uart.
			-- from BCM2837-ARM-Peripherals.-.Revised.-.V2-1.pdf
		
		这句话提示我们, GPIO 之所以能和 UART 有联系, 很可能仅是树莓派主板的设计.
	*/

	put32(AUX_ENABLES,1);                   //Enable mini uart (this also enables access to it registers)
	put32(AUX_MU_CNTL_REG,0);               //Disable auto flow control and disable receiver and transmitter (for now)
	put32(AUX_MU_IER_REG,0);                //Disable receive and transmit interrupts
	put32(AUX_MU_LCR_REG,3);                //Enable 8 bit mode
	put32(AUX_MU_MCR_REG,0);                //Set RTS line to be always high
	put32(AUX_MU_BAUD_REG,270);             //Set baud rate to 115200

	put32(AUX_MU_CNTL_REG,3);               //Finally, enable transmitter and receiver
}
