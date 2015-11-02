#include <iostream>
#include "RRRTable.h"
#include <bitset>

using namespace std;

int main() {
	RRRTable::getInstance().createTable(5);

	for (int i = 0; i < RRRTable::getInstance().getTable().size(); i++) {
		class_t cls = RRRTable::getInstance().getTable()[i];
		for (int j = 0; j < cls.size(); j++) {
			element_t el = cls[j];
			bitset<5> y(el.first);
			cout << i << "-" << j << "-" << y;
			for (int k = 0; k < el.second.size(); k++) {
				cout << " " << el.second[k];
			}
			cout << endl;
		}
	}

	cout << "P" << endl;
	cout << RRRTable::getInstance().getOffset(1, 4, 5) << endl;
	cout << "Z" << endl;
}