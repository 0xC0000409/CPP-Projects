#include "Header.h"
#include <algorithm>
#include <iostream>
#include <cmath>

Divide_Concur::Divide_Concur() {
	coins = new int[5]{ 1, 5, 10, 25, 50 };
	House = new int[7]{ 6, 7, 1, 30, 8, 2, 4 };
	items = new std::pair<int, int>[3]{ {60, 10}, {100, 20}, {120, 30} };
	
	Matrix = {
		{ 4, 7, 8, 6, 4 },
		{ 6, 7, 3, 9, 2 },
		{ 3, 8, 1, 2, 4 },
		{ 7, 1, 7, 3, 7 },
		{ 2, 9, 8, 9, 3 }
	};
	
	coinSize = 5;
	HouseSize = 7;
	itemsSize = 3;
	init_def = true;
}

Divide_Concur::Divide_Concur(const int* _coins, const int _coinSize, const int* _House, const size_t _HouseSize, std::pair<int, int>* _items, size_t _itemsSize, std::vector<std::vector<int>>& _Matrix
) : coins(_coins), coinSize(_coinSize), House(_House), HouseSize(_HouseSize), items(_items), itemsSize(_itemsSize), Matrix(_Matrix) {
}

const int Divide_Concur::coinChange(const int change, int n) const {
	if (change == 0)
		return 1;
	else if (change < 0 || n < 0)
		return 0;
	else
		return coinChange(change, n - 1) + coinChange(change - coins[n], n);
}

const int Divide_Concur::HouseThief(size_t n, const int index) const {
	if (index >= n)
		return 0;
	
	int steal = House[index] + HouseThief(n, index + 2);
	int skip = HouseThief(n, index + 1);

	return std::max(steal, skip);
}

const int Divide_Concur::str_convert(const std::string& trgt, const std::string& orig, const size_t Tidx, const size_t Oidx) const {
	if (Tidx >= trgt.size())
		return orig.size() - Oidx;

	if (Oidx >= orig.size())
		return trgt.size() - Tidx;

	if (orig[Oidx] == trgt[Tidx])
		str_convert(trgt, orig, Tidx + 1, Oidx + 1);
	else {
		int insrt = 1 + str_convert(trgt, orig, Tidx, Oidx + 1);
		int rmv = 1 + str_convert(trgt, orig, Tidx + 1, Oidx);
		int rplc = 1 + str_convert(trgt, orig, Tidx + 1, Oidx + 1);

		return std::min({ rmv, insrt, rplc });
	}
}

const int Divide_Concur::zero_one_knapsack(const int capacity, size_t n, int index) const {
	int profit1 = 0;

	if (capacity <= 0 || index >= n)
		return 0;
	else if (items[index].second <= capacity)
		profit1 = items[index].first + zero_one_knapsack(capacity - items[index].second, n, index + 1);

	int profit2 = zero_one_knapsack(capacity, n, index + 1);

	return std::max(profit1, profit2);
}

const int Divide_Concur::LCS(const std::string& s1, const std::string& s2, const int s1i, const int s2i) const { //Longest Common Subsequence
	if (s1i >= s1.size() || s2i >= s2.size())
		return 0;

	if (s1[s1i] == s2[s2i])
		return 1 + LCS(s1, s2, s1i + 1, s2i + 1);

	int m1 = LCS(s1, s2, s1i + 1, s2i);
	int m2 = LCS(s1, s2, s1i, s2i + 1);

	return std::max(m1, m2);

}

//----Custom LPS (Needs additional testing, but everything seems to work fine)----
//Caution: bw in given argument is equal to s1 size so, s1[bw] = '\0', but it seems to work anyway.
const int Divide_Concur::LPS(const std::string& s, const int bw, const int fw) const { //Longest Palindromic Subsequence
	if (fw >= s.size() || bw < 0)
		return 0;

	if (s[fw] == s[bw])
		return 1 + LPS(s, bw - 1, fw + 1);

	int forward = LPS(s, bw, fw + 1);
	int backward = LPS(s, bw - 1, fw);

	return std::max(forward, backward);
}

