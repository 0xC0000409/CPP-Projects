#ifndef HEADER_H_
#define HEADER_H_
#include <utility>
#include <string>
#include <memory>
#include <vector>

typedef std::unique_ptr<int[]> smart_array;
typedef std::unique_ptr<smart_array[]> smart_array3D;

class Divide_Concur {
private:
	const int* coins = nullptr;
	const int* House = nullptr;
	std::pair<int, int>* items = nullptr;
	std::vector<std::vector<int>> Matrix;
	int coinSize = 0;
	size_t HouseSize = 0;
	size_t itemsSize = 0;
	bool init_def = false;

	const int coinChange(const int change, const int n) const;
	const int HouseThief(size_t n, const int index = 0) const;
	const int zero_one_knapsack(const int capacity, size_t n, int index = 0) const;
	const int LPS(const std::string& s, const int bw, const int fw = 0) const;
	const int LPs(const std::string& s, const int bw, const int fw = 0) const;
	const int minCost(const size_t x, const size_t y) const;
	const int numOfWays(const int cost, const int x, const int y);
public:
	Divide_Concur();
	Divide_Concur(const int* _coins, const int _coinSize, const int* _House, const size_t _HouseSize, std::pair<int, int>* _items, size_t _itemsSize, std::vector<std::vector<int>> &_Matrix);
	const int coinChange(const int change) const { return coinChange(change, coinSize - 1); }
	const int HouseThief() const { return HouseThief(HouseSize); }
	const int str_convert(const std::string& trgt, const std::string& orig, const size_t Tidx = 0, const size_t Oidx = 0) const;
	const int zero_one_knapsack(const int capacity) const { return zero_one_knapsack(capacity, itemsSize); }
	const int LCS(const std::string& s1, const std::string& s2, const int s1i = 0, const int s2i = 0) const;
	const int LPS(const std::string& s) const { return LPS(s, s.size()); }
	const int LPs(const std::string& s) const { return LPs(s, s.size()); }
	const int minCost() const { return minCost(Matrix.size(), Matrix[0].size()); };
	const int numOfWays(const int cost) { return numOfWays(cost, Matrix.size() - 1, Matrix[0].size() - 1); }
	~Divide_Concur();
};

class Dynamic_Programming {
private:
	const int* coins = nullptr;
	const int* House = nullptr;
	std::pair<int, int>* items = nullptr;
	std::vector<std::vector<int>> Matrix;
	int coinSize = 0;
	size_t HouseSize = 0;
	size_t itemsSize = 0;
	bool init_def = false;
private:
	const int coinChangeTD(const int change, const int n) const;
	const int coinChangeBU(const int change, const int n) const;
	const int HouseThiefTD(size_t n, const int index = 0) const;
	const int HouseThiefBU(size_t n, const int index = 0) const;
	const int str_convertTD(const std::string& trgt, const std::string& orig, const size_t Tidx = 0, const size_t Oidx = 0) const;
	const int str_convertBU(const std::string& trgt, const std::string& orig) const;
	const int zero_one_knapsackTD(const int capacity, size_t n, int index = 0) const;
	const int zero_one_knapsackBU(const int capacity, size_t n) const;
	const int LCS_TD(const std::string& s1, const std::string& s2, const int s1i = 0, const int s2i = 0) const;
	const int LCS_BU(const std::string& s1, const std::string& s2) const;
	const int LPS_TD(const std::string& s, const int bw, const int fw = 0) const;
	const int LPS_BU(const std::string& s) const;
	const int LPs_TD(const std::string& s, const int bw, const int fw = 0) const;
	const int LPs_BU(const std::string& s) const;
	const int minCostTD(const size_t x, const size_t y) const;
	const int minCostBU(const size_t x, const size_t y) const;
	const int numOfWaysTD(const int cost, const int x, const int y) const;
public:
	Dynamic_Programming();
	Dynamic_Programming(const int* _coins, const int _coinSize, const int* _House, const size_t _HouseSize, std::pair<int, int>* _items, size_t _itemsSize, std::vector<std::vector<int>>& _Matrix) :
		coins(_coins), coinSize(_coinSize), House(_House), HouseSize(_HouseSize), items(_items), itemsSize(_itemsSize), Matrix(_Matrix) {};
	const int coinChange(const int change, char flag = 'T') const;
	const int HouseThief(char flag = 'T') const;
	const int str_convert(const std::string& trgt, const std::string& orig, char flag) const;
	const int zero_one_knapsack(const int capacity, char flag = 'T') const;
	const int LCS(const std::string& s1, const std::string& s2, char flag = 'T') const;
	const int LPS(const std::string& s, char flag = 'T') const;
	const int LPs(const std::string& s, char flag = 'T') const;
	const int minCost(char flag = 'T') const;
	const int numOfWays(const int cost, char flag = 'T') const;
	~Dynamic_Programming();
};

#endif // !HEADER_H_