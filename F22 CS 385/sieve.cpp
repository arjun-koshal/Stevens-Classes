/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Arjun Koshal
 * Date        : 10/07/2022
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
}

void PrimesSieve::display_primes() const {
    // TODO: write code to display the primes in the format specified in the
    // requirements document.
    cout << endl << "Number of primes found: " << num_primes() <<endl;
    cout << "Primes up to " << limit_ << ":" <<endl;
    
    const int max_prime_width = num_digits(max_prime_), 
    primes_per_row = floor(80 / (max_prime_width + 1));
  
    int primes_row = 0;

    if (num_primes_ <= primes_per_row) {
        for (int i = 2; i <= limit_; i++) {
            if (is_prime_[i] && (max_prime_ == i)) {
                cout << i << endl;
            } 
            else if (is_prime_[i]) {
                cout << i << " ";
            }
        }
    } 
    else {
        for (int i = 2; i <= limit_; i++) {
            if (((primes_row == primes_per_row - 1) && is_prime_[i]) || (max_prime_ == i)) {
                cout << right << setw(max_prime_width) << i;
                primes_row++;
            } 
            if ((primes_per_row - primes_row == 0) && (primes_row > 0)) {
                cout << endl;
                primes_row = 0;
            }
            else if ((max_prime_ != i) && is_prime_[i]) {
                cout << right << setw(max_prime_width) << i << " ";
                primes_row++;
            }
        }
    }
}

int PrimesSieve::count_num_primes() const {
    // TODO: write code to count the number of primes found
    int primes = 0;
    for (int i = 2; i <= limit_ ; i++){
        if (is_prime_[i]) {
            primes++;
        }
    }
    return primes;
}

void PrimesSieve::sieve() {
    // TODO: write sieve algorithm
    for (int i = 2; i <= limit_; i++) {
        is_prime_[i] = true;
  }

    for (int i = 2; i <= sqrt(limit_); i++) {
        if (is_prime_[i]) {
            for (int j = i * i; j <= limit_; j += i) {
                is_prime_[j] = false;
            }
        }
    }

    for (int i = 2; i <= limit_ ; i++) {
        if (is_prime_[i]) {
            max_prime_ = i;
        }
    }
    num_primes_ = count_num_primes();
}

int PrimesSieve::num_digits(int num) {
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.
    int digits = 0;
    while (num > 0) {
        num = num / 10;
        digits++;
    }
    return digits;
}

int main() {
    cout << "**************************** " << "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // TODO: write code that uses your class to produce the desired output.
    PrimesSieve PS(limit);
    PS.display_primes();

    return 0;
}