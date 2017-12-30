#include<iostream>
#include<string>
using namespace std;

int main(void)
{
    string s;
    while(cin>>s){
        int len=s.size();
        for(int i=1;i<len;i++){
            if(islower(s[i])){
                char t=s[i];
                int j;
                for(j=i-1;j>=0;j--){
                    if(isupper(s[j])){
                        s[j+1]=s[j];
                    }
                    else
                        break;
                }
                s[j+1]=t;
            }
        }
        cout<<s<<endl;
    }

    return 0;
}
