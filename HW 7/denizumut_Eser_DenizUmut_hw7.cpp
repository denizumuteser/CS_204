#include <iostream>
#include <thread>
#include <mutex>

#include <random>
#include <time.h>

#include <chrono>
#include <ctime>
#include <iomanip>

#include "denizumut_Eser_DenizUmut_hw7_HW7DynIntQueue.h"


using namespace std;

mutex filling_queue_mutex, packing_queue_mutex, cout_mutex;

HW7DynIntQueue filling_queue; //queue for empty boxes
HW7DynIntQueue packing_queue; //queue for filled boxes

//vars
int total_box_count;
int finished_box_count;
int min_producer, max_producer, min_filler, max_filler, min_packager, max_packager;

int random_range(const int& min, const int& max)
{
	static mt19937 generator(time(0));
	uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);
}

tm* get_current_time()
{
	time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
	struct tm* ptm = new struct tm;
	localtime_s(ptm, &tt);
	return ptm;
}

void producer() //produce empty boxes
{
	int wait;
	int size;
	for (int i = 1; i < total_box_count+1; i++)
	{

		//wait
		wait = random_range(min_producer, max_producer);
		this_thread::sleep_for(chrono::seconds(wait)); //simulation for production

		//produce
		filling_queue_mutex.lock();
		filling_queue.enqueue(i);
		size = filling_queue.getCurrentSize();
		filling_queue_mutex.unlock();

		//print
		cout_mutex.lock();
		cout << "Producer has enqueued a new box " << i << " to filling queue (filling queue size is " << size << "): " << put_time(get_current_time(), "%X") << endl;
		cout_mutex.unlock();


	}
}


void filler(int id) //fills empty boxes, 2 workers
{
	int item;
	int wait;
	int counter = 0;
	int filling_size;
	int packing_size;
	while (total_box_count > finished_box_count)
	{
		filling_queue_mutex.lock();
		if (!filling_queue.isEmpty())
		{

			//recieving
			filling_queue.dequeue(item);
			filling_size = filling_queue.getCurrentSize();
			filling_queue_mutex.unlock();

			//print start
			cout_mutex.lock();
			cout << "Filler " << id << " started filling the box " << item << " (filling queue size is " << filling_size << "): " << put_time(get_current_time(), "%X") << endl;
			cout_mutex.unlock();

			//wait
			wait = random_range(min_filler, max_filler);
			this_thread::sleep_for(chrono::seconds(wait)); //simulation for filling

			//print stop
			cout_mutex.lock();
			cout << "Filler " << id << " finished filling the box " << item << ": " << put_time(get_current_time(), "%X") << endl;
			cout_mutex.unlock();

			//send to packing queue
			packing_queue_mutex.lock();
			packing_queue.enqueue(item);
			packing_size = packing_queue.getCurrentSize();
			packing_queue_mutex.unlock();

			//print send boxed
			cout_mutex.lock();
			cout << "Filler " << id << " put box " << item << " into packaging queue (packaging queue size is " << packing_size << "): " << put_time(get_current_time(), "%X") << endl;
			cout_mutex.unlock();

		}
		else
		{
			filling_queue_mutex.unlock();
		}
	}
}

void packager(int id) //packs filled boxes, 2 workers
{
	int item;
	int wait;
	int counter = 0;
	int size;
	while (total_box_count > finished_box_count)
	{
		packing_queue_mutex.lock();
		if (!packing_queue.isEmpty())
		{
			//recieving boxes
			packing_queue.dequeue(item);
			size = packing_queue.getCurrentSize();
			packing_queue_mutex.unlock();

			//print start
			cout_mutex.lock();
			cout << "Packager " << id << " started packing the box " << item << " (packing queue size is " << size << "): " << put_time(get_current_time(), "%X") << endl;
			cout_mutex.unlock();

			//wait
			wait = random_range(min_packager, max_packager);
			this_thread::sleep_for(chrono::seconds(wait)); //simulation for packing

			//print stop
			cout_mutex.lock();
			cout << "Packager " << id << " finished packing the box " << item << ": "<< put_time(get_current_time(), "%X") << endl;
			cout_mutex.unlock();

			finished_box_count++;
		}
		else
		{
			packing_queue_mutex.unlock();
		}
		
	}
}

int main()
{

	//taking inputs
	cout << "Please enter the total number of items: ";
	cin >> total_box_count;
	cout << "Please enter the min-max waiting time range of producer:" << endl;
	cout << "Min: ";
	cin >> min_producer;
	cout << "max: ";
	cin >> max_producer;
	cout << "Please enter the min-max waiting time range of filler workers:" << endl;
	cout << "Min: ";
	cin >> min_filler;
	cout << "max: ";
	cin >> max_filler;
	cout << "Please enter the min-max waiting time range of packager workers:" << endl;
	cout << "Min: ";
	cin >> min_packager;
	cout << "max: ";
	cin >> max_packager;



	cout << "Simulation starts " << put_time(get_current_time(), "%X") << endl;
	// creating threads
	thread t_producer(producer);
	thread t_filler1(filler, 1);
	thread t_filler2(filler, 2);
	thread t_packager1(packager, 1);
	thread t_packager2(packager, 2);

	//joining threads back
	t_producer.join();
	t_filler1.join();
	t_filler2.join();
	t_packager1.join();
	t_packager2.join();
	
	cout << "End of the simulation ends: " << put_time(get_current_time(), "%X") << endl;
	return 0;
}