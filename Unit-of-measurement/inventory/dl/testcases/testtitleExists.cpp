#include<iostream>
#include<uomdao>
#include<iuom>
#include<uom>
#include<forward_list>
using namespace inventory;
using namespace data_layer;
int main()
{
UnitOfMeasurementDAO unitOfMeasurementDAO;

string title;
cout<<"Enter Title: ";
cin>>title;
int check;
check= unitOfMeasurementDAO.titleExists(title);
if(check==true)
{
cout<<title<<" already exists"<<endl;
}
else
{
cout<<title<<" not found"<<endl;
}

return 0;
}