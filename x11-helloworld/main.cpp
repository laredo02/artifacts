
#include <X11/Xlib.h>
#include <iostream>

#include <assert.h>
#include <unistd.h>

using namespace std;

int main () {
  Display *display = XOpenDisplay(0);
  int blackColor = BlackPixel(display, DefaultScreen(display)),
    whiteColor = WhitePixel(display, DefaultScreen(display));

  assert(display);
  
  Window window = XCreateSimpleWindow(display, DefaultRootWindow(display),
				      0, 0, 640, 480, 0, whiteColor, whiteColor);
    
  XSelectInput(display, window, StructureNotifyMask);
  XMapWindow(display, window);
  GC gc = XCreateGC(display, window, 0, 0);
  XSetForeground(display, gc, blackColor);
  
  while (1) {
    XEvent event;
    XNextEvent(display, &event);
    if (event.type == MapNotify)
      break;
  }

  XDrawLine(display, window, gc, 0, 480, 640, 0);
  XDrawLine(display, window, gc, 0, 0, 640, 480);
  
  XFlush(display);
  sleep(10);
  
  return 0;
}
