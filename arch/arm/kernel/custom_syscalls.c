#include <asm/io.h>
#include <linux/syscalls.h>

asmlinkage long sys_seca_init(void* addr_a, void* addr_b, void* addr_c, unsigned int* stampmem)
{
	int syscall_nr = 3;
	if(addr_a == NULL) return -1;
	if(addr_b == NULL) return -1;
	if(addr_c == NULL) return -1;

	if ( stampmem != NULL )
		syscall_nr = 4;

	printk("0x%X 0x%X 0x%X 0x%X\n",addr_a,addr_b,addr_c,stampmem);
	if ( stampmem != NULL )
		asm volatile ("MRC p15, 0, %0, c9, c13, 0\t\n": "=r"(*(stampmem+1))); //t1

	asm volatile ("mov r0, %[n] \n"
				  "mov r1, %[a] \n"
				  "mov r2, %[b] \n"
				  "mov r3, %[c] \n"
				  "mov r4, %[d] \n"
				  "isb \n"
				  "dsb \n"
				  ".arch_extension	sec\n"
				  "smc #0 \n"
				  :
				  : [n] "r" (syscall_nr),
					[a] "r" (addr_a),
				    [b] "r" (addr_b),
				    [c] "r" (addr_c),
				    [d] "r" (stampmem));

	if ( stampmem != NULL )
		asm volatile ("MRC p15, 0, %0, c9, c13, 0\t\n": "=r"(*(stampmem+4)));//t4
	return 0;
}

asmlinkage long sys_init_hw_cnt(void)
{
	printk("enabling hw counters for usr access\n");
	asm ("MCR p15, 0, %0, C9, C14, 0\n\t" :: "r"(1));
	return 0;
}
