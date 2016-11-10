#ifndef AIRLINE5020_B_H
#define AIRLINE5020_B_H
#include "Airline.h"
class Airline;
class Flight;
class Portal;

class Airline5020_b: public Airline{
public:
	Airline5020_b(Portal *pl);
	~Airline5020_b();

	//methods

	void init(string ifile);
	string getName();

	float getPrice(Flight* flight);
	bool issueTicket(Flight* flight);
	void findFlights(string origin, string destination, vector <Flight*>& flights);
	
	int getNumSold();
	void getSalesStats(float& revenue, float& passKm);
	
	//own methods
	
	void addFlight(Flight* flight);
	vector <Flight*> getFlights();

private:
	vector <Flight*> flightList;
	int totalSeats;
	string airlineName;
	float revenue, d,n;
	string setFlightName();
	string setDepartureTime();
};
#endif
