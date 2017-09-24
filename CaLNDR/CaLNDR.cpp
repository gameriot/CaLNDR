// CaLNDR.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>


using namespace std;

struct Location {
	std::string address; 
};

struct timeRange {
	int startTime, endTime;
};

struct Time {
	int month;
	int date;
	timeRange time;
};

struct timeStandard {
	int hour;
	int minute;
};

struct Event {
	std::string eventName;
	Location eventLocation;
	Time eventTime;
};

struct freeTime {
	Location eventLocationPre;
	Location eventLocationPost;
	Time eventTime;
};

struct freeTimeDistance {
	int distancePre;
	int distancePost;
	Time eventTime;
};

struct fixedTimeDistance {
	int distance;
	Time eventTime;
};

vector<Time> calculateFreeTime(vector<Event> &calendar, int dayStart, int dayEnd);
Time largestChunk(vector<Time> freeTime);
void outputTime(vector<Time> time);
timeStandard convertTimeToStandard(int time);
vector<Time> filterInvalidTimeSpan(vector<Time> freeTime, timeRange eventTimeRange);
Event finalLogic(Event &addedEvent, vector<Event> &calendar, int locationRange, vector<freeTime> finalFilteredFreeTimeWithLocation);
vector<freeTimeDistance> makeDistanceVector(vector<freeTime> &finalFreeTimeWithLocations, Event &addedEvent);
vector<fixedTimeDistance> makeDistanceVectorFixed(vector<Event> &calendar, Event addedEvent);
vector<freeTime> addLocationTags(vector<Time> &freeTime, vector<Event> & calendar);
void calculateDistances(vector<vector<Location>> &locationVector, vector<vector<int>> &distanceVector);
void calcuateDistancesFixed(vector<Location> &locationVector, vector<int> &distanceVector);

