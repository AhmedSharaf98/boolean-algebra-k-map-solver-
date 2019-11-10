#include "k_map.h"
#include <iostream>
#include "Colors.h"
using namespace std;

string kmap::getExpression() {
	if (output == "") {
		if (k_map[0][0]) output += '1';
		else output += '0';
	}
	return output;
}
void kmap::checkDuplicates() {
	for (int i = 0; i <= 1; i++)
		for (int j = 0; j <= 3; j++)
			if (included[i][j % 4] > 1 && included[i][(j + 1) % 4] > 1)
				if (exclude(express(i, i, j, j + 1)))
					print(true, true, i, i, j, j + 1);
}
void kmap::solve() {
	if (!match(0, 1, 0, 3)) { //Checking 8x1
		match(0, 0, 0, 3); // 4x1 First row
		match(1, 1, 0, 3); // 4x1 Second Row
		for (int j = 0; j <= 3; j++)//Checks 2x2 4 times with offsets 
			match(0, 1, j, j + 1);
		for (int j = 0; j <= 3; j++) { 
			match(0, 0, j, j + 1);
			match(1, 1, j, j + 1);
			match(0, 1, j, j);
		}
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 4; j++)
				if (!included[i][j] && k_map[i][j]) match(i, i, j, j);
	}
	checkDuplicates();
}

bool kmap::exclude(std::string term) {
	size_t i = output.find(term);
	if (i != string::npos) {
		cout << endl << termcolor::on_magenta << "Duplicate Term " << term << termcolor::on_grey << endl;
		if (i) output.erase(i - 3, term.size() + 3);
		else output.erase(i, term.size() + 3);
		return true;
	}
	return false;
}
void kmap::include(int s_i, int e_i, int s_j, int e_j) {
	if (step != 1) output += " + ";
	output += express(s_i, e_i, s_j, e_j);
	cout << termcolor::on_red << "The K-Map After Inclusion Number " << step++ << termcolor::on_grey << endl;
	print(true, false, s_i, e_i, s_j, e_j);
	for (int i = s_i; i <= e_i; i++)
		for (int j = s_j; j <= e_j; j++)
			included[i][j % 4]++;
}

bool kmap::unique(int s_i, int e_i, int s_j, int e_j) {
	for (int i = s_i; i <= e_i; i++)
		for (int j = s_j; j <= e_j; j++)
			if (!(included[i][j % 4])) return true;
	return false;
}

string kmap::express(int s_i, int e_i, int s_j, int e_j) {
	string term = "";
	if (!(e_i - s_i)) {
		term += 'A';
		if (!e_i) term += "\'";
	}
	if (e_j - s_j != 3) {
		if (e_j - s_j)
			switch (e_j % 4) {
			case 0: term += "C'"; break;
			case 1: term += "B'"; break;
			case 2: term += 'C'; break;
			case 3: term += 'B'; break;
			}
		else
			switch (e_j % 4) {
			case 0: term += "B'C'"; break;
			case 1: term += "B'C"; break;
			case 2: term += "BC"; break;
			case 3: term += "BC'"; break;
			}
	}
	return term;
}
bool kmap::match(int s_i, int e_i, int s_j, int e_j) {
	if (!unique(s_i, e_i, s_j, e_j)) return false;
	for (int i = s_i; i <= e_i; i++)
		for (int j = s_j; j <= e_j; j++)
			if (!(k_map[i][j % 4])) return false;

	include(s_i, e_i, s_j, e_j);
	return true;
}
void kmap::print(bool colorize, bool exclude, int _si, int _ei, int _sj, int _ej) {
	bool swapped = false;
	if (_ej == 4) {
		swapped = true;
		_sj = 0;
		_ej = 3;
	}
	cout << "    " << termcolor::green << "B'C' " << "B'C " << "BC " << "BC' " << termcolor::white << endl;

	cout << "   ";
	//char(196) is the ASCI Representation for that sympol - we use it to draw array borders
	//char(179) is the ASCI Representation for that sympol | we use it to draw array borders
	for (int j = 0; j < 4; j++) cout << " " << char(196) << char(196) << char(196); cout << endl;

	for (int i = 0; i < 2; i++) {
		if (i == 0) cout << termcolor::green << " A'";
		else cout << termcolor::green << " A ";

		for (int j = 0; j < 4; j++) {
			if (colorize && i >= _si && i <= _ei && j >= _sj && j <= _ej) {
				if (!swapped)cout << termcolor::white << char(179) << ((exclude) ? termcolor::on_red : termcolor::on_green) << " " << k_map[i][j] << " " << termcolor::on_grey;
				else
					if (j == 1 || j == 2) {
						if (k_map[i][j]) cout << termcolor::white << char(179) << " " << termcolor::cyan << k_map[i][j] << " ";
						else cout << termcolor::white << char(179) << " " << termcolor::yellow << k_map[i][j] << " ";
					}
					else
						cout << termcolor::white << char(179) << ((exclude) ? termcolor::on_red : termcolor::on_green) << " " << k_map[i][j] << " " << termcolor::on_grey;
			}
			else if (k_map[i][j]) cout << termcolor::white << char(179) << " " << termcolor::cyan << k_map[i][j] << " ";
			else cout << termcolor::white << char(179) << " " << termcolor::yellow << k_map[i][j] << " ";
		}
		cout << termcolor::white << char(179) << endl;

		cout << "   ";
		for (int j = 0; j < 4; j++) cout << " " << char(196) << char(196) << char(196); cout << endl;
	}
}

bool kmap::validate_input(string s) {
	if (s[0] == ',') return false;
	for (int i = 1; i < s.length(); i++) {
		if (s[i] != ' ' && s[i] != ',' && s[i] != '/t' && !(s[i] >= '0' && s[i] <= '7'))
			return false;
	}
	return true;
}
void kmap::requestInput() {
	bool valid = false;
	while (!valid)
	{
		valid = true;
		cout << "Please enter the midterms separated by a comma (ex. 1, 3, 4, 5)" << endl;
		string minterms;
		getline(cin, minterms);
		if (!validate_input(minterms)) {
			cout << "Invalid Input!!" << endl;
			valid = false;
			continue;
		}
		int tmp;
		while (minterms.length() != 0)
		{
			if (minterms.find(',') != string::npos) {
				tmp = atoi(minterms.substr(0, minterms.find(',')).c_str());
				minterms.erase(0, minterms.find(',') + 1);
			}
			else {
				tmp = atoi(minterms.c_str());
				minterms = "";
			}
			if (tmp < 0 || tmp > 7) {
				cout << "Invalid Input!!" << endl;
				valid = false;
				break;
			}
			if (tmp % 4 == 2) tmp++;
			else if (tmp % 4 == 3) tmp--;
			k_map[tmp / 4][tmp % 4] = 1;
		}
	}
}
void kmap::reset() {
	for (int i = 0; i <= 1; i++)
		for (int j = 0; j <= 3; j++) {
			k_map[i][j] = false;
			included[i][j] = 0;
			output = "";
			step = 1;
		}
}