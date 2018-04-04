#include <fstream>
#include <iostream>
#include <cmath>
#include <string>

using namespace std;

typedef unsigned char byte;

double gauss(double x, double sigma) {
	return exp(-x * x / (2 * sigma));
}

struct color {
	int r, g, b;
	color(int r, int g, int b) : r(r), g(g), b(b) {}
	color() : r(0), g(0), b(0) {}
	color invert() {
		return color(255 - r, 255 - g, 255 - b);
	}
};

void print(ofstream &out, int size, int num) {
	for (int i = 0; i < size; ++i) {
		out << (byte)num;
		num >>= 8;
	}
}

int read(ifstream &in, int size) {
	byte* buff = new byte[size];
	in.read((char*)buff, size);

	int x = 0;
	for (int i = 0; i < size; ++i) {
		x += buff[i] << (8 * i);

	}
	delete[] buff;

	return x;
}

class tga {
public:
	tga(string name);
	tga(string name, int w, int h);
	~tga();
	void set_pixel(int x, int y, color cl);
	color get_pixel(int x, int y);
	int width, height;
private:
	string name;
	color** data;
};

tga::tga(string n, int w, int h) {
	name = n;
	width = w;
	height = h;

	data = new color*[height];
	for (int i = 0; i < height; ++i) {
		data[i] = new color[width];
	}
}

tga::tga(string n) {
	name = n;
	ifstream in(name, ios::binary);
	read(in, 12);
	width = read(in, 2);
	height = read(in, 2);
	read(in, 2);

	data = new color*[height];
	for (int i = 0; i < height; ++i) {
		data[i] = new color[width];
		for (int j = 0; j < width; ++j) {
			data[i][j].b = read(in, 1);
			data[i][j].g = read(in, 1);
			data[i][j].r = read(in, 1);
		}
	}
	in.close();

}

tga::~tga() {
	ofstream out(name, ios::binary);
	print(out, 1, 0); // Id length
	print(out, 1, 0); // Color map type
	print(out, 1, 2); // Image type
	print(out, 5, 0); // No color map

	print(out, 2, 0); // X
	print(out, 2, 0); // Y
	print(out, 2, width); // Width
	print(out, 2, height); // Height

	print(out, 1, 24); // Color depth
	print(out, 1, 0);

	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			print(out, 1, data[i][j].b);
			print(out, 1, data[i][j].g);
			print(out, 1, data[i][j].r);
		}
	}

	out.close();
}

void tga::set_pixel(int x, int y, color cl) {
	data[y][x] = cl;
}

color tga::get_pixel(int x, int y) {
	if (x >= width) x = width - 1;
	if (y >= height) y = height - 1;
	if (x < 0) x = 0;
	if (y < 0) y = 0;
	return data[y][x];
}

double k[1000][1000];

void count_k(int radius) {
	double sm = 0;
	int blur_width = 2 * radius + 1;

	double sigma = radius / 3.0;

	for (int i = 0; i < blur_width; ++i) {
		for (int j = 0; j < blur_width; ++j) {
			k[i][j] = gauss(hypot(i - radius, j - radius), sigma);
			sm += k[i][j];
		}
	}
	for (int i = 0; i < blur_width; ++i) {
		for (int j = 0; j < blur_width; ++j) {
			k[i][j] /= sm;
		}
	}
}

int main() {

    int n;
    cin>>n;
	tga img("img.tga");
	tga res("res.tga", img.width+2*n, img.height+2*n);

	int radius = 10;

//	count_k(radius);
double y;
	for (int i = 0; i < img.width; ++i) {
		for (int j = 0; j < img.height; ++j) {
            double r=0,g=0,b=0;
/*
			for (int dx = -radius; dx <= radius; ++dx) {
				for (int dy = -radius; dy <= radius; ++dy) {
					r += img.get_pixel(i + dx, j + dy).r * k[radius + dx][radius + dy];
					g += img.get_pixel(i + dx, j + dy).g * k[radius + dx][radius + dy];
					b += img.get_pixel(i + dx, j + dy).b * k[radius + dx][radius + dy];
				}
			}
*/

            if (i<n)
                res.set_pixel(j, i, color(img.data[2*n-i][j].r,img.data[2*n-i][j].g, img.data[2*n-i][j].b));
            else {
                if (i>img.width+n)  res.set_pixel(j, i, color(img.data[2*n+2*img.width-i][j].r,img.data[2*n+2*img.width-i][j].g, img.data[2*n+2*img.width-i][j].b));
                else{
                    if (j<n)  res.set_pixel(j, i, color(img.data[i][2*n-j].r,img.data[i][2*n-j].g, img.data[i][2*n-j].b));
                    else{
                         if (j>img.width+n)  res.set_pixel(j, i, color(img.data[i][2*n+2*width-j].r,img.data[i][2*n+2*width-j].g, img.data[i][2*n+2*width-j].b));
                         else{
                            res.set_pixel(j,i,color(img.data[i-n][j-n]));
                         }
                    }
                }
            }

		}
	}

	return 0;
}
