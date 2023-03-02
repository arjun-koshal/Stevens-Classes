/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Arjun Koshal
 * Version     : 1.0
 * Date        : 11/21/2022
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in Theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
    long count = 0;
    for(int i = 0; i < length; i++){
        for(int j = i + 1; j < length; j++){
            if(array[i] > array[j]){
                count++;
            }
        }
    }
    return count;
}

/**
 * Counts the number of inversions in an array in Theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
    // TODO
    // Hint: Use mergesort!
    int *scratch = new int [length];
    long count = mergesort(array, scratch, 0, length - 1);
    delete[] scratch;
    return count;
}

static long mergesort(int array[], int scratch[], int low, int high) {
    // TODO
    long count = 0;
    if(low < high){
        int middle = low + (high - low)/2;
        count += mergesort(array, scratch, low, middle);
        count += mergesort(array, scratch, middle + 1, high);
        long l = low;
        long h = middle + 1;
        for(int i = low; i <= high; i++){
            if(l <= middle && (h > high || array[l] <= array[h])){
                scratch[i] = array[l];
                l++;
            } else {
                scratch[i] = array[h];
                h++;
                count +=middle - l + 1;
            }
        }
        for(int i = low; i <= high; i++){
            array[i] = scratch[i];
        }
    }
    return count;
}

int main(int argc, char *argv[]) {
    // TODO: parse command-line argument
    bool slow = 0;
    if (argc > 2) {
		cerr << "Usage: ./inversioncounter [slow]" << endl;
		return 1;
	}
	if ((argv[1] != NULL) && (strcmp(argv[1], "slow") == 0)){
		slow = 1;
	}
	else if (argv[1] != NULL) {
		cerr << "Error: Unrecognized option '" << argv[1] << "'.";
		return 1;
	}

    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    // TODO: produce output
    if(values.size() > 0){
        if(slow){
            cout << "Number of inversions: " << count_inversions_slow(&values[0], values.size()) << endl;
            return 0;
        }
        else{
             cout << "Number of inversions: " << count_inversions_fast(&values[0], values.size()) << endl;
            return 0;
        }
    } else {
        cout << "Error: Sequence of integers not received." << endl;
        return 1;
    }
    return 0;
}
