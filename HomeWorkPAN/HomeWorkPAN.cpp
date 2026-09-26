#include <iostream>
using namespace std;

double calculate_time(double h, double a_y) {
    return sqrt(2 * h / a_y);
}

int main()
{
    double h, a_y;

    cout << "Enter hight:";
    cin >> h;
    cout << "\nEnter acceleration on y axis:";
    cin >> a_y;
    cout << "\nResulted time: " << calculate_time(h, a_y);
}
