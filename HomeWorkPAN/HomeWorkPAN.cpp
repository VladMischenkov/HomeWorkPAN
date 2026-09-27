#include <iostream>
#include <iomanip>
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
    double getTime() { return t; }
    double getAcceleration() { return a; }

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
    void calculateOptimalForce(double h, double Tmin, double Tmax, double Tstep) {
        cout << "\n|   T    | Vert. acceleration | Time to reach H    |\n";
        double max_T_a = Tmin;
        for (double T_ = Tmin; T_ <= Tmax; T_ += Tstep) {
            double verticalAcceleration = calculate_acceleration_y(T_, m);
            double time = calculate_time(h, verticalAcceleration);
            cout << "| " << setw(6) << T_ << " | " 
                << setw(18) << verticalAcceleration << " | "
                << setw(18) << time << " |\n";
            if (verticalAcceleration > calculate_acceleration_y(max_T_a, m))
                max_T_a = T_;
        }
        cout << "\nMin time to reach hight: " << calculate_time(h, calculate_acceleration_y(max_T_a, m));
        cout << "\nMax value of acceleration: " << calculate_acceleration_y(max_T_a, m);
        cout << "\nThis value was reached with T: " << max_T_a;
    }
    


    void setTime(double t_) { t = t_; }
    void setAccelerationY(double a_y_) { a_y = a_y_; }
    void setAcceleration(double a_) { a = a_; }
    void setMass(double m_) { m = m_; }
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
        cout << "\nAcceleration: " << a;
        cout << "\nY axis acceleration: " << a_y;
        cout << "\nLifting force: " << L;
    }

};
int maxAccelerationIndex(int n, aircraft* a);
void sortByTime(int n, aircraft* a);


int main()
{
    
    double ro, h;
    
    cout << "Enter hight: "; cin >> h;
    double m, Tmin, Tmax, Tstep;

    cout << "\nEnter mass: "; cin >> m;
    cout << "\nEnter Tmin: "; cin >> Tmin;
    cout << "\nEnter Tmax: "; cin >> Tmax;
    cout << "\nEnter Tstep: "; cin >> Tstep;

    
    aircraft plane;
    plane.setMass(m);
    plane.calculateOptimalForce(h, Tmin, Tmax, Tstep);


    return 0;
}



double calculate_acceleration(double T, double D, double m) {
    if (T - D < 0) return 0;
    return ((T - D) / m);

}

double calculate_acceleration_y(double L, double m) {
    return ((L - m * g) / g);
}
double calculate_L(double S, double V, double ro, double cl) {
    return (0.5 * ro * V * V * S * cl);
}

double calculate_time(double h, double a_y) {
    if (a_y < 0) return -1;                                                         // Если самолет снижается, то время = -1
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

int maxAccelerationIndex(int n, aircraft* a) {
    int max_ind = 0;
    for (int i = 1; i < n; i++) 
        if (a[max_ind].getAcceleration() < a[i].getAcceleration()) 
            max_ind = i;
    return max_ind;
}