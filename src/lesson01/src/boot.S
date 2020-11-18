/*
  .S文件是汇编语言的源码文件扩展名, "gcc -c foo.S"命令在运行时会使用C语言的预处理器,
  也就是说, .S文件中可以使用"#include<>, #if, #define"这些预处理语法
  具体语法参考: https://jsandler18.github.io/explanations/boot_S.html
*/
#include "mm.h"

.section ".text.boot"
// 告诉linker, 此段代码在.text.boot段

.globl _start
// 告诉linker, _start函数应该在boot.S文件之外也可以被看到

_start:
	mrs	x0, mpidr_el1		
	// mrs(Move to Rigister from State register)用于将程序状态寄存器的内容传递到通用寄存器
	// mpidr_el1(Multiprocessor Affinity Register, EL1), 该寄存器保存了processor id
	and	x0, x0,#0xFF		// Check processor id
	// 逻辑与指令, 将通用寄存器x0和立即数#0xFF作与, 然后赋值给通用寄存器x0
	cbz	x0, master		// Hang for all non-primary CPU
	// cbz(Compare and Branch on Zero)比较, 如果x0为0则转移至master
	b	proc_hang
	// b(Branch)直接转移至proc_hang, 同时我们可以看到proc_hang的内容就是b proc_hang,
	// 也就是说程序一旦跳转到proc_hang就会陷入死循环

	// 总结: _start的作用就是判断当前CPU是否为主核, 是则进入master, 否则跳入到无意义的死循环中

proc_hang: 
	b 	proc_hang

master:
	adr	x0, bss_begin
	// 计算当前指令(PC)和bss_begin之间的距离, 然后将值赋给x0
	adr	x1, bss_end
	// 计算当前指令(PC)和bss_end之间的距离, 然后将值赋给x1
	sub	x1, x1, x0
	// sub(Subtract without carry) 将x1-x0赋值给x1
	bl 	memzero
	// bl(Branch with Link)此指令跳转到memzero同时将下一个指令的地址复制到LR(R14, the link register)

	mov	sp, #LOW_MEMORY 
	// mov(Move)将#LOW_MEMORY的值copy到sp寄存器中
	// sp(Stack Pointer)指示栈顶的位置
	// LOW_MEMORY作为立即数定义在"mm.h"中
	bl	kernel_main
	// kernel_main函数定义在kernel.c, 只是不知道为什么这里可以访问到kernel_main这个符号???
	b 	proc_hang		// should never come here
