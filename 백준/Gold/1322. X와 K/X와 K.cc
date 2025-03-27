#include <iostream>
#include <bitset>
using namespace std;
typedef long long ll;

int main(){
    ll X, K;
    cin >> X >> K;
    bitset<64> bsX(X);
    bitset<64> bsY;
    for (int i = 0; i < 64; i++){
        if (!bsX[i]){
            if (K & 1LL)
                bsY.set(i);
            K >>= 1;
        }
    }
    ll Y = static_cast<ll>(bsY.to_ullong());
    cout << Y << "\n";
    return 0;
}
