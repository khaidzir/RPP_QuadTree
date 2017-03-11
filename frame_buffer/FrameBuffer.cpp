#include "FrameBuffer.h"
#include <string.h>
#include <cmath>

// inisialisasi awal framebuffer dengan membuka device framebuffer pada
// /dev/fb0
// inisialisasi dilakukan dengan mengambil ukuran layar pada framebuffer
// ukuran layar pada framebuffer dapat diatur pada grub
FrameBuffer::FrameBuffer(){
	fbfd = open("/dev/fb0", O_RDWR);

	if(fbfd == -1){
		perror("Error : ");
		exit(1);
	}

	//get var screen info
	if(ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo)){
		perror("Error ");
		exit(3);
	}
	vinfo.grayscale=0;
	vinfo.bits_per_pixel=32;
	//ioctl(fbfd, FBIOPUT_VSCREENINFO, &vinfo);
	if(ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo)){
		perror("Error ");
		exit(2);
	}
	
	height = vinfo.yres;
	width = vinfo.xres;
     //Get fix screen information
	ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo);

	screensize = vinfo.yres_virtual * finfo.line_length;
	
	backbuffer = new char[screensize];
	fbp = (char*) mmap(0, finfo.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, (off_t)0);
}

// destroy framebuffer
// menghapus backbuffer dan framebuffer serta menutup device framebuffer
FrameBuffer::~FrameBuffer(){
	initScreen();
	delete [] backbuffer;
	munmap(fbp, screensize);
	close(fbfd);
}

// menggambar titik pada framebuffer
void FrameBuffer::putPixel(int x, int y, unsigned int color){
	long int location = getRelativePosition(x,y);
	if(location <= screensize && location > 0)
		*((char*)(backbuffer + location)) = color;

	*(backbuffer+location) = (color&0xFF);
	*(backbuffer+location+1) = ((color&0xFF00)>>8);
	*(backbuffer+location+2) = ((color&0xFF0000)>>16);
	*(backbuffer+location+3) = ((color&0xFF000000)>>24);
}
void FrameBuffer::putPixel(Point P, unsigned int color){
	long int location = getRelativePosition(P.getX(),P.getY());
	if(location <= screensize && location > 0)
		*((char*)(backbuffer + location)) = color;

	*(backbuffer+location) = (color&0xFF);
	*(backbuffer+location+1) = ((color&0xFF00)>>8);
	*(backbuffer+location+2) = ((color&0xFF0000)>>16);
	*(backbuffer+location+3) = ((color&0xFF000000)>>24);
}

// menggambar garis pada framebuffer
// menggambar garis dengan menggunakan algoritma bressenham
// dengan memanfaatkan fungsi putPixel()
void FrameBuffer::drawLine(Point p0, Point p1, unsigned int color) {
	int x0 = p0.getX();
	int y0 = p0.getY();
	int x1 = p1.getX();
	int y1 = p1.getY();
	
	int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
	int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1;
	int err = (dx>dy ? dx : -dy)/2, e2;

	for(;;){
		putPixel(x0,y0,color);
		if(x0==x1 && y0==y1) break;
		e2 = err;
		if(e2 > -dx) { err -= dy; x0 += sx;}
		if(e2 < dy) { err += dx; y0 += sy;}
	}
}

// mendapatkan informasi nilai warna di koordinat x,y pada framebuffer
unsigned int FrameBuffer::getPixel(int x, int y){
	long int location = getRelativePosition(x, y);
	return *((unsigned int*)(backbuffer+location));
}
unsigned int FrameBuffer::getPixel(Point P){
	long int location = getRelativePosition(P.getX(), P.getY());
	return *((unsigned int*)(backbuffer+location));
}

// mendapatkan ukuran dari framebuffer
long int FrameBuffer::getScreensize(){
	return screensize;
}

// mendapatkan ukuran relatif dari koordinat x,y
// koordinat relatif adalah perhitungan y*width + x
long FrameBuffer::getRelativePosition(int x, int y){
	return (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y+vinfo.yoffset) * finfo.line_length;
}

// inisialisasi framebuffer
// mengosongkan backbuffer
// backbuffer adalah tempat pengguna menggambar titik dan garis
// sebelum ditampilkan pada framebuffer (layar)
void FrameBuffer::initScreen(){
	memset(backbuffer, 0, screensize);
}

// menggambarkan titik-titik dari backbuffer ke framebuffer (layar)
void FrameBuffer::drawScreen(){
	memcpy(fbp, backbuffer, screensize);
}

// mendapatkan ukuran panjang framebuffer
int FrameBuffer::getWidth(){
	return width;
}

// mendapatkan ukuran lebar/tinggi framebuffer
int FrameBuffer::getHeight(){
	return height;
}

// menggambarkan layer baru pada layar
// layer adalah lapisan di atas backbuffer yang berukuran sama dengan backbuffer
// layer digambarkan setelah backbuffer digambar sehingga layer selalu berada
// di atas backbuffer
// layer akan digambar bersamaan dengan backbuffer ke framebuffer
// pada saat pemanggilan method drawScreen()

void FrameBuffer::drawLayer(char * layer)
{
	memcpy(backbuffer, layer, screensize);
}

// menggambar lingkaran pada layar
void FrameBuffer::drawCircle(int xm, int ym, int r, unsigned int color)
{
	int x = -r, y = 0, err = 2-2*r; /* II. Quadrant */ 
   do {
      putPixel(xm-x, ym+y, color); /*   I. Quadrant */
      putPixel(xm-y, ym-x, color); /*  II. Quadrant */
      putPixel(xm+x, ym-y, color); /* III. Quadrant */
      putPixel(xm+y, ym+x, color); /*  IV. Quadrant */
      r = err;
      if (r <= y) err += ++y*2+1;           /* e_xy+e_y < 0 */
      if (r > x || err > y) err += ++x*2+1; /* e_xy+e_x > 0 or no 2nd y-step */
   } while (x < 0);
}