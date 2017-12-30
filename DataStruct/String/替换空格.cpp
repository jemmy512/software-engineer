#include<iostream>
using namespace std;

void ReplaceBlank(char string[],int length)
{
    // ‰»Î“Ï≥£≈–∂œ
    if(string==NULL||length<0)
        return ;
    int originalLength=0;
    int numberOfBlank=0;
    for(int i=0;string[i]!='\0';i++){
        ++originalLength;
        if(string[i]==' ')
            ++numberOfBlank;
    }

    int newLength=originalLength+numberOfBlank*2;
    if(newLength>length)
        return;
    int indexOfOriginal=originalLength;
    int indexOfNew=newLength;

    while(indexOfOriginal>=0&&indexOfOriginal<indexOfNew){
        if(string[indexOfOriginal]==' '){
            string[indexOfNew--]='0';
            string[indexOfNew--]='2';
            string[indexOfNew--]='%';
        }else{
            string[indexOfNew--]=string[indexOfOriginal];
        }
        indexOfOriginal--;
    }
    cout<<string<<endl;
}

int main(void)
{

    char string[]="we are happy.\0";
    cout<<string<<endl;
    ReplaceBlank(string,30);
    return 0;
}
