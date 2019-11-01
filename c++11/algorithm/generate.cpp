#include <iostream> 
#include <random> 
#include <algorithm> 

void initalData(float *ip, int size)
{
    std::mt19937 gen; 
    std::uniform_int_distribution<float> dis(0.0f, 100000.0f);

    auto rand_num ([=]() mutable
        {
            return dis(gen)/13.0f;
        });

    std::generate(ip, ip+size, rand_num); 
}

int main()
{
    int nElem = 10; 
    
    float *h_A = new float[nElem];

    initalData(h_A, nElem);

    for (unsigned i=0; i<nElem; ++i)
    {
        std::cout << h_A[i] << ", ";
    }
    std::cout << std::endl; 

    delete[] h_A; 
}