#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>

#include "X11/Xlib.h"

#define LINE_WIDTH 5
#define SCREEN_X 900
#define SCREEN_Y 700


void error_and_exit(char *desc)
{
	perror(desc);
	exit(1);
}


int main(void)
{	
	Display *display;
	Window window;
	GC gcontext;
	int screen;

	display = XOpenDisplay(NULL);
	if (display ==  NULL)
		error_and_exit("XOpenDisplay");

	screen = DefaultScreen(display);

	window = XCreateSimpleWindow(display, RootWindow(display, screen), 
		                         0, 0, SCREEN_X, SCREEN_Y, 10, 
		                         WhitePixel(display, screen), 
		                         WhitePixel(display, screen));

    XGCValues gc_vals;
    gc_vals.line_width = LINE_WIDTH;
    gcontext = XCreateGC(display, window, GCLineWidth, &gc_vals);
	XMapWindow(display, window);

	Window w;
	XSegment segments[4];
	int root_x, root_y, mouse_x, mouse_y;
	unsigned int mouse_mask;

	int start_pts[4][2] = {{100, 100},
                           {SCREEN_X - 100, 100},
                           {100, SCREEN_Y - 100},
                           {SCREEN_X - 100, SCREEN_Y - 100}};

    for (int i = 0; i < 4; ++i) {
    	segments[i].x1 = start_pts[i][0];
    	segments[i].y1 = start_pts[i][1];
    }


	while (true) {
		XQueryPointer(display, window, &w, &w, &root_x, &root_y,
			          &mouse_x, &mouse_y, &mouse_mask);
    	for (int i = 0; i < 4; ++i) {
	    	segments[i].x2 = mouse_x;
    		segments[i].y2 = mouse_y;
    	}
    	XClearWindow(display, window);
    	XDrawSegments(display, window, gcontext, &segments[0], 4);
		XMapWindow(display, window);
		usleep(1000);
	}

	XCloseDisplay(display);
	return 0;
}
