#include <iostream>
#include<vector>
#include <algorithm>
using namespace std;

/*

Determine the fastest time that the hikers can cross each bridge and the total time for all crossings.

yaml file that describes the

person_speed = speeds of each person

bridges = the bridges encountered

bridge_length = their length

new_hikers = additional hikers encountered

Demonstrate the operation of your program using the following inputs: the hikers cross 3
bridges, at the first bridge (100 ft long) 4 hikers cross (hiker A can cross at 100 ft/minute, B at 50
ft/minute, C at 20 ft/minute, and D at 10 ft/minute), at the second bridge (250 ft long) an
additional hiker crosses with the team (E at 2.5 ft/minute), and finally at the last bridge (150 ft
long) two hikers are encountered (F at 25 ft/minute and G at 15 ft/minute).

*/
typedef struct Bridge {
	double length = 0.0;
	vector<double> hikers;
}Bridge;


double crossTime(vector<int> timeToCross, int n);
double crossTimePerBridge(Bridge bridge);
vector<double> getTimeInSeconds(vector<double> hikerSpeed, int bridgeLength);

int main() {

	vector<Bridge> bridges;
	bridges.push_back({ 100, {100,50,20,10} });
	bridges.push_back({ 250, {2.5} });
	bridges.push_back({ 150, {25,15} });
	Bridge tmpBridge;
	double totalCrossTime = 0.0;

	for (int i = 0; i < bridges.size(); ++i) {

		/*if (i > 0) {
			bridges[i].hikers.insert(bridges[i].hikers.end(), bridges[i - 1].hikers.begin(),bridges[i-1].hikers.end());
		}
		totalCrossTime += totalCrossTimePerBridge(bridges[i]);*/
		tmpBridge.length = bridges[i].length;
		tmpBridge.hikers.insert(tmpBridge.hikers.end(), bridges[i].hikers.begin(), bridges[i].hikers.end());
		totalCrossTime += crossTimePerBridge(tmpBridge);
		
		cout << "Cross Time at Bridge#" << i << ": " << totalCrossTime / 60 << " minutes" << endl;

	}

	cout << "Total time taken:" << totalCrossTime << " seconds" << endl;
	cout << "Total time taken:" << totalCrossTime / 60 << " minutes" << endl;


	return 0;


}
vector<double> getTimeInSeconds(vector<double> hikerSpeed, int bridgeLength) {
	vector<double> tmp;
	for (int i = 0; i < hikerSpeed.size(); ++i) {
		tmp.push_back((bridgeLength / hikerSpeed[i]) * 60);
	}
	return tmp;
}

double crossTime(vector<double> timeToCross, int n) {
	if (n < 3) {
		return timeToCross[n - 1];
	}
	if (n == 3) {
		return timeToCross[0] + timeToCross[1] + timeToCross[2];
	}

	double timeTakenCaseOne = timeToCross[1] + timeToCross[0] + timeToCross[n - 1] + timeToCross[1];
	double timeTakenCaseTwo = timeToCross[n - 1] + timeToCross[0] + timeToCross[n - 2] + timeToCross[0];

	if (timeTakenCaseOne < timeTakenCaseTwo) {
		return timeTakenCaseOne + crossTime(timeToCross, n - 2);
	}

	if (timeTakenCaseTwo < timeTakenCaseOne) {
		return timeTakenCaseTwo + crossTime(timeToCross, n - 2);
	}

	return timeTakenCaseTwo + crossTime(timeToCross, n - 2);

}

double crossTimeIterative(vector<double> timeToCross) {
	int n = timeToCross.size();
	double totalTime = 0.0;
	while (true) {
		if (n < 3) {
			totalTime += timeToCross[n - 1];
			break;
		}
		if (n == 3) {
			totalTime += timeToCross[0] + timeToCross[1] + timeToCross[2];
			break;
		}

		double timeTakenCaseOne = timeToCross[1] + timeToCross[0] + timeToCross[n - 1] + timeToCross[1];
		double timeTakenCaseTwo = timeToCross[n - 1] + timeToCross[0] + timeToCross[n - 2] + timeToCross[0];

		if (timeTakenCaseOne < timeTakenCaseTwo) {
			totalTime += timeTakenCaseOne;
			n -= 2;
			continue;
		}
		if (timeTakenCaseTwo < timeTakenCaseOne) {
			totalTime += timeTakenCaseTwo;
			n -= 2;
			continue;
		}
		totalTime += timeTakenCaseTwo;
		n -= 2;


	}
	return totalTime;
}
double crossTimePerBridge(Bridge bridge) {

	vector<double> crossTimes = getTimeInSeconds(bridge.hikers, bridge.length);
	sort(crossTimes.begin(), crossTimes.end());
	return crossTime(crossTimes, bridge.hikers.size());
	//return crossTimeIterative(crossTimes);


}


