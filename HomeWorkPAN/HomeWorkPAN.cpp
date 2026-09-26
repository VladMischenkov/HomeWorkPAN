#include <iostream>
#include <iomanip>
using namespace std;
double g = 9.8067;

double calculate_L(double S, double V, double ro, double cl);
void printTable(int n, double S, double cl, double* V, double* ro);

int main()
{
    int n;
    cout << "Number of elements: "; cin >> n;

    double* V = new double[n];
    double* ro = new double[n];

    cout << "\nEnter V[i] and ro[i] in pairs\n";
    for (int i = 0; i < n; i++) {
        cin >> V[i];
        cin >> ro[i];
    }
    double S, cl;
    cout << "Enter surface area: "; cin >> S;
    cout << "\nEnter c_l: "; cin >> cl;

    printTable(n, S, cl, V, ro);
}


double calculate_L(double S, double V, double ro, double cl) {
    return (0.5 * ro * V * V * S * cl);
}

void printTable(int n, double S, double cl, double* V, double* ro) {
    cout << "\n| Step   | Speed        | Density      | Lifting force   |\n";
    for (int i = 0; i < n; i++) {
        cout << "| " << setw(6) << i << " | " << setw(12) << V[i] << " | " << setw(12) << ro[i] << " | " << setw(15) << calculate_L(S, V[i], ro[i], cl) << " |\n";
    }
}