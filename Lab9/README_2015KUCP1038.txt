Question 1
	a) malloc(), calloc(), realloc(), free():
		- allocate and free dynamic memory
		
		- defined in <stdlib.h>
		- void *malloc(size_t size);
		- void free(void *ptr);
		- void *calloc(size_t nmemb, size_t size);
		- void *realloc(void *ptr, size_t size);
		- Allocates size bytes of uninitialized storage. 
		
		- The malloc() function allocates size bytes and returns a pointer to the allocated memory.  The memory is not initialized.  If size is  0,  then malloc()  returns either NULL, or a unique pointer value that can later be successfully passed to free().
		
		- The free() function frees the memory space pointed  to  by  ptr,  which must  have  been  returned by a previous call to malloc(), calloc(), or realloc().  Otherwise, or if free(ptr) has already been called  before, undefined behavior occurs.  If ptr is NULL, no operation is performed.

		- The  calloc()  function allocates memory for an array of nmemb elements of size bytes each and returns a pointer to the allocated memory.   The memory  is  set  to zero.  If nmemb or size is 0, then calloc() returns either NULL, or a unique pointer value that can later  be  successfully passed to free().
		
		- The  realloc() function changes the size of the memory block pointed to by ptr to size bytes.  The contents will be unchanged in the range from the start of the region up to the minimum of the old and new sizes.  If the new size is larger than the old size, the added memory will not  be initialized.   If  ptr  is  NULL,  then  the call is equivalent to malloc(size), for all values of size; if size is equal to zero, and ptr is not  NULL,  then  the  call  is equivalent to free(ptr).  Unless ptr is NULL, it must have been returned by an earlier call to  malloc(),  calloc()  or  realloc().  If the area pointed to was moved, a free(ptr) is done.

		
		- Implemention by C standard language API (glibc):
			a) ptmalloc2 is implemented in glibc. ptmalloc2 was forked from dlmalloc.
			b) system Calls: malloc internally invokes either brk or mmap syscall.
			c) due to ptmalloc2’s threading support, it became the default memory allocator for linux.
			d) in ptmalloc2, when two threads call malloc at the same time memory is allocated immediately since each thread maintains a separate heap segment and hence freelist data structures maintaining those heaps are also separate.
			e) This act of maintaining separate heap and freelist data structures for each thread is called per thread arena
			f) The malloc implementation in glibc either obtains memory from the brk()/sbrk() system call or anonymous memory via mmap().
			g) This gives glibc a big contiguous (regarding virtual memory addresses) chunk of memory, which the malloc implementation further slices and dices in smaller chunks and hands out to your application.
			h) The brk()/sbrk() calls in the kernel adjust some of the offsets in the struct mm_struct of the process, so the process data segment will be larger. At first, there will be no physical memory mapped to the additional virtual addresses which extending the data segment gave.
			i) When that unmapped memory is first touched (likely a read/write by the malloc implementation) a fault handler will kick in and trap down to the kernel, where the kernel will assign physical memory to the unmapped memory.
			
		- Implementation by Linux Kernel:
			When user space applications call malloc(), that call isn't implemented in the kernel. Instead, it's a library call (implemented glibc or similar).
		
		-Precautions:
			a) malloc returns a void pointer (void *), which indicates that it is a pointer to a region of unknown data type. The use of casting is required in C++ due to the strong type system, whereas this is not the case in C. 
			b) The memory allocated using malloc() function contains garbage values.Initialize malloc-ed memory using memset.
			c) We should not use more memory then what is allocated.
			d) Realloc will fail if sufficient memory is not available. So, sufficient memory should be available.
			e) We should not use a pointer after freeing the memory it points at
			f) The best practice for this is to set the pointer to NULL after freeing the memory, because you can easily test for NULL, and attempting to access memory via a NULL pointer will cause a bad but consistent behaviour, which is much easier to debug.
			
			
	b) alloca():
		- allocate memory that is automatically freed
		- defined in #include <alloca.h>
		- void *alloca(size_t size);
		- The  alloca()  function  allocates size bytes of space in the stack frame of the caller.  This temporary space is automatically freed when the function that called alloca() returns to its caller.
		- The alloca() function returns a pointer to the beginning of the allocated space.  If the allocation causes  stack  overflow,  program behavior is undefined.
		- The alloca() function is machine- and compiler-dependent.  For certain applications, its use can improve efficiency compared  to  the use  of  malloc()  plus  free().  In certain cases, it can also simplify memory deallocation in applications that use longjmp() or siglongjmp().  Otherwise, its use is discouraged.
		
		- Implementation:
			a) alloca() is directly implemented in assembly code. So, we cannot control stack layout directly from high level languages.
			b) Although alloca() is not part of SUSv3, it is provided on most UNIX implementations and is thus reasonably portable.
			c) alloca() is implemented by the compiler as inline code that directly adjusts the stack pointer.
			d) alloca() doesn't need to maintain a list of free blocks.
		
		- Visualize memory allocation and deallocation:
			The space allocated by alloca() is allocated within the stack frame. The space is automatically freed if the function return is jumped over by a call to longjmp(3) or siglongjmp().
		
		-Precautions:
			a) Do not attempt to free() space allocated by alloca()!
			b) If the allocation causes stack overflow, program behavior is undefined.
			c) On many systems alloca() cannot be used inside the list of arguments of a function call, because the stack space reserved by alloca() would appear on the stack in the middle of the space for the function arguments.
		
		
	c) longjmp():
		- nonlocal jump to a saved stack context
		- defined in <setjmp.h>
		- void longjmp(jmp_buf env, int val);
		-  longjmp()  and  setjmp() are useful for dealing with errors and interrupts encountered in a low-level subroutine of  a  program.   longjmp() restores  the  environment saved by the last call of setjmp() with the corresponding env argument.  After longjmp() is completed, program execution  continues  as  if  the corresponding call of setjmp() had just returned the value val.  longjmp() cannot cause 0 to be  returned.   If longjmp()  is  invoked  with a second argument of 0, 1 will be returned instead.
		- This function never return.
		
		- Implementation:
			a) POSIX does not specify whether longjmp() will restore the  signal  context. If we want to portably save and restore signal masks, we can use sigsetjmp() and siglongjmp().
			b) The values of automatic variables  are  unspecified  after  a  call  to longjmp() if they meet all the following criteria:
				> they are local to the function that made the corresponding setjmp() call;
				> their  values  are  changed  between  the  calls  to  setjmp() and longjmp();
				> they are not declared as volatile.
		
		- Precautions:
			a) Using setjmp/longjmp has an effect on the validity of local variables which is often not considered.
			b) longjmp() makes program hard to understand and maintain. If possible, an alternative should be used.

	d) brk():
		- change data segment size
		- defined in <unistd.h>
		- int brk(void *addr);
		- brk()  and  sbrk()  change  the location of the program break, which defines the end of the process's data segment (i.e., the program break is the first location after the end of the uninitialized data segment). Increasing the program break has the effect  of  allocating memory to the process; decreasing the break deallocates memory.
		- brk()  sets  the end of the data segment to the value specified by addr, when that value is reasonable, the system has enough memory, and the process does not exceed its maximum data size
		- On success, brk() returns zero.  On error, -1 is returned, and errno is set to ENOMEM.
		
		- C library/kernel differences :
			a) The return value described above for brk() is the behavior provided by the glibc wrapper function for the Linux  brk()  system  call.
			b) The actual Linux system call returns the new program break on success.  On failure, the system call returns the current  break.   
			c) The  glibc  wrapper  function  does some work (i.e., checks whether the new break is less than addr) to provide the 0 and -1 return values described above.
	
		-Precautions:
			a) Avoid using brk(). We can use malloc().
			
	e) mmap(), munmap():
		- map or unmap files or devices into memory
		- defined in <sys/mman.h>
		- void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
		- int munmap(void *addr, size_t length);
		
		- mmap() creates a new mapping in the virtual address space of the calling process.  The starting address for the new mapping is specified in addr. The length argument specifies the length of the mapping.
		- If addr is NULL, then the kernel chooses the address at which to create the mapping; this is the most portable method of  creating  a new mapping.  If addr is not NULL, then the kernel takes it as a hint about where to place the mapping; on Linux, the mapping will be created at a nearby page boundary.  The address of the new mapping is returned as the result of the call.
		- The contents of a file mapping (as opposed to an anonymous mapping; see MAP_ANONYMOUS below),  are  initialized  using  length  bytes starting at offset offset in the file (or other object) referred to by the file descriptor fd.  offset must be a multiple of the page size as returned by sysconf(_SC_PAGE_SIZE).
		- The prot argument describes the desired memory protection of the mapping (and must not conflict with the open mode of the file). It is either PROT_NONE or the bitwise OR of one or more of the following flags:
			> PROT_EXEC  Pages may be executed.
			> PROT_READ  Pages may be read.
			> PROT_WRITE Pages may be written.
			> PROT_NONE  Pages may not be accessed.
		- The  flags  argument  determines  whether  updates to the mapping are visible to other processes mapping the same region, and whether updates are carried through to the underlying file.  This behavior is determined by including exactly one of the following values  in flags:
			> MAP_SHARED Share  this mapping.
			> MAP_PRIVATE  Create a private copy-on-write mapping.
		- Memory mapped by mmap() is preserved across fork(2), with the same attributes.
		
		- The  munmap() system call deletes the mappings for the specified address range, and causes further references to addresses within the range to generate invalid memory references.  The region is also automatically unmapped when the process is terminated.  On the other hand, closing the file descriptor does not unmap the region.
		- The  address  addr  must be a multiple of the page size (but length need not be).  All pages containing a part of the indicated range are unmapped, and subsequent references to these pages will generate SIGSEGV.  It is not an error if the  indicated  range  does  not contain any mapped pages.
		
		- On  success,  mmap()  returns  a  pointer to the mapped area.  On error, the value MAP_FAILED (that is, (void *) -1) is returned, and errno is set to indicate the cause of the error.
		- On success, munmap() returns 0.  On failure, it returns -1, and errno is set to indicate the cause of the error (probably to EINVAL).
		
		- The portable way to create a mapping is to specify addr as 0 (NULL), and omit MAP_FIXED from flags.  In this case, the system chooses the  address  for  the  mapping;  the  address  is chosen so as not to conflict with any existing mapping, and will not be 0.  If the MAP_FIXED flag is specified, and addr is 0 (NULL), then the mapped address will be 0 (NULL).
		
		- C library/kernel differences:
			a) This  page describes the interface provided by the glibc mmap() wrapper function.  Originally, this function invoked a system call of the same name.  Since kernel 2.4, that system call has been superseded by mmap2(), and nowadays the glibc  mmap()  wrapper  function invokes mmap2() with a suitably adjusted value for offset.
			
		-Precautions:
			a) In kernels before 2.6.7, the MAP_POPULATE flag has effect only if prot is specified as PROT_NONE.
			b) SUSv3 specifies that mmap() should fail if length is 0.  However, in kernels before 2.6.12, mmap() succeeded in this case: no mapping was created and the call returned addr.  Since kernel 2.6.12, mmap() fails with the error EINVAL for this case.

-----------------------------------------------------------------------------------------------------------------------------------------
Question 2
	- C program/application to illustrate memory leak :
		#include<stdio.h>
		#include<stdlib.h>
		
		int main(){
			char *ch;
			ch = (char*) malloc(10485760);
			//some code
			return 0;
			}//ch not valid outside, no way to access malloc-ed memory
			
	- What is memory leak? 
		A memory leak occurs when a piece (or pieces) of memory that was previously allocated by a programmer is not properly deallocated by the programmer. Even though that memory is no longer in use by the program, it is still “reserved”, and that piece of memory can not be used by the program until it is properly deallocated by the programmer. That’s why it’s called a memory leak
		
	- How does this program leak memory? 
		In the above program, Char-ptr ch is a local variable that goes out of scope at the end of the main function, leaking the dynamically allocated 10485760 bytes. Image "mem_without_free.png" shows this. There is large difference between the memory available before and after running the program. Image "mem_with_free.png" shows the memory status after using free() function. We observe that this time there is less difference between the memory available before and after running the program.
		
	- How can this be fixed? 
		This can be fixed by using the folloowing code before the return statement:
		free(ch);
		
	- What are the best practices that should be followed while using memory management related functions? 
		a) Have a corresponding free to every malloc.
		b) Make sure you are not accessing null pointer.
		c) Always use memset along with malloc, or always use calloc.
		d) Always properly handle return values of functions returning references of dynamically allocated memory.
		
-----------------------------------------------------------------------------------------------------------------------------------------
Question 3
	- C program to find out address of stack, heap and code segment:
		#include<stdio.h>
		#include<stdlib.h>

		int a;
		void func(int n);

		int main(){
			int i,*ptr;
			ptr = (int *)malloc(sizeof(int));
			printf("address of stack(local variable)  i = %p\n",(void *)&i);
			printf("address of data segment(global variable)  a = %p\n",(void *)&a);
			printf("address of dynamic (Heap) = %p\n", (void *)&ptr);
			func(10);
			return 0;
			}

		void func(int n){
			printf("address of function (stack) = %p\n", (void *)&n);
			}
	- When i ran the above code, after duplicating at 4 different locations in 4 different terminals at a time, i observed that the every time the program gets different memory location allocated. Image "ques3.png" shows this observation.
	
----------------------------------------------------------------------------------------------------------------------------------------
Question 4  
	- C program to display a string “Hello OS” using printf:
		
		#include<stdio.h>

		int main(){
			int x=0;
			printf("Hello OS\n");
			return 0;
			}

	- Result after disassmbling main is shown in image "ques4.png".
	- Yes, relocation register and limit register kind of check exists. It can be visualised as %rbp stores the base address and count (address<count> as shown in image) is used to keep check as limit register.
	- address binding takes place at run-time.
