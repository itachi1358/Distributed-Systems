/*
 * client.c : CORBA client in C using ORBit2
 *
 * Steps (Ubuntu 18.04):
 *   sudo apt install liborbit2-dev
 *   orbit-idl-2 Calc.idl
 *   gcc client.c Calc-common.c Calc-stubs.c -o client $(pkg-config --cflags --libs ORBit-2.0)
 *   ./client --ORBIIOPIPv4=1      (start the Python server first)
 */

#include <stdio.h>
#include <stdlib.h>
#include <orbit/orbit.h>
#include "Calc.h"

/* Check for a CORBA exception after each call */
static void
abort_if_exception(CORBA_Environment *ev, const char *msg)
{
	if (ev->_major != CORBA_NO_EXCEPTION) {
		fprintf(stderr, "Error: %s (%s)\n", msg, CORBA_exception_id(ev));
		exit(1);
	}
}

int
main(int argc, char *argv[])
{
	CORBA_Environment ev;
	CORBA_ORB orb;
	Demo_Calc calc;
	CORBA_long result;
	char ior[4096];
	FILE *fp;

	CORBA_exception_init(&ev);

	/* Step 1: Initialise the ORB */
	orb = CORBA_ORB_init(&argc, argv, "orbit-local-orb", &ev);
	abort_if_exception(&ev, "ORB init failed");

	/* Step 2: Read the IOR written by the server */
	fp = fopen("calc.ior", "r");
	if (fp == NULL || fscanf(fp, "%4095s", ior) != 1) {
		fprintf(stderr, "Could not read calc.ior\n");
		exit(1);
	}
	fclose(fp);

	/* Step 3: Convert the IOR string into an object reference */
	calc = (Demo_Calc) CORBA_ORB_string_to_object(orb, ior, &ev);
	abort_if_exception(&ev, "string_to_object failed");

	/* Step 4: Call the remote method */
	result = Demo_Calc_add(calc, 5, 10, &ev);
	abort_if_exception(&ev, "add failed");

	printf("Result: 5 + 10 = %d\n", (int) result);

	/* Step 5: Clean up */
	CORBA_Object_release(calc, &ev);
	CORBA_ORB_destroy(orb, &ev);
	return 0;
}
