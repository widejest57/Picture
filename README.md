#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

using namespace std;

struct Pixel{                                              ///Для каджого пикселя картинки
    int R,G,B;
    Pixel ( int R,int G,int B): R(R),G(G),B(B) {}
    Pixel() : R(0),G(0), B(0) {}
};

typedef unsigned char byte;                                ///Что бы был диапозон от 0 до 255
ifstream fin ("picture!.tga",ios_base::binary);
void print(ofstream &out, int size, int num) {
	for (int i = 0; i < size; ++i) {
		out << (byte)num;
		num >>= 8;                                         ///Сдвиг на байт
	}
}

int read_pix(ifstream& fin, int size){                     ///Побайтовое считывание (взято с интернетов)
    byte* arr = new byte[size];
	fin.read((char*) arr, size);
	int x = 0;
	for (int i = 0; i < size; ++i) {
		x += arr[i] << (8 * i);

	}
	delete[] arr;

	return x;
}



class Picture{
    public:
    int width,height;
    Pixel** table;
    string n;                                        ///Матрица пикселей-table
    Picture(int w,int h){
        width=w;
        height=h;
        table = new Pixel*[height];
        for (int i = 0; i < h; i++) {
            table[i] = new Pixel[w];
        }
    }
    void input(int x, int y , Pixel p){
        table[x][y]=p;
    }
    Pixel output(int x,int y){
        return table[x][y];
    }
    void check(){
     for (int i=0;i<width;i++){
        for(int j=0;j<height;j++) cout<<(table[i][j]).R<<" ";
        cout<<endl;
    }

    }
   // ~Picture();
    Picture(){
        read_pix(fin, 12);
        width = read_pix(fin, 2);
        height = read_pix(fin, 2);
        read_pix(fin, 2);

        table = new Pixel*[height];
        for (int i = 0; i < height; i++) {
		table[i] = new Pixel[width];
		for (int j = 0; j < width; j++) {
                table[i][j].B = read_pix(fin, 1);
                table[i][j].G = read_pix(fin, 1);
                table[i][j].R = read_pix(fin, 1);
            }
        }
	fin.close();
    }
};

//Picture::~Picture(){
  //delete table;
//}



int main()
{
    Picture pict;
    cout<<pict.table[1][1].B;


    ofstream fout ("picture!_2.tga");                      ///Сюда будет записываться результат обработки картинки
    fout.close();












    return 0;
}

