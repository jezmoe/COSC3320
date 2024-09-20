#include <iostream>
#include <math.h>
#include <vector>

int main() {
    // n mod b; -> n wrt b;
    int n = 91379;
    int b = 262144;

    std::vector<int> Multipliers;

    int ModuloNumber = n;
    int CurrentNumber = b;
    int Multiplier;
    int Remainder;

    while (ModuloNumber != 1) {
        Multiplier = floor(CurrentNumber / ModuloNumber);
        Remainder = CurrentNumber % ModuloNumber;
        Multipliers.push_back(Multiplier);

        std::cout << CurrentNumber << " % " << ModuloNumber << " = ";
        CurrentNumber = ModuloNumber;
        ModuloNumber = Remainder;

        std::cout << Multiplier << " + " << Remainder << "\n";
    }

    Multipliers.push_back(floor(CurrentNumber / ModuloNumber));
    std::cout << CurrentNumber << " % " << ModuloNumber << " = ";
    std::cout << CurrentNumber << " + 0\n\n";

    int T1 = 0;
    int T2 = 1;
    int CurrentSum;


    for (int i = 0; i < Multipliers.size(); i++) {
        std::cout << T1 << " + (" << T2 << " * -" << Multipliers[i] << ") = ";

        CurrentSum = T1 + (T2 * -(Multipliers[i]));
        std::cout << CurrentSum << "\n";

        T1 = T2;
        T2 = CurrentSum;
    }

    std::cout << "\nFinal Answer for multiplicative inverse:\n";
    std::cout << T1 << " % " << b << " = ";

    int MultiplicativeInverse = T1 % b;

    if (T1 >= 0) {
        std::cout << MultiplicativeInverse << "\n";
    } else {
        std::cout << T1 + b << "\n";
    }

    return 0;
}