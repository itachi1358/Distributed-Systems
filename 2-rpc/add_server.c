/*
 * add_server.c : Server side of the RPC program
 *
 * Steps:
 *   rpcgen -C add.x
 *   gcc add_server.c add_svc.c add_xdr.c -o add_server -I/usr/include/tirpc -ltirpc
 *   sudo systemctl start rpcbind
 *   sudo ./add_server
 */

#include <stdio.h>
#include "add.h"

int *
add_1_svc(numbers *argp, struct svc_req *rqstp)
{
	static int result;

	printf("Got request: adding %d and %d\n", argp->a, argp->b);
	result = argp->a + argp->b;

	return &result;
}
