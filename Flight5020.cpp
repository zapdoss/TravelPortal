#include <iostream>
#include "Flight5020.h"
#include "Airline.h"
using namespace std;

Flight5020:: Flight5020(string name,string start, string end,
				string departure, float duration, int seats, 
				float distance, Airline* airline ):Flight()
{

	flightName=name;
	origin=start;
	destination=end;
	this->departure=departure;
	this->duration=duration;
	totalSeats=seats;
	seatsAvailable=seats;
	this->distance=distance;	
	this->airline=airline;


}



Flight5020::~Flight5020(){}

//methods

string Flight5020:: getName(){
	return flightName;
}

void Flight5020:: setCurrentSeats(){
	seatsAvailable-=1;
}

int Flight5020:: getCurrentSeats(){
	return seatsAvailable;
}

int Flight5020:: getTotalSeats(){
	return totalSeats;
}

string Flight5020:: getOrigin(){
	return origin;
}
string Flight5020:: getDestination(){
	return destination;
}
string Flight5020:: getDeparture(){
	return departure;
}

float Flight5020:: getDuration(){
	return duration;
}

float Flight5020:: getDistance(){
	return distance;
}

int Flight5020:: numAvailableSeats(){
	return seatsAvailable;
}

Airline& Flight5020:: getAirline(){
	return *airline;
}
