#include <iostream>
using namespace std;
double g = 9.8067;

double calculate_L(double S, double V, double ro, double cl);
double calculate_acceleration(double T, double D, double m);
double calculate_acceleration_y(double L, double m);
double calculate_time(double h, double a_y);


class aircraft {
private:
    double m; //Mass
    double S; //Surface of wings //Известно
    double T; //Force
    double C_l;
    double C_d;
    double V;

    double L; //Lifting Force
    double D; // Resistance 
    double a; 
    double a_y;
public:
    

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
    aircraft array[3];
    double resultedTime[3];
    int ro, h;

    cout << "Enter ro:";  cin >> ro;
    cout << "\nEnter h:";  cin >> h;

    for (int i = 0; i < 3; i++) {
        cout << "Aircraft #" << i + 1<< endl;
        array[i].setParameters();
        resultedTime[i] = array[i].solve(ro, h);
    }


    for (int i = 0; i < 3; i++) {
        cout << "\n\naircraft #" << i + 1 << endl;
        array[i].printParameters();
        if (resultedTime[i] >= 0)
            cout << "\ntime to reach hight h:" << resultedTime[i] << endl;
        else
            cout << "\nAircraft never reaches hight";
    }

    for (int i = 0; i < 3; i++)
        if (resultedTime[i] < resultedTime[(i + 1) % 3] && resultedTime[i] < resultedTime[(i + 2) % 3])
            cout << "\nAircraft #" << i + 1 << " got the best time";

}


double calculate_acceleration(double T, double D, double m) {
    return ((T - D) / m);
}

double calculate_acceleration_y(double L, double m) {
    return ((L - m * g) / g);
}
double calculate_L(double S, double V, double ro, double cl) {
    return (0.5 * ro * V * V * S * cl);
}

double calculate_time(double h, double a_y) {
    return sqrt(2 * h / a_y);
}

