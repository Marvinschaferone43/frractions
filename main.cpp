#include "fraction.h"
#include <iostream>

void testFraction() {
    // Test constructors
    fraction f1;
    fraction f2(3, 4, true);
    fraction f3(f2);
    fraction f4(1.25L);
    fraction f5(5);
    fraction f6(123456789012345LL);
    fraction f7(2.5f);

    // Test getters and setters
    f1.setA(2);
    f1.setB(3);
    f1.setSign(true);
    f1.setOverflow();

    std::cout << "f1: " << f1.to_string() << std::endl;
    std::cout << "f2: " << f2.to_string() << std::endl;
    std::cout << "f3: " << f3.to_string() << std::endl;
    std::cout << "f4: " << f4.to_string() << std::endl;
    std::cout << "f5: " << f5.to_string() << std::endl;
    std::cout << "f6: " << f6.to_string() << std::endl;
    std::cout << "f7: " << f7.to_string() << std::endl;

    // Test to_float
    std::cout << "f1 as float: " << f1.to_float() << std::endl;

    // Test operator overloading
    fraction f8 = f2 + f3;
    fraction f9 = f2 - f3;
    fraction f10 = f2 * f3;
    fraction f11 = f2 / f3;

    std::cout << "f2 + f3: " << f8.to_string() << std::endl;
    std::cout << "f2 - f3: " << f9.to_string() << std::endl;
    std::cout << "f2 * f3: " << f10.to_string() << std::endl;
    std::cout << "f2 / f3: " << f11.to_string() << std::endl;

    // Test comparison operators
    std::cout << "f2 == f3: " << (f2 == f3) << std::endl;
    std::cout << "f2 != f3: " << (f2 != f3) << std::endl;
    std::cout << "f2 > f3: " << (f2 > f3) << std::endl;
    std::cout << "f2 < f3: " << (f2 < f3) << std::endl;
    std::cout << "f2 >= f3: " << (f2 >= f3) << std::endl;
    std::cout << "f2 <= f3: " << (f2 <= f3) << std::endl;

    // Test assignment operators
    fraction f12;
    f12 = f2;
    std::cout << "f12 (assigned from f2): " << f12.to_string() << std::endl;

    f12 = 2.5L;
    std::cout << "f12 (assigned from 2.5L): " << f12.to_string() << std::endl;

    f12 = 10;
    std::cout << "f12 (assigned from 10): " << f12.to_string() << std::endl;

    f12 = 123456789012345LL;
    std::cout << "f12 (assigned from 123456789012345LL): " << f12.to_string() << std::endl;

    f12 = 3.14f;
    std::cout << "f12 (assigned from 3.14f): " << f12.to_string() << std::endl;

    // Test commonDenom
    std::vector<fraction> common = f2.commonDenom(f2, f3);
    std::cout << "Common denominator of f2 and f3: " << common[0].to_string() << " and " << common[1].to_string() << std::endl;
}

int main() {
    testFraction();
    return 0;
}
