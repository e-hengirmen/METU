#include <iostream>
#include "person.h"
#include "corporation.h"
#include "villa.h"
#include "apartment.h"
#include "office.h"

using namespace std;

int main(int argc, char const *argv[])
{
    Person per = Person("Ahmet", 5000, 10);
    Corporation corp = Corporation("ACME", 5000, "cankaya");

    Villa est1 = Villa("Villa 1", 150, &per, 2, false);
    Apartment est2 = Apartment("Apartment 1", 200, &corp, 7, 1);
    Office est3 = Office("Apartment 2", 200, NULL, 5, 0);

    per.print_info();
    est1.print_info();

    cout << "----------------------------\n";
    per.list_properties();
    corp.list_properties();
    cout << "----------------------------\n";
    per.buy(&est2, &corp);
    per.sell(&est1, &corp);
    cout << "----------------------------\n";
    per.list_properties();
    corp.list_properties();
    cout << "----------------------------\n";

    return 0;
}
