/* Compile with:
 * gcc -lpthread goodcnt.c -o goodcnt 
 */

#include <stdlib.h> 
#include <stdio.h> 
#include <pthread.h>
#include <semaphore.h>

unsigned int cnt = 0; /* shared */ 
unsigned int NUM_ITERS;
sem_t sem;

/* thread routine */ 
 void *count(void *arg) {
 	int i;
 	for (i=0; i<NUM_ITERS; i++)
 	{
 		sem_wait(&sem);
 		cnt++; 
 		sem_post(&sem);
 	}
 	return NULL;
 }

 int main(int argc, char* argv[]) 
 {
 	pthread_t tid1, tid2;
 	if(sem_init(&sem, 0, 1) < 0) /* initialize sem to 1 */
 	{
 		fputs("sem_init error\n", stderr);
 		exit(1);
 	}

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

$ gdb goodcnt
GNU gdb (GDB) Red Hat Enterprise Linux (7.0.1-32.el5_6.2)
....
(gdb) disass count
Dump of assembler code for function count:
0x08048624 <count+0>:	push   %ebp
0x08048625 <count+1>:	mov    %esp,%ebp
0x08048627 <count+3>:	sub    $0x18,%esp
0x0804862a <count+6>:	movl   $0x0,-0x4(%ebp)
0x08048631 <count+13>:	jmp    0x804865c <count+56>
0x08048633 <count+15>:	movl   $0x8049aec,(%esp)
0x0804863a <count+22>:	call   0x80484ac <sem_wait@plt> // critical section starts here
0x0804863f <count+27>:	mov    0x8049ae8,%eax
0x08048644 <count+32>:	add    $0x1,%eax
0x08048647 <count+35>:	mov    %eax,0x8049ae8
0x0804864c <count+40>:	movl   $0x8049aec,(%esp)
0x08048653 <count+47>:	call   0x804851c <sem_post@plt> // critcal section ends here
0x08048658 <count+52>:	addl   $0x1,-0x4(%ebp)
0x0804865c <count+56>:	mov    -0x4(%ebp),%edx
0x0804865f <count+59>:	mov    0x8049afc,%eax
0x08048664 <count+64>:	cmp    %eax,%edx
0x08048666 <count+66>:	jb     0x8048633 <count+15>
0x08048668 <count+68>:	mov    $0x0,%eax
0x0804866d <count+73>:	leave  
0x0804866e <count+74>:	ret    
End of assembler dump.
(gdb) 


 */
