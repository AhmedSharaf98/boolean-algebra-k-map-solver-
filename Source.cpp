#include <iostream>
#include <string>
#include "Colors.h"
#include "k_map.h"

using namespace std;
int main() {
	cout << termcolor::on_cyan << "KMAP 3 Variables\nAhmed Sharaf - Alaa Mahmoud\n" << termcolor::on_grey;
	kmap k_map;
	while (true) {
		k_map.requestInput();
		cout << termcolor::on_red << "The Initial K-Map Is\n" << termcolor::on_grey;
		k_map.print();
		k_map.solve();
		cout << termcolor::on_blue << "F = " << k_map.getExpression() << endl << termcolor::on_grey;
		cout << "Press N for New Test, and any other key for terminating\n";
		char decision; cin >> decision;
		if (tolower(decision) != 'n') break;
		k_map.reset();
		cin.ignore();
	}
	system("pause");
	return 0;
}