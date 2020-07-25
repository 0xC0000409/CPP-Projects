#ifndef HEADER_H_
#define HEADER_H_
#include <string>

//base abstract class
class AbsHashing {
protected:
	int hTableSize = 0;
	const int tableSize() const { return hTableSize; }
public:
	AbsHashing(const int TableSize);
	int HashFunc(const std::string& str) const;
	virtual void insertVal(const std::string& str) = 0;
	virtual ~AbsHashing() {};
};

class DirectHashing : public AbsHashing {
private:
	struct Node {
		std::string hashStr = "\0";
		Node* next = nullptr;
	};
	Node* HashArr;
public:
	DirectHashing(const int TableSize);
	void insertVal(const std::string& str);
	~DirectHashing();
};

class LinearHashing : public AbsHashing {
protected:
	std::string* HashArr;
	int NumOfElements = 0;
public:
	LinearHashing(const int TableSize);
	virtual void insertVal(const std::string& str);
	virtual ~LinearHashing();
};

class QuadraticHashing : public LinearHashing {
public:
	QuadraticHashing(const int TableSize) : LinearHashing(TableSize) {};
	void insertVal(const std::string& str);
	~QuadraticHashing() {};
};

class DoubleHashing : public LinearHashing {
	DoubleHashing(const int TableSize) : LinearHashing(TableSize) {};
	void insertVal(const std::string& str);
	~DoubleHashing() {};
};

#endif // !HEADER_H_