#include <bits/stdc++.h>
using namespace std;

// N명의 아이, M개의 놀이기구
// 각 놀이기구의 운행 시간: times[i]

static long long N, M;
static vector<long long> times;

// 함수: 시점 T(분)까지 탈 수 있는 전체 인원 수를 계산
long long totalRiders(long long T) {
	// 0분에 이미 모든 놀이기구에 사람이 1명씩 탑승했다고 가정
	// T분 동안, 각 놀이기구는 floor(T / times[i])번 추가로 태울 수 있음
	// 따라서 각 놀이기구별로 (T / times[i]) + 1 명 탑승 가능
	long long count = 0;
	for(int i = 0; i < M; i++) {
		count += (T / times[i]) + 1;
	}
	return count;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	// 입력 받기
	cin >> N >> M;
	times.resize(M);
	for(int i = 0; i < M; i++){
		cin >> times[i];
	}

	// 만약 놀이기구 수(M)가 아이 수(N) 이상이면
	// N번째 아이는 그냥 N번째 놀이기구(또는 남는 가장 번호가 작은 놀이기구)를 타게 됨.
	// (왜냐하면 0분에 이미 1명씩 탈 수 있으므로)
	// 이 경우, 단순히 N명 모두가 한 번에 탈 수 있기 때문에
	// N <= M일 경우에는 N번째 아이가 타는 놀이기구 번호는 N이 됨.
	if(N <= M){
		cout << N << "\n";
		return 0;
	}

	// 1) 이분 탐색으로 "N명이 모두 탑승 가능한 최소 시점(answerT)" 찾기
	//    시간의 최댓값: 모든 놀이기구 운행시간이 1분일 때, (N명을 태우려면) 최대 1분 * N번 운행
	//    혹은 문제 조건에서 운행시간이 최대 30이므로, 안전하게 30 * N까지 탐색 범위를 잡는다.
	long long left = 0;
	long long right = 30LL * N;  // 최대 30 * N
	long long answerT = right;

	while(left <= right){
		long long mid = (left + right) / 2;

		// mid분까지 탈 수 있는 사람 수
		long long riders = totalRiders(mid);

		// mid분까지 N명 이상 탈 수 있다면, 시간을 더 줄일 수 있는지 확인
		if(riders >= N){
			answerT = mid;
			right = mid - 1;
		} else {
			// N명을 태우기에 아직 부족하다면 시간을 늘려야 함
			left = mid + 1;
		}
	}

	// 여기까지 오면 answerT는 "N명이 모두 탈 수 있게 되는 최소 시간"이 됨
	// 2) (answerT-1)분까지 탄 사람 수를 구한다.
	//    answerT가 0이 될 수도 있으니 조건 체크
	long long countUntilPrev = 0;
	if(answerT > 0){
		for(int i = 0; i < M; i++){
			countUntilPrev += ((answerT - 1) / times[i]) + 1;
		}
	}

	// 3) 마지막 아이( N번째 )가 answerT 시점에 몇 번째로 탑승하는지
	//    => (N - (answerT-1까지 탑승한 사람 수)) 번째
	long long pos = N - countUntilPrev;

	// 4) answerT에 새로 비는 놀이기구(즉, answerT 시점에 딱 운행이 끝나는 놀이기구)를
	//    번호 오름차순(1번 -> 2번 -> ... -> M번)으로 확인하며 pos번째에 해당하는 놀이기구 번호를 찾는다.
	long long result = -1;
	for(int i = 0; i < M; i++){
		// 놀이기구 i가 answerT에 정확히 운행을 마치는 경우
		// => answerT % times[i] == 0
		if(answerT % times[i] == 0){
			pos--;
			if(pos == 0){
				result = i + 1; // 놀이기구 번호는 (i+1)
				break;
			}
		}
	}

	// 결과 출력
	cout << result << "\n";
	return 0;
}
