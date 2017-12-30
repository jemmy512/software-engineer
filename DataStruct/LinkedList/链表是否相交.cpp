#include<iostream>

using namespace std;

NTnode* findFirstCommentNode(BTnode* head1,BTnode* head2)
{
    BTnode* p1=head1;
    BTnode* p2=head2;
    while(p1!=p2){
        p1= (p1==NULL?head2:p1=p1->next);
        p2= (p2==NULL?head1:p2=p2->next);
    }
    return p1;
}

int main(void)
{

    return 0;
}
