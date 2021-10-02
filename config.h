#include<complex>

const int XRES = 2000;
const int YRES = 2000;
const unsigned int ITERATIONS = 30;
const long double ZOOM = 1;
const long double RCENTER = -0.0;
const long double ICENTER = -0.0;

std::complex<long double> function(std::complex<long double> z, std::complex<long double> c) { return

    std::pow(z, 2) + c;

}
