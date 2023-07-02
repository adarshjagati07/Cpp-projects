#include<iostream>
#include<bl/uom>
#include<bl/uommanager>
using namespace inventory;
using namespace business_layer;
int main()
{
UnitOfMeasurement uom;
uom.setCode(0);
string title;
cout<<"Enter Unit Of Measurement : ";
cin>>title;
uom.setTitle(title);
UnitOfMeasurementManager manager;
try
{
manager.addUnitOfMeasurement(&uom);
cout<<title<<" added."<<endl;
}catch(BLException blException)
{
if(blException.hasGenericException())
{
cout<<blException.getGenericException()<<endl;
}
if(blException.hasPropertyException("code"))
{
cout<<blException.getPropertyException("code")<<endl;
}
if(blException.hasPropertyException("title"))
{
cout<<blException.getPropertyException("title")<<endl;
}
}
return 0;
}