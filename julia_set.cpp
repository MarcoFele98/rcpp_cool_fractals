#include <Rcpp.h>
#include <complex>

using namespace Rcpp;

// [[Rcpp::export]]
IntegerMatrix generate_juliaset(const double &real,
                                const double &immaginary,
                                const int &resX,
                                const int &resY,
                                const int &maxIterations,
                                const double &realMin,
                                const double &realMax,
                                const double &imMin,
                                const double &imMax) {
  IntegerMatrix pixels(resY, resX);
  const double stepReal((realMax - realMin) / static_cast<double>(resX));
  const double stepIm((imMax - imMin) / static_cast<double>(resY));
  
  std::complex<double> c(real, immaginary);
  
  for(int x = 0; x < resX; x++) {
    for(int y = 0; y < resY; y++) {
      std::complex<double> z(realMin + (stepReal * static_cast<double>(x)), 
                             imMin + (stepIm * static_cast<double>(y)));
      
      int iteration = 0;
      for(; iteration < maxIterations; iteration++) {
        z = pow(z, 2) + c;
        
        if(std::abs(z) > 2.f) {
          break;
        }
      } 
      
      pixels.at(y, x) = iteration;
    }
  }
  
  return(pixels);
} 

// [[Rcpp::export]]
NumericMatrix iterate_function(const int &resX,
                               const int &resY,
                               const int &maxIterations,
                               const double &realMin,
                               const double &realMax,
                               const double &imMin,
                               const double &imMax) {
  NumericMatrix pixels(resY, resX);
  const double stepReal((realMax - realMin) / static_cast<double>(resX));
  const double stepIm((imMax - imMin) / static_cast<double>(resY));
  
  std::complex<double> i(0, 1);
  
  for(int x = 0; x < resX; x++) {
    for(int y = 0; y < resY; y++) {
      std::complex<double> z(realMin + (stepReal * static_cast<double>(x)), 
                             imMin + (stepIm * static_cast<double>(y)));
      
      for(int iteration = 0; iteration < maxIterations; iteration++) {
        //z = 1. /((0.15 + 0.15 * i) * pow(z, 5.) + pow(z, 3.) + (-3. + 3. * i) * z);
        //z = -z + std::tanh(2. * pow(z, 2.));
        z = -z + std::tanh(2. * pow(z, 2.) - 0.1) - std::tanh(- 0.1);
      } 
      
      pixels.at(y, x) = std::abs(z);
    }
  }
  
  return(pixels);
}

