// 判断两个浮点数是否相等的例子程序。 
// 简单的使用绝对差和相对差都会有各自的问题。
// 相对最好的办法是判断两个浮点数中间的maxULPs，就是两者之间相隔了多少个可能的其他浮点数取值。
// 就是说：我觉得结果是10000.0，但是鉴于浮点数的天生缺陷，
//        我可以接受10000前面5个或者后面5个数。
// https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/

#include <iostream> 
#include <cassert>

bool AlmostEqualFloat(float A, float B, int maxULPs)
{
    // Make sure maxULPs non-negative and small enough that the 
    // default NAN won't compare as equal to anything. 
    assert(maxULPs > 0 && maxULPs < 4 * 1024 * 1024);

    int aInt = *(int*)&A; 
    // Make aInt lexicographically ordered as a twos-complement int. 
    if (aInt < 0)
    {
        aInt = 0x80000000 - aInt; 
    }
    // Make bInt lexicographically ordered as a twos-complement int. 
    int bInt = *(int*)&B;
    if (bInt < 0)
    {
        bInt = 0x80000000 - bInt; 
    }

    int intDiff = abs(aInt - bInt);
    if (intDiff <= maxULPs)
    {
        return true;
    }
    
    return false; 
}

// NOT WORKING as we need to change the 0x80000000. 
bool AlmostEqualDouble(double A, double B, long maxULPs)
{
    // Make sure maxULPs non-negative and small enough that the 
    // default NAN won't compare as equal to anything. 
    assert(maxULPs > 0 && maxULPs < 4 * 1024 * 1024);

    long aInt = *(long*)&A; 
    // Make aInt lexicographically ordered as a twos-complement int. 
    if (aInt < 0)
    {
        aInt = 0x80000000 - aInt; 
    }
    // Make bInt lexicographically ordered as a twos-complement int. 
    long bInt = *(long*)&B;
    if (bInt < 0)
    {
        bInt = 0x80000000 - bInt; 
    }

    long intDiff = abs(aInt - bInt);
    if (intDiff <= maxULPs)
    {
        return true;
    }
    
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
    std::cout << "almosteq?  : " << AlmostEqualFloat(b, 1.0, 12) << std::endl;
    return 0;
}