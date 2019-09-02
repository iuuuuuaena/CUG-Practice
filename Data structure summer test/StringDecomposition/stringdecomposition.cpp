#include "stringdecomposition.h"

StringDecomposition::StringDecomposition(char in[])
{
    this->length=strlen(in);
//    this->in=new char[length];
    this->out=new int[length];
    this->in=in;
//    for(int i=0;i<length;i++){
//        this->in[i]=in[i];
//    }
    this->length_out=0;
}
StringDecomposition::~StringDecomposition(){
    delete []in;
    in=NULL;
    delete []out;
    out=NULL;
}

void StringDecomposition::calculate(){
    int n=0;
    for(int i=0;i<length;i++){
        if(in[i]>='0'&&in[i]<='9'){
            n++;
            if(i==length-1){
                if(n>1){
                    int sum=0;
                    for(int j=i-n+1;j<=i;j++){
                        sum=sum*10+int(in[j]-48);
                    }
                    out[length_out]=sum;
                    length_out++;
                    n=0;
                }
            }
        }
        else {
            if(n>1){
                int sum=0;
                for(int j=i-n;j<i;j++){
                    sum=sum*10+int(in[j]-48);
                }
                out[length_out]=sum;
                length_out++;
                n=0;
            }
            n=0;
        }
    }
}

int *StringDecomposition::get(){
    return this->out;
}

int StringDecomposition::getlength(){
    return this->length_out;
}












