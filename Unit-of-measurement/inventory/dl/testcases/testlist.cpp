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
forward_list<abc::IUnitOfMeasurement *> *list;
try
{
list=unitOfMeasurementDAO.getAll();
abc::IUnitOfMeasurement *unitOfMeasurement;
forward_list<abc::IUnitOfMeasurement *>::iterator i;
for(i=list->begin();i!=list->end();++i)
{
unitOfMeasurement= *i;
cout<<"Code : "<<unitOfMeasurement->getCode()<<", Title: "<<unitOfMeasurement->getTitle()<<endl;
}
}catch(DAOException daoException)
{
cout<<daoException.what();
}
return 0;
}