# operatig-system-with-all-the-essential-functions
this project mainly contains all the essential functions that an operating system should perform like io mgmt, memory mgmt, process mgmt etc. different methods are used for each and explained here and in the file:

========================================================================================================================

INTRODUCTION:
Linux is an operating system or a kernel. It is distributed under an open source license. Its functionality list is quite like UNIX. The main advantage of Linux was that programmers were able to use the Linux Kernel to design their own custom operating systems. With time, a new range of user-friendly OS's stormed the computer world. Now, Linux is one of the most popular and widely used Kernel, and it is the backbone of popular operating systems like Debian, Knoppix, Ubuntu, and Fedora. Nevertheless, the list does not end here as there are thousands of OS's based on Linux which offer a variety of functions to the users. It offers a free operating system. You do not have to shell hundreds of dollars to get the OS like Windows.
•	Being open-source, anyone with programming knowledge can modify it.
•	The Linux operating systems now offer millions of programs/applications to choose from, most of them free!
•	Once you have Linux installed you no longer need an antivirus! Linux is a highly secure system. More so, there is a global development community constantly looking at ways to enhance its security. With each upgrade, the OS becomes more secure and robust
•	Linux is the OS of choice for Server environments due to its stability and reliability (Mega-companies like Amazon, Facebook, and Google use Linux for their Servers). A Linux based server could run non-stop without a reboot for years on end.

========================================================================================================================
 
Problem Statement:
To develop a working application simulating the working of a mini version of an OS.
The simulated mini OS must include the following features of an OS:
•	Process Management 
•	Memory Management
•	File Management 
•	I/O Management

========================================================================================================================

Analysis and Design:
..........................................................
Process Management:
Pre-emptive SJF: Shortest Job First (SJF) is an algorithm used in LINUX based OS in which the process having the smallest execution time is chosen for the next execution. This scheduling method can be pre-emptive or non-pre-emptive. It significantly reduces the average waiting time for other processes awaiting execution. In Pre-emptive SJF Scheduling, jobs are put into the ready queue as they come. A process with shortest burst time begins execution. If a process with even a shorter burst time arrives, the current process is removed or pre-empted from execution, and the shorter job is allocated CPU cycle. Algorithm is as follows:-
1- Traverse until all process gets completely executed.
   a) Find a process with minimum remaining time at
     every single time lap.
   b) Reduce its time by 1.
   c) Check if its remaining time becomes 0 
   d) Increment the counter of process completion.
   e) Completion time of current process = current_time +1;
   e) Calculate waiting time for each completed process.
   	wt[i]= Completion time - arrival_time-burst_time
   f) Increment time lap by one.
2- Find turnaround time (waiting_time+burst_time).
..........................................................
File Management:
Ext2 file system: Linux ext2 – Linux ext2 is a file management system in which files are represented by inodes, directories are simply files containing a list of entries and devices can be accessed by requesting I/O on special files. Each file is represented by a structure, called an inode. Each inode contains the description of the file: file type, access rights, owners, timestamps, size, pointers to data blocks. a user requests an I/O operation on the file, the kernel code converts the current offset to a block number, uses this number as an index in the block addresses table and reads or writes the physical block. Directories are structured in a hierarchical tree. Each directory can contain files and subdirectories. A directory is a file containing a list of entries. Each entry contains an inode number and a file name.
Diagrammatic representation of file system:       
****picture not available**** 
The algorithm is as follows:
1.	First, we define a structure of nodes known as inodes which stores metadata like when file was created, file size. It contains all data except file name and contents of the file.
2.	If we want to create a file, we will allocate a structure of file type which contains name of file, its size and extension of the file.
3.	If we want to create a directory/folder we will create an alternate structure which consist of pointers to the files which are mapped to the nodes.
4.	The inputs taken for creation of file will be will be name of file, size of file and extension of file. Input for creation of folder will be folder name.
..........................................................
MEMORY MANAGEMNT: 
Next - Fit Algorithm - Next fit is a modified version of ‘first fit’. It begins as the first fit to find a free partition but when called next time it starts searching from where it left off, not from the beginning. This policy makes use of a roving pointer. The pointer moves along the memory chain to search for a next fit. This helps in, to avoid the usage of memory always from the head (beginning) of the free block chain. Algorithm is as follows: 

1.	Input the number of memory blocks and their sizes and initializes all the blocks as free.
2.	Input the number of processes and their sizes.
3.	Start by picking each process and check if it can be assigned to the current block, if yes, allocate it the required memory and check for next process but from the block where we left not from starting.
4.	If the current block size is smaller then keep checking the further blocks.
..........................................................
I/O MANAGEMNT:
Circular SCAN: C-SCAN scheduling algorithm is a modified version of SCAN disk scheduling algorithm that deals with the inefficiency of SCAN algorithm by servicing the requests more uniformly. Like SCAN (Elevator Algorithm) C-SCAN moves the head from one end servicing all the requests to the other end. However, as soon as the head reaches the other end, it immediately returns to the beginning of the disk without servicing any requests on the return trip (see chart below) and starts servicing again once reaches the beginning. Algorithm is as follows:
1.	Let Request array represents an array storing indexes of tracks that have been requested in ascending order of their time of arrival. ‘head’ is the position of disk head.
2.	The head services only in the right direction from 0 to size of the disk.
3.	While moving in the left direction do not service any of the tracks.
4.	When we reach at the beginning(left end) reverse the direction.
5.	While moving in right direction it services all tracks one by one.
6.	While moving in right direction calculate the absolute distance of the track from the head.
7.	Increment the total seek count with this distance.
8.	Currently serviced track position now becomes the new head position.
9.	Go to step 6 until we reach at right end of the disk.
10.	If we reach at the right end of the disk reverse the direction and go to step 3 until all tracks in request array have not been serviced.
