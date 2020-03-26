#include<iostream>
using namespace std;

int MinInorder(int * numbers,int index1,int index2){
	int result=numbers[index1];
	for(int i=index1;i<=index2;i++){
		if(numbers[i]<result)
			result=numbers[i];
	}
	return result;
}

int Min(int *numbers,int length)
{
	if(numbers==NULL&&length<=0){
//		throw new std::exception("Invalid parameters");
	}
	
	int index1=0;
	int index2=length-1;
	int indexMid=index1;
	while(numbers[index1]>=numbers[index2]){
		if(index2-index1==1){
			indexMid=index2;
			break;
		}
		indexMid=(index1+index2)/2;
		if(numbers[index1]==numbers[index2]&&numbers[index2]==numbers[index1])
			return MinInorder(numbers,index1,index2);
		if(numbers[index1]>=numbers[indexMid]){
			index1=indexMid;
		}else if(numbers[indexMid]<=numbers[index2]){
			index2=indexMid;
		}
	}
	return numbers[indexMid];
}



int main(void){
	int a[5]={3,4,5,1,2};
	cout<<Min(a,5)<<endl;
	return 0;
} 
