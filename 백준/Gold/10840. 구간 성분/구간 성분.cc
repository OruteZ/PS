#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

typedef unsigned long long ull; // ull로 typedef

string N, M;
int Nlen, Mlen;
ull X[26]; // 미리 각 알파벳에 대응하는 X의 거듭제곱 값을 저장

// 주어진 길이 len의 구간에 대해, 두 문자열에서 동일한 해시값(즉, 동일한 문자 빈도)를 가지는 구간이 있는지 검사
int findSubstring(int len) {
    ull Mhash = 0;
    ull Mcnt[26];
    fill(Mcnt, Mcnt + 26, 0);
    vector<ull> v; // M의 길이 len 구간들의 해시값을 저장

    // 문자열 M의 모든 길이 len 구간에 대해 해시값 계산 (슬라이딩 윈도우 방식)
    for (int i = 0; i <= Mlen - len; i++) {
        if (i == 0) { // 첫 구간 처리
            for (int j = i; j < i + len; j++) {
                Mcnt[M[j] - 'a']++;
            }
            for (int j = 0; j < 26; j++) {
                Mhash += Mcnt[j] * X[j];
            }
        }
        v.push_back(Mhash);
        
        // 다음 구간으로 이동: 첫 문자 제거, 다음 문자 추가
        if (i != Mlen - len) {
            Mhash -= X[M[i] - 'a'];
            Mcnt[M[i] - 'a']--;
            Mcnt[M[i + len] - 'a']++;
            Mhash += X[M[i + len] - 'a'];
        }
    }
    sort(v.begin(), v.end()); // 이분탐색 전 정렬

    ull Nhash = 0;
    ull Ncnt[26];
    fill(Ncnt, Ncnt + 26, 0);
    
    // 문자열 N의 모든 길이 len 구간에 대해 해시값 계산하며, M의 해시값 벡터에서 동일 값이 있는지 이분탐색
    for (int i = 0; i <= Nlen - len; i++) {
        if (i == 0) { // 첫 구간 처리
            for (int j = i; j < i + len; j++) {
                Ncnt[N[j] - 'a']++;
            }
            for (int j = 0; j < 26; j++) {
                Nhash += Ncnt[j] * X[j];
            }
        }
        if (binary_search(v.begin(), v.end(), Nhash)) {
            return 1; // 동일한 성분의 구간이 존재하면 1 반환
        }
        // 다음 구간으로 이동
        if (i != Nlen - len) {
            Nhash -= X[N[i] - 'a'];
            Ncnt[N[i] - 'a']--;
            Ncnt[N[i + len] - 'a']++;
            Nhash += X[N[i + len] - 'a'];
        }
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // X 배열에 base 1501의 거듭제곱을 미리 계산 (문자열 길이 최대 1500보다 크게 설정)
    ull x = 1;
    for (int i = 0; i < 26; i++) {
        X[i] = x;
        x *= 1501;
    }
    
    cin >> N >> M;
    
    // |N| <= |M|가 되도록, N이 더 짧은 문자열이 되게 swap
    if (N.length() > M.length()) {
        swap(N, M);
    }
    Nlen = N.length();
    Mlen = M.length();
    
    // N의 전체 길이부터 1까지 내림차순으로, 같은 성분 구간이 존재하는지 확인
    for (int len = Nlen; len > 0; len--) {
        if (findSubstring(len)) {
            cout << len;
            return 0;
        }
    }
    cout << 0;
    return 0;
}
