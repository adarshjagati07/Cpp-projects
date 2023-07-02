#include<iostream>
#include<uom>
#include<iuom>
#include<uomdao>
using namespace std;
using namespace inventory;
using namespace data_layer;

int main()
{
UnitOfMeasurementDAO unitOfMeasurementDAO;
cout<<"Total number of records added are: "<<unitOfMeasurementDAO.getCount()<<endl;
return 0;
}