#include <iostream>
#include <numeric>
#include <array>

int sequential_search( int search_array[], int val, int begin, int end ){
    int i = 0;
    for ( i = begin; i <=end; ++i){
        if( val == search_array[i]){ return i; }
    }
    
    return -1;
}

int main(){

    const auto SIZE = 100;
    int a[SIZE];

    srand(1234);
    for( auto e : a) {
        e = rand();
    }

    auto found = sequential_search(a, a[SIZE/2], 0, SIZE);

    std::cout << "Searching for: " << a[SIZE/2] << std::endl;
    std::cout << "Found: " << a[found] << " @ a[" << found << "]" << std::endl;

    return 0;
}