#include <bl/uom>
#include <bl/iuom>
#include <bl/uommanager>
#include <bl/iuommanager>
#include <common/stringutils>
#include <dl/uom>
#include <dl/iuom>
#include <dl/uomdao>
#include <dl/iuomdao>
#include <dl/daoexception>
#include <map>
#include <forward_list>
using namespace inventory;
using namespace business_layer;
using namespace stringutils;
bool UnitOfMeasurementTitleComparator::operator()(string *left, string *right)
{
    return compareStringIgnoreCase(left->c_str(), right->c_str()) < 0;
}
UnitOfMeasurementManager::DataModel UnitOfMeasurementManager::dataModel; // as static property hence declaring outside class
UnitOfMeasurementManager::DataModel::DataModel()
{
    populateDataStructure();
}
UnitOfMeasurementManager::DataModel::~DataModel()
{
    // code of release all bl UnitOfMeasurement objects and clear both maps
}

void UnitOfMeasurementManager::DataModel::populateDataStructure()
{
    forward_list<inventory::data_layer::abc::IUnitOfMeasurement *> *dlUnitOfMeasurements;
    inventory::data_layer::UnitOfMeasurementDAO unitOfMeasurementDAO;
    try
    {
        dlUnitOfMeasurements = unitOfMeasurementDAO.getAll();
        inventory::data_layer::abc::IUnitOfMeasurement *dlUnitOfMeasurement;
        _UnitOfMeasurement *blUnitOfMeasurement;
        forward_list<inventory::data_layer::abc::IUnitOfMeasurement *>::iterator i;
        int code;
        string *title;
        for (i = dlUnitOfMeasurements->begin(); i != dlUnitOfMeasurements->end(); ++i)
        {
            dlUnitOfMeasurement = *i;
            code = dlUnitOfMeasurement->getCode();
            title = new string(dlUnitOfMeasurement->getTitle());
            blUnitOfMeasurement = new _UnitOfMeasurement;
            blUnitOfMeasurement->code = code;
            blUnitOfMeasurement->title = title;
            dataModel.codeWiseMap.insert(pair<int, _UnitOfMeasurement *>(code, blUnitOfMeasurement));
            dataModel.titleWiseMap.insert(pair<string *, _UnitOfMeasurement *>(title, blUnitOfMeasurement));
            delete dlUnitOfMeasurement;
        }
        dlUnitOfMeasurements->clear();
        delete dlUnitOfMeasurements;
    }
    catch (inventory::data_layer::DAOException &daoException)
    {
        // do nothing
    }
}

UnitOfMeasurementManager::UnitOfMeasurementManager()
{
}

void UnitOfMeasurementManager::addUnitOfMeasurement(abc::IUnitOfMeasurement *unitOfMeasurement) throw(BLException)
{
    BLException blException;
    if (unitOfMeasurement == NULL)
    {
        blException.setGenericException("Unit Of Measurement required, NULL Encountered");
        throw blException;
    }
    int code = unitOfMeasurement->getCode();
    string title = unitOfMeasurement->getTitle();
    if (code != 0)
    {
        blException.addPropertyException("code", "Code should be zero");
    }
    if (title.length() == 0)
    {
        blException.addPropertyException("title", "Title required");
    }
    if (title.length() > 50)
    {
        blException.addPropertyException("title", "Title should not be more than 50 characters");
    }
    if (blException.hasExceptions())
    {
        throw blException;
    }
    map<string *, _UnitOfMeasurement *>::iterator i;
    i = dataModel.titleWiseMap.find(&title); // checking existance of title
    if (i != dataModel.titleWiseMap.end())
    {
        blException.addPropertyException("title", "Given title exists.");
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
        string *t = new string(title);
        _UnitOfMeasurement *blUnitOfMeasurement;
        blUnitOfMeasurement = new _UnitOfMeasurement;
        blUnitOfMeasurement->code = code;
        blUnitOfMeasurement->title = t;
        dataModel.codeWiseMap.insert(pair<int, _UnitOfMeasurement *>(code, blUnitOfMeasurement));
        dataModel.titleWiseMap.insert(pair<string *, _UnitOfMeasurement *>(t, blUnitOfMeasurement));
    }
    catch (inventory::data_layer::DAOException daoException)
    {
        BLException blException;
        blException.setGenericException(string(daoException.what()));
        throw blException;
    }
}

void UnitOfMeasurementManager::updateUnitOfMeasurement(abc::IUnitOfMeasurement *unitOfMeasurement) throw(BLException)
{
}
void UnitOfMeasurementManager::removeUnitOfMeasurementByCode(int code) throw(BLException)
{
}
void UnitOfMeasurementManager::removeUnitOfMeasurementByTitle(string &title) throw(BLException)
{
}
abc::IUnitOfMeasurement *UnitOfMeasurementManager::getUnitOfMeasurementByCode(int code) throw(BLException)
{
}
abc::IUnitOfMeasurement *UnitOfMeasurementManager::getUnitOfMeasurementByTitle(string &title) throw(BLException)
{
}
forward_list<abc::IUnitOfMeasurement *> *UnitOfMeasurementManager::getUnitOfMeasurements() throw(BLException)
{
    /*
    Iterate on map(2 of any)
    Create a forward_list of UnitOfMeasurement *
    */
    map<string *, _UnitOfMeasurement *>::iterator i = dataModel.titleWiseMap.begin();
    _UnitOfMeasurement *unitOfMeasurement;
    abc::IUnitOfMeasurement *blUnitOfMeasurement;
    forward_list<abc::IUnitOfMeasurement *> *unitOfMeasurements;
    unitOfMeasurements = new forward_list<abc::IUnitOfMeasurement *>;
    forward_list<abc::IUnitOfMeasurement *>::iterator listi = unitOfMeasurements->before_begin();
    while (i != dataModel.titleWiseMap.end())
    {
        unitOfMeasurement = i->second;
        blUnitOfMeasurement = new UnitOfMeasurement;
        blUnitOfMeasurement->setCode(unitOfMeasurement->code);
        blUnitOfMeasurement->setTitle(*(unitOfMeasurement->title));
        listi = unitOfMeasurements->insert_after(listi, blUnitOfMeasurement);
        ++i;
    }
    return unitOfMeasurements;
}
int UnitOfMeasurementManager::unitOfMeasurementCodeExists(int code) throw(BLException)
{
}
string UnitOfMeasurementManager::unitOfMeasurementTitleExists(string &title) throw(BLException)
{
}
int UnitOfMeasurementManager::getUnitOfMeasurementCount() throw(BLException)
{
}
