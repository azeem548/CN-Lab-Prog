//program name:add.x

struct intpair
{
	int a;
	int b;
};
program intpair{
version intpair_ver{
	int add(intpair)=1;
	}=1;
	}=0x20001080;
// compiling add.x using rpcgen
$ rpcgen –a add.x
$ ls 
// seeing the list of files which gets created(7 files)
$ add.h add.x aad_client.c add_clnt.c add_server.c add_svc.c  add_xdr.c Makefile.add
// open add_server.c to do changes.
//add_server.c
/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "addition.h"

int *
add_1_svc(intpair *argp, struct svc_req *rqstp)
{
	static int  result;

	/*
	 * insert server code here
	 */
        result=argp->a+argp->b;
	return &result;
}

// open add_client.c to make changes
//add_client.c
/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "addition.h"
#include <stdio.h>
#include <stdlib.h>


void
sum_prog_1(char *host, int a, int b)
{
	CLIENT *clnt;
	int  *result_1;
	intpair  add_1_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, add_prog, add_ver, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */
	add_1_arg.a=a;
	add_1_arg.b=b;
	result_1 = add_1(&add_1_arg, clnt);
	if (result_1 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	else{
	printf("\nSum of %d\t%d\t is %d\n",add_1_arg.a,add_1_arg.b,*result_1);
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;

	if (argc < 4) {
		printf ("usage: %s server_host num1 num2\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	add_prog_1 (host, atoi(argv[2]), atoi(argv[3]));
exit (0);
}

 
OUTPUT: 
//compiling server and server stub program
$ cc add_server.c add_svc.c add_xdr.c –o sadd
$ ./sadd 			(In Server Terminal)

 $ cc add _client.c add _clnt.c add_xdr.c 
$ ./a.out 10.2.0.3  50  70 	(In client Terminal)
