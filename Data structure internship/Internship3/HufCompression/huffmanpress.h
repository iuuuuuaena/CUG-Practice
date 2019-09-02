#ifndef HUFFMANPRESS_H
#define HUFFMANPRESS_H
#include"huffmantree.h"
#include"HuffmanTree.h"
#include"Windows.h"
#include"wchar.h"
#include<fstream>
#include<QProgressBar>
#include<QMessageBox>
#include<QDebug>
#include<QProgressDialog>
typedef long long lolo;
struct info
{
    unsigned char ch;
    lolo count;
    string str;
    info(long long c = 0) :ch(0), count(c), str("") {}
    info operator +(const info &n) {
        long long temp = this->count + n.count;
        return info(temp);
    }
    bool operator <(const info&n) {
        return this->count < n.count;
    }
    bool operator <=(const info&n) {
        return this->count < n.count || this->count == n.count;
    }
    bool operator >(const info&n) {
        return this->count > n.count;
    }
    bool operator >=(const info&n) {
        return this->count > n.count || this->count == n.count;
    }
    bool operator ==(const info&n) {
        return this->count == n.count;
    }
    bool operator !=(const info&n) {
        return this->count != n.count;
    }
};


class HuffCode
{
public:
    HuffCode(string openfile,QProgressBar *bar);
    ~HuffCode();
    bool Coding(); //压缩函数
    bool Decoding();//解压函数
private:
    info Infos[256];//根据ASCII码存储
    string oFile;
    HuffmanTree<info> *hfTree;
    lolo sum;
    void getHfCode(HuffmanNode<info>* sub,string str);
    bool CreatInfo(); //得到基本信息创建树
    bool SaveConfig();
    bool CreatInfoByConfig();
    QProgressBar *bar;
    bool UTF8ToUnicode(const char* UTF8, wchar_t* strUnicode);
    /*******测试用*********/
    void Debug();
};


#endif // HUFFMANPRESS_H
