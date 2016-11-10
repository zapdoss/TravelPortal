#ifndef AIRLINE5020_A_H
#define AIRLINE5020_A_H
#include "Airline.h"
class Airline;
class Flight;
class Portal;

class Airline5020_a: public Airline{
public:
	Airline5020_a(Portal *pl);
	~Airline5020_a();


	void init(string ifile);
	string getName();

	float getPrice(Flight* flight);
	bool issueTicket(Flight* flight);
	void findFlights(string origin, string destination, vector <Flight*>& flights);
	
	int getNumSold();
	void getSalesStats(float& revenue, float& passKm);
	
	//methods not virtual in base class
	
	void addFlight(Flight* flight);
	vector <Flight*> getFlights();

private:
	vector <Flight*> flightList;
	int totalSeats;
	string airlineName;
	float revenue,n,d;
	string setFlightName();
	string setDepartureTime();
};
#endif
