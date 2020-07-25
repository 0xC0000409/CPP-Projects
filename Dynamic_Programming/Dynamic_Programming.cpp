#include <iostream>
#include <vector>
#include <algorithm>
#include "Header.h"
using namespace std;

const string LCS_BU(const std::string& s1, const std::string& s2) {
	std::string temp = "";
	auto tempArr = std::unique_ptr<smart_array[]>(new smart_array[s1.size() + 1]{});
	for (int i = 0; i <= s1.size(); i++)
		tempArr[i] = smart_array(new int[s2.size() + 1]{});

	for (size_t i = s1.size(); i-- > 0;) { //starts with s1.size() - 1
		int x1 = 0, x2 = 0;
		for (size_t j = s2.size(); j-- > 0;) {
			if (s1[i] == s2[j])
				tempArr[i][j] = 1 + tempArr[i + 1][j + 1];
			else {
				x1 = tempArr[i][j + 1];
				x2 = tempArr[i + 1][j];
				tempArr[i][j] = std::max(x1, x2);
			}
			if (tempArr[i][j] > temp.size()) {
				temp += s1[i];
			}
		}
	}
	return temp;
}

int main() {
	Divide_Concur dc; Dynamic_Programming dp;
	cout << dp.coinChange(1000, 'b') << endl;
	cout << dp.HouseThief('T') << endl;
	cout << dp.str_convert("str", "string", 't') << endl;
	cout << dp.zero_one_knapsack(15) << endl;
	cout << dp.zero_one_knapsack(15, 'B') << endl;
	cout << dp.LCS("ABCBDAB", "BDCABA", 'b') << endl;
	cout << dp.LPS("tattarrattat", 't') << endl;
	cout << dp.LPs("tattarttat", 'b') << endl;
	cout << dp.minCost() << endl;
	cout << dp.numOfWays(40) << endl;
	string s = LCS_BU("ABCBDAB", "BDCABA");
	reverse(s.begin(), s.end());
	cout << s << endl;
}
