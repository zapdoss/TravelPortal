#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <cstring>
#include <string>
#include <stdlib.h>
#include "Airline5020_a.h"
#include "Flight5020.h"
#include "Portal.h"

using namespace std;

Airline5020_a:: Airline5020_a(Portal* pl):Airline(pl){
	pl->addAirline(this);
	airlineName="Airline5020_a";
	revenue=0;
	n=0;
	d=0;
}


Airline5020_a:: ~Airline5020_a(){
	int i;
	for(i=0;i<flightList.size();i++){
		delete flightList[i];
		}
}



void Airline5020_a:: init(string ifile){

	string start, end;
	int totalSeats, num_of_flights, flightCounter=0;

	char* fileName= new char[ifile.length()+1];
	strcpy(fileName,ifile.c_str());

	fstream fObj;
	fObj.open(fileName, ios::in);
	fObj>>totalSeats;


	fObj>>start>>end>>num_of_flights;
	while(!fObj.eof()){
		flightCounter+=num_of_flights;
		fObj>>start>>end>>num_of_flights;
		
	}

	fObj.close();
	int seats;
	float duration, minPrice, maxPrice, timeVariation, distance;
	string flightName, departure;

	fObj.open(fileName, ios::in);
	fObj>>totalSeats;

	seats= totalSeats/flightCounter;


	fObj>>start>>end>>num_of_flights;
	while(!fObj.eof()){
		getPortal()->routeInfo(start, end, distance, duration, 
										minPrice, maxPrice, timeVariation);

		for (int i = 0; i < num_of_flights; ++i)
		{	

			flightName = setFlightName();
			departure = setDepartureTime();
			Flight5020* temp = new Flight5020(flightName, start, end, departure, 
											duration, seats, distance, this);
			addFlight(temp);
		}

		fObj>>start>>end>>num_of_flights;
	}

}


string Airline5020_a:: setFlightName(){
	static int ff =10;
	
	stringstream ss;
	ss<<ff;

	ff++;

	return airlineName + ss.str();
	
}

string Airline5020_a:: setDepartureTime(){
	
	int hr, min;

	hr = rand()%24;
	min = rand()%59;

	stringstream ss;
	ss<<setw(2)<<setfill('0')<<hr<<setw(2)<<setfill('0')<<min;

	string s= ss.str();

	return s;

}

string Airline5020_a:: getName(){
	return airlineName;
}


float Airline5020_a:: getPrice(Flight* flight){

	float distance, duration, minPrice, maxPrice, timeVariation;

	float factor;
	Portal* portal= getPortal();
	int du = atoi((flight->getDeparture()).c_str());
	
	int s = flight->numAvailableSeats();
	portal->routeInfo(flight->getOrigin(), flight->getDestination(),
					distance, duration, minPrice,
					maxPrice, timeVariation);

	
		
		int m1= minPrice* 10;
		int m2= maxPrice* 10;
		factor = ((du)*(10/s))%(m2-m1)*0.1 + minPrice;
		if (factor<0) factor=factor*-1;
		if(factor>maxPrice) factor=maxPrice;
		return factor * distance;
}


bool Airline5020_a:: issueTicket(Flight* flight){

		if(flight->numAvailableSeats()){
			revenue = revenue + (getPrice(flight));
			n++;
			d=d+(flight->getDistance());
			Flight5020 *temp= (Flight5020*) flight;
			//revenue = revenue + getPrice(flight);
			//cout<<revenue<<endl;
			temp->setCurrentSeats(); 
			return true;
		}
		else 
			return false;
}
	


void Airline5020_a:: findFlights(string origin ,string destination, vector <Flight*>& flights){
	// cout<<"FlightListsize ="<<flightList.size()<<endl;
	for (int i = 0; i < flightList.size(); ++i)
	{
		//cout<<flightList[i]->getName()<<endl;
		if(flightList[i]->getOrigin()== origin && flightList[i]->getDestination()== destination){
				flights.push_back(flightList[i]);

			}
		}
	}

//}

int Airline5020_a:: getNumSold(){
	int totalSeatsLeft=0;
	for (int i = 0; i < flightList.size(); ++i)
	{
		totalSeatsLeft+=flightList[i]->numAvailableSeats();
	}

	return totalSeats-totalSeatsLeft;
}



void Airline5020_a:: addFlight(Flight* flight){
	flightList.push_back(flight);
}


vector <Flight*> Airline5020_a:: getFlights(){
	return flightList;
}

void Airline5020_a:: getSalesStats(float& revenue, float& passKm){
	float passKm1=0;
          revenue=this->revenue;
          passKm = (this->revenue)/(d*n);         
}
