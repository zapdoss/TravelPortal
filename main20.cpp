#include "Portal5020.h"
#include "Airline5020_a.h"
#include "Airline5020_b.h"
#include <iostream>
#include "Airline5033_a.h"
#include "Airline5033_b.h"
using namespace std;

int main () {
    Portal5020 *mainPortal = new Portal5020();
    float r=0,km=0;
    mainPortal->initRoutes("routes.txt");
    //Airline5033_b *a1 = new Airline5033_b(mainPortal);
   //Airline5033_a *a2 = new Airline5033_a(mainPortal);
   Airline5020_a *a3 = new Airline5020_a(mainPortal);
   Airline5020_b *a4 = new Airline5020_b(mainPortal);
   
    //a1->init("airline1.txt");
   //a2->init("airline2.txt");
   a3->init("airline3.txt");
   a4->init("airline4.txt");
    mainPortal->processUserInput("userInput.txt");
    //a2->getSalesStats(r,km);
    //cout<<r<<endl<<km<<endl;
    
    return 0;
}
