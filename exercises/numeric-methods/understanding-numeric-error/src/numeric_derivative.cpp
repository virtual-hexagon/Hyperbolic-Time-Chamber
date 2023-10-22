#include <array>     //std::array
#include <algorithm> //std::for_each
#include <iostream>  //std::{cout, ostream_iterator}
#include <numeric>   //std::iota
#include <ranges>    //std::{ranges, views}


// Define a function that we want to examine
// Notes:
// - The function we inspect for this exercise must have a 'True' analytic solution
//   so we can measure the accuracy of our numeric approximation of the derivative
double Fx( const double &x ){
    using namespace std;
    return ( (1+x*sin(x)) / pow(x,3) );
}

// Define the true analytic derivative of the function
// that was computed by hand
double derivFx ( const double &x ){
    using namespace std;
    return ( (pow(x,2)*cos(x)-2*x*sin(x)-3) / ( pow(x,4) ) );
}

int main() {
    // Define the value of x @ which we want to approximate f'(x)
    const double x = 3.9;

    // Define the range [-1, 25]. 
    // we will use a step size of 1 for simplicity.
    // Notes:
    // - the size of the range is 27= 25-(-1) + 1 to account for zero
    // - iota generates a linear space with step size 1. For more complex behavior use std::generate    std::array<int, 27> powers;
    const int data_size_ = 27;
    std::array<double, data_size_> powers;
    std::iota(powers.begin(), powers.end(), -1);

    // Generate an array of different grid spacings
    // using a base of 2 and each exponent in the powers array
    std::array<double, data_size_> grids;

    // Note that the transform is comparable to:
    //>`std::copy(powers.begin(),powers.end(),grids.begin());`
    //>`std::for_each(grids.begin(),grids.end(), [](auto &x) { x = std::pow(2,x); });`
    std::ranges::transform(powers, grids.begin(),[](auto x) { return std::pow(2,x); });

    // Define some strategies for approximating derivatives using
    // Finite Difference Approximations
    // Notes:
    // - 1st order forward difference
    // - 2nd order central difference
    // - 4th order central difference
    auto forwardDiffFun  = [&x](auto h){ return Fx(x+h)-Fx(x)   /   h; };
    auto centralDiffFun  = [&x](auto h){ return Fx(x+h)-Fx(x-h) / 2*h; }; 
    auto centralDiff4Fun = [&x](auto h){ return Fx(x-2*h)-8*Fx(x-h)+8*Fx(x+h)-Fx(x+2*h) / 12*h; };

    auto trueDerivative = grids | std::ranges::views::transform(derivFx);
    auto forwardDiff    = grids | std::ranges::views::transform(forwardDiffFun);
    auto centralDiff    = grids | std::ranges::views::transform(centralDiffFun);
    auto centralDiff4   = grids | std::ranges::views::transform(centralDiff4Fun);

    // Compute the error by taking the difference between the analytic solution and the approximation
    std::array<double, data_size_> forwardDiffError;
    std::array<double, data_size_> centralDiffError;
    std::array<double, data_size_> centralDiff4Error;

    std::ranges::transform(trueDerivative, forwardDiff,  forwardDiffError.begin(), std::minus{});
    std::ranges::transform(trueDerivative, centralDiff,  centralDiffError.begin(), std::minus{});
    std::ranges::transform(trueDerivative, centralDiff4, centralDiff4Error.begin(),std::minus{});

    auto absFun = [](auto x){ return std::abs(x); };
    std::ranges::transform(forwardDiffError, forwardDiffError.begin(), absFun);
    std::ranges::transform(forwardDiffError, centralDiffError.begin(), absFun);
    std::ranges::transform(forwardDiffError, centralDiff4Error.begin(),absFun);


    // create an ostream iterator and then copy our begin and end pointer
    // to the anonymous ostream iterator.
    std::cout << "1st Order Forward Diff Error" << std::endl;
    std::ranges::copy(forwardDiffError, std::ostream_iterator<double>(std::cout," "));
    std::cout << std::endl << std::endl;

    std::cout << "1st Order Central Diff Error" << std::endl;
    std::ranges::copy(centralDiffError, std::ostream_iterator<double>(std::cout," "));
    std::cout << std::endl << std::endl;

    std::cout << "4th Order Central Diff Error" << std::endl;
    std::ranges::copy(centralDiff4Error, std::ostream_iterator<double>(std::cout," "));
    std::cout << std::endl << std::endl;

    return 0;
}
    
    