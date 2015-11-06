#include <iostream>
#include <string>
#include "RRRTable.h"
#include "RRR.h"
#include <bitset>

using namespace std;

int main() {
	/*RRRTable::getInstance().createTable(5);

	for (unsigned int i = 0; i < RRRTable::getInstance().getTable().size(); i++) {
		class_t cls = RRRTable::getInstance().getTable()[i];
		for (unsigned int j = 0; j < cls.size(); j++) {
			element_t el = cls[j];
			bitset<5> y(el.first);
			cout << i << "-" << j << "-" << y;
			for (unsigned int k = 0; k < el.second.size(); k++) {
				cout << " " << el.second[k];
			}
			cout << endl;
		}
	}

	cout << "P" << endl;
	cout << RRRTable::getInstance().getOffset(1, 4, 5) << endl;
	cout << "Z" << endl;*/

	RRR rrr(string("001010011010101101000001001010011011000101101101011"));
	cout << "jkjk" << endl;

	cout << rrr.rank1(29) << endl;
	cout << rrr.rank0(29) << endl;

	cout << rrr.rank1(0) << endl;
	cout << rrr.rank0(0) << endl;

	cout << rrr.rank1(1) << endl;
	cout << rrr.rank0(1) << endl;

	cout << rrr.rank1(50) << endl;
	cout << rrr.rank0(50) << endl;
}