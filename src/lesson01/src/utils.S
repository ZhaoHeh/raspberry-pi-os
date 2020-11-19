.globl put32
put32:
	str w1,[x0]
	// aarch有31个通用寄存器, 使用64位是就是xn, 使用低32位时就是wn, 所以w1就是x1的低32位
	// 将w1中的数据存储到x0指示的内存地址对应的内存中
	// * * * * * * * *
	// * ARM遵循ATPCS规则, ARM64汇编语言函数前8个参数使用x0-x7寄存器(或w0-w7寄存器)传递,
	// * 多于8个的参数均通过堆栈传递, 并且返回值通过x0寄存器(或w0寄存器)返回.
	// * * * * * * * *
	// 将入参中的第一个参数的值写到[x0]指示的地址中
	ret

.globl get32
get32:
	ldr w0,[x0]
	// ldr(Load with immediate offset)
	// 将[x0]中的数据加载到w0中
	// 本函数的功能就是读取[x0]地址中的值并返回给调用者
	ret

.globl delay
delay:
	subs x0, x0, #1
	bne delay
	// bne(Branch if Not Equal)数据跳转指令, 标志寄存器中Z标志位不等于零时, 跳转到BNE后标签处
	ret
