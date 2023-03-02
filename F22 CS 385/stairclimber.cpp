/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Arjun Koshal
 * Date        : 10/20/2022
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

// Global variables to assist with get ways function
vector<vector<int>> ways;
vector<int> num;

vector< vector<int> > get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.
    if (num_stairs <= 0){
        // Adding what we have to the list, saved by out global variable
        ways.push_back(num);
    } else {
        for (int i = 1; i < 4; i++){
            if (num_stairs >= i){
                // Putting the number first
                num.push_back(i);
                // Getting the next iterations
                get_ways(num_stairs - i);
                // Bringing it back to where we were
                num.pop_back();
            }
        }
    }
    return ways;
}


int get_digits(int num){
    // Added function (from sieve.cpp) helps create cleaner outputs.
    int digits = 0;
    while (num > 0){
        num /= 10;
        digits++;
    }
    return digits;
}

void display_ways(const vector< vector<int> > &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.

    if (ways.size() == 1){
        cout << "1 way to climb 1 stair." << endl;
    } 
    else {
        string s = "";
        s += to_string(ways.size());
        s += " ways to climb ";
        s += to_string(ways[0].size());
        s += " stairs.";
        cout << s << endl;
    }
    for (int i = 0; i < (int)ways.size(); i++){
        string str = "";

        // Aligns the digit outputs properly
        int digits = get_digits((int)ways.size());
        for (int j = get_digits(i + 1); j < digits; j++){
            str += " ";
        }
        
        str += to_string(i+1);
        str += ". [";
        for (int j = 0; j < (int)ways[i].size(); j++){
            str += "";
            str += to_string(ways[i][j]);
            if (j != (int)ways[i].size() - 1){
                str += ", ";
            }
        }
        str += "]";
        cout << str << endl;
    }
}

int main(int argc, char * const argv[]) {
    int num;
    istringstream iss;

    if(argc < 2){
        cout << "Usage: ./stairclimber <number of stairs>" << endl;
        return 1;
    }
    if(argc > 2){
        cout << "Usage: ./stairclimber <number of stairs>" <<endl;
        return 1;
    }

    iss.str(argv[1]);
    if(!(iss >> num) || num <= 0){
        cout << "Error: Number of stairs must be a positive integer." <<endl;
        return 1;
    }

    display_ways(get_ways(num));

    return 0;
}