#ifndef FLIGHT5020_H
#define FLIGHT5020_H
#include "Flight.h"
using namespace std;


class Airline;
class Flight;

class Flight5020: public Flight{
public:
	Flight5020(string name, string start, string end,
			string departure, float duration, int seats, 
			float distance, Airline* airline );

	~Flight5020();


	string getName();
	string getOrigin();
	string getDestination();
	string getDeparture();
	float getDuration();
	int numAvailableSeats();
	float getDistance();
	Airline& getAirline();

	//methods not virtual in base class

	void setCurrentSeats();
	int getCurrentSeats();
	int getTotalSeats();

private:
	string flightName, origin, destination, departure;
	float duration, distance;
	int seatsAvailable, totalSeats;
	Airline* airline;

};
#endif
