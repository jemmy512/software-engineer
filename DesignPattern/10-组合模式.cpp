/**
    将对象组合成树形结构以表示“部分-整体”的层次结构
*/

#include<iostream>
#include<string>
#include<vector>
#include<typeinfo>
using namespace std;

class Abstract{
	protected:
		string name;
	public:
		Abstract(string name="新建文件"){
			this->name=name;
		}
		virtual void getName(){
			cout<<name<<endl;
		}
		virtual Abstract *getChild();
};

class File:public Abstract{
	public:
		File(string name):Abstract(name){}
		Abstract *getChild(){
			return NULL;
		}
};

class Folder:public Abstract{
	private:
		vector<Abstract *> vec;
	public:
		Folder(string name="新建文件夹"):Abstract(name){
			this->name=name;
		}
		void add(Abstract *t){
			vec.push_back(t);
		}
		Abstract *getChild(){
			return vec;
		}
		void out(){
			this->getName();
			auto p=this->getChild();
			for(auto c:vec){
				if(p!=NULL){
					out();
				}else{
					c->getName();
				}
			}

		}
};

int main(void)
{
	Folder * Fol=new Folder("root");
	Fol->add(new File("doc_1"));
	Fol->add(new File("doc_2"));
	Fol->add(new File("doc_3"));
	Folder *Fol2=new Folder("root_1");

	Fol->add(Fol2);
	Fol2->add(new File("doc_4"));
	Fol2->add(new Folder("doc_5"));
	Fol->out();

	return 0;
}
