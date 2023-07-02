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
int code;
cout<<"Enter code: ";
cin>>code;
abc::IUnitOfMeasurement *unitOfMeasurement;
unitOfMeasurement=unitOfMeasurementDAO.getByCode(code);
cout<<"Code : "<<unitOfMeasurement->getCode()<<", Title: "<<unitOfMeasurement->getTitle()<<endl;
}catch(DAOException daoException)
{
cout<<daoException.what();
}
return 0;
}