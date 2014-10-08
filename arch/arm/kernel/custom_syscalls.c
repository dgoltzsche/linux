#include <asm/io.h>
#include <linux/syscalls.h>

asmlinkage int sys_trustl_init(void* addr_a, void* addr_b, void* addr_c)
{
	//int tid_low = tid;
	//int tid_high = (tid >>32);
	//seems not to working without printing??
	printk("trustl init syscall: 0x%X 0x%X 0x%X\n", addr_a, addr_b, addr_c);
	asm volatile ("mov r0, #3 \n"
				  "mov r1, %[a] \n"
				  "mov r2, %[b] \n"
				  "mov r3, %[c] \n"
				  "isb \n"
				  "dsb \n"
				  ".arch_extension	sec\n"
				  "smc #0 \n"
				  :
				  : [a] "r" (addr_a),
				    [b] "r" (addr_b),
				    [c] "r" (addr_c) );
	return 0;
}
