#include<complex>

const int XRES = 2000;
const int YRES = 2000;
const int ITERATIONS = 8000;
const long double ZOOM = 5;
const long double RCENTER = -0.170337;
const long double ICENTER = -1.06506;

std::complex<long double> function(std::complex<long double> z, std::complex<long double> c) { return

    std::pow(z, 2) + c;

}