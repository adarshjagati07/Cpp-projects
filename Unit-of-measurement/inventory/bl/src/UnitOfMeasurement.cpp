#include <bl/iuom>
#include <bl/uom>
#include <iostream>
using namespace std;
using namespace inventory;
using namespace business_layer;

UnitOfMeasurement::UnitOfMeasurement()
{
    this->code = 0;
    this->title = "";
}
UnitOfMeasurement::UnitOfMeasurement(int code, string title)
{
    this->code = code;
    this->title = title;
}
UnitOfMeasurement::UnitOfMeasurement(const UnitOfMeasurement &other)
{
    this->code = other.code;
    this->title = other.title;
}
UnitOfMeasurement::~UnitOfMeasurement()
{
    // do nothing
}
void UnitOfMeasurement::setCode(int code)
{
    this->code = code;
}
int UnitOfMeasurement::getCode() const
{
    return this->code;
}
void UnitOfMeasurement::setTitle(string title)
{
    this->title = title;
}
string UnitOfMeasurement::getTitle() const
{
    return this->title;
}
abc::IUnitOfMeasurement &UnitOfMeasurement::operator=(const IUnitOfMeasurement &other)
{
    this->code = getCode();
    this->title = getTitle();
    return *this;
}
int UnitOfMeasurement::operator==(const IUnitOfMeasurement &other)
{
    return this->code == other.getCode();
}
int UnitOfMeasurement::operator!=(const IUnitOfMeasurement &other)
{
    return this->code != other.getCode();
}
int UnitOfMeasurement::operator<(const IUnitOfMeasurement &other)
{
    return this->code < other.getCode();
}
int UnitOfMeasurement::operator>(const IUnitOfMeasurement &other)
{
    return this->code > other.getCode();
}
int UnitOfMeasurement::operator<=(const IUnitOfMeasurement &other)
{
    return this->code <= other.getCode();
}
int UnitOfMeasurement::operator>=(const IUnitOfMeasurement &other)
{
    return this->code >= other.getCode();
}
