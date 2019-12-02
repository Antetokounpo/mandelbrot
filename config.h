#include<complex>

const int XRES = 1000;
const int YRES = 1000;
const int ITERATIONS = 1000;
const double ZOOM = 1;
const double RCENTER = 0.5;
const double ICENTER = 0.;

std::complex<double> function(std::complex<double> z, std::complex<double> c) { return

    std::pow(z, 2) + c;

}