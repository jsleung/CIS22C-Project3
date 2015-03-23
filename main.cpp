#include "AdjacencyList.h"

using namespace std;

int main(){
	int in;
	cout << "How many jobs would you like to schedule?\n";
	cin >> in;
	TaskManager jobSchedule(in);
	jobSchedule.getInput(in);
	/*jobSchedule.getEE();
	jobSchedule.getLE();*/
	//jobSchedule.print();
	jobSchedule.findCritical();
	return 0;
}
