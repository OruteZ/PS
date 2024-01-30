#include <iostream>
#include<queue>
#include<stack>
#include<cstring>
using namespace std;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n; cin >> n;

    priority_queue<int> cards;

    while(n--){
        int a; cin >> a;
        cards.push(-a);
    }


    int result = 0;
    int n1;int n2;
    while(cards.size() > 1){
        n1 = -cards.top(); cards.pop();
        n2 = -cards.top(); cards.pop();

        result += n1 + n2;
        cards.push(-(n1 + n2));
    }

    cout << result << endl;
    return 0;
}