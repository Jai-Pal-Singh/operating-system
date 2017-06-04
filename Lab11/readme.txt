Ques1:
	- Linux uses paging model that suits both 32-bit and 64-bit architectures. Only two paging levels are sufficient for 32-bit architectures, but 64-bit architectures require a higher number of paging levels. 
	- Up to version 2.6.10, the Linux paging model consisted of three paging levels. 
	- From version 2.6.11, a four-level paging model has been adopted. 
	- Three level paging is shown in fig. 3level_Paging.png. The three levels are- 
		a) Page Global Directory(PGD)
		b) Page Middle Directory(PMD)
		c) Page Table Entry(PTE)
	- Four level paging is shown in fig. 4level_Paging.png. The four levels are- 
		a)Page Global Directory
		b)Page Upper Directory
		c)Page Middle Directory
		d)Page Table
	- References:
		a) Understanding the Linux Kernel, 3rd Edition by Marco Cesati, Daniel P. Bovet
		b) https://lwn.net/Articles/106177/
		c) https://hungys.xyz/linux-kernel-memory-addressing/
		
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Ques2:
	- I wrote a simple program that runs infinitly to check the process memory layout. The code is-
		
		#include<stdio.h>

		int main(void){
			while(1);
			return 0;
			}
			
	- Then I compiled the program and ran it. When I ran $cat /proc/$pid/maps I got the following output:

---address------- perms-offset- -dev- -inode-                            ---------pathname-----------------	
00400000-00401000 r-xp 00000000 08:03 2640218                            /home/jaipal/Desktop/a.out			//code segment
00600000-00601000 r--p 00000000 08:03 2640218                            /home/jaipal/Desktop/a.out			//initialised data segment
00601000-00602000 rw-p 00001000 08:03 2640218                            /home/jaipal/Desktop/a.out			//uninitialised data segment (bss)
7fa6f12f9000-7fa6f14b8000 r-xp 00000000 08:03 532202                     /lib/x86_64-linux-gnu/libc-2.23.so //library segment
7fa6f14b8000-7fa6f16b8000 ---p 001bf000 08:03 532202                     /lib/x86_64-linux-gnu/libc-2.23.so	//library segment
7fa6f16b8000-7fa6f16bc000 r--p 001bf000 08:03 532202                     /lib/x86_64-linux-gnu/libc-2.23.so	//library segment
7fa6f16bc000-7fa6f16be000 rw-p 001c3000 08:03 532202                     /lib/x86_64-linux-gnu/libc-2.23.so	//library segment
7fa6f16be000-7fa6f16c2000 rw-p 00000000 00:00 0 															//library segment
7fa6f16c2000-7fa6f16e8000 r-xp 00000000 08:03 532203                     /lib/x86_64-linux-gnu/ld-2.23.so	//loader segment
7fa6f18c2000-7fa6f18c5000 rw-p 00000000 00:00 0 															//loader segment
7fa6f18e5000-7fa6f18e7000 rw-p 00000000 00:00 0 															//loader segment
7fa6f18e7000-7fa6f18e8000 r--p 00025000 08:03 532203                     /lib/x86_64-linux-gnu/ld-2.23.so	//loader segment
7fa6f18e8000-7fa6f18e9000 rw-p 00026000 08:03 532203                     /lib/x86_64-linux-gnu/ld-2.23.so	//loader segment
7fa6f18e9000-7fa6f18ea000 rw-p 00000000 00:00 0 															//loader segment
7ffe92f69000-7ffe92f8a000 rw-p 00000000 00:00 0                          [stack]							//stack
7ffe92fd6000-7ffe92fd8000 r--p 00000000 00:00 0                          [vvar]
7ffe92fd8000-7ffe92fda000 r-xp 00000000 00:00 0                          [vdso]								//virtual dynamic shared objec
ffffffffff600000-ffffffffff601000 r-xp 00000000 00:00 0                  [vsyscall]							//syscall space

	- The address field is the address space in the process that the mapping occupies.  
	- The perms field is a set of permissions:
                   r = read
                   w = write
                   x = execute
                   s = shared
                   p = private (copy on write)
    - The  offset field is the offset into the file/whatever; 
    - dev is the device (major:minor); 
    - inode is the inode on that device.  0 indicates that no inode is associated with the memory region, as would be the case with BSS (uninitialized data).
    -  The pathname field will usually be the file that is backing the mapping.
    - If  the  pathname  field is blank, this is an anonymous mapping as obtained via the mmap(2) function.  There is no easy way to coordinate this back to a process's source, short of running it through gdb(1), strace(1), or similar.
 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



