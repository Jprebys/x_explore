#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "X11/Xlib.h"


void error_and_exit(char *desc)
{
	perror(desc);
	exit(1);
}


int main(void)
{	
	Display *display = XOpenDisplay(NULL);
	if (display ==  NULL)
		error_and_exit("XOpenDisplay");

	printf("Hello World\n");

	XCloseDisplay(display);
	return 0;
}