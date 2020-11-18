.globl put32
put32:
	str w1,[x0]
	// aarch有31个通用寄存器, 使用64位是就是xn, 使用低32位时就是wn, 所以w1就是x1的低32位
	// 将w1中的数据存储到x0指示的内存地址对应的内存中
	ret

.globl get32
get32:
	ldr w0,[x0]
	// ldr(Load with immediate offset)
	// 将[x0]中的数据加载到w0中
	ret

.globl delay
delay:
	subs x0, x0, #1
	bne delay
	ret
