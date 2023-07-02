#include<iostream>
#include<uomdao>
#include<uom>
using namespace inventory;
using namespace data_layer;
int main()
{
int code;
string title;
cout<<"Enter code : ";
cin>>code;
UnitOfMeasurementDAO unitOfMeasurementDAO;
try
{
unitOfMeasurementDAO.remove(code);
cout<<"Unit of measurement Deleted."<<endl;
}catch(DAOException daoException)
{
cout<<daoException.what();
}
return 0;
}
