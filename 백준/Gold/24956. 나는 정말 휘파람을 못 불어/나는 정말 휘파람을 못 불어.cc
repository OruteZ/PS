#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

typedef long long int ll;

int main()
{
	int size;
	cin >> size;

	string str;
	cin >> str;

	ll W = 0;
	ll WH = 0;
	ll WHE = 0;
	ll WHEE = 0;

	for (int i = 0; i < size; i++)
	{

		if (str[i] == 'W')
		{
			W++;
			W %= MOD;
		}
		else if (str[i] == 'H')
		{
			WH += W;
			WH %= MOD;
		}
		else if (str[i] == 'E')
		{
			WHEE += WHE + WHEE;
			WHEE %= MOD;

			WHE += WH;
			WHE %= MOD;
		}

		//cout << W << " " << WH << " " << WHE << " " << WHEE << endl;
	}

	cout << WHEE % MOD << endl;

}