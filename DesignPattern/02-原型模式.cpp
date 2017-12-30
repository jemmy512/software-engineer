#include<iostream>
using namespace std;
//接口
class CPrototype
{
    public:
        int m_counter;
    public:
        CPrototype():m_counter(10){
            cout<<"CProtoType(){}"<<endl;
        }

        virtual ~CPrototype(){}

        virtual CPrototype* Clone() = 0;
};

//实现
class CConcretePrototype : public CPrototype
{
//    private:
//        int m_counter;
    public:
    CConcretePrototype(){}

    //拷贝构造函数
    CConcretePrototype(const CConcretePrototype& rhs)
    {
        m_counter = rhs.m_counter+1;
    }

    //复制自身
    CPrototype* Clone(){
        //调用拷贝构造函数
        return new CConcretePrototype(*this);
    }
    ~CConcretePrototype(){}


};

int main(void)
{
    //生成对像
    CPrototype* conProA = new CConcretePrototype();
    //复制自身
    CPrototype* conProB = conProA->Clone();

    cout<<conProA->m_counter<<endl;
    cout<<conProB->m_counter<<endl;
    delete conProA; conProA=NULL;
    delete conProB; conProB=NULL;

    return 0;
}
