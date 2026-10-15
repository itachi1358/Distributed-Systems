/*
 * add_client.c : Client side of the RPC program
 *
 * Steps:
 *   gcc add_client.c add_clnt.c add_xdr.c -o add_client -I/usr/include/tirpc -ltirpc
 *   ./add_client localhost 5 10
 */

#include <stdio.h>
#include <stdlib.h>
#include "add.h"

void
add_prog_1(char *host, int x, int y)
{
	CLIENT *clnt;
	int *result_1;
	numbers add_1_arg;

	clnt = clnt_create(host, ADD_PROG, ADD_VERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror(host);
		exit(1);
	}

	add_1_arg.a = x;
	add_1_arg.b = y;

	result_1 = add_1(&add_1_arg, clnt);
	if (result_1 == (int *) NULL) {
		clnt_perror(clnt, "call failed");
	} else {
		printf("Result: %d + %d = %d\n", x, y, *result_1);
	}

	clnt_destroy(clnt);
}

int
main(int argc, char *argv[])
{
	char *host;

	if (argc < 4) {
		printf("usage: %s server_host num1 num2\n", argv[0]);
		exit(1);
	}
	host = argv[1];
	add_prog_1(host, atoi(argv[2]), atoi(argv[3]));
	exit(0);
}
