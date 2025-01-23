#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
	int n, k;
	cin >> n >> k;

	// {id, time}
	vector<pair<int, int>> waiting;

	// {last_time, number}
	priority_queue<
		pair<int, int>,
		deque<pair<int, int>>,
		greater<>
	> cashiers;

	// { finish_time, -cashier_id, customer_id }
	priority_queue<
		tuple<int, int, int>,
		vector<tuple<int, int, int>>,
		greater<>
	> finish_queue;


	// init
	// customers
	for (int i = 0; i < n; i++) {
		int id, duration;
		cin >> id >> duration;
		waiting.emplace_back(id, duration);
	}

	// simulation

	// first k customers
	for (int cashier_id = 0; cashier_id < k; cashier_id++) {
		cashiers.emplace(0, cashier_id);
	}


	for (int i = 0; i < n; i++) {
		auto [id, duration] = waiting[i];
		auto [last_time, number] = cashiers.top(); cashiers.pop();

		int finish_time = last_time + duration;
		finish_queue.emplace(finish_time, -number, id);
		cashiers.emplace(finish_time, number);
	}

	ll r = 1;
	ll answer = 0;
	while (not finish_queue.empty()) {
		auto [finish_time, cashier_id, customer_id] = finish_queue.top(); finish_queue.pop();

		//cout << finish_time << " " << cashier_id << " " << customer_id << endl;

		answer += (r++) * (ll)customer_id;
	}

	cout << answer << endl;

}
