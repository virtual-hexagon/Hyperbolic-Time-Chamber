#include <iostream>
#include <numeric>
#include <array>
#include <algorithm>


// Note that Binary Search requires and ordered array!
int binary_search( int search_array[], int val, int begin, int end ){
    while(end >= 1) {
        // Compute half the range
        // Notes:
        // - notice how we ensure that the halfway index is still an int. no doubles here!
        // - integer truncation could occur here
        int halfway = (begin + end)/2;

        // Early return if our value happens to be exactly in the middle of the range
        if( val == search_array[halfway] ) { return halfway; }

        if( val < search_array[halfway] ){
            end = halfway-1;
        } else {
            begin = halfway+1;
        }

        std::cout << "halfway: " << halfway << std::endl;
    }


    return -1;
}

int main(){

    const auto SIZE = 10;
    int a[SIZE];

    // Initalized ordered array with linear increasing values
    for( auto i = 0; i <= SIZE; ++i) {
        a[i] = i;
    }

    for( auto e: a) {
        std::cout << e << ", ";
    }
    std::cout << std::endl;

    auto found = binary_search(a, a[SIZE/4], 0, SIZE);

    std::cout << std::endl;
    std::cout << "Searching for: " << a[SIZE/2] << std::endl;
    std::cout << "Found: " << a[found] << " @ a[" << found << "]" << std::endl;

    return 0;
}