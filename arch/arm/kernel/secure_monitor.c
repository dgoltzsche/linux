#include <asm/io.h>
#include <linux/syscalls.h>
 
asmlinkage int sys_secure_monitor(void* addr_a, void* addr_b)
{
	asm volatile ("mov r0, #2 \n"
				  "mov r1, %[a] \n"
				  "mov r2, %[b] \n"
				  "isb \n"
				  "dsb \n"
				  ".arch_extension	sec\n"
				  "smc #0 \n"
				  :
				  : [a] "r" (addr_a), [b] "r" (addr_b) );

	return 0;
}

