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
try
{
string title;
cout<<"Enter title: ";
cin>>title;
abc::IUnitOfMeasurement *unitOfMeasurement;
unitOfMeasurement=unitOfMeasurementDAO.getByTitle(title);
cout<<"Code : "<<unitOfMeasurement->getCode()<<", Title: "<<unitOfMeasurement->getTitle()<<endl;
}catch(DAOException daoException)
{
cout<<daoException.what();
}
return 0;
}