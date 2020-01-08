#include <iostream> 
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

int mandelbrot(const std::complex<float> &z0, const int max)
{
    std::complex<float> z = z0; 
    for (int t=0; t<max; t++)
    {
        if (z.real()*z.real() + z.imag()*z.imag() > 4.0f)
        {
            return t; 
        }
    }

    return max; 
}

int mandelbrotFormula(const std::complex<float> &z0, const int maxIter=500)
{
    int value = mandelbrot(z0, maxIter); 
    if (maxIter - value == 0)
    {
        return 0; 
    }

    return cvRound(sqrt(value/(float)maxIter) * 255); 
}

int main()
{

    return EXIT_SUCCESS;
}
