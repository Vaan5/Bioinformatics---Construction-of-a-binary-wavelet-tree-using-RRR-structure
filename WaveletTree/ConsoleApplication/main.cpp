#include <iostream>
#include <string>
#include "..\WaveletTree\RRR.h"
#include <bitset>
#include "../WaveletTree/WaveletTree.h"
using namespace std;

int main() {
	/*RRR rrr(string("0111"));
	cout << rrr.rank0(0) << endl;
	cout << rrr.rank0(1) << endl;
	cout << rrr.rank0(2) << endl;
	cout << rrr.rank0(3) << endl;
	cout << rrr.rank1(0) << endl;
	cout << rrr.rank1(1) << endl;
	cout << rrr.rank1(2) << endl;
	cout << rrr.rank1(3) << endl;*/

	string input = "Hajro i Denis imaju 100 bodova!";
	WaveletTree tree(input);

	cout << tree.rank('a', 20) << endl;
	cout << tree.rank('a', 29) << endl;
	cout << tree.rank('a', 28) << endl;


	cout << tree.rank('!', 30) << endl;
	cout << tree.rank('!', 29) << endl;
	cout << tree.rank('!', 5) << endl;
	cout << tree.rank('!', 0) << endl;

	/////////////////////////////////////
	// TODO
	// rank za nepostojece indekse i slova, indekse van intervala itd...
	/////////////////////////////////////


}