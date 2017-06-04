Steps Followed After installing PintOS:
Part1:
	-created print_something.c and print_something.h in /pintos/src/threads.
	-added the files as thread source in Makefile located at /pintos/src/threads/build
	-included it in the function list in test.c located at /pintos/src/tests/threads
	-edited test.h to include my header file in it. test.h is located at /pintos/src/tests/threads
	-executed the program using command "pintos run print_something"

Part2:
	-updated print_something.c by adding 2 functions namely test_sort and sort_random_number. test_sort function creates a thread and calls sort_random_number. sort_random_number function generates random numbers through function random_bytes and sorts them.
	-added function name in print_something.h header file
	-made same changes in other files as in part 1
	-executed the program using command "pintos run sort"

Part3:
	- Pintos implements thread creation and thread completion, a simple scheduler to switch between threads, and synchronization primitives (semaphores, locks, condition variables, and optimization barriers).
	-a thread can be created using thread_create() function.
	-at any given time, exactly one thread runs and the rest become inactive.
	-The scheduler decides which thread to run next. 
	-The mechanics of a context switch are in threads/switch.S, which is x86 assembly code.  It saves the state of the currently running thread and restores the state of the next thread onto the CPU.
	-schedule() is responsible for switching threads.  It is internal to threads/thread.c
	-it  called only by the three public thread functions that need to switch threads:thread_block(),thread_exit(), and thread_yield().

