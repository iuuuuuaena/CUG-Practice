#include "substringstatistics.h"

SubstringStatistics::SubstringStatistics(QString str1,QString str2)
{
    this->str1=str1;
    this->str2=str2;
    len1=str1.length();
    len2=str2.length();
    count=0;

}

SubstringStatistics::~SubstringStatistics(){

}

void SubstringStatistics::calculate(){
    for (int i = 0; i <= len1-len2; i++) {
            if (str1[i] == str2[0]) {
                int sum = 0;
                for (int j = 0; j < len2; j++)
                {
                    if (str1[i + j] == str2[j]) {
                        sum++;
                    }
                }
                if (sum == len2) {
                    count++;
                }
            }
        }
}

int SubstringStatistics::getcount(){
    return count;
}
