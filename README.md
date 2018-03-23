# Picture


#include <iostream>
#include <fstream>
using namespace std;

struct Pixel{                                              ///Для каджого пикселя картинки
    int R,G,B;
    Pixel ( int R,int G,int B): R(R),G(G),B(B) {}
    Pixel() : R(0),G(0), B(0) {}
};

typedef unsigned char byte;                                ///Что бы был диапозон от 0 до 255

void print(ofstream &out, int size, int num) {
	for (int i = 0; i < size; ++i) {
		out << (byte)num;
		num >>= 8;                                         ///Сдвиг на байт
	}
}

int read_pix(ifstream& fin, int size){                     ///Побайтовое считывание (взято с интернетов)
    byte* buff = new byte[size];
	fin.read((char*) buff, size);
	int x = 0;
	for (int i = 0; i < size; ++i) {
		x += buff[i] << (8 * i);

	}
	delete[] buff;

	return x;
}

//class Picture{
//    int width,height;
 //   Picture(w,h);
   // void input();
//};

//Picture::Picture(int w,int h){
 //width=w;
 //height=h;

//}

int main()
{


    ofstream fout ("picture!_2.bmp");                      ///Суда будет записываться результат обработки картинки
//    fout<<"Hello world!"<<endl;
    fout.close();



    ifstream fin ("picture!.bmp", ios_base::binary);

    fin.close();

    //int* prim= new int(5757);
   // cout<<*prim<<endl;
   // delete prim;


    return 0;
}
