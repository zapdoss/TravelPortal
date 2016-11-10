
#ifndef PORTAL5020_H
#define PORTAL5020_H

#include "Portal.h"
#include "Flight.h"
#include "Airline.h"
#include <stdlib.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>
#include <iterator>
#include <algorithm>
using namespace std;

class Route;


class Portal5020 : public Portal {
    private:
        vector <Route*> routeArray;
        vector <Airline*> airlineArray;
        string Origin;
        string Destination;
    public:
        Portal5020 ();
        ~Portal5020 ();
        void initRoutes(string routeInfo);
        void addAirline(Airline *airline);
        void routeInfo(string origin, string destination, float& dist, float& duration,
                               float& minPrice, float& maxPrice, float& timeVariation);
        void processUserInput(string inputFileName);

    protected:
        void showFlights(string origin, string destination, SortField sortField = Airlines,
                         SortOrder sortOrder = Descending);
        bool buyTicket(BuyOption cirteria, string airline = NULL);
};

class Route {
    public:
        string origin;
        string destination;
        float dist;
        float duration;
        float minPrice;
        float maxPrice;
        float timeVariation;
        Route(string origin, string destination, float dist, float duration, float minPrice, float maxPrice, float timeVariation);
};

class SortByAirline {
public:
    SortByAirline(int _order) : order(_order) {}
    bool operator()(Flight *a, Flight *b) {
        if(order == 0) {
            if (strcmp(a->getName().c_str(), b->getName().c_str()) <= 0)
                return true;
            else
                return false;
        }
        else {
            if (strcmp(a->getName().c_str(), b->getName().c_str()) > 0)
                return false;
            else
                return false;
        }
    }
private:
    int order;
    bool mode;
};

class SortByTime {
public:
    SortByTime(int _order) : order(_order) {}
    bool operator()(Flight *a, Flight *b) {
        int ai = atoi(a->getDeparture().c_str());
        int bi = atoi(b->getDeparture().c_str());

        if(order == 0) {
            return ai < bi;
        }
        else {
            return ai > bi;
        }
    }
private:
    int order;
    bool mode;
};

class SortByDuration {
public:
    SortByDuration(int _order) : order(_order) {}
    bool operator()(Flight *a, Flight *b) {
        if(order == 0) {
            return a->getDuration() < b->getDuration();
        }
        else {
            return a->getDuration() > b->getDuration();
        }
    }
private:
    int order;
    bool mode;
};

class SortByPrice {
public:
    SortByPrice(int _order) : order(_order) {}
    bool operator()(Flight *a, Flight *b) {
		float d = a->getAirline().getPrice(a);
		float e = b->getAirline().getPrice(b);
        if(order == 0) {
            return d < e;
        }
        else {
            return d > e;
        }
    }
private:
    int order;
    bool mode;
};
#endif
