#include <iostream>
using namespace std;

double calculate_L(double S, double V, double ro, double cl);

int main()
{
    double S, V, ro, cl;

    cout << "Enter parametrs:\n";
    cout << "S:";
    cin >> S;

    cout << "V:";
    cin >> V;

    cout << "ro:";
    cin >> ro;

    cout << "Cl:";
    cin >> cl;
    cout << "Calculated L\n";
    cout << "Result: " << calculate_L(S, V, ro, cl);

}

double calculate_L(double S, double V, double ro, double cl) {
    return 0.5 * ro * V * V * S * cl;
}

