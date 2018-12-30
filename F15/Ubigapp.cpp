#include "Ubigint.h"
#include <iostream>
using namespace std;
int main() {
	Ubigint u1 = 1234, u2("23561235235278957498574897");
	Ubigint u3 = 3;
	u1 += u2;
	cout << "u1 " << u1 << " ska vara 23561235235278957498576131" << endl;
	cout << "u1 + u3 " << u1 + u3 << " ska vara 23561235235278957498576134" << endl;
	cout << "u1 + 3 " << u1 + 3 << " ska vara 23561235235278957498576134" << endl;
	cout << "3 + u1 " << 3 + u1 << " ska vara 23561235235278957498576134" << endl;
	cout << "u1++ " << u1++ << " ska vara 23561235235278957498576131" << endl;
	cout << "u1 " << u1 << " men ska nu vara 23561235235278957498576132" << endl;
	cout << "++u1 " << ++u1 << " ska vara 23561235235278957498576133" << endl;
	cout << boolalpha; // Gör att boolska värden skrivs ut med ord
	cout << endl << "u1 = " << u1 << ", u2 = " << u2 << endl;
	cout << "u1 < u2? " << (u1 < u2) << " ska vara false" << endl;
	cout << "u2 < u1? " << (u2 < u1) << " ska vara true" << endl;
	cout << "u1 == u2? " << (u1 == u2) << " ska vara false" << endl;
	cout << "u1 > u2? " << (u1 > u2) << " ska vara true" << endl;
	cout << "u2 > u1? " << (u2 > u1) << " ska vara false" << endl;
	cout << "u1 != u2? " << (u1 != u2) << " ska vara true" << endl;
	cout << "u1 <= u2? " << (u1 <= u2) << " ska vara false" << endl;
	cout << "u1 >= u2? " << (u1 >= u2) << " ska vara true" << endl;
	cout << "u1 + 0.5 " << (double(u1) + 0.5) << " ska vara 2.35...*10^25" << endl;


	return 0;
}