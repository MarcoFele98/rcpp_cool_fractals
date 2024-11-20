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
  double stepIm((imMax - imMin) / static_cast<double>(resY));
  
  std::complex<double> c(real, immaginary);
  
  for(int x = 0; x < resX; x++) {
    for(int y = 0; y < resY; y++) {
      std::complex<double> z(realMin + (stepReal * static_cast<double>(x)), 
                             imMin + (stepIm * static_cast<double>(y)));
  
      int iteration = 0;
      for(; iteration < maxIterations; iteration++) {
        z = pow(z, 2) + c;
        
        if(std::abs(z) > 2.) {
          break;
        } 
      }
      
      pixels.at(y, x) = iteration;
      
    }
  }
  
  return(pixels);
} 
