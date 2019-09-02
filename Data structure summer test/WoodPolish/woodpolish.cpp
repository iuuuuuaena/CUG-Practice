#include "woodpolish.h"
#include<algorithm>

WoodPolish::WoodPolish(int n,wood w[])
{
    this->n=n;
    this->w=new wood[n];
    this->w=w;
    record="";
    time=0;
}

bool WoodPolish::cmp(wood a, wood b){
    if (a.l != b.l)
        {
            return a.l<b.l;
        }
        else
        {
            return a.wei<b.wei;
        }
}

void WoodPolish::calculate(){
    std::sort(w,w+n,cmp);
    for (int i = 0; i<n; i++)
            {
                if (w[i].wei) //避免重复的访问
                {
                    time++;
                    int temp = w[i].wei;
                    record=record+"("+QString::number(w[i].l)+","+QString::number(w[i].wei)+")"+" ";
                    for (int j = i + 1; j<n; j++)
                    {
                        if (w[j].wei >= temp)
                        {
                            temp = w[j].wei;
                            record=record+"("+QString::number(w[j].l)+","+QString::number(w[j].wei)+")"+" ";
                            w[j].wei = 0; //这个点已访问
                        }
                    }
                    record+='\n';
                }

            }
    record=QString::number(time)+'\n'+record+'\n';
}

QString WoodPolish::getrecord(){
    return record;
}
