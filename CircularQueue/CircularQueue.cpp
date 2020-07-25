#include "CircularQueueLib.cpp"
using namespace cQueue;

int main()
{
	CircularQueue<double> cq(4);
	cq.push_back(2.3); cq.push_back(3.5); cq.push_back(5.7); cq.push_back(7.11);
	cq.pop(); 
	cq.push_back(11.13); 
	cq.pop(); cq.pop(); cq.pop(); cq.pop(); cq.pop();
	cq.push_back(13.17); 
	cq.pop(); 
	cq.push_back(17.19); cq.push_back(19.23); cq.push_back(23.27);
	cq.pop();
}
