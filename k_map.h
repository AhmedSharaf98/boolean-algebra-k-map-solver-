#pragma once
#ifndef K_MAP
#define K_MAP
#include <string>

//Project Conventions:
//s_i => intial value of i inside the loop 
//e_i => final value of i inside the loop
//s_j => intial value of j inside the loop 
//e_j => final value of j inside the loop


class kmap
{
public:
	void print(bool = false, bool = false, int = 0, int = 0, int = 0,int = 0); //Prints the KMAP(With or Without Colors)
	void requestInput();//Filling the KMap
	std::string getExpression(); //Returns the Final Expression as String 
	void solve(); //Solves the KMAP
	void reset(); // Resets the kmap for further usages
private:
	std::string output = ""; //Final Expression
	int step = 1; // Current Step (used to print the number of inclusion when printing the KMap
	bool k_map[2][4] = { { false } }; //Kmap 2D array intialized false
	int included[2][4] = { { 0 } }; //Array to check how many times every term was included
	bool unique(int s_i, int e_i, int s_j, int e_j); //Function that checks whether there is at least one term isn't included before within specific range
	void include(int s_i, int e_i, int s_j, int e_j); //Mark all terms in thatrange as included
	bool match(int s_i, int e_i, int s_j, int e_j); //Checks whether all elements in that range are 1(s)
	std::string express(int s_i, int e_i, int s_j, int e_j);// Function the converts ranges into expressions
	void checkDuplicates(); // Function that double checks whther there is duplicate elements or not
	bool exclude(std::string term); // function that excludes duplicate terms from the expression if there is any
	bool validate_input(std::string minterms); //Validates the input
};

#endif // !K_MAP
