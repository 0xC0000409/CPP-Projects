//average queue size, wait time may not be working
#include <iostream>
#include <cstdlib> // for rand() and srand()
#include <ctime> // for time()
#include "Header.h"
const int MIN_PER_HR = 60;

bool newcustomer(double x); // is there a new customer? (very cool)

int main()
{
	using std::cin; using std::cout; using std::endl; using std::ios_base;

	std::srand(std::time(0)); // random initializing of rand()
	cout << "Case Study: Bank of Heather Automatic Teller\n";
	cout << "Enter maximum size of queue: ";

	int qs;
	cin >> qs;
	queue line(qs);
	queue line2(qs); // line queue holds up to qs people
	cout << "Enter the number of simulation hours: ";
	int hours; // hours of simulation
	cin >> hours;
	// simulation will run 1 cycle per minute
	long cyclelimit = MIN_PER_HR * hours; // # of cycles
	cout << "Enter the average number of customers per hour: ";
	double perhour; // average # of arrival per hour
	cin >> perhour;
	double min_per_cust; // average time between arrivals
	min_per_cust = MIN_PER_HR / perhour;

	Item temp, temp2;
	// new customer data
	long turnaways = 0; // turned away by full queue
	long customers = 0; // joined the queue
	long served = 0; // served during the simulation
	long sum_line = 0; // cumulative line length
	int wait_time = 0; // time until autoteller is free
	long line_wait = 0;
	int wait_time2 = 0;
	long line_wait2 = 0;

	for (int cycle = 0; cycle < cyclelimit; cycle++)
	{
		if (newcustomer(min_per_cust)) // have newcomer
		{
			if (line.isFull() && line2.isFull())
				turnaways++;

			if (line.queueCount() <= line2.queueCount() && !line.isFull()) {
				customers++;
				temp.set(cycle); // cycle = time of arrival
				line.enqueue(temp); // add newcomer to line
			}

			if (line2.queueCount() <= line.queueCount() && !line2.isFull()) {
				customers++;
				temp2.set(cycle);
				line2.enqueue(temp2);
			}
		}
		if (wait_time <= 0 && !line.isEmpty())
		{
			line.dequeue(temp); // attend next customer
			wait_time = temp.ptime(); // for wait_time minutes
			line_wait += cycle - temp.when();
			served++;
		}
		if (wait_time > 0)
			wait_time--;

		if (wait_time2 <= 0 && !line2.isEmpty())
		{
			line2.dequeue(temp2); // attend next customer
			wait_time2 = temp2.ptime(); // for wait_time minutes
			line_wait2 += cycle - temp2.when();
			served++;
		}
		if (wait_time2 > 0)
			wait_time2--;

		sum_line += line.queueCount() + line2.queueCount();
	}
	// reporting results
	if (customers > 0)
	{
		cout << "customers accepted: " << customers << endl;
		cout << " customers served: " << served << endl;
		cout << " turnaways: " << turnaways << endl;
		cout << "average queue size: ";
		cout.precision(2);
		cout.setf(ios_base::fixed, ios_base::floatfield);
		cout << (double)sum_line / cyclelimit << endl;
		cout << " average wait time: "
			<< ((double)line_wait / served + (double)line_wait / served) / 2 << " minutes\n";
	}
	else
		cout << "No customers!\n";
	cout << "Done!\n";

	return 0;
}
// x = average time, in minutes, between customers
// return value is true if customer shows up this minute
bool newcustomer(double x)
{
	return (std::rand() * x / RAND_MAX < 1);
}