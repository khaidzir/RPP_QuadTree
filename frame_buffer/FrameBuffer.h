#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <linux/fb.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "Point.h"
using namespace std;

class FrameBuffer{
	private :
		struct fb_fix_screeninfo finfo;
		struct fb_var_screeninfo vinfo;
		int fbfd;
		long int screensize;
		char *backbuffer;
		char *fbp;
		
	public :	
		FrameBuffer();
		~FrameBuffer();
		int width, height;
		void putPixel(int x, int y, unsigned int color);
		void putPixel(Point P, unsigned int color);
		void drawLine(Point p0, Point p1, unsigned int color);
		unsigned int getPixel(int x, int y);
		unsigned int getPixel(Point P);
		long int getScreensize();
		long getRelativePosition(int x, int y);
		void initScreen();
		void drawScreen();
		void drawLayer(char * layer);
		int getWidth();
		int getHeight();
		void drawCircle(int xm, int ym, int r, unsigned int color);
};
#endif
