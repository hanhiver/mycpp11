// 判断两个浮点数是否相等的例子程序。 
// 简单的使用绝对差和相对差都会有各自的问题。
// 相对最好的办法是判断两个浮点数中间的maxULPs，就是两者之间相隔了多少个可能的其他浮点数取值。
// 就是说：我觉得结果是10000.0，但是鉴于浮点数的天生缺陷，
//        我可以接受10000前面5个或者后面5个数。
// https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/

#include <iostream> 
#include <cassert>
#include <stdint.h>
#include <cmath>
#include <float.h>

union Float_t
{
    Float_t(float num = 0.0f) : f(num) {}
    // Portable extraction of components.
    bool Negative() const { return (i >> 31) != 0; }
    int32_t RawMantissa() const { return i & ((1 << 23) - 1); }
    int32_t RawExponent() const { return (i >> 23) & 0xFF; }

    int32_t i;
    float f;
#ifdef _DEBUG
    struct
    {   // Bitfields for exploration. Do not use in production code.
        uint32_t mantissa : 23;
        uint32_t exponent : 8;
        uint32_t sign : 1;
    } parts;
#endif
};

bool AlmostEqualUlpsAndAbs(float A, float B,
            float maxDiff, int maxUlpsDiff)
{
    // Check if the numbers are really close -- needed
    // when comparing numbers near zero.
    float absDiff = fabs(A - B);
    if (absDiff <= maxDiff)
        return true;

    Float_t uA(A);
    Float_t uB(B);

    // Different signs means they do not match.
    if (uA.Negative() != uB.Negative())
        return false;

    // Find the difference in ULPs.
    int ulpsDiff = abs(uA.i - uB.i);
    if (ulpsDiff <= maxUlpsDiff)
        return true;

    return false;
}

bool AlmostEqualRelativeAndAbs(float A, float B,
            float maxDiff, float maxRelDiff = FLT_EPSILON)
{
    // Check if the numbers are really close -- needed
    // when comparing numbers near zero.
    float diff = fabs(A - B);
    if (diff <= maxDiff)
        return true;

    A = fabs(A);
    B = fabs(B);
    float largest = (B > A) ? B : A;

    if (diff <= largest * maxRelDiff)
        return true;
    return false;
}

int main()
{
    std::cout << "float:   " << sizeof(float) << "\n"
              << "int:     " << sizeof(int) << "\n"
              << "double:  " << sizeof(double) << "\n"
              << "long:    " << sizeof(long) << "\n";

    float a = 0.01; 
    float b = 0; 
    for (int i=0; i<100; i++)
    {
        b += a; 
    }
    std::cout << b << std::endl; 
    std::cout << "equal(==)? : " << (b == 1.0) << std::endl; 
    std::cout << "almosteq?  : " << AlmostEqualUlpsAndAbs(b, 1.0, 0.01, 1) << std::endl;
    return 0;
}