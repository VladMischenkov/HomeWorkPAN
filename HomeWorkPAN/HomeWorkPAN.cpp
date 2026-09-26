#include <iostream>
using namespace std;
double g = 9.8067;

double calculate_L(double S, double V, double ro, double cl);
double calculate_acceleration(double T, double D, double m);
double calculate_acceleration_y(double L, double m);

int main()
{
    double m, L, T, D;
    cout << "Enter mass: ";
    cin >> m;
    cout << "\nEnter force: ";
    cin >> T;
    cout << "\nEnter resistance: ";
    cin >> D;
    cout << "\nLift force: ";
    cin >> L;


    cout << "Resulted acceleration: " << calculate_acceleration(T, D, m) << "\n";
    cout << "Resulted acceleration (y axis): " << calculate_acceleration_y(L, m);
}


double calculate_acceleration(double T, double D, double m) {
    return (T - D) / m;
}

double calculate_acceleration_y(double L, double m) {
    return (L - m * g) / g;
}
double calculate_L(double S, double V, double ro, double cl) {
    return 0.5 * ro * V * V * S * cl;
}
