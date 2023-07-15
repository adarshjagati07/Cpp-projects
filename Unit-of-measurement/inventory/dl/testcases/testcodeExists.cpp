#include <iostream>
#include <uomdao>
#include <iuom>
#include <uom>
#include <forward_list>
using namespace inventory;
using namespace data_layer;
int main()
{
    UnitOfMeasurementDAO unitOfMeasurementDAO;

    int code;
    cout << "Enter code: ";
    cin >> code;
    int check;
    check = unitOfMeasurementDAO.codeExists(code);
    if (check == true)
    {
        cout << "Code " << code << " already exists" << endl;
    }
    else
    {
        cout << "Code " << code << " not found" << endl;
    }

    return 0;
}