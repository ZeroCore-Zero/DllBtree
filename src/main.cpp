#include<iostream>
#include "sort.h"
#include "btreeclass.h"
#include "uuid.h"
using std::cin,std::cout,std::endl;
using ZC::Btree;
using ZC::generate_uuid;

int main()
{
    Btree ori;
    //输出初始B树
    cout<<"start:"<<endl;
    ori.printTree();

    int n;
    cin>>n;

    cout<<"In loop."<<endl<<endl;
    for(int i=1;i<=n;i++)
    {
        cout<<"Loop of "<<i<<" start."<<endl;

        cout<<"Insert "<<i<<endl;
        ori.insert(i);
        cout<<endl
            <<"Print "<<i<<endl;
        ori.printTree();

        cout<<"Loop of "<<i<<" end."<<endl<<endl;
    }
    cout<<endl<<"Out loop."<<endl;

    //输出最终B树
    cout<<endl<<"Final:"<<endl;
    ori.printTree();
    return 0;
}