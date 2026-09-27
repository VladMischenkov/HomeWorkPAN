#include <iostream>
using namespace std;

double g = 9.8067;
double calculate_acceleration(double T, double D, double m);
double calculate_acceleration_y(double L, double m);
double calculate_L(double S, double V, double ro, double cl);
double calculate_time(double h, double a_y);

class aircraft {
private:
    // Дано
    double m;    //Mass
    double S;    //Surface of wings 
    double T;    //Force
    double C_l;
    double C_d;
    double V;

    // Расчитать
    double L;    // Lifting Force
    double D;    // Resistance 
    double a;    // Acceleration
    double a_y;  // Y axis acceleration
    double t;
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
    void calculateTime(double ro, double h) {
        t = calculate_time(h, a_y);
    }

    void setAcceleration(double a_) { a = a_; }
    void setTime(double t_) { t = t_; }
    void setAccelerationY(double a_y_) { a_y = a_y_; }

    void setParameters() {
        while (m <= 0) { cout << "Enter mass: "; cin >> m; }
        while (S <= 0) { cout << "\nEnter surface area: "; cin >> S; }
        while (T <= 0) { cout << "\nEnter force: "; cin >> T; }
        while (C_l <= 0) { cout << "\nEnter C_l: "; cin >> C_l; }
        while (C_d <= 0) { cout << "\nEnter C_d: "; cin >> C_d; }
        while (V <= 0) { cout << "\nEnter speed: "; cin >> V; }

    }

    void solve(double ro, double h) {
        calculateLiftingForce(ro);
        calculateResistance(ro);
        calculateVerticalAcceleration(ro);
        calculateAcceleration(ro);
        calculateTime(ro, h);
    }

    void printParameters() {
        if (t < 0) cout << "\nPlane will never reach hight";
        else cout << "\nTime to reach hight: " << t;

        cout << "\nY axis acceleration: " << a_y;
    }

    double getTime() { return t; }
};

void sortByTime(int n, aircraft* a);


int main()
{
    
    double ro = 1, h = 1;
    /*
    cout << "Enter ro: "; cin >> ro;
    cout << "Enter hight: "; cin >> h;
    */

    int n = 5;
    //cout << "Enter number of airplanes: ";
    //cin >> n;

    aircraft* planes = new aircraft[n];
    /*
    for (int i = 0; i < n; i++) {
        cout << "Plane #" << i + 1 << endl;
        planes[i].setParameters();
        planes[i].solve(ro, h);
    }
    */
    
    planes[0].setAccelerationY(1); planes[0].calculateTime(ro, h);
    planes[1].setAccelerationY(5); planes[1].calculateTime(ro, h);
    planes[2].setAccelerationY(-1); planes[2].calculateTime(ro, h);
    planes[3].setAccelerationY(2); planes[3].calculateTime(ro, h);
    planes[4].setAccelerationY(3); planes[4].calculateTime(ro, h);



    sortByTime(n, planes);

    for (int i = 0; i < n; i++){
        cout << "\n\nPlane #" << i + 1;
        planes[i].printParameters();
    }
    cout << "\n\n\n\n";
    return 0;
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
    if (a_y < 0) return -1; // Если самолет снижается, то время = -1
    return sqrt(2 * h / a_y);
}

void sortByTime(int n, aircraft* a) {
    aircraft temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if ((a[j].getTime() > a[j + 1].getTime() and a[j + 1].getTime() > 0) or // Проверка если оба положительные
                (a[j].getTime() < 0 and a[j + 1].getTime() > 0)                     // Проверка если один отрицательный
                ) {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

