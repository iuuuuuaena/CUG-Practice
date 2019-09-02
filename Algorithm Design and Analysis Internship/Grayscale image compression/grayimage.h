#ifndef GRAYIMAGE_H
#define GRAYIMAGE_H
#include<QFile>
#include<QDebug>
#include<string>
#include<QMessageBox>
#include<iostream>
#include<QProgressDialog>
#include"Windows.h"
#include<fstream>
using namespace std;

class GrayImage
{
public:
    GrayImage(string fileName);
    bool Compress();
    bool UnCompress();

private:

    void dp(int n, unsigned char p[], unsigned int s[], unsigned int l[], unsigned int b[]);
    void Traceback(int n, int& m, unsigned int s[], unsigned int l[]);
    int Output(unsigned int s[], unsigned int l[], unsigned int b[], int n);
    int length(unsigned char n);

    bool ReadBitmap();
    bool Linearization();
    bool UnLinearization();

    bool UTF8ToUnicode(const char *UTF8, wchar_t *strUnicode);

    BITMAPFILEHEADER *bmpfileheader;
    BITMAPINFOHEADER *bmpinfoheader;
    RGBQUAD *rgbquad;//调色板
    string fileName;

    int bmpWidth;
    int bmpHeight;
    int rgb_count;//调色板个数
    BYTE **img;
    unsigned char *imgline;
    QProgressDialog *dialog;
};

#endif // GRAYIMAGE_H