const int Divide_Concur::LPs(const std::string& s, const int bw, const int fw) const {
	if (fw >= s.size() || bw < 0)
		return 0;

	if (fw == bw)
		return 1;

	int z = 0;
	if (s[fw] == s[bw]) {
		int remaining_lngth = bw - fw - 1;
		if (remaining_lngth == LPs(s, bw - 1, fw + 1))
			z = remaining_lngth + 2;
	}
	int forward = LPs(s, bw, fw + 1);
	int backward = LPs(s, bw - 1, fw);

	return std::max({ forward, backward, z });
}

const int Divide_Concur::minCost(const size_t x, const size_t y) const {
	if (x <= 0 || y <= 0)
		return INT_MAX;

	if (x == 1 && y == 1)
		return Matrix[0][0];

	return std::min(minCost(x - 1, y), minCost(x, y - 1)) + Matrix[__int64(x) - 1][__int64(y) - 1];
}

const int Divide_Concur::numOfWays(const int cost, const int x, const int y) {
	if (x < 0 || y < 0 || cost < 0)
		return 0;

	if (x == 0 && y == 0)
		return ((cost - Matrix[0][0]) >= 0) ? 1 : 0;

	return numOfWays(cost - Matrix[x][y], x - 1, y) + numOfWays(cost - Matrix[x][y], x, y - 1);
}

Divide_Concur::~Divide_Concur() {
	if (init_def) {
		delete[] coins;
		delete[] House;
		delete[] items;
	}
}

Dynamic_Programming::Dynamic_Programming() {
	coins = new int[5]{ 1, 5, 10, 25, 50 };
	House = new int[7]{ 6, 7, 1, 30, 8, 2, 4 };
	items = new std::pair<int, int>[3]{ {60, 10}, {100, 20}, {120, 30} };

	Matrix = {
		{ 4, 7, 8, 6, 4 },
		{ 6, 7, 3, 9, 2 },
		{ 3, 8, 1, 2, 4 },
		{ 7, 1, 7, 3, 7 },
		{ 2, 9, 8, 9, 3 }
	};

	coinSize = 5;
	HouseSize = 7;
	itemsSize = 3;
	init_def = true;
}

//Top-down approach
const int Dynamic_Programming::coinChangeTD(const int change, const int n) const {
	static auto temp = std::unique_ptr<smart_array[]>(new smart_array[change + 1]{});
	for (static int i = 0; i <= change; i++)
		temp[i] = smart_array(new int[__int64(n) + 1]{});

	if (change < 0 || n < 0)
		return 0;
	else if (change == 0)
		return 1;

	if (temp[change][n] == 0)
		temp[change][n] = coinChangeTD(change, n - 1) + coinChangeTD(change - coins[n], n);

	return temp[change][n];
}

const int Dynamic_Programming::coinChangeBU(const int change, const int n) const {
	int x = 0, y = 0;

	int vSize = change + 1;
	auto table = std::unique_ptr<smart_array[]>(new smart_array[vSize]{});
	for (int i = 0; i < vSize; i++)
		table[i] = smart_array(new int[n] {});

	for (int j = 0; j < n; j++)
		table[0][j] = 1;

	for (int i = 1; i < vSize; i++) {
		for (int j = 0; j < n; j++) {
			x = (i - coins[j] >= 0) ? table[__int64(i) - coins[j]][j] : 0;
			y = (j >= 1) ? table[i][__int64(j) - 1] : 0;

			table[i][j] = x + y;
		}
	}
	return table[change][__int64(n) - 1];
}

const int Dynamic_Programming::HouseThiefTD(size_t n, const int index) const {
	static std::unique_ptr<int[]> temp(new int[n] {});

	if (index >= n)
		return 0;

	if (temp[index] == 0) {
		int steal = House[index] + HouseThiefTD(n, index + 2);
		int skip = HouseThiefTD(n, index + 1);
		temp[index] = std::max(steal, skip);
	}
	return temp[index];
}

const int Dynamic_Programming::HouseThiefBU(size_t n, const int index) const {
	std::unique_ptr<int[]> temp(new int[n]);
	temp[n - 1] = House[n - 1];
	int a = 0, b = 0;

	for (int i = n - 2; i >= 0; i--) {
		a = ((__int64(i) + 2) < n) ? House[i] + temp[__int64(i) + 2] : 0;
		b = ((__int64(i) + 1) < n) ? temp[__int64(i) + 1] : 0;

		temp[i] = std::max(a, b);
	}

	return temp[0];
}

const int Dynamic_Programming::str_convertTD(const std::string& trgt, const std::string& orig, const size_t Tidx, const size_t Oidx) const {
	static auto temp = std::unique_ptr<smart_array[]>(new smart_array[trgt.size() + 1]{});
	for (static int i = 0; i <= trgt.size(); i++)
		temp[i] = smart_array(new int[orig.size() + 1]{});

	if (temp[Tidx][Oidx] == 0) {
		if (Tidx == trgt.size())
			temp[Tidx][Oidx] = orig.size() - Oidx;
		else if (Oidx == orig.size())
			temp[Tidx][Oidx] = trgt.size() - Tidx;
		else if (trgt[Tidx] == orig[Oidx])
			temp[Tidx][Oidx] = str_convertTD(trgt, orig, Tidx + 1, Oidx + 1);
		else {
			int insrt = str_convertTD(trgt, orig, Tidx, Oidx + 1);
			int rmv = str_convertTD(trgt, orig, Tidx + 1, Oidx);
			int rplc = str_convertTD(trgt, orig, Tidx + 1, Oidx + 1);

			temp[Tidx][Oidx] = 1 + std::min({ rmv, insrt, rplc });
		}
	}
	return temp[Tidx][Oidx];
}

const int Dynamic_Programming::str_convertBU(const std::string& trgt, const std::string& orig) const {
	auto temp = std::unique_ptr<smart_array[]>(new smart_array[trgt.size() + 1]{});
	for (size_t i = 0; i < trgt.size() + 1; i++)
		temp[i] = smart_array(new int[orig.size() + 1]{});

	for (size_t i = 0, j = 0; i <= orig.size() && j <= trgt.size(); i++, j++) {
		temp[trgt.size()][i] = orig.size() - i;
		temp[j][orig.size()] = trgt.size() - j;

	}
	for (int i = trgt.size() - 1; i >= 0; i--) {
		for (int j = orig.size() - 1; j >= 0; j--) {
			if (trgt[i] == orig[j])
				temp[i][j] = temp[__int64(i) + 1][__int64(j) + 1];
			else
				temp[i][j] = 1 + std::min({ temp[i][__int64(j) + 1], temp[__int64(i) + 1][j], temp[__int64(i) + 1][__int64(j) + 1] });
		}
	}
	return temp[0][0];
}

const int Dynamic_Programming::zero_one_knapsackTD(const int capacity, size_t n, int index) const {
	static auto temp = std::unique_ptr<smart_array[]>(new smart_array[n]{});
	for (static int i = 0; i < n; i++)
		temp[i] = smart_array(new int[__int64(capacity) + 1]{});

	if (capacity <= 0 || index >= n)
		return 0;
	if (temp[index][capacity] != 0)
		return temp[index][capacity];

	int profit1 = 0;
	if (items[index].second <= capacity)
		profit1 = items[index].first + zero_one_knapsackTD(capacity - items[index].second, n, index + 1);

	int profit2 = zero_one_knapsackTD(capacity, n, index + 1);
	temp[index][capacity] = std::max(profit1, profit2);

	return temp[index][capacity];
}

const int Dynamic_Programming::zero_one_knapsackBU(const int capacity, size_t n) const {
	auto tempArr = std::unique_ptr<smart_array[]>(new smart_array[__int64(n) + 1]{}); //n + 1 is need to access the whole items[]
	for (int i = 0; i <= n; i++)
		tempArr[i] = smart_array(new int[__int64(capacity) + 1]{});

	for (int r = n - 1; r >= 0; r--) {
		for (int c = 1; c <= capacity; c++) {
			int profit1 = 0, profit2 = 0;
			if (items[r].second <= c)
				profit1 = items[r].first + tempArr[__int64(r) + 1][__int64(c) - items[r].second];

			profit2 = tempArr[__int64(r) + 1][c];

			tempArr[r][c] = std::max(profit1, profit2);
		}
	}
	return tempArr[0][capacity];
}

const int Dynamic_Programming::LCS_TD(const std::string& s1, const std::string& s2, const int s1i, const int s2i) const {
	static auto temp = std::unique_ptr<smart_array[]>(new smart_array[s1.size() + 1]{});
	for (static int i = 0; i <= s1.size(); i++)
		temp[i] = smart_array(new int[s2.size() + 1]{});

	if (s1i >= s1.size() || s2i >= s2.size())
		return 0;

	if (temp[s1i][s2i] != 0)
		return temp[s1i][s2i];

	if (s1[s1i] == s2[s2i])
		temp[s1i][s2i] = 1 + LCS_TD(s1, s2, s1i + 1, s2i + 1);
	else {
		int m1 = LCS_TD(s1, s2, s1i + 1, s2i);
		int m2 = LCS_TD(s1, s2, s1i, s2i + 1);
		temp[s1i][s2i] = std::max(m1, m2);
	}
	return temp[s1i][s2i];
}

const int Dynamic_Programming::LCS_BU(const std::string& s1, const std::string& s2) const {
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
		}
	}

	return tempArr[0][0];
}

const int Dynamic_Programming::LPS_TD(const std::string& s, const int bw, const int fw) const {
	static auto temp = std::unique_ptr<smart_array[]>(new smart_array[s.size()]{});
	for (static int i = 0; i < s.size(); i++)
		temp[i] = smart_array(new int[s.size()]{});

	if (fw > bw)
		return 0;

	if (temp[fw][bw] != 0)
		return temp[fw][bw];
	else if (fw == bw)
		temp[fw][bw] = 1;
	else if (s[fw] == s[bw])
		temp[fw][bw] = 2 + LPS_TD(s, bw - 1, fw + 1);
	else {
		int forward = LPS_TD(s, bw, fw + 1);
		int backward = LPS_TD(s, bw - 1, fw);

		temp[fw][bw] = std::max(forward, backward);
	}
	return temp[fw][bw];
}


const int Dynamic_Programming::LPS_BU(const std::string& s) const {
	auto temp = std::unique_ptr<smart_array[]>(new smart_array[s.size() + 1]{});
	for (static int i = 0; i < s.size() + 1; i++)
		temp[i] = smart_array(new int[s.size() + 1]{});

	for (size_t i = 0; i < s.size(); i++) {
		for (size_t j = s.size() - 1; j-- > 0;) {
			if (j <= i) {
				if (i == j)
					temp[j][i] = 1;
				else if (s[i] == s[j])
					temp[j][i] = 2 + temp[j + 1][i - 1];
				else
					temp[j][i] = std::max(temp[j + 1][i], temp[j][i - 1]);
			}
		}
	}
	return temp[0][s.size() - 1];
}

const int Dynamic_Programming::LPs_TD(const std::string& s, const int bw, const int fw) const {
	static auto temp = std::unique_ptr<smart_array[]>(new smart_array[s.size() + 1]{});
	for (static int i = 0; i <= s.size(); i++)
		temp[i] = smart_array(new int[s.size() + 1]{});

	if (fw >= s.size() || bw < 0)
		return 0;
	else if (fw == bw)
		temp[fw][bw] = 1;
	else if (temp[fw][bw] == 0) {
		int z = 0;
		if (s[fw] == s[bw]) {
			int remaining_lngth = bw - fw - 1;
			if (remaining_lngth == LPs_TD(s, bw - 1, fw + 1))
				z = remaining_lngth + 2;
		}
		int forward = LPs_TD(s, bw, fw + 1);
		int backward = LPs_TD(s, bw - 1, fw);

		temp[fw][bw] = std::max({ forward, backward, z });
	}
	return temp[fw][bw];
}
//Different approach than just reverse engineering top-down approach
const int Dynamic_Programming::LPs_BU(const std::string& s) const {
	auto temp = std::unique_ptr<smart_array[]>(new smart_array[s.size() + 1]{});
	for (int i = 0; i <= s.size(); i++)
		temp[i] = smart_array(new int[s.size() + 1]{});

	for (size_t i = 0; i < s.size(); i++)
		temp[i][i] = 1;

	for (size_t i = 0; i < s.size() - 1; i++)
		if (s[i] == s[i + 1])
			temp[i][i + 1] = 2;

	for (size_t k = 3; k <= s.size(); k++) {
		for (int i = 0; i < s.size() - k + 1; i++) {
			int j = i + k - 1;
			if (s[i] == s[j] && temp[__int64(i) + 1][__int64(j) - 1] != 0)
				temp[i][j] = std::max({ temp[__int64(i) + 1][__int64(j) - 1] + 2, temp[i][__int64(j) - 1], temp[__int64(i) + 1][j] });
			else
				temp[i][j] = std::max(temp[i][__int64(j) - 1], temp[__int64(i) + 1][j]);
		}
	}
	return temp[0][s.size() - 1];
}

const int Dynamic_Programming::minCostTD(const size_t x, const size_t y) const {
	static auto temp = std::unique_ptr<smart_array[]>(new smart_array[x + 1]{});
	for (static int i = 0; i <= x; i++)
		temp[i] = smart_array(new int[y + 1]{});

	if (x <= 0 || y <= 0)
		return USHRT_MAX;

	if (temp[x][y] != 0)
		return temp[x][y];

	if (x == 1 && y == 1)
		temp[x][y] = Matrix[0][0];
	else
		temp[x][y] = Matrix[x - 1][y - 1] + std::min(minCostTD(x - 1, y), minCostTD(x, y - 1));

	return temp[x][y];
}

const int Dynamic_Programming::minCostBU(const size_t x, const size_t y) const {
	auto temp = std::unique_ptr<smart_array[]>(new smart_array[x + 1]{});
	for (size_t i = 0; i <= x; i++)
		temp[i] = smart_array(new int[y + 1]{});

	for (size_t i = 0; i <= x; i++)
		temp[i][0] = USHRT_MAX;

	for (size_t j = 0; j <= y; j++)
		temp[0][j] = USHRT_MAX;

	temp[0][1] = 0;
	for (size_t i = 1; i <= x; i++)
		for (size_t j = 1; j <= y; j++)
			temp[i][j] = Matrix[i - 1][j - 1] + std::min(temp[i - 1][j], temp[i][j - 1]);

	return temp[x][y];
}

const int Dynamic_Programming::numOfWaysTD(const int cost, const int x, const int y) const {
	static auto temp = std::unique_ptr<smart_array3D[]>(new smart_array3D[x + 1]{});
	for (static int i = 0; i <= x; i++) {
		temp[i] = smart_array3D(new smart_array[y + 1]{});
		for (int j = 0; j <= y; j++) {
			temp[i][j] = smart_array(new int[cost + 1]{});
		}
	}
	if (x < 0 || y < 0 || cost < 0)
		return 0;

	if (x == 0 && y == 0)
		return ((cost - Matrix[0][0]) >= 0) ? 1 : 0;

	if (temp[x][y][cost] == 0)
		temp[x][y][cost] = numOfWaysTD(cost - Matrix[x][y], x - 1, y) + numOfWaysTD(cost - Matrix[x][y], x, y - 1);

	return temp[x][y][cost];
}

const int Dynamic_Programming::coinChange(const int change, char flag) const {
	if (flag == 'T' || flag == 't') {
		std::cout << "Coin change problem->(Top-down approach): ";
		return coinChangeTD(change, coinSize - 1);
	}
	else if (flag == 'B' || flag == 'b') {
		std::cout << "Coin change problem->(Bottom-up approach): ";
		return coinChangeBU(change, coinSize);
	}
	else
		std::cout << "Please specify a flag(T(t) or B(b)) Error Value: ";

	return -1;
}

const int Dynamic_Programming::HouseThief(char flag) const {
	if (flag == 'T' || flag == 't') {
		std::cout << "House Thief problem->(Top-down approach): ";
		return HouseThiefTD(HouseSize);
	}
	else if (flag == 'B' || flag == 'b') {
		std::cout << "House Thief problem->(Bottom-up approach): ";
		return HouseThiefBU(HouseSize);
	}
	else
		std::cout << "Please specify a flag(T(t) or B(b)) Error Value: ";

	return -1;
}

const int Dynamic_Programming::str_convert(const std::string& trgt, const std::string& orig, char flag) const {
	if (flag == 'T' || flag == 't') {
		std::cout << "String convert problem->(Top-down approach): ";
		return str_convertTD(trgt, orig);
	}
	else if (flag == 'B' || flag == 'b') {
		std::cout << "String convert problem->(Bottom-up approach): ";
		return str_convertBU(trgt, orig);
	}
	else
		std::cout << "Please specify a flag(T(t) or B(b)) Error Value: ";

	return -1;
}

const int Dynamic_Programming::zero_one_knapsack(const int capacity, char flag) const {
	if (flag == 'T' || flag == 't') {
		std::cout << "0/1 knapsack problem->(Top-down approach): ";
		return zero_one_knapsackTD(capacity, itemsSize);
	}
	else if (flag == 'B' || flag == 'b') {
		std::cout << "0/1 knapsack problem->(Bottom-up approach): ";
		return zero_one_knapsackBU(capacity, itemsSize);
	}
	else
		std::cout << "Please specify a flag(T(t) or B(b)) Error Value: ";

	return -1;
}

const int Dynamic_Programming::LCS(const std::string& s1, const std::string& s2, char flag) const {
	if (flag == 'T' || flag == 't') {
		std::cout << "Longest common subsequence knapsack problem->(Top-down approach): ";
		return LCS_TD(s1, s2);
	}
	else if (flag == 'B' || flag == 'b') {
		std::cout << "Longest common subsequence problem->(Bottom-up approach): ";
		return LCS_BU(s1, s2);
	}
	else
		std::cout << "Please specify a flag(T(t) or B(b)), Error Value: ";

	return -1;
}

const int Dynamic_Programming::LPS(const std::string& s, char flag) const {
	if (flag == 'T' || flag == 't') {
		std::cout << "Longest Palindromic Substring Problem->(Top-down approach): ";
		return LPS_TD(s, s.size() - 1);
	}
	else if (flag == 'B' || flag == 'b') {
		std::cout << "Longest Palindromic Substring Problem->(Bottom-up approach): ";
		return LPS_BU(s);
	}
	else
		std::cout << "Please specify a flag(T(t) or B(b)), Error Value: ";

	return -1;
}

const int Dynamic_Programming::LPs(const std::string& s, char flag) const {
	if (flag == 'T' || flag == 't') {
		std::cout << "Longest Palindromic Substring Problem->(Top-down approach): ";
		return LPs_TD(s, s.size());
	}
	else if (flag == 'B' || flag == 'b') {
		std::cout << "Longest Palindromic Substring Problem->(Bottom-up approach): ";
		return LPs_BU(s);
	}
	else
		std::cout << "Please specify a flag(T(t) or B(b)), Error Value: ";

	return -1;
}

const int Dynamic_Programming::minCost(char flag) const {
	if (flag == 'T' || flag == 't') {
		std::cout << "Min cost to reach end of array Problem->(Top-down approach): ";
		return minCostTD(Matrix.size(), Matrix[0].size());
	}
	else if (flag == 'B' || flag == 'b') {
		std::cout << "Min cost to reach end of array Problem-->(Bottom-up approach): ";
		return minCostBU(Matrix.size(), Matrix[0].size());
	}
	else
		std::cout << "Please specify a flag(T(t) or B(b)), Error Value: ";

	return -1;
}

const int Dynamic_Programming::numOfWays(const int cost, char flag) const {
	if (flag == 'T' || flag == 't') {
		std::cout << "Number of ways to reach end of array Problem->(Top-down approach): ";
		return numOfWaysTD(cost, Matrix.size() - 1, Matrix[0].size() - 1);
	}
	else if (flag == 'B' || flag == 'b') {
		std::cout << "Bottom-up approach unavailable right now: "
			/*"Number of ways to reach end of array Problem-->(Bottom-up approach): "*/;
		return 0;
	}
	else
		std::cout << "Please specify a flag(T(t) or B(b)), Error Value: ";

	return -1;
}

Dynamic_Programming::~Dynamic_Programming() {
	if (init_def) {
		delete[] coins;
		delete[] House;
		delete[] items;
	}
}