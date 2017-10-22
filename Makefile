all:MI6 CE2 CE3 fork1 fork2 fork3 fork4 thr fork6 mem

BlindBingo2: BlindBingo2.c
	g++ -o BlindBingo2 BlindBingo2.c

mem: memoryLeak1.c
	g++ -o mem memoryLeak1.c

fork6: forkExample6.c
	cc -o fork6 forkExample6.c

MI6: MI6.c
	g++ MI6.c -o MI6

CE2: TableDrivenCE2.c
	g++ TableDrivenCE2.c -o CE2

CE3: TableDrivenCE3.c
	g++ TableDrivenCE3.c -o CE3

fork1: forkExample1.c
	g++ forkExample1.c -o fork1

fork2: forkExample2.c
	g++ forkExample2.c -o fork2

fork3: forkExample3.c
	g++ forkExample3.c -o fork3

fork4: forkExample4.c
	g++ forkExample4.c -o fork4

thr: thread1 thread2 thread3 thread4 thread5 thread6

CC=g++
LD=-lpthread

thread1:thread1.c
	g++ thread1.c -o thread1 -lpthread

thread2:thread2.c
	g++ thread2.c -o thread2 -lpthread

thread3:thread3.c
	g++ thread3.c -o thread3 -lpthread

thread5:thread5.c
	g++ thread5.c -o thread5 -lpthread

thread6:thread6.c
	g++ thread6.c -o thread6 -lpthread

thread4:thread4.c
	g++ thread4.c -o thread4 -lpthread
DCAS:DCAS.cpp
	g++ DCAS.cpp -o DCAS -lpthread
DCAS1:DCAS1.cpp
	g++ DCAS1.cpp -o DCAS1 -lpthread



