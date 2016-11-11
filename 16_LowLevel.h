/*
16.1 Explain the following terms: virtual memory, page fault, thrashing.
*/
/*
Virtual memory is a computer system technique which gives an application program the impression
that it has contiguous working memory (an address space), while in fact it may be
physically fragmented and may even over"ow on to disk storage. Systems that use this technique
make programming of large applications easier and use real physical memory (e.g.
RAM) more e$ciently than those without virtual memory.
http://en.wikipedia.org/wiki/Virtual_memory
Page Fault: A page is a !xed-length block of memory that is used as a unit of transfer between
physical memory and external storage like a disk, and a page fault is an interrupt (or
exception) to the software raised by the hardware, when a program accesses a page that is
mapped in address space, but not loaded in physical memory.
http://en.wikipedia.org/wiki/Page_fault
Thrash is the term used to describe a degenerate situation on a computer where increasing
resources are used to do a decreasing amount of work. In this situation the system is
said to be thrashing. Usually it refers to two or more processes accessing a shared resource
repeatedly such that serious system performance degradation occurs because the system is
spending a disproportionate amount of time just accessing the shared resource. Resource
access time may generally be considered as wasted, since it does not contribute to the advancement
of any process. In modern computers, thrashing may occur in the paging system
(if there is not ‘su$cient’ physical memory or the disk access time is overly long), or in the
communications system (especially in con"icts over internal bus access), etc.
http://en.wikipedia.org/wiki/Thrash_(computer_science)
*/



/*
16.2 What is a Branch Target buffer? Explain how it can be used in reducing bubble cycles
in cases of branch misprediction.
*/

/*
Branch misprediction occurs when the CPU mispredicts the next instruction to be executed.
The CPU uses pipelining which allows several instructions to be processed simultaneously.
But during a conditional jump, the next instruction to be executed depends on the result of
the condition. Branch Prediction tries to guess the next instruction. However, if the guess is
wrong, we are penalized because the instruction which was executed must be discarded.
Branch Target Bu#er (BTB) reduces the penalty by predicting the path of the branch, computing
the target of the branch and caching the information used by the branch. There will be
no stalls if the branch entry found on BTB and the prediction is correct, otherwise the penalty
will be at least two cycles.
*/

/*
16.3
Describe direct memory access (DMA). Can a user level bu#er / pointer be used by
kernel or drivers?
*/

/*
Direct Memory is a feature which provides direct access (read/write) to system memory without
interaction from the CPU. The “DMA Controller” manages this by requesting the System
bus access (DMA request) from CPU. CPU completes its current task and grants access by asserting
DMA acknowledgement signal. Once it gets the access, it reads/writes the data and
returns back the system bus to the CPU by asserting the bus release signal. This transfer is
faster than the usual transfer by CPU. Between this time CPU is involved with processing task
which doesn’t require memory access.
By using DMA, drivers can access the memory allocated to the user level buffer / pointer.
*/



/*
16.4  Write a step by step execution of things that happen after a user presses a key on the
keyboard. Use as much detail as possible.
*/

/*
1. The keyboard sends a scan code of the key to the keyboard controller (Scan code for
key pressed and key released is di#erent).
2. The keyboard controller interprets the scan code and stores it in a bu#er.
3. The keyboard controller sends a hardware interrupt to the processor. This is done by
putting signal on “interrupt request line”: IRQ 1.
4. The interrupt controller maps IRQ 1 into INT 9.
5. An interrupt is a signal which tells the processor to stop what it was doing currently
and do some special task.
6. The processor invokes the “Interrupt handler”. CPU fetches the address of “Interrupt
Service Routine” (ISR) from “Interrupt Vector Table” maintained by the OS (Processor
use the IRQ number for this).
7. The ISR reads the scan code from port 60h and decides whether to process it or pass
the control to program for taking action.

*/


/*
16.5 Write a program to find whether a machine is big endian or little endian.
*/
#define BIG_ENDIAN    0
#define LITTLE_ENDIAN 1
int TestMachineEndian(void);



/*
16.6 Discuss how would you make sure that a process doesn’t access an unauthorized part
of the stack.
*/

/*
As with any ambiguously worded interview question, it may help to probe the interviewer to
understand what speci!cally you’re intended to solve. Are you trying to prevent code that
has over"owed a bu#er from compromising the execution by overwriting stack values? Are
you trying to maintain some form of thread-speci!c isolation between threads? Is the code
of interest native code like C++ or running under a virtual machine like Java?
Remember that, in a multi-threaded environment, there can be multiple stacks in a process.
NATIVE CODE
One threat to the stack is malicious program input, which can over"ow a bu#er and overwrite
stack pointers, thus circumventing the intended execution of the program.
If the interviewer is looking for a simple method to reduce the risk of bu#er over"ows in
native code, modern compilers provide this sort of stack protection through a command
line option. With Microsoft’s CL, you just pass /GS to the compiler. With GCC, you can use
-fstack-protector-all.
For more complex schemes, you could set individual permissions on the range of memory
pages representing the stack section you care about. In the Win32 API, you’d use the VirtualProtect
API to mark the page PAGE_READONLY or PAGE_NOACCESS. This will cause the
code accessing the region to go through an exception on access to the speci!c section of
the stack.
Alternately, you could use the HW Debug Registers (DRs) to set a read or write breakpoint
on the speci!c memory addresses of interest. A separate process could be used to debug
the process of interest, catch the HW exception that would be generated if this section of the
stack were accessed.
However, it’s very important to note that under normal circumstances, threads and processes
are not means of access control. Nothing can prevent native code from writing anywhere
within the address space of its process, including to the stack. Speci!cally, there is nothing
to prevent malicious code in the process from calling VirtualProtect and marking the stack
sections of interest PAGE_EXECUTE_READWRITE. Equally so, nothing prevents code from
zeroing out the HW debug registers, eliminating your breakpoints. In summary, nothing can
fully prevent native code from accessing memory addresses, including the stack, within its
own process space.
MANAGED CODE
A !nal option is to consider requiring this code that should be “sandboxed” to run in a managed
language like Java or C# / .NET. By default, the virtual machines running managed code
in these languages make it impossible to gain complete access to the stack from within the
process.
One can use further security features of the runtimes to prevent the code from spawning additional
processes or running “unsafe” code to inspect the stack. With .NET, for example, you
can use Code Access Security (CAS) or appdomain permissions to control such execution.
*/


/*
16.7 What are the best practices to prevent reverse engineering of DLLs?
*/

/*
Best practices include the following:
» Use obfuscators.
» Do not store any data (string, etc) in open form. Always compress or encode it.
» Use a static link so there is no DLL to attack.
» Strip all symbols.
» Use a .DEF !le and an import library to have anonymous exports known only by their
export ids.
» Keep the DLL in a resource and expose it in the !le system (under a suitably obscure
name, perhaps even generated at run time) only when running.
» Hide all real functions behind a factory method that exchanges a secret (better, proof of
knowledge of a secret) for a table of function pointers to the real methods.
» Use anti-debugging techniques borrowed from the malware world to prevent reverse
engineering. (Note that this will likely get you false positives from AV tools.)
» Use protectors.
*/



/*
16.8 A device boots with an empty FIFO queue. In the !rst 400 ns period after startup,
and in each subsequent 400 ns period, a maximum of 80 words will be written to the
queue. Each write takes 4 ns. A worker thread requires 3 ns to read a word, and 2 ns to
process it before reading the next word. What is the shortest depth of the FIFO such
that no data is lost?
*/

/*
While a perfectly optimal solution is complex, an interviewer is most interested in how you
approach the problem.
THEORY
First, note that writes do not have to be evenly distributed within a period. Thus a likely worst
case is 80 words are written at the end of the !rst period, followed by 80 more at the start of
the next.
Note that the maximum write rate for a full period is exactly matched by a full period of processing
(400 ns / ((3 ns + 2 ns)/process) = 80 processed words/period).
As the 2nd period in our example is fully saturated, adding writes from a 3rd period would
not add additional stress, and this example is a true worst case for the conditions.
A SAFE QUEUE DEPTH
For an estimate of maximum queue size, notice that these 160 writes take 640 ns (160 writes
* 4 ns / write = 640 ns), during which time only 128 words have been read (640 ns / ((3 ns + 2
ns) / word) = 128 words). However, the !rst read cannot start until the !rst write has !nished,
which !lls an extra slot in the queue.
Also, depending on the interactions between read and write timing, a second additional slot
may be necessary to ensure a write does not trash the contents of a concurrently occurring
read. Thus, a safe estimate is that the queue must be at least 34 words deep (160 - 128 + 1 +
1 = 34) to accommodate the unread words.
...
*/

/*
16.9 Write an aligned malloc & free function that takes number of bytes and aligned byte
(which is always power of 2)
EXAMPLE
align_malloc (1000,128) will return a memory address that is a multiple of 128 and
that points to memory of size 1000 bytes.
aligned_free() will free memory allocated by align_malloc.
_______________________________________________________________
*/