int main()
{
	ifstream Activity;
	ifstream Duration;
	ifstream Address;
	Activity.open("
	vector<Event> fixedCalendar{};

	vector<Time> freeTimeandDay = calculateFreeTime(fixedCalendar, 330, 1320);

	vector<Time> finalTimeSpans = filterInvalidTimeSpan(freeTimeandDay, lunch.eventTime.time);

	vector<freeTime> finalFreeTimeWithLocation = addLocationTags(finalTimeSpans, fixedCalendar);

	finalLogic(lunch, fixedCalendar, 45, finalFreeTimeWithLocation);

    return 0;
}

vector<Time> calculateFreeTime(vector<Event> &calendar, int dayStart, int dayEnd) {
	vector<timeRange> fixedTime;
	for (int i = 0; i < calendar.size(); i++) {
		fixedTime.push_back({ calendar[i].eventTime.time.startTime, calendar[i].eventTime.time.endTime });
	}
	vector<timeRange> freeTime;
	vector<Time> freeTimeandDay;
	freeTime.push_back({ dayStart, calendar[0].eventTime.time.startTime });
	for (int i = 0; i < calendar.size(); i++) {
		if (i != (calendar.size() - 1)) {
			freeTime.push_back({ calendar[i].eventTime.time.endTime, calendar[i + 1].eventTime.time.startTime });
		} else {
			freeTime.push_back({ calendar[i].eventTime.time.endTime, dayEnd });
		}
	}
	for (int i = 0; i < freeTime.size(); i++) {
		freeTimeandDay.push_back({ calendar[0].eventTime.month, calendar[0].eventTime.date, freeTime[i] });
	}
	return freeTimeandDay;
}

void outputTime(vector<Time> time) {
	for (int i = 0; i < time.size(); i++) {
		cout << time[i].month << "/" << time[i].date << "/(" << time[i].time.startTime <<
		"-" << time[i].time.endTime << ")" << endl;
	}
}

Time largestChunk(vector<Time> freeTime) {
	vector<int> freeLengths;
	for (int i = 0; i < freeTime.size(); i++) {
		freeLengths.push_back(abs(freeTime[i].time.endTime - freeTime[i].time.startTime));
	}

	int maxPos = 0;
	for (int i = 0; i < freeLengths.size(); i++) {
		if (freeLengths[i] > freeLengths[maxPos])
			maxPos = i;
	} 
	
	return freeTime[maxPos];
}

timeStandard convertTimeToStandard(int time) {
	int hours = time / 60; 
	int minutes = time - (hours * 60);
	timeStandard outputTime = { hours, minutes };
	return outputTime;
}

Time findMinDistanceWithFreeTime(vector<int> distances, vector<Time> freeTime) {
	int minPos = 0;
	for (int i = 0; i < distances.size(); i++) {
		if (distances[i] < distances[minPos])
			minPos = i;
	}
	return freeTime[minPos];
}

vector<Time> filterInvalidTimeSpan(vector<Time> freeTime, timeRange eventTimeRange) {
	vector<Time> finalFilteredFreeTime; 
	for (int i = 0; i < freeTime.size(); i++) {
		if ((abs(freeTime[i].time.endTime - freeTime[i].time.startTime)) >= abs(eventTimeRange.endTime - eventTimeRange.startTime)) {
			finalFilteredFreeTime.push_back(freeTime[i]);
		}
	}
	return finalFilteredFreeTime;
}

Event finalLogic(Event &addedEvent, vector<Event> &calendar, int locationTimeRange, vector<freeTime> finalFilteredFreeTimeWithLocation) {
	vector<freeTime> freeTimeWithinRange;
	vector<Event> fixedTimeWithinRange;
	vector<freeTimeDistance> distances = makeDistanceVector(freeTimeWithinRange, addedEvent);
	vector<fixedTimeDistance> distancesFixed = makeDistanceVectorFixed(calendar, addedEvent);
	for (int i = 0; i < distances.size(); i++) {
		if (locationTimeRange >= distances[i].distancePre || locationTimeRange > distances[i].distancePost) {
			freeTimeWithinRange.push_back(finalFilteredFreeTimeWithLocation[i]);
		}
	}	
	if (freeTimeWithinRange.empty()) {
		vector<Time> finalFilteredFreeTime;
		Time temp_time;
		for (int i = 0; i < finalFilteredFreeTimeWithLocation.size(); i++) {
			temp_time = finalFilteredFreeTimeWithLocation[i].eventTime;
			finalFilteredFreeTime.push_back(temp_time);
		}
		if (abs(largestChunk(finalFilteredFreeTime).time.endTime - largestChunk(finalFilteredFreeTime).time.startTime) > abs(addedEvent.eventTime.time.endTime - addedEvent.eventTime.time.startTime)) {
			int maxPos = 0;
			for (int i = 0; i < finalFilteredFreeTimeWithLocation.size(); i++) {
				if (abs(finalFilteredFreeTimeWithLocation[i].eventTime.time.endTime - finalFilteredFreeTimeWithLocation[i].eventTime.time.startTime) > abs(finalFilteredFreeTimeWithLocation[maxPos].eventTime.time.endTime - finalFilteredFreeTimeWithLocation[maxPos].eventTime.time.startTime)) {
					maxPos = i;
				}
				Event recommendation = { addedEvent.eventName, addedEvent.eventLocation,  {calendar[0].eventTime.month, calendar[0].eventTime.date, {finalFilteredFreeTimeWithLocation[maxPos].eventTime.time.startTime, (finalFilteredFreeTimeWithLocation[maxPos].eventTime.time.startTime + addedEvent.eventTime.time.endTime)} } };
				return recommendation;
			}
		} else {
			for (int i = 0; i < distancesFixed.size(); i++) {
				if (locationTimeRange >= distancesFixed[i].distance) {
					fixedTimeWithinRange.push_back(calendar[i]);
				} 
			}
			if (fixedTimeWithinRange.empty()) {
				int maxPos = 0;
				for (int i = 0; i < calendar.size(); i++) {
					if (abs(calendar[i].eventTime.time.endTime - calendar[i].eventTime.time.startTime) > abs(calendar[maxPos].eventTime.time.endTime - calendar[maxPos].eventTime.time.startTime)) {
						maxPos = i;
					}
				}
				Event recommendation = { addedEvent.eventName, addedEvent.eventLocation, {calendar[0].eventTime.month, calendar[0].eventTime.date, {(calendar[maxPos].eventTime.time.endTime / 2),((calendar[maxPos].eventTime.time.endTime / 2) + addedEvent.eventTime.time.endTime) }} };
				return recommendation;
			} else {
				int minPos = 0;
				for (int i = 0; i < fixedTimeWithinRange.size(); i++) {
					if (abs(fixedTimeWithinRange[i].eventTime.time.endTime - fixedTimeWithinRange[i].eventTime.time.startTime) < abs(fixedTimeWithinRange[minPos].eventTime.time.endTime - fixedTimeWithinRange[minPos].eventTime.time.startTime)) {
						minPos = i;
					}
				}
				Event recommendation = { addedEvent.eventName, addedEvent.eventLocation, {calendar[0].eventTime.month, calendar[0].eventTime.date, {(calendar[minPos].eventTime.time.endTime / 2), ((calendar[minPos].eventTime.time.endTime / 2) + addedEvent.eventTime.time.endTime)} } };
				return recommendation;
			}
		}
	} else {
		vector<freeTimeDistance> distances = makeDistanceVector(freeTimeWithinRange, addedEvent);
		for (int i = 0; i < distances.size(); i++) {
			if (distances[i].distancePre < distances[i].distancePost) {
				Event recommendation = { addedEvent.eventName, addedEvent.eventLocation, {calendar[0].eventTime.month, calendar[0].eventTime.date, {freeTimeWithinRange[i].eventTime.time.startTime,(freeTimeWithinRange[i].eventTime.time.startTime + addedEvent.eventTime.time.endTime) }} };
			}
			else {
				Event recommendation = { addedEvent.eventName, addedEvent.eventLocation, {calendar[0].eventTime.month, calendar[0].eventTime.date, {(freeTimeWithinRange[i].eventTime.time.endTime - addedEvent.eventTime.time.endTime), freeTimeWithinRange[i].eventTime.time.endTime}} };
			}
		}
	}
}


vector<freeTime> addLocationTags (vector<Time> &freeTime,  vector<Event> & calendar) {
	vector<struct freeTime> finalFilteredFreeTimeWithLocation;
	for (int i = 0; i < calendar.size(); i++) {
		for (int k = 0; k < freeTime.size(); k++) {
			if (calendar[i].eventTime.time.endTime == freeTime[k].time.startTime) {
				struct freeTime index;
				index.eventLocationPre = { calendar[i].eventLocation };
				index.eventTime = { freeTime[k] };
				for (int j = 0; j < calendar.size(); j++) {
					if (freeTime[k].time.endTime == calendar[j].eventTime.time.startTime) {
						index.eventLocationPost = { calendar[j].eventLocation };
					}
				}
				finalFilteredFreeTimeWithLocation.push_back(index);
			}
		}
	}
	return finalFilteredFreeTimeWithLocation;
}

vector<freeTimeDistance> makeDistanceVector(vector<freeTime> &finalFreeTimeWithLocations, Event &addedEvent) {
	vector<freeTimeDistance> distances;
	vector<vector<int>> tempDistance;
	vector<vector<Location>> locationVector;

	for (int i = 0; i < finalFreeTimeWithLocations.size(); i++) {
		locationVector.push_back({ finalFreeTimeWithLocations[i].eventLocationPre, finalFreeTimeWithLocations[i].eventLocationPost });
	}
	calculateDistances(locationVector, tempDistance);
	freeTimeDistance temp_distance;
	for (int i = 0; i < finalFreeTimeWithLocations.size(); i++) {
		temp_distance.eventTime = finalFreeTimeWithLocations[i].eventTime;
		distances.push_back(temp_distance);
	}
	for (int i = 0; i < tempDistance.size(); i++) {
		temp_distance.distancePost = tempDistance[i][1];
		temp_distance.distancePre = tempDistance[i][0];
		distances.push_back(temp_distance);
	}
	return distances;
}

vector<fixedTimeDistance> makeDistanceVectorFixed(vector<Event> &calendar, Event addedEvent) {
	vector<fixedTimeDistance> distances;
	vector<int> tempDistance;
	vector<Location> locationVector;
	for (int i = 0; i < calendar.size(); i++) {
		locationVector.push_back(calendar[i].eventLocation);
	}
	calcuateDistancesFixed(locationVector, tempDistance);
	fixedTimeDistance temp_distance;
	for (int i = 0; i < calendar.size(); ++i) {
		temp_distance.eventTime = calendar[i].eventTime;
		distances.push_back(temp_distance);
	}
	for (int i = 0; i < tempDistance.size(); i++) {
		temp_distance.distance = tempDistance[i];
		distances.push_back(temp_distance);
	}
	return distances;
}

void calculateDistances(vector<vector<Location>> &locationVector, vector<vector<int>> &distanceVector) {
	std::ofstream outfile("Backend.txt");
	for (int i = 0; i < (locationVector.size()); i++) {
		outfile << locationVector[i][0].address << endl;
		outfile << locationVector[i][1].address << endl;
	}

	outfile.close();
}

void calcuateDistancesFixed(vector<Location> &locationVector, vector<int> &distanceVector) {
	std::ofstream outfile("BackendFixed.txt");
	for (int i = 0; i < (locationVector.size()-1); i++) {
		outfile << locationVector[i].address << endl;
		outfile << locationVector[1].address << endl;
	}
	outfile.close();
}
