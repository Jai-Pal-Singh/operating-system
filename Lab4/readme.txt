Steps Followed:
My OS is Linux Ubuntu 16.04 and the kernel version I have implemented is, 4.9.7. I followed the following steps for adding a system call-
	1.I  created a folder named hello and add two files namely hello.c and Makefile in the folder linux-4.9.7.
	2.Added it in Makefile in the folder linux-4.9.7to  tell the compiler that the source files of my new system call (sys_hello()) is in present in the hello directory. Edited command on line 913 to "core-y+= kernel/ certs/ mm/ fs/ ipc/ security/ crypto/ block/ hello/".
	3.Added the new system call (sys_hello() ) into the system call table (linux-4.9.7/arch/x86/entry/syscalls/syscall_32.tbl file)
	4.Added the new system call(sys_hello() )  in the system call header file(linux-4.9.7/include/linux/syscalls.h).
	5.Compiled this kernel on my system using "make menuconfig" and "make" commands.
	6.After compilation, install the new kernel using "make modules_install install" command.
	7.After this, I rebooted my system. Checked kernel version using "uname -r" command.
	8.To test the system call I created a program namely user.c. After executing it, ran "dmesg" to check the message of the kernel.
	
Problems Faced:
I faced some problems in addding a system call like-
	1.Stable Kernel version is updated regularly. New kernel version has a little different folder system. This make difficult in finding required files.
	2.Compilation of kernel takes too much time. A little error in coding costs too much time.
	3.Kernel grows too much after compilation which cost in system running out of memory. To overcome this problem, I had to reinstall Ubuntu in my system with increased space.
	4.The newly installed kernel is not compatible with the system and has resulted in some problems like sometimes system gets hanged, execution speed has decreased etc.     
