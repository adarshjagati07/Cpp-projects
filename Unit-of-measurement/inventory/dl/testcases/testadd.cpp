#include<iostream>
#include<uomdao>
#include<uom>
using namespace inventory;
using namespace data_layer;
int main()
{
UnitOfMeasurement m;
string title;
cout<<"Enter the Unit of measurement : ";
cin>>title;
m.setTitle(title);
UnitOfMeasurementDAO unitOfMeasurementDAO;
try
{
unitOfMeasurementDAO.add(&m);
cout<<"Unit of measurement added with code as: "<<m.getCode();
}catch(DAOException daoException)
{
cout<<daoException.what();
}
return 0;

}
