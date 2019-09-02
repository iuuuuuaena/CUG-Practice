#include"huffmanpress.h"
/*#pragma warning(disable : 4996)*/
//#include<QObject>


HuffCode::HuffCode(string openfile, QProgressBar *bar)
{
    this->oFile = openfile;
    this->bar=bar;
    for (int i = 0; i < 256; i++) {
        Infos[i].ch = i;
        Infos->count = 0;
    }
    hfTree=NULL;
}

HuffCode::~HuffCode()
{
    delete this->hfTree;
}

bool HuffCode::CreatInfo()
{
    //qDebug()<<"开始创建树.";
    wchar_t strUnicode[260];
    UTF8ToUnicode(this->oFile.c_str(), strUnicode);

    FILE *foFile = _wfopen(strUnicode, L"rb");
    if (foFile == NULL) {
        QMessageBox::critical(NULL,"error","创建树时打开文件失败.","ok");
        return false;
    }
    //qDebug()<<"1";
    int ch = fgetc(foFile);
    sum = 0;
    while (1)
    {
        if (feof(foFile))break;
        Infos[ch].count++;
        ch = fgetc(foFile);
        sum++;
    }
    if(hfTree)delete hfTree;hfTree=NULL;
    hfTree = new HuffmanTree<info>(Infos, 256);
    HuffmanNode<info> *root = hfTree->getRoot();
    string str;
    getHfCode(root, str);
    fclose(foFile);
    //qDebug()<<"创建树完成.";
    //Debug();
    return true;
}

bool HuffCode::Coding()
{
    if(!CreatInfo()){return false;}
    if(!SaveConfig()){return false;}
    string codeFile = oFile;
    codeFile += ".haf";

    wchar_t strUnicode[260];
    UTF8ToUnicode(codeFile.c_str(), strUnicode);
    wchar_t strUnicode1[260];
    UTF8ToUnicode(oFile.c_str(), strUnicode1);

    FILE *fsFile = _wfopen(strUnicode,L"wb");
    FILE *foFile = _wfopen(strUnicode1,L"rb");
    if(foFile==NULL){
        QMessageBox::critical(NULL,"error","压缩文件时打开文件失败.","ok");
        return false;
    }
    if(fsFile==NULL){
        QMessageBox::critical(NULL,"error","压缩文件时创建新文件失败.","ok");
        return false;
    }
    rewind(foFile);
    int ch = fgetc(foFile);
    unsigned char value = 0;
    size_t pos = 0;
    //int i=0;//记录进度
    while (1)
    {
        if (feof(foFile))break;
        string str = Infos[ch].str;
        for (size_t i = 0; i < str.size(); i++) {
            value=(value<<1)|(str[i]-'0');
            if (++pos == 8)   //满8位写入文件
            {
                fputc(value, fsFile);
                value = 0;
                pos = 0;
            }
        }
        ch = fgetc(foFile);//i++;
        //this->bar->setValue(int(i/sum*100));
    }
    if (pos) {
        value=value << (8 - pos);
        fputc(value, fsFile);
    }
    this->bar->setValue(100);
    fclose(foFile);
    fclose(fsFile);
    return true;
}

bool HuffCode::Decoding()
{
    if(!CreatInfoByConfig()){
        return false;
    }
    HuffmanNode<info>* root = hfTree->getRoot();
    HuffmanNode<info>* cur = root;
    string sFile=oFile.substr(0,oFile.length()-4);

    wchar_t strUnicode[260];
    UTF8ToUnicode(oFile.c_str(), strUnicode);
    wchar_t strUnicode1[260];
    UTF8ToUnicode(sFile.c_str(), strUnicode1);

    FILE *fnew = _wfopen(strUnicode, L"rb");
    if(fnew==NULL){
        QMessageBox::critical(NULL,"error","解压缩文件时打开文件失败.","ok");
        return false;
    }
    FILE *fsave = _wfopen(strUnicode1, L"wb");
    if(fsave==NULL){
        QMessageBox::critical(NULL,"error","解压缩文件时创建新文件失败.","ok");
        return false;
    }
    unsigned char ch = fgetc(fnew);
    int pos = 8;
//    int i=sum;//记录进度 加上进度条之后很慢 故去掉
//    QProgressDialog *progressDialog=new QProgressDialog;
//            QFont font("ZYSong18030",12);
//            progressDialog->setFont(font);
//            //设置进度对话框采用模态方式进行，即显示进度的同时，其他窗口将不响应输入信号
//            progressDialog->setWindowModality(Qt::WindowModal);
//            //设置进度对话框出现需等待的时间，默认为4s
//            progressDialog->setMinimumDuration(5);
//            //设置进度对话框的窗体标题
//            progressDialog->setWindowTitle(QObject::tr("Please Wait"));
//            //设置进度对话框的显示文字信息
//            progressDialog->setLabelText(QObject::tr("Copying..."));
//            //设置进度对话框的“取消”按钮的显示文字
//            progressDialog->setCancelButtonText(QObject::tr("Cancel"));
//            progressDialog->setRange(0,sum); //设置进度对话框的步进范围
    while (1)
    {
        --pos;
        if ((ch >> pos) & 1)
        {
            cur = cur->rightChild;
        }
        else
        {
            cur = cur->leftChild;
        }

        if (cur->leftChild == NULL && cur->rightChild == NULL)
        {
            fputc(cur->data.ch, fsave);
            cur = root;   //再次从根节点遍历
            sum--;
//            this->bar->setValue(int((i-sum)/i*100));
//            progressDialog->setValue(i-sum);
//                        if(progressDialog->wasCanceled())
//                            return false;
        }
        if (pos == 0)
        {
            ch = fgetc(fnew);
            pos = 8;
        }
        if (sum == 0)  //不读取压缩时为了凑够一个字节而加进去的比特位
            break;
    }
    fclose(fnew);
    fclose(fsave);
    this->bar->setValue(100);
    return true;
}

void HuffCode::getHfCode(HuffmanNode<info>* sub, string str)
{
    if (sub == NULL)return;
    if (sub->leftChild == NULL && sub->rightChild == NULL) {
        Infos[sub->data.ch].str = str;
        return;
    }
    getHfCode(sub->leftChild, str + '0');
    getHfCode(sub->rightChild, str + '1');
}

bool HuffCode::SaveConfig(){
    /*********配置信息**********/
    string configFile = oFile;
    configFile += ".config";
    ofstream out;
    out.open(configFile.c_str(),ios::out);
    if(!out){
        QMessageBox::critical(NULL,"error","创建配置文件失败.","ok");
        return false;
    }
    out<<this->sum;
    for(int i=0;i<256;i++){
        out<<" "<<this->Infos[i].count;
    }
    //qDebug()<<"创建配置文件完成.";
    return true;
}

bool HuffCode::CreatInfoByConfig(){
    string configFile=oFile.substr(0,oFile.length()-3)+"config";
    ifstream in;
    in.open(configFile.c_str(),ios::in);
    if(!in){
        QMessageBox::critical(NULL,"error","请将配置文件放在解压文件同一目录下.","ok");
        return false;
    }
    in>>this->sum;
    qDebug()<<sum;
    for(int i=0;i<256;i++){
        in>>Infos[i].count;
    }
    if(hfTree)delete hfTree;hfTree=NULL;
    hfTree=new HuffmanTree<info>(Infos,256);
    //Debug();
    return true;
}
void HuffCode::Debug(){
    for(int i=0;i<256;i++){
        qDebug()<<Infos[i].count;
    }
}
bool HuffCode::UTF8ToUnicode(const char *UTF8, wchar_t *strUnicode){
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
