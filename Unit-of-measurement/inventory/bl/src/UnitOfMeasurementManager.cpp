#include<bl/iuom>
#include<iostream>
#include<bl/uom>
#include<bl/iuommanager>
#include<bl/uommanager>
#include<common/stringutils>
#include<dl/iuom>
#include<dl/uom>
#include<dl/daoexception>
#include<dl/iuomdao>
#include<dl/uomdao>
#include<map>
#include<forward_list>
using namespace inventory;
using namespace business_layer;
using namespace stringutils;
bool UnitOfMeasurementTitleComparator::operator()(string *left,string *right)
{
return compareStringIgnoreCase(left->c_str(), right->c_str())<0;
}
UnitOfMeasurementManager::DataModel UnitOfMeasurementManager::dataModel;
UnitOfMeasurementManager::DataModel::DataModel()
{
populateDataStructure();
}
UnitOfMeasurementManager::DataModel::~DataModel()
{
/*
Iterate any one map, and release al bl UnitOfMeasurement objects
clear both maps
*/
}

void UnitOfMeasurementManager::DataModel::populateDataStructure()
{
forward_list<inventory::data_layer::abc::IUnitOfMeasurement *> *dlUnitOfMeasurements;
inventory::data_layer::UnitOfMeasurementDAO unitOfMeasurementDAO;
try
{
dlUnitOfMeasurements=unitOfMeasurementDAO.getAll();
inventory::data_layer::abc::IUnitOfMeasurement *dlUnitOfMeasurement;
_UnitOfMeasurement *blUnitOfMeasurement;
forward_list<inventory::data_layer::abc::IUnitOfMeasurement *>::iterator i;
int code;
string *title;
for(i=dlUnitOfMeasurements->begin(); i!=dlUnitOfMeasurements->end(); ++i)
{
dlUnitOfMeasurement=*i;
code=dlUnitOfMeasurement->getCode();
title = new string(dlUnitOfMeasurement->getTitle());
blUnitOfMeasurement= new _UnitOfMeasurement;
blUnitOfMeasurement->code=code;
blUnitOfMeasurement->title=title;
dataModel.codeWiseMap.insert(pair<int,_UnitOfMeasurement *>(code,blUnitOfMeasurement));
dataModel.titleWiseMap.insert(pair<string *,_UnitOfMeasurement *>(title,blUnitOfMeasurement));
delete dlUnitOfMeasurement;
}
dlUnitOfMeasurements->clear();
delete dlUnitOfMeasurements;
}
catch(inventory::data_layer::DAOException &daoException)
{
//nothing needed to write in here..
}
}

UnitOfMeasurementManager::UnitOfMeasurementManager()
{
}

void UnitOfMeasurementManager::updateUnitOfMeasurement(abc::IUnitOfMeasurement *unitOfMeasurement)
{
}

void UnitOfMeasurementManager::addUnitOfMeasurement(abc::IUnitOfMeasurement *unitOfMeasurement)
{
BLException blException;
if(unitOfMeasurement==NULL)
{
blException.setGenericException("Unit of measurement required, NULL encountered");
throw blException;
}
int code=unitOfMeasurement->getCode();
string title=unitOfMeasurement->getTitle();
if(code!=0)
{
blException.addPropertyException("code","Code should be zero");
}
if(title.length()==0)
{
blException.addPropertyException("title","Title required");
}
if(title.length()>50)
{
blException.addPropertyException("title","Length of title should not exceed more than 50 characters");
}
if(blException.hasExceptions())
{
throw blException;
}
map<string *,_UnitOfMeasurement *>::iterator i;
i=dataModel.titleWiseMap.find(&title);
if(i!=dataModel.titleWiseMap.end())
{
blException.addPropertyException("title","Given title already Exists");
throw blException;
}
inventory::data_layer::UnitOfMeasurementDAO unitOfMeasurementDAO;
try
{
inventory::data_layer::abc::IUnitOfMeasurement *dlUnitOfMeasurement;
dlUnitOfMeasurement = new inventory::data_layer::UnitOfMeasurement;
dlUnitOfMeasurement->setCode(0);
dlUnitOfMeasurement->setTitle(title);
unitOfMeasurementDAO.add(dlUnitOfMeasurement);
unitOfMeasurement->setCode(dlUnitOfMeasurement->getCode());
delete dlUnitOfMeasurement;
string *t= new string(title);
_UnitOfMeasurement *blUnitOfMeasurement;
blUnitOfMeasurement=new _UnitOfMeasurement;
blUnitOfMeasurement->code=code;
blUnitOfMeasurement->title=t;
dataModel.codeWiseMap.insert(pair<int,_UnitOfMeasurement *>(code,blUnitOfMeasurement));
dataModel.titleWiseMap.insert(pair<string *,_UnitOfMeasurement *>(t,blUnitOfMeasurement));
}
catch(inventory::data_layer::DAOException daoException)
{
BLException blException;
blException.setGenericException(string(daoException.what()));
throw blException;
}
}

void UnitOfMeasurementManager::removeUnitOfMeasurementByCode(int code)
{
}

void UnitOfMeasurementManager::removeUnitOfMeasurementByTitle(string &title)
{
}


abc::IUnitOfMeasurement * UnitOfMeasurementManager::getUnitOfMeasurementByCode(int code)
{
abc::IUnitOfMeasurement *uom;
return uom;
}

abc::IUnitOfMeasurement * UnitOfMeasurementManager::getUnitOfMeasurementByTitle(string &title)
{
abc::IUnitOfMeasurement *uom;
return uom;
}

forward_list<abc::IUnitOfMeasurement *> UnitOfMeasurementManager::getUnitOfMeasurements()
{
forward_list<abc::IUnitOfMeasurement *> uom;
return uom;
}

int UnitOfMeasurementManager::unitOfMeasurementCodeExists(int code)
{
return 0;
}

int UnitOfMeasurementManager::unitOfMeasurementTitleExists(string &title)
{
return 0;
}

int UnitOfMeasurementManager::getUnitOfMeasurementCount()
{
return 0;
}

