#include "LinkedQueueLib.cpp"
using namespace Queue;

int main()
{
	using std::cout; using std::endl;

	LinkedQueue<const char*> *lq = new LinkedQueue<const char*>;
	lq->Push("zuka");
	lq->Push("vaja");
	lq->Push("gurama");
	lq->Push("ako");

	cout << "Front: " << lq->Front() << endl;
	cout << "Back: " << lq->Back() << endl;

	lq->Pop(); lq->Pop(); lq->Push("Area 51");

	cout << "Front: " << lq->Front() << endl;
	cout << "Back: " << lq->Back() << endl;
}
