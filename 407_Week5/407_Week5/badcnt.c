/* Compile with:
 * gcc -lpthread badcnt.c -o badcnt 
 */

#include <stdlib.h> 
#include <stdio.h> 
#include <pthread.h>

unsigned int cnt = 0; /* shared */ 
unsigned int NUM_ITERS;

/* thread routine */ 
 void *count(void *arg) {
 	int i;
 	for (i=0; i<NUM_ITERS; i++)
 		cnt++; 
 	return NULL;
 }

 int main(int argc, char* argv[]) 
 {
 	pthread_t tid1, tid2;

 	if ( (argc >= 2) && isdigit(*argv[1]) )
 		NUM_ITERS = atoi(argv[1]); 
 	else
 	{
 		const int LINE_SIZE = 16; 
 		char line[LINE_SIZE];

 		do {
 			printf("How many iterations? "); 
 			fgets(line,LINE_SIZE,stdin);
 		}
 		while ( !isdigit(line[0]) ); 
 		
 		NUM_ITERS = atoi(line); 
 	}

 	pthread_create(&tid1, NULL, count, NULL); 
 	pthread_create(&tid2, NULL, count, NULL); 
 	
 	pthread_join(tid1, NULL);
 	pthread_join(tid2, NULL);

 	printf("Should be %d is %d\n",NUM_ITERS*2,cnt);
 	
 	return(0);
 }

 /*

$ gdb badcnt

GNU gdb (GDB) Red Hat Enterprise Linux (7.0.1-32.el5_6.2)
....
(gdb) disass count
Dump of assembler code for function count:
0x08048504 <count+0>:	push   %ebp
0x08048505 <count+1>:	mov    %esp,%ebp
0x08048507 <count+3>:	sub    $0x10,%esp
0x0804850a <count+6>:	movl   $0x0,-0x4(%ebp)
0x08048511 <count+13>:	jmp    0x8048524 <count+32>
0x08048513 <count+15>:	mov    0x8049940,%eax  // CPU stop here
0x08048518 <count+20>:	add    $0x1,%eax	   // problem
0x0804851b <count+23>:	mov    %eax,0x8049940  // problem
0x08048520 <count+28>:	addl   $0x1,-0x4(%ebp)
0x08048524 <count+32>:	mov    -0x4(%ebp),%edx
0x08048527 <count+35>:	mov    0x8049944,%eax
0x0804852c <count+40>:	cmp    %eax,%edx
0x0804852e <count+42>:	jb     0x8048513 <count+15>
0x08048530 <count+44>:	mov    $0x0,%eax
0x08048535 <count+49>:	leave  
0x08048536 <count+50>:	ret    
End of assembler dump.
(gdb) 

 */
