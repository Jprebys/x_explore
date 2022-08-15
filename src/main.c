#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

#include "X11/Xlib.h"


void error_and_exit(char *desc)
{
	perror(desc);
	exit(1);
}


int main(void)
{	
	Display *display;
	Window window;
	XEvent event;
	int screen;

	display = XOpenDisplay(NULL);
	if (display ==  NULL)
		error_and_exit("XOpenDisplay");

	screen = DefaultScreen(display);

	window = XCreateSimpleWindow(display, RootWindow(display, screen), 
		                         0, 0, 600, 400, 10, 
		                         WhitePixel(display, screen), 
		                         BlackPixel(display, screen));

    XSelectInput(display, window, ExposureMask | KeyPressMask);
	XMapWindow(display, window);

	while (true) {
		XNextEvent(display, &event);
		if (event.type == Expose) {
			printf("Hello World\n");
		} else if (event.type == KeyPress) {
			break;
		}
	}

	printf("Hello World\n");

	XCloseDisplay(display);
	return 0;
}
