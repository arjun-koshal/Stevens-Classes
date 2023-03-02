/******************************************************************************* 
 * Filename: gcd.cpp 
 * Author  : Arjun Koshal
 * Version : 1.0 
 * Date    :  9/9/2022
 * Description: Program that computes GCD of a number both iteratively and recrusively.
 * Pledge  :  I pledge my honor that I have abided by the Stevens Honor System
 ******************************************************************************/ 

#include <iostream>
#include <sstream>
using namespace std;

// Returns gcd of m and n iteratively
int gcd_iterative(int m, int n)
{
	m = abs(m); 
	n = abs(n);
    if (m == 0)
        return n;
    else if (n == 0)
        return m;
    while (m != n) {
        if (m > n)
            m = m - n;
        else
            n = n - m;
    }
    return m;
}
 


// Returns gcd of m and n recursively
int gcd_recursive(int m, int n) {
	m = abs(m); n = abs(n);
	if (m == 0)
	return n;
	if (n == 0)
	return m;
	else if (m == n)
	return abs(m);
	else if (m > n)
	return gcd_recursive(m-n, n);
	else return gcd_recursive(m, n-m);
}


int main(int argc, char* argv[]) {
	int m, n;
	istringstream iss; // input string stream variable

	if(argc != 3) {
		cerr << "Usage: " << argv[0] << " <integer m> <integer n>" << endl;
		return 1;
	}
	iss.str(argv[1]);
	if(!(iss >> m)) { // Read one integer from iss and check for failure too.
		cerr << "Error: The first argument is not a valid integer." << endl;
		return 1;
	}
	iss.clear(); // Remember to clear iss before using it with another string!
	iss.str(argv[2]);
	if(!(iss >> n)) {
		cerr << "Error: The second argument is not a valid integer." << endl;
		return 1;
	}
	cout<<"Iterative: gcd("<< m <<", "<< n <<") = "<< gcd_iterative(m, n) << endl;
	cout<<"Recursive: gcd("<< m <<", "<< n <<") = "<< gcd_recursive(m, n) << endl;
	return 0;
}