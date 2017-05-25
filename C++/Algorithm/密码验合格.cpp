#include<iostream>
#include<cstring>
#include<string>
using namespace std;

/*
密码要求:

1.长度超过8位

2.包括大小写字母.数字.其它符号,以上四种至少三种

3.不能有相同长度超2的子串重复

说明:长度超过2的子串
*/

bool checkPassword(string p)
{
    int len=p.size();
    if(len<8)
        return false;

    int a[4]={0};
    int count=0;
    for(int i=0;i<len;i++){
        if(p[i]>='A'&&p[i]<='Z')
            a[0]=1;
        else if(p[i]>='a'&&p[i]<='z')
            a[1]=1;
        else if(p[i]>='0'&&p[i]<='9')
            a[2]=1;
        else
            a[3]=1;
        count=0;
        for(auto t:a){
            count+=a[t];
        }
        if(count>=3)
            break;
    }
    if(count<3)
        return false;

    for(int i=0;i<len;i++){
        for(int j=i+1;j<len;j++){
            if(p[i]==p[j]&&p[j]==p[j+1])
                return false;
        }
    }

    return true;
}

int main(void)
{
    string p;
    bool result;
    while(getline(cin,p)){
        result=checkPassword(p);
        if(result)
            cout<<"OK"<<endl;
        else
            cout<<"NG"<<endl;
    }

    return 0;
}
