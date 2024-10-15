#include <iostream>

using namespace std;

int N, S;

int array[100001] = {0,};
int sums[100001] = {0,};
int solution(){
    if(sums[N] < S) return 0;

    int ptr1 = 1, ptr2 = 1;
    int answer = N+1;
    while(true){
       // cout << "ptr1 : " <<ptr1<< " | ptr2 : " << ptr2<<endl;


        int sum = sums[ptr2] - sums[ptr1-1];

        if(sum >= S){
            if(ptr2 - ptr1 + 1 < answer) answer = ptr2 - ptr1 + 1;
        }

        if(sum <= S){
            if(++ptr2 > N) break;
        } else {
            if(++ptr1 > ptr2) break;
        }
    }
    return answer;
}
int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);std::cout.tie(nullptr);

    cin >> N >> S;
    for(int i = 1; i <= N; i++){
        cin >> array[i];
        sums[i] = sums[i-1] + array[i];
    }

    cout << solution() << endl;


    return 0;
}
