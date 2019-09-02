#include "changeproblem.h"

ChangeProblem::ChangeProblem(int n,int *t,int *coins,int m)
{
    this->n=n;
    this->t=new int[n+1];
    for(int i=1;i<=n;i++){
        this->t[i]=t[i];
    }
    this->coins=new int[n+1];
    for(int i=1;i<=n;i++){
        this->coins[i]=coins[i];
    }
    this->m=m;
//    for(int i=1;i<=n;i++){
//        qDebug()<<this->t[i]<<coins[i];
//    }
//    qDebug()<<n<<m;
}


ChangeProblem::~ChangeProblem(){
    delete []t;
    t=NULL;
    delete []coins;
    coins=NULL;
}

void ChangeProblem::calculate(){
    int dp[20002] = { 0 };   //dp[i] 用来记录钱数为i时的最少的硬币数
    for (int i = 1; i <= m; i++)
        dp[i] = 99999;
    //dp[0] = 0;
    for (int i = 1; i <= n; i++)    //硬币面值的种数
        for (int j = 1; j <= coins[i]; j++)   //硬币的面值的个数
            for (int k = m; k >= t[i]; k--)
            {
                dp[k] = mini(dp[k - t[i]] + 1, dp[k]);
//				qDebug()<<k<<": "<<dp[k]<<endl;  用于测试使用
            }
    if (dp[m] == 99999){count=-1;}
    else {count=dp[m];}
//    qDebug()<<dp[m];
}

int ChangeProblem::getcount(){
    return count;
}

int ChangeProblem::mini(int a, int b){
    return a<b?a:b;
}
