#include <iostream>
using namespace std;

double g = 9.8067;
double calculate_acceleration(double T, double D, double m);
double calculate_acceleration_y(double L, double m);
double calculate_L(double S, double V, double ro, double cl);
double calculate_time(double h, double a_y);


class aircraft {
private:
    double m;    //Mass
    double S;    //Surface of wings //Известно
    double T;    //Force
    double C_l;
    double C_d;
    double V;

    double L;    // Lifting Force
    double D;    // Resistance 
    double a;    // Acceleration
    double a_y;  // Y axis acceleration
public:
    string getStatus() {
        if (a > 0.5) return "Rising";
        if (a > 0) return "Horizontal";
        return "Down";
    }

    void calculateVerticalAcceleration(double ro) { 
        a_y = calculate_acceleration_y(L, m); 
    }
    void calculateAcceleration(double ro) {
        a = calculate_acceleration(T, D, m);
    }
    void calculateLiftingForce(double ro) { 
        L = calculate_L(S, V, ro, C_l); 
    }
    void calculateResistance(double ro) { 
        D = calculate_L(S, V, ro, C_d); 
    }
    double calculateTime(double ro, double h) {
        return calculate_time(h, a_y);
    }

    void setAcceleration(double a_) { a = a_; }

    void setParameters() {
        while (m <= 0) { cout << "Enter mass: "; cin >> m; }
        while (S <= 0) { cout << "\nEnter surface area: "; cin >> S; }
        while (T <= 0) { cout << "\nEnter force: "; cin >> T; }
        while (C_l <= 0) { cout << "\nEnter C_l: "; cin >> C_l; }
        while (C_d <= 0) { cout << "\nEnter C_d: "; cin >> C_d; }
        while (V <= 0) { cout << "\nEnter speed: "; cin >> V; }

    }

    double solve(double ro, double h) {
        calculateLiftingForce(ro);
        calculateResistance(ro);
        calculateVerticalAcceleration(ro);
        calculateAcceleration(ro);
        return calculateTime(ro, h);
    }

    void printParameters() {
        cout << "Lifting force: " << L;
        cout << "\nResistance: " << D;
        cout << "\nAcceleration: " << a;
        cout << "\nY axis acceleration: " << a_y;
    }
};

int main()
{
    aircraft plane;
    double a;
    cout << "Enter acceleration: "; cin >> a;

    plane.setAcceleration(a);

    cout << plane.getStatus();

}

double calculate_L(double S, double V, double ro, double cl) {
    return 0.5 * ro * V * V * S * cl;
}

