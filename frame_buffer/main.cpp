#include "FrameBuffer.h"
#include <cstdio>
#include <string>
#include <cstring>
#include <termios.h>
#include <sys/select.h>
#include <ctime>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <term.h>
#include <curses.h>
using namespace std;

struct termios orig_termios;
struct termios new_termios;

/*void loadMap(string mapname, vector<Point> &v, double scale) {
	FILE * filemap = fopen(mapname.c_str(), "r");
	int x,y;
	while(fscanf(filemap, "%d %d", &x, &y) != EOF) {
		Point p(x*scale,y*scale);
		v.push_back(p);
	}
	fclose(filemap);
}*/

void resetTerminal(){
	tcsetattr(0, TCSANOW, &orig_termios);
}

void gotoxy(int x, int y) {
	int err;
	if (!cur_term) {
		if (setupterm( NULL, STDOUT_FILENO, &err ) == ERR) return;
	}
	putp( tparm( tigetstr( "cup" ), y, x, 0, 0, 0, 0, 0, 0, 0 ) );
}

void drawSquare (FrameBuffer * fb, Point center, int r, unsigned int color) {
	int x = center.getX()-r;
	int y = center.getY()-r;
	int size = r*2+1;
	for(int i=0; i<size; i++) {
		for(int j=0; j<size; j++) {
			if ( (x+i) >=0 && (x+i) < fb->width && (y+j) >= 0 && (y+j) < fb->height ) {
				fb->putPixel(x+i, y+j, color);
			}
		}
	}
}

int main() {
	FrameBuffer fb;
	Point p0(0,0), p1(100,0), p2(100,100), p3(0,100);
	srand(time(0));
	int start = true;
	int a=1;

	int r = 2;

	while(a) {
		fb.initScreen();
		
		// Transformasi objek
		if (start) start = false;
		else {
			p0.setXY(rand()%1366, rand()%768);
			p1.setXY(rand()%1366, rand()%768);
			p2.setXY(rand()%1366, rand()%768);
			p3.setXY(rand()%1366, rand()%768);
		}

		// Gambar objek
		fb.drawLine(p0,p1,0xFFFF0000);
		fb.drawLine(p0,p2,0xFF0000FF);
		fb.drawLine(p0,p3,0xFF00FF00);
		fb.drawLine(p1,p2,0xFF00FFFF);
		fb.drawLine(p1,p3,0xFFFFFF00);
		fb.drawLine(p2,p3,0xFFFFFFFF);
		drawSquare(&fb, p0, r, 0xFFFF0000);
		drawSquare(&fb, p1, r, 0xFF00FF00);
		drawSquare(&fb, p2, r, 0xFF0000FF);
		drawSquare(&fb, p3, r, 0xFFFFFFFF);
		
		
		// Gambar semua
		fb.drawScreen();
		
		// Update objek
		// this_thread::sleep_for(chrono::milliseconds(17));
		gotoxy(0,47);
		cin >> a;
	}

	fb.initScreen();
	fb.drawScreen();
	gotoxy(0,0);

	return 0;
}

