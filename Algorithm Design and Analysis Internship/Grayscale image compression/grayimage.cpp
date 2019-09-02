#include "grayimage.h"
#include"note.h"

GrayImage::GrayImage(string fileName)
{
    this->bmpfileheader=new BITMAPFILEHEADER;
    this->bmpinfoheader=new BITMAPINFOHEADER;
    this->rgbquad=new RGBQUAD[256];
    this->fileName=fileName;
    dialog=new QProgressDialog;
    //设置进度对话框采用模态方式进行，即显示进度的同时，其他窗口将不响应输入信号
    dialog->setWindowModality(Qt::WindowModal);
    //设置进度对话框出现需等待的时间，默认为4s
    dialog->setMinimumDuration(5);
    //设置进度对话框的窗体标题
    dialog->setWindowTitle(QObject::tr("Please Wait"));
    dialog->setRange(0,300); //设置进度对话框的步进范围
    //设置进度对话框的“取消”按钮的显示文字
    dialog->setCancelButtonText(QObject::tr("Cancel"));
}

bool GrayImage::ReadBitmap()
{
    wchar_t strUnicode[260];
    UTF8ToUnicode(this->fileName.c_str(), strUnicode);
    FILE* fp=_wfopen(strUnicode,L"rb");
    if(fp==NULL){
        QMessageBox::critical(NULL,"error","打开文件失败.","ok");
        return false;
    }
    fread(bmpfileheader,sizeof(BITMAPFILEHEADER),1,fp);
    fread(bmpinfoheader,sizeof(BITMAPINFOHEADER),1,fp);
    //    showBmpHead(*bmpfileheader);
    //    showBmpInforHead(*bmpinfoheader);
    this->rgb_count=(bmpfileheader->bfOffBits-54)/4;
    fread(rgbquad,sizeof(RGBQUAD),this->rgb_count,fp);
//    bmpWidth=(bmpinfoheader->biWidth+3)/4*4;
    bmpWidth=bmpinfoheader->biWidth;
    bmpHeight=bmpinfoheader->biHeight;
    //qDebug()<<bmpfileheader->bfOffBits;
    img=new BYTE*[bmpHeight];
    for(int i=0;i<bmpHeight;++i){
        img[i]=new BYTE[bmpWidth];
        fread(img[i],1,bmpWidth,fp);
    }
    fclose(fp);
    return true;
}

bool GrayImage::Compress()
{
    this->Linearization();
    int count=this->bmpHeight*this->bmpWidth;
    dialog->setLabelText(QObject::tr("Compressing..."));//设置进度对话框的显示文字信息
    unsigned int *s=new unsigned int[count+1];//纪录分段位置
    unsigned int *l=new unsigned int[count+1];//纪录每段长度
    unsigned int *b=new unsigned int[count+1];//纪录每段位数
    this->dp(count,this->imgline,s,l,b);
    int m=this->Output(s,l,b,count);
    string nfileName=this->fileName.substr(0,fileName.length()-4);
    nfileName+=".img";
    wchar_t strUnicode[260];
    UTF8ToUnicode(nfileName.c_str(), strUnicode);
    FILE *nfp=_wfopen(strUnicode,L"wb");
    if(nfp==NULL){
        QMessageBox::critical(NULL,"error","打开文件失败.","ok");
        return false;
    }
    //写入头文件信息
    fwrite(this->bmpfileheader,sizeof(BITMAPFILEHEADER),1,nfp);
    fwrite(this->bmpinfoheader,sizeof(BITMAPINFOHEADER),1,nfp);
    fwrite(this->rgbquad,sizeof(RGBQUAD),this->rgb_count,nfp);
    fseek(nfp,this->bmpfileheader->bfOffBits,SEEK_SET);
    fwrite(&m,sizeof(m),1,nfp);
    /******************************************************/
//    int index=1;//要读取的位置
    unsigned char value=0;//每次写入八位
    size_t pos=0;
    unsigned int t;
    for(int i=1;i<=m;i++){
        dialog->setValue(200+i/m*100);
        if(dialog->wasCanceled()){
            fclose(nfp);
            remove(nfileName.c_str());
            return false;
        }
        size_t a=8;
        t=l[i]-1;
        while (a>0) {
            value=(value<<1)|((t>>(a-1))&1);
            if (++pos == 8)
            {
                fputc(value, nfp);
                value = 0;
                pos = 0;
            }
            --a;
        }
        a=3;
        t=b[i]-1;
//        qDebug()<<b[i];
        while (a>0) {
            value=(value<<1)|((t>>(a-1))&1);
            if (++pos == 8)
            {
                fputc(value, nfp);
                value = 0;
                pos = 0;
            }
            --a;
        }
        for(size_t j=1;j<=l[i];j++){
            size_t tmp=b[i];
            while (tmp>0) {//?
                value=(value<<1)|((imgline[s[i-1]+j]>>(tmp-1))&1);
                if (++pos == 8)
                {
                    fputc(value, nfp);
                    value = 0;
                    pos = 0;
                }
                --tmp;
            }
        }
    }
    if (pos) {
        value=value << (8 - pos);
        fputc(value, nfp);
    }
    fclose(nfp);
    return true;
}

bool GrayImage::Linearization()
{
    this->ReadBitmap();
    this->imgline=new unsigned char[this->bmpWidth*this->bmpHeight+1];
    imgline[0]=0;
    int k=1;
    for(int i=0;i<bmpHeight;i++){
        if(i%2==0){
            for(int j=0;j<bmpWidth;j++){
                imgline[k++]=img[i][j];
            }
        }else {
            for(int j=bmpWidth-1;j>=0;j--){
                imgline[k++]=img[i][j];
            }
        }
    }
    return true;
}

bool GrayImage::UnCompress()
{
    dialog->setLabelText(QObject::tr("Compressing..."));//设置进度对话框的显示文字信息
    wchar_t strUnicode[260];
    UTF8ToUnicode(this->fileName.c_str(), strUnicode);
    FILE *fp=_wfopen(strUnicode,L"rb");
    if(fp==NULL){
        QMessageBox::critical(NULL,"error","打开文件失败.","ok");
        return false;
    }
    fread(bmpfileheader,sizeof(BITMAPFILEHEADER),1,fp);
    fread(bmpinfoheader,sizeof(BITMAPINFOHEADER),1,fp);
    this->rgb_count=(bmpfileheader->bfOffBits-54)/4;
    fread(rgbquad,sizeof(RGBQUAD),this->rgb_count,fp);
//    fseek(fp,bmpfileheader->bfOffBits,SEEK_SET);
//    bmpWidth=(bmpinfoheader->biWidth+3)/4*4;
    bmpWidth=bmpinfoheader->biWidth;
    bmpHeight=bmpinfoheader->biHeight;
    this->imgline=new unsigned char[this->bmpWidth*this->bmpHeight+1];
    int m;//多少段
    fread(&m,sizeof(m),1,fp);
    unsigned char value=0;
    unsigned int l=0,b=0;
    int pos=0;size_t tmp;
    int index=0;
//    qDebug()<<this->bmpWidth*this->bmpHeight;
    for(int i=0;i<m;i++){
        this->dialog->setValue((i*200)/m);
        if(dialog->wasCanceled()){
            fclose(fp);
            return false;
        }
        l=0;b=0;
        tmp=0;
        while (tmp<8) {
            if(pos==0){
                value=fgetc(fp);
                pos=8;
            }
            --pos;
            l=(l<<1)|((value>>pos)&1);
            ++tmp;
        }
        tmp=0;
        while (tmp<3) {
            if(pos==0){
                value=fgetc(fp);
                pos=8;
            }
            --pos;
            b=(b<<1)|((value>>pos)&1);
            ++tmp;
        }
        for(size_t j=0;j<=l;j++){
            tmp=0;
            imgline[index]=0;
            while (tmp<=b) {
                if(pos==0){
                    value=fgetc(fp);
                    pos=8;
                }
                --pos;
                this->imgline[index]=(imgline[index]<<1)|((value>>(pos))&1);
                ++tmp;
            }
            ++index;
        }
    }
    fclose(fp);
    return UnLinearization();
}

bool GrayImage::UnLinearization()
{
    string nfileName=this->fileName.substr(0,fileName.length()-4);
    nfileName+="_decompress.bmp";
    wchar_t strUnicode[260];
    UTF8ToUnicode(nfileName.c_str(), strUnicode);
    FILE *nfp=_wfopen(strUnicode,L"wb");
    if(nfp==NULL){
        QMessageBox::critical(NULL,"error","创建文件失败.","ok");
        return false;
    }
    fwrite(this->bmpfileheader,sizeof(BITMAPFILEHEADER),1,nfp);
    fwrite(this->bmpinfoheader,sizeof(BITMAPINFOHEADER),1,nfp);
    fwrite(this->rgbquad,sizeof(RGBQUAD),this->rgb_count,nfp);
    int index=0;
    for(int i=0;i<bmpHeight;i++){
        this->dialog->setValue(200+((i+1)*100)/bmpHeight);
        if(dialog->wasCanceled()){
            fclose(nfp);
            remove(nfileName.c_str());
            return false;
        }
        if(i%2==0){
            for(int j=0;j<bmpWidth;j++){
                fputc(imgline[index++],nfp);
            }
        }else {
            for(int j=bmpWidth;j>0;j--){
                fputc(imgline[index+j-1],nfp);
            }
            index+=bmpWidth;
        }
    }
    fclose(nfp);
    return true;
}

void GrayImage::dp(int n, unsigned char p[], unsigned int s[], unsigned int l[], unsigned int b[])
{
    int Lmax = 256,header = 11;
    s[0] = 0;
    for(int i=1; i<=n; i++)
    {
        if(i%100==0){
            dialog->setValue((i*200)/n);
        }

        b[i] = length(p[i]);//计算像素点p需要的存储位数
        int bmax = b[i];
        s[i] = s[i-1] + bmax;
        l[i] = 1;

        for(int j=2; j<=i && j<=Lmax;j++)//i=1时，不进入此循环
        {
            if(bmax<b[i-j+1])
            {
                bmax = b[i-j+1];
            }

            if(s[i]>s[i-j]+j*bmax)
            {
                s[i] = s[i-j] + j*bmax;
                l[i] = j;
            }
        }
        s[i] += header;
    }
}

void GrayImage::Traceback(int n, int &i, unsigned int s[], unsigned int l[])
{
    if(n==0)
        return;
    Traceback(n-l[n],i,s,l);//p1,p2,p3,...,p(n-l[n])像素序列，最后一段有l[n]个像素
    s[i++]=n-l[n];//重新为s[]数组赋值，用来存储分段位置，最终i为共分了多少段
//    if (n == 0)
//        return;
//    Traceback(n - l[n], m, s, l);//s[i]纪录第i段到的位置
//    s[m++] = n - l[n];  //重新为s[]数组赋值，用来存储分段位置
}

int GrayImage::Output(unsigned int s[], unsigned int l[], unsigned int b[], int n)
{
    int m = 0;
    Traceback(n,m,s,l);//s[0]:第一段从哪分，s[1]:第二段从哪分...，s[m-1]第m段从哪分
    s[m] = n;//此时m为总段数，设s[m]=n，分割位置为第n个像素
//    qDebug()<<"将原灰度序列分成"<<m<<"段序列段"<<endl;
    for(int j=1; j<=m; j++)
    {
        l[j] = l[s[j]];
//        b[j] = b[s[j]];
    }
    for (int j = 1; j <= m; j++) {
        b[j] = b[s[j - 1] + 1];
        for (int i = s[j-1] + 1; i <= s[j-1] + l[j];i++) {
            b[j] = max(b[j], b[i]);
        }
    }
//    for (int j = 1; j <= m; j++)
//        {
//            qDebug() << "l" << l[j] << ",b:" << b[j] <<"s"<<s[j-1];
//        }
    return m;//段数
}

int GrayImage::length(unsigned char n)
{
    if(!n)return 1;
    int c = 0;  // counter
    for(; n; n >>= 1)
        ++c ;
    return c ;
}

bool GrayImage::UTF8ToUnicode(const char *UTF8, wchar_t *strUnicode)
{
    DWORD dwUnicodeLen;    //转换后Unicode的长度
    TCHAR *pwText;      //保存Unicode的指针
    // wchar_t* strUnicode;    //返回值
    //获得转换后的长度，并分配内存
    dwUnicodeLen = MultiByteToWideChar(CP_UTF8,0,UTF8,-1,NULL,0);
    pwText = new TCHAR[dwUnicodeLen];
    if(!pwText)
    {
        return false;
    }
    //转为Unicode
    MultiByteToWideChar(CP_UTF8,0,UTF8,-1,pwText,dwUnicodeLen);
    //转为CString
    wcscpy(strUnicode, pwText);
    //清除内存
    delete[] pwText;
    return true;
}


