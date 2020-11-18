.globl memzero
// .global告诉linker memzero这个符号在"mm.S"之外也是可见的(boot.S就调用了memzero)
memzero:
	str xzr, [x0], #8
	// str(Store with immediate offset) 将xzr寄存器中的数据写入到以x0中的数据为内存地址的内存空间中, 并将新地址(x0+8)写入x0
	// xzr(Zero Register, xzr/wzr表示64/32位), 这是ARMv8在硬件层面新引入的, 效果和Linux软件层面的"/dev/zero"类似, 
	// 作为源寄存器产生0，作为目标寄存器丢弃传入的数据
	subs x1, x1, #8
	// subs(sub加s后缀), 将x1减#8的结果赋值给x1, 并根据结果更新condition flags(可能是个标志寄存器)
	b.gt memzero
	// ARM指令集中应该不存在b.gt
	// 这里可能是想用bgt(Branch if Greater than), 例如 bgt s,t,label 表示如果s>t, 则branch到label所在的位置
	// 同时根据https://www.keil.com/support/man/docs/armclang_mig/armclang_mig_chr1398243831925.htm
	// bgt label 的格式也存在, 根据上一条指令修改的condition flag的值, 如果大于0就跳转到label
	ret
