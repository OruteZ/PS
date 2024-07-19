#include<iostream>
#include<cmath>
using namespace std;

int main() {
    int a, b, c;
    cin >> a >> b >> c;
    
    double diff = b - a;
    
    cout << (int)ceil(diff / c) << endl;
}