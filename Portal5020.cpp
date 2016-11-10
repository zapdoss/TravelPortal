	#include "Portal5020.h"
	#include "Flight.h"

	using namespace std;
	Portal5020::Portal5020 () {

	}

	Portal5020::~Portal5020() {
			int i;
	for(i=0;i<airlineArray.size();i++){
		delete airlineArray[i];
		for(i=0;i<routeArray.size();i++){
		delete routeArray[i];
		}
	}
	}

	Route::Route(string origin, string destination, float dist, float duration, float minPrice, float maxPrice, float timeVariation) {
			this->origin = origin;
			this->destination = destination;
			this->dist = dist;
			this->duration = duration;
			this->minPrice = minPrice;
			this->maxPrice = maxPrice;
			this->timeVariation = timeVariation;
	}

	void Portal5020::initRoutes(string routeInfo) {
		ifstream routeInputFile;
		routeInputFile.open (routeInfo.c_str());
		string line;
		string _origin, _destination;
		float _dist, _duration, _minPrice, _maxPrice, _timeVariation;
		while (getline(routeInputFile, line)) {
			stringstream ss(line);
			istream_iterator<string> begin(ss), end;
			vector<string> wordArray(begin, end);
			_origin = wordArray[0];
			_destination = wordArray[1];
			_dist = atof(wordArray[2].c_str());
			_duration = atof(wordArray[3].c_str());
			_minPrice = atof(wordArray[4].c_str());
			_maxPrice = atof(wordArray[5].c_str());
			_timeVariation = atof(wordArray[6].c_str());
			routeArray.push_back(new class Route(_origin, _destination, _dist, _duration, _minPrice, _maxPrice, _timeVariation));
		}
		routeInputFile.close();
	}

	void Portal5020::addAirline(Airline *airline) {
		airlineArray.push_back(airline);
	}

	void Portal5020::routeInfo(string _origin, string _destination, float& _dist, float& _duration, float& _minPrice, float& _maxPrice, float& _timeVariation) {
		for (int i = 0; i < routeArray.size(); i+=1) {
			if (routeArray[i]->origin == _origin && routeArray[i]->destination == _destination) {
				_dist = routeArray[i]->dist;
				_duration = routeArray[i]->duration;
				_minPrice = routeArray[i]->minPrice;
				_maxPrice = routeArray[i]->maxPrice;
				_timeVariation  = routeArray[i]->timeVariation;
				break;
			}
		}
	}

	void Portal5020::processUserInput(string inputFileName) {
		ifstream inputFile;
		inputFile.open(inputFileName.c_str());
		string _origin, _destination,line,airlineName;
		SortField sortF;
		SortOrder sortO;
		BuyOption buyO;
		
		
		getline(inputFile,line);
		stringstream ss(line);
		istream_iterator<string> begin(ss);
		istream_iterator<string> end;
		vector<string> wordArray(begin, end);
		_origin = wordArray[0];
		_destination = wordArray[1];
		Origin = _origin;
		Destination = _destination;
		
		CitiesLoop : {}

		while (getline(inputFile,line)) {
			stringstream ss(line);
			istream_iterator<string> begin(ss);
			istream_iterator<string> end;
			vector<string> wordArray(begin, end);
			if(wordArray[0]=="sort") {
				if(wordArray.size()==3) {
					if(wordArray[1] == "airline")
						sortF = Airlines;
					else if(wordArray[1] == "time")
						sortF = Time;
					else if(wordArray[1] == "duration")
						sortF = Duration;
					else if(wordArray[1] == "price")
						sortF = Price;
					if(wordArray[2] == "ascending")
						sortO = Ascending;
					else if(wordArray[2] == "descending")
						sortO = Descending;
				}
				
				else if(wordArray.size()==2) {
					if(wordArray[1] == "airline")
						sortF = Airlines;
					else if(wordArray[1] == "time")
						sortF = Time;
					else if(wordArray[1] == "duration")
						sortF = Duration;
					else if(wordArray[1] == "price")
						sortF = Price;
					if(wordArray[1] == "ascending")
						sortO = Ascending;
					else if(wordArray[1] == "descending")
						sortO = Descending;
				}
				showFlights(_origin,_destination, sortF, sortO);
			}
			else if(wordArray[0] == "buy") {
				if(wordArray.size() == 3) {
					if(wordArray[1] == "cheapest")
						buyO = Cheapest;
					else if(wordArray[1] == "fastest")
						buyO = Fastest;
					else if(wordArray[1] == "earliest")
						buyO = Earliest;
					else if(wordArray[1] == "latest")
						buyO = Latest;
					airlineName = wordArray[2];
				}
				else if(wordArray.size() == 2) {
					if(wordArray[1] == "cheapest")
						buyO = Cheapest;
					else if(wordArray[1] == "fastest")
						buyO = Fastest;
					else if(wordArray[1] == "earliest")
						buyO = Earliest;
					else if(wordArray[1] == "latest")
						buyO = Latest;
				}
				
				//cout<<"a"<<endl;
				buyTicket(buyO, airlineName);
				cout<<endl;
				
				//cout<<"b"<<endl;
			}
			else {
				_origin = wordArray[0];
				_destination = wordArray[1];
				Origin = _origin;
				Destination = _destination;
				goto CitiesLoop;
			}
		}
		float r,p;
		int i;
		for(i=0;i<airlineArray.size();i++){
			airlineArray[i]->getSalesStats(r,p);
			cout<<endl<<airlineArray[i]->getName()<<" : "<<"Revenue: "<<r<<"    Revenue per KM per passenger: "<<p<<endl;
			}
		inputFile.close();
	}

	void Portal5020::showFlights(string origin, string destination, SortField sortField, SortOrder sortOrder) {
		for(int i = 0; i < airlineArray.size(); i++) {
			vector<Flight *> flights;
			cout << "Airline :  " << airlineArray[i] -> getName() << ": " << endl;
			airlineArray[i]->findFlights (origin, destination, flights);
			string order;
			if (sortOrder == Ascending)
				order = "Increasing order";
			else
				order = "Decreasing order";
			if(sortField == Airlines) {
				cout << "Sort by Airline in " + order << endl;
				sort(flights.begin(), flights.end(), SortByAirline(sortOrder));
			}
			else if(sortField == Time) {
				cout << "Sort by Time in " + order << endl;
				sort(flights.begin(), flights.end(), SortByTime(sortOrder));
			}
			else if(sortField == Duration) {
				cout << "Sort by Airline in " + order << endl;
				sort(flights.begin(), flights.end(), SortByDuration(sortOrder));
			}
			else if(sortField == Price){
				cout << "Sort by Price in " + order << endl;
				sort(flights.begin(), flights.end(), SortByPrice(sortOrder));
			}
			cout<<endl;
			for(int j = 0; j < flights.size(); j++) {
				cout << "Name : " << flights[j]->getName() << " -- " << "Origin : " << flights[j]->getOrigin() << " -- " << "Destination : " << flights[j]->getDestination() << " -- " << "Departure Time : " << flights[j]->getDeparture() << " -- "<< "Duration : " << flights[j]->getDuration() << " -- "<< "No. of Seats Available :" << flights[j]->numAvailableSeats() << " -- " << "Price : " << flights[j]->getAirline().getPrice(flights[j])<< endl;
			}
			cout << endl;
			cout<<endl;
		}
	}

	bool Portal5020::buyTicket(BuyOption criteria, string airline) {
		vector<Flight *> tempFlightVector;
		if (airline == "") {
			for (int i = 0; i < airlineArray.size(); i++) {
				airlineArray[i]->findFlights(Origin, Destination, tempFlightVector);
			}
			if (criteria == Cheapest) {
				sort(tempFlightVector.begin(), tempFlightVector.end(), SortByPrice(Ascending));
			}
			else if (criteria == Latest) {
				sort(tempFlightVector.begin(), tempFlightVector.end(), SortByTime(Descending));
			}
			else if (criteria == Earliest) {
				sort(tempFlightVector.begin(), tempFlightVector.end(), SortByTime(Ascending));
			}
			else if (criteria == Fastest) {
				sort(tempFlightVector.begin(), tempFlightVector.end(), SortByDuration(Ascending));
			}
		}
		else {
			for (int i = 0; i < airlineArray.size(); i++) {
				if (airlineArray[i]->getName() == airline) {
					airlineArray[i]->findFlights(Origin, Destination, tempFlightVector);
					if (criteria == Cheapest) {
						sort(tempFlightVector.begin(), tempFlightVector.end(), SortByPrice(Ascending));
					}
					else if (criteria == Latest) {
						sort(tempFlightVector.begin(), tempFlightVector.end(), SortByTime(Descending));
					}
					else if (criteria == Earliest) {
						sort(tempFlightVector.begin(), tempFlightVector.end(), SortByTime(Ascending));
					}
					else if (criteria == Fastest) {
						sort(tempFlightVector.begin(), tempFlightVector.end(), SortByDuration(Ascending));
					}
				}
			}
		}
		if (tempFlightVector.size()<=0){
			cout<<"No Flights!"<<endl<<endl;
			return false;
			}
		if (tempFlightVector[0]->getAirline().issueTicket(tempFlightVector[0])) {
			cout << tempFlightVector[0]->getName() << " Flight Ticket bought! Congrats!" << endl;
			return true;
		}
		else {
			cout << "Flight ticket for " << tempFlightVector[0]->getName() << " could not be purchased." << endl;
			return false;
		}
		//return tempFlightVector[0]->getAirline().issueTicket(tempFlightVector[0]);

	}
