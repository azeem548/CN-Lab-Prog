//program name: echo.x
program ECHOPRG{
version ECHOER{
string echo(string)=1;
}=1;
}=0x20000001;


// compiling echo.x using rpcgen
$ rpcgen –a echo.x
$ ls 
// seeing the list of files which gets created(6 files)
echo.h echo.x echo_client.c echo_clnt.c echo_server.c echo_svc.c Makefile.echo
// open echo_server.c to do changes.
//echo_server.c
/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "echo.h"

char **
echo_1_svc(char **argp, struct svc_req *rqstp)
{
	static char * result;

	/*
	 * insert server code here
	 */
        result=*argp;
	return &result;
}
// open echo_client.c to make changes
//echo_client.c
/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "echo.h"


void
echoprg_1(char *host,char *str)//argument for ECHOPRG_1
{
	CLIENT *clnt;
	char * *result_1;
	char * echo_1_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, ECHOPRG, ECHOER, "udp");//used for creating client.can use udp or tcp
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */
        echo_1_arg=str;
	result_1 = echo_1(&echo_1_arg, clnt);//for calling client stub
	if (result_1 == (char **) NULL) {
		clnt_perror (clnt, "call failed");
       // printf("%s",*result_1);
	}
else
printf("%s",*(result_1));
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}
int
main (int argc, char *argv[])
{
	char *host;

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	echoprg_1 (host,argv[2]);
exit (0);
}
 
OUTPUT: 
//compiling server and server stub program
$ cc echo_server.c echo_svc.c –o recho
$ ./recho			(In Server Terminal)

 
// compiling client and client stub program
$ cc echo_client.c echo_clnt.c

$ ./a.out 10.2.0.3  str		(In Client Terminal)
