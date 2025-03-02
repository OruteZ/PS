#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
vector<ll> tri; // 삼각수 배열

// begin부터 end까지의 합을 반환한다.
ll sum(ll begin, ll end) {
	return (end - begin + 1) * (begin + end) / 2;
}

// H까지의 삼각수를 미리 계산
void precomputeTri(int H) {
	tri.resize(H + 2);  // 0부터 H까지
	tri[0] = 0;
	for (int i = 1; i <= H; i++) {
		tri[i] = tri[i - 1] + i;
	}
}

// pos가 삼각형 내에서 어느 높이에 속하는지 계산 (이진 탐색 사용)
// 삼각수 tri[i]는 1부터 i까지의 합 = i*(i+1)/2
int getHeight(ll pos) {
	// pos가 속하는 최소의 i를 찾는다: tri[i-1] < pos <= tri[i]
	int lo = 1, hi = tri.size() - 1;
	while (lo < hi) {
		int mid = (lo + hi) / 2;
		if (tri[mid] >= pos)
			hi = mid;
		else
			lo = mid + 1;
	}
	return lo;
}

// height번째 삼각형의 pos위치가 leaf라면, leaf의 번호를 반환한다. 아니라면 -1을 반환한다.
ll getLeaf(int height, ll pos) {
	ll minimum = sum(1, height - 1) + 1;
	ll maximum = sum(1, height);

	if(minimum <= pos && pos <= maximum) {
		return (pos - minimum) + 1;
	} else {
		return 1e9;
	}
}

// 크기가 height인 삼각형에서 pos위치에 구슬을 떨굴때 구슬이 떨어지는 구간을 반환한다.
pair<ll, ll> getRange(int height, ll pos) {
	int local_height = getHeight(pos);

	if(local_height == height) {
		return {getLeaf(height, pos), getLeaf(height, pos)};
	}

	ll start = getLeaf(height, pos + sum(local_height, height - 1));
	ll end = getLeaf(height, pos + sum(local_height + 1, height));

	return {start, end};
}

// 크기가 height인 삼각형에서 pos위치에 amount개수의 구슬을 떨군다면,
// [begin, back] 구간에 cnt만큼의 기댓값이 더해진다.
// 반환 형식은 (begin, back, cnt)
tuple<ll, ll, double> getResult(int height, ll pos, int amount) {
	pair<ll, ll> range = getRange(height, pos);
	ll begin = range.first;
	ll back = range.second + 1;
	ll length = back - begin + 1;

	double cnt = (double)amount / length;

	return {begin, back, cnt};
}

int main() {

//	int testH = 5;
//	ll start = 1, end = sum(1, testH);
//	for(ll i = start; i <= end; i++) {
//		cout << i << " : " << getHeight(i) << " : " << getLeaf(testH, i) << endl;
//	}
//	cout << endl;



	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(6);

	int H, Q, R;
	cin >> H >> Q >> R;

	int finish_size = H + 1;
	precomputeTri(H);

	// 차분 배열: 인덱스 1부터 H+1까지 사용하므로, H+3 크기로 선언 (H+2 업데이트를 위해)
	vector<double> diff(finish_size + 5, 0.0);
	vector<double> prefix(finish_size + 5, 0.0);

	for(int i = 0; i < Q; i++) {
		ll pos;
		int amount;
		cin >> pos >> amount;

		tuple<ll, ll, double> result = getResult(H, pos, amount);

		ll begin = get<0>(result);
		ll back = get<1>(result);

		diff[begin] += get<2>(result);
		diff[back + 1] -= get<2>(result);
	}


	double current = 0.0;    // 현재까지의 실제 배열 값 (arr[i])
	double sumPrefix = 0.0;  // 현재까지의 prefix sum
	for (int i = 1; i <= finish_size; i++){
		current += diff[i];     // arr[i] 계산
		sumPrefix += current;     // prefix[i] = prefix[i-1] + arr[i]
		prefix[i] = sumPrefix;
	}

	int l, r;
	for(int i = 0; i < R; i++) {
		cin >> l >> r; // [l, r] 구간의 평균 계산
		double sum = prefix[r] - prefix[l-1];

		cout << sum << '\n';
	}

	return 0;
}