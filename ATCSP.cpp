#include "ATCSP.h"

// City class implementation
City::City()
{
    cityname = " ";
}
City::City(std::string cityN)
{
    cityname = cityN;
}
void City::setName(std::string cityN)
{
    cityname = cityN;
}
std::string City::getCityname()
{
    return cityname;
}
void City::displayCityinfo()
{
    std::cout << COLOR_CYAN << "THE NAME OF THE CITY IS : " << cityname << COLOR_RESET << std::endl;
}

// Airport class implementation
int Airport::airportCount = 0;

Airport::Airport()
{
    airportName = "";
    totalRunways = 0;
    availableRunways = 0;
    airportCount++;
}

Airport::Airport(std::string cityN, std::string airportN, int totalRunw, int availableRunw)
    : City(cityN), airportName(airportN), totalRunways(totalRunw), availableRunways(availableRunw)
{
    airportCount++;
}

void Airport::setAirportn(std::string airportN)
{
    airportName = airportN;
}
std::string Airport::getAirportn()
{
    return airportName;
}
void Airport::setTotalrunw(int totalRunw)
{
    totalRunways = totalRunw;
}
int Airport::getTotalrunw()
{
    return totalRunways;
}
void Airport::setAvailablerunw(int availableRunw)
{
    availableRunways = availableRunw;
}
int Airport::getAvailablerunw()
{
    return availableRunways;
}

void Airport::initializeRunways()
{
    runwayNames.clear();
    runwayOccupied.clear();
    for (int i = 1; i <= totalRunways; ++i)
    {
        runwayNames.push_back(airportName + " RUNWAY " + std::to_string(i));
        runwayOccupied.push_back(false);
    }
    availableRunways = totalRunways;
}

std::string Airport::allocateRunway()
{
    if (availableRunways == 0)
        return "";
    for (int i = totalRunways - 1; i >= 0; i--)
    {
        if (!runwayOccupied[i])
        {
            runwayOccupied[i] = true;
            availableRunways--;
            return runwayNames[i];
        }
    }
    return "";
}

void Airport::freeRunway(const std::string &runwayName)
{
    for (int i = 0; i < runwayNames.size(); i++)
    {
        if (runwayNames[i] == runwayName)
        {
            if (runwayOccupied[i])
            {
                runwayOccupied[i] = false;
                availableRunways++;
            }
            break;
        }
    }
}

bool Airport::isrunwayAvailable()
{
    return this->availableRunways > 0;
}

void Airport::displayAirportinfo()
{
    displayCityinfo();
    std::cout << COLOR_CYAN << "THE NAME OF THE AIRPORT IS : " << airportName << std::endl;
    std::cout << "THE NUMBER OF TOTAL RUNWAYS ARE : " << totalRunways << COLOR_RESET << std::endl;

    std::cout << "THE NUMBER OF AVAILABLE RUNWAYS ARE : ";
    if (availableRunways == 0)
    {
        std::cout << COLOR_RED << availableRunways << COLOR_RESET << " (UNAVAILABLE)";
    }
    else if (availableRunways < totalRunways)
    {
        std::cout << COLOR_YELLOW << availableRunways << COLOR_RESET << " (PARTIALLY AVAILABLE)";
    }
    else
    {
        std::cout << COLOR_GREEN << availableRunways << COLOR_RESET << " (AVAILABLE)";
    }
    std::cout << std::endl;
    std::cout << "RUNWAYS STATUS: " << std::endl;
    for (int i = totalRunways - 1; i >= 0; i--)
    {
        std::cout << "  " << runwayNames[i] << ": ";
        if (runwayOccupied[i])
        {
            std::cout << COLOR_RED << "OCCUPIED" << COLOR_RESET << std::endl;
        }
        else
        {
            std::cout << COLOR_GREEN << "AVAILABLE" << COLOR_RESET << std::endl;
        }
    }
}

int Airport::getAirportCount()
{
    return airportCount;
}

// Aircraft class implementation
Aircraft::Aircraft()
{
    aircraftModel = "";
    registrationNumber = "";
    isundermaintenance = true;
}
Aircraft::Aircraft(std::string aircraftM, std::string regNum, bool maintenance)
{
    aircraftModel = aircraftM;
    registrationNumber = regNum;
    isundermaintenance = maintenance;
}

void Aircraft::setAircraftmodel(std::string aircraftM)
{
    aircraftModel = aircraftM;
}
std::string Aircraft::getAircraftm() const
{
    return aircraftModel;
}
void Aircraft::setRegnum(std::string regNum)
{
    registrationNumber = regNum;
}
std::string Aircraft::getRegnum() const
{
    return registrationNumber;
}
void Aircraft::setMaintenance(bool maintenance)
{
    isundermaintenance = maintenance;
}

bool Aircraft::toggleMaintenance()
{
    this->isundermaintenance = !this->isundermaintenance;
    return this->isundermaintenance;
}

void Aircraft::updateMaintenancestatus(bool status)
{
    this->isundermaintenance = status;
}

bool Aircraft::getMaintenanceStatus() const
{
    return this->isundermaintenance;
}

void Aircraft::displayAircraftinfo() const
{
    std::cout << COLOR_CYAN << "THE MODEL OF THE AIRCRAFT IS : " << aircraftModel << std::endl;
    std::cout << "THE REGISTRATION NUMBER OF THE AIRCRAFT IS : " << registrationNumber << COLOR_RESET << std::endl;
    std::cout << "MAINTENANCE STATUS : " << (this->isundermaintenance ? COLOR_YELLOW "UNDER MAINTENANCE" COLOR_RESET : COLOR_GREEN "OPERATIONAL" COLOR_RESET) << std::endl;
}

// PassengerAircraft class implementation
PassengerAircraft::PassengerAircraft()
{
    maxPassengers = 0;
}
PassengerAircraft::PassengerAircraft(std::string aircraftM, std::string regNum, bool maintenance, int maxP)
    : Aircraft(aircraftM, regNum, maintenance)
{
    maxPassengers = maxP;
}

void PassengerAircraft::setMaxPas(int maxP)
{
    maxPassengers = maxP;
}
int PassengerAircraft::getMaxPas() const
{
    return maxPassengers;
}
AircraftType PassengerAircraft::getAircraftType() const
{
    return AircraftType::PASSENGER;
}

void PassengerAircraft::displayAircraftinfo() const
{
    Aircraft::displayAircraftinfo();
    std::cout << COLOR_CYAN << "THE MAXIMUM NUMBER OF PASSENGERS IN THE AIRCRAFT ARE : " << maxPassengers << COLOR_RESET << std::endl;
}

// CargoAircraft class implementation
CargoAircraft::CargoAircraft()
{
    maxcargokg = 0.0;
}
CargoAircraft::CargoAircraft(std::string aircraftM, std::string regNum, bool maintenance, double maxCargo)
    : Aircraft(aircraftM, regNum, maintenance)
{
    maxcargokg = maxCargo;
}

void CargoAircraft::setMaxcargo(double maxCargo)
{
    maxcargokg = maxCargo;
}
double CargoAircraft::getMaxcargo() const
{
    return maxcargokg;
}
AircraftType CargoAircraft::getAircraftType() const
{
    return AircraftType::CARGO;
}

void CargoAircraft::displayAircraftinfo() const
{
    Aircraft::displayAircraftinfo();
    std::cout << COLOR_CYAN << "THE MAXIMUM CARGO CAPACITY OF THE AIRCRAFT IS : " << maxcargokg << COLOR_RESET << std::endl;
}

// Airline class implementation
Airline::Airline()
{
    Airlinename = "";
}
Airline::Airline(std::string Airlinen)
{
    Airlinename = Airlinen;
}

void Airline::addAircraft(Aircraft *aircraft)
{
    fleet.push_back(aircraft);
}

void Airline::displayFleet()
{
    std::cout << COLOR_CYAN << "THE NAME OF THE AIRLINE IS : " << Airlinename << std::endl;
    std::cout << "-----FLEET-INFO!-----" << COLOR_RESET << std::endl;
    for (int i = 0; i < fleet.size(); i++)
    {
        std::cout << "    AIRCRAFT " << i + 1 << " --- " << std::endl;
        fleet[i]->displayAircraftinfo();
    }
}

void getMaxCapacities(const Airline &airline, int &maxPassengerCapacity, double &maxCargoCapacity)
{
    maxPassengerCapacity = 0;
    maxCargoCapacity = 0.0;
    for (Aircraft *aircraft : airline.fleet)
    {
        if (aircraft->getAircraftType() == PASSENGER)
        {
            int p = aircraft->getMaxPas();
            if (p > maxPassengerCapacity)
            {
                maxPassengerCapacity = p;
            }
        }
        else if (aircraft->getAircraftType() == CARGO)
        {
            double c = aircraft->getMaxcargo();
            if (c > maxCargoCapacity)
            {
                maxCargoCapacity = c;
            }
        }
    }
}

// Flight class implementation
Flight::Flight()
{
    flightNumber = "";
    aircraft = nullptr;
    departureAirport = nullptr;
    arrivalAirport = nullptr;
    departureTime = " ";
    arrivalTime = " ";
    status = 0;
    passengersOnboard = 0;
    cargoWeight = 0.0;
    isDelayed = false;
    assignDepartureRunway = "";
    assignArrivalRunway = "";
}

Flight::Flight(std::string flightN, Aircraft *AC, Airport *depA, Airport *arrA, std::string depT,
               std::string arrT, int stat, int passOnb, double cargoW, std::string asgndeprunw, std::string asgnarrrunw)
{
    this->flightNumber = flightN;
    this->aircraft = AC;
    this->departureAirport = depA;
    this->arrivalAirport = arrA;
    this->departureTime = depT;
    this->arrivalTime = arrT;
    this->status = stat;
    this->passengersOnboard = passOnb;
    this->cargoWeight = cargoW;
    this->isDelayed = false;
    assignDepartureRunway = asgndeprunw;
    assignArrivalRunway = asgnarrrunw;
}

void Flight::setFlightnumber(std::string flightN)
{
    flightNumber = flightN;
}
std::string Flight::getFlightnumber() const
{
    return flightNumber;
}
void Flight::setAircraft(Aircraft *AC)
{
    aircraft = AC;
}
Aircraft *Flight::getAircraft() const
{
    return aircraft;
}
void Flight::setDepartureairport(Airport *depA)
{
    departureAirport = depA;
}
Airport *Flight::getDepartureairport() const
{
    return departureAirport;
}
void Flight::setArrivalairport(Airport *arrA)
{
    arrivalAirport = arrA;
}
Airport *Flight::getArrivalairport() const
{
    return arrivalAirport;
}
void Flight::setDeparturetime(std::string deptT)
{
    departureTime = deptT;
}
std::string Flight::getDeparturetime() const
{
    return departureTime;
}
void Flight::setArrivaltime(std::string arrT)
{
    arrivalTime = arrT;
}
std::string Flight::getArrivaltime() const
{
    return arrivalTime;
}
void Flight::setStatus(int stat)
{
    status = stat;
}
int Flight::getStatus() const
{
    return status;
}
void Flight::setPassengersonboard(int passOnb)
{
    passengersOnboard = passOnb;
}
int Flight::getPassengersonboard() const
{
    return passengersOnboard;
}
void Flight::setCargoweight(double cargoW)
{
    cargoWeight = cargoW;
}
double Flight::getCargoweight() const
{
    return cargoWeight;
}
void Flight::setDelayed(bool delayed)
{
    isDelayed = delayed;
}
bool Flight::getDelayed() const
{
    return isDelayed;
}
void Flight::setAssignDepartureRunway(const std::string &runway)
{
    assignDepartureRunway = runway;
}
std::string Flight::getAssignDepartureRunway() const
{
    return assignDepartureRunway;
}
void Flight::setAssignArrivalRunway(const std::string &runway)
{
    assignArrivalRunway = runway;
}
std::string Flight::getAssignArrivalRunway() const
{
    return assignArrivalRunway;
}

bool Flight::hasDepartureRunwayAssigned() const
{
    return !assignDepartureRunway.empty();
}

bool Flight::hasArrivalRunwayAssigned() const
{
    return !assignArrivalRunway.empty();
}

void Flight::displayFlightinfo() const
{
    std::cout << std::endl;
    std::cout << "--------------------------------" << std::endl;
    std::cout << COLOR_CYAN << "FLIGHT-NUMBER : " << flightNumber << std::endl;
    std::cout << "DEPARTURE TIME : " << departureTime << std::endl;
    std::cout << "ARRIVAL TIME : " << arrivalTime << std::endl;
    std::cout << "FLIGHT-STATUS : " << COLOR_RESET;

    if (isDelayed)
    {
        std::cout << COLOR_RED;
    }
    else
    {
        std::cout << COLOR_GREEN;
    }

    switch (status)
    {
    case 0:
        std::cout << COLOR_GREEN << "SCHEDULED!" << COLOR_RESET << std::endl;
        break;
    case 1:
        std::cout << COLOR_GREEN << "DEPARTED!" << COLOR_RESET << std::endl;
        break;
    case 2:
        std::cout << COLOR_GREEN << "ARRIVED!" << COLOR_RESET << std::endl;
        break;
    case 3:
        std::cout << COLOR_RED << "CANCELLED!" << COLOR_RESET << std::endl;
        break;
    case 4:
        std::cout << COLOR_YELLOW << "UNKNOWN!" << COLOR_RESET << std::endl;
        break;
    }
    std::cout << std::endl;
    std::cout << "---DEPARTURE AIRPORT INFO---" << std::endl;
    if (departureAirport != nullptr)
    {
        departureAirport->displayAirportinfo();
        std::cout << "ASSIGNED DEPARTURE RUNWAY : " << (assignDepartureRunway.empty() ? "NONE" : assignDepartureRunway) << std::endl;
    }
    std::cout << "---ARRIVAL AIRPORT INFO---" << std::endl;
    if (arrivalAirport != nullptr)
    {
        arrivalAirport->displayAirportinfo();
        std::cout << "ASSIGNED ARRIVAL RUNWAY : " << (assignArrivalRunway.empty() ? "NONE" : assignArrivalRunway) << std::endl;
    }
    std::cout << "---AIRCRAFT INFO---" << std::endl;
    if (aircraft != nullptr)
    {
        aircraft->displayAircraftinfo();
    }
    std::cout << COLOR_CYAN << "THE NUMBER OF PASSENGERS ON BOARD ARE : " << passengersOnboard << std::endl;
    std::cout << "THE CARGO WEIGHT IN KILOGRAMS(KG) IS : " << cargoWeight << COLOR_RESET << std::endl;
    std::cout << "--------------------------------" << std::endl;
}

// ATCSystem class implementation
void ATCSystem::initializeData()
{
    City *city1 = new City("KARACHI");
    City *city2 = new City("GWADAR");
    City *city3 = new City("QUETTA");
    City *city4 = new City("MULTAN");
    City *city5 = new City("LAHORE");
    City *city6 = new City("PESHAWAR");
    City *city7 = new City("ISLAMABAD");

    atcsCity.push_back(city1);
    atcsCity.push_back(city2);
    atcsCity.push_back(city3);
    atcsCity.push_back(city4);
    atcsCity.push_back(city5);
    atcsCity.push_back(city6);
    atcsCity.push_back(city7);

    Airport *airport1 = new Airport("KARACHI", "KIA", 7, 7);
    Airport *airport2 = new Airport("GWADAR", "GIA", 1, 1);
    Airport *airport3 = new Airport("QUETTA", "QIA", 2, 2);
    Airport *airport4 = new Airport("MULTAN", "MIA", 4, 4);
    Airport *airport5 = new Airport("LAHORE", "LIA", 6, 6);
    Airport *airport6 = new Airport("PESHAWAR", "PesIA", 5, 5);
    Airport *airport7 = new Airport("ISLAMABAD", "IsLIA", 3, 3);

    airport1->initializeRunways();
    airport2->initializeRunways();
    airport3->initializeRunways();
    airport4->initializeRunways();
    airport5->initializeRunways();
    airport6->initializeRunways();
    airport7->initializeRunways();

    atcsAirport.push_back(airport1);
    atcsAirport.push_back(airport2);
    atcsAirport.push_back(airport3);
    atcsAirport.push_back(airport4);
    atcsAirport.push_back(airport5);
    atcsAirport.push_back(airport6);
    atcsAirport.push_back(airport7);

    PassengerAircraft *pAircraft1 = new PassengerAircraft("BOEING-747", "B2-17", false, 900);
    PassengerAircraft *pAircraft2 = new PassengerAircraft("AIRBUS-A350", "AB-35", false, 1000);

    CargoAircraft *cAircraft1 = new CargoAircraft("LOCKHEED-C130", "H-C130", false, 30000.00);
    CargoAircraft *cAircraft2 = new CargoAircraft("LOCKHEED-C150", "H-150", false, 50000.00);

    Airline *airline1 = new Airline("PIA");
    airline1->addAircraft(pAircraft1);
    airline1->addAircraft(cAircraft1);
    atcsAirline.push_back(airline1);

    Airline *airline2 = new Airline("EMIRATES");
    airline2->addAircraft(pAircraft2);
    airline2->addAircraft(cAircraft2);
    atcsAirline.push_back(airline2);

    Airline *airline3 = new Airline("QATAR-AirWays");
    airline3->addAircraft(pAircraft2);
    airline3->addAircraft(cAircraft1);
    atcsAirline.push_back(airline3);

    Flight *flight1 = new Flight("P001", pAircraft1, airport1, airport2, "09:00", "11:00", 0, 0, 0.0, "", "");
    Flight *flight2 = new Flight("E003", pAircraft2, airport2, airport3, "12:00", "14:00", 0, 0, 0.0, "", "");
    Flight *flight3 = new Flight("Q005", pAircraft2, airport3, airport4, "03:00", "05:00", 0, 0, 0.0, "", "");
    Flight *flight4 = new Flight("P007", pAircraft1, airport4, airport5, "06:00", "08:00", 0, 0, 0.0, "", "");
    Flight *flight5 = new Flight("E009", pAircraft2, airport5, airport6, "09:00", "11:00", 0, 0, 0.0, "", "");
    Flight *flight6 = new Flight("Q011", pAircraft2, airport6, airport7, "00:00", "13:00", 0, 0, 0.0, "", "");
    Flight *flight7 = new Flight("P013", pAircraft1, airport7, airport1, "14:00", "17:00", 0, 0, 0.0, "", "");

    atcsFlight.push_back(flight1);
    atcsFlight.push_back(flight2);
    atcsFlight.push_back(flight3);
    atcsFlight.push_back(flight4);
    atcsFlight.push_back(flight5);
    atcsFlight.push_back(flight6);
    atcsFlight.push_back(flight7);

    Flight *flight8 = new Flight("P911", cAircraft1, airport1, airport6, "00:00", "05:00", 0, 0, 0.0, "", "");
    Flight *flight9 = new Flight("E922", cAircraft2, airport2, airport7, "06:00", "10:00", 0, 0, 0.0, "", "");
    Flight *flight10 = new Flight("Q933", cAircraft1, airport4, airport6, "12:00", "15:30", 0, 0, 0.0, "", "");

    atcsFlight.push_back(flight8);
    atcsFlight.push_back(flight9);
    atcsFlight.push_back(flight10);

    for (Flight *flight : atcsFlight)
    {
        Aircraft *aircraft = flight->getAircraft();

        if (aircraft->getAircraftType() == PASSENGER)
        {
            int maxPax = aircraft->getMaxPas();
            int randomPax = rand() % (maxPax + 1);
            flight->setPassengersonboard(randomPax);
        }
        else if (aircraft->getAircraftType() == CARGO)
        {
            double maxCargo = aircraft->getMaxcargo();
            int percentage = rand() % 1001;
            double randomCargo = (percentage * maxCargo) / 1000.0;
            flight->setCargoweight(randomCargo);
        }
    }
}

void ATCSystem::showMainmenu()
{
    std::cout << std::endl;
    std::cout << COLOR_BLUE << "***AIR-TRAFFIC CONTROL SYSTEM***" << std::endl;
    std::cout << "1.   VIEW ALL FLIGHTS" << std::endl;
    std::cout << "2.   VIEW ALL AIRPORTS" << std::endl;
    std::cout << "3.   VIEW ALL AIRLINES" << std::endl;
    std::cout << "4.   VIEW CURRENT FLIGHT-LOG" << std::endl;
    std::cout << "5.   VIEW MAX-CAPACITIES OF AIRLINES" << std::endl;
    std::cout << "6.   SHOW AIRPORT COUNT(STATIC)" << std::endl;
    std::cout << "7.   UPDATE FLIGHT STATUS" << std::endl;
    std::cout << "8.   BOARD PASSENGERS" << std::endl;
    std::cout << "9.   LOAD CARGO" << std::endl;
    std::cout << "10.  UNLOAD PASSENGERS" << std::endl;
    std::cout << "11.  UNLOAD CARGO" << std::endl;
    std::cout << "12.  ASSIGN RUNWAYS" << std::endl;
    std::cout << "13.  COPY AIRPORT" << std::endl;
    std::cout << "14.  CHECK FLIGHT CONFLICTS" << std::endl;
    std::cout << "15.  SAVE FLIGHT LOG TO FILE" << std::endl;
    std::cout << "16.  VIEW SAVED FLIGHT LOGS" << std::endl;
    std::cout << "17.  CANCEL FLIGHT" << std::endl;
    std::cout << "18.  PROJECT-DESCRIPTION" << std::endl;
    std::cout << "19.  DEVLOPERS DESCRIPTION" << std::endl;
    std::cout << "20.  EXIT" << COLOR_RESET << std::endl;
}

void ATCSystem::run()
{
    std::cout << std::endl;
    initializeData();
    int choice;
    do
    {
        showMainmenu();
        std::cout << COLOR_BLACK << "ENTER YOUR CHOICE(1-20) : " << COLOR_RESET << std::endl;
        std::cin >> choice;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << COLOR_RED << "INVALID INPUT! Please enter a valid number." << COLOR_RESET << std::endl;
            continue;
        }

        std::cin.ignore(10000, '\n');

        if (choice < 1 || choice > 20)
        {
            std::cout << COLOR_RED << "INVALID CHOICE! TRY AGAIN." << COLOR_RESET << std::endl;
            run();
        }

        switch (choice)
        {
        case 1:
            viewAllFlights();
            break;
        case 2:
            viewAllAirports();
            break;
        case 3:
            viewAllAirlines();
            break;
        case 4:
            viewcurrentFlightlog();
            break;
        case 5:
            viewMaxCapacities();
            break;
        case 6:
            std::cout << "Total Airports Created: " << Airport::getAirportCount() << std::endl;
            break;
        case 7:
            updateFlightstatus();
            break;
        case 8:
            boardPassengers();
            break;
        case 9:
            loadCargo();
            break;
        case 10:
            unloadPassengers();
            break;
        case 11:
            unloadCargo();
            break;
        case 12:
            assignRunwayToFlight();
            break;
        case 13:
            copyAirport();
            break;
        case 14:
            checkFlightConflicts();
            break;
        case 15:
            saveFlightLogToFile();
            break;
        case 16:
            viewSavedFlightLogs();
            break;
        case 17:
            cancelFlight();
            break;
        case 18:
            projectDescription();
            break;
        case 19:
            devlopersDescription();
            break;
        case 20:
            std::cout << COLOR_GREEN << "AIR TRAFFIC CONTROL SIMULATION EXITED SUCCESSFULLY!" << COLOR_RESET << std::endl;
            break;
        default:
            std::cout << COLOR_RED << "INVALID CHOICE! TRY AGAIN." << COLOR_RESET << std::endl;
        }
    } while (choice != 20);
}

void ATCSystem::viewAllFlights()
{
    std::cout << "---ALL FLIGHTS(DATA)--- " << std::endl;
    for (Flight *flight : atcsFlight)
    {
        flight->displayFlightinfo();
    }
}

void ATCSystem::viewAllAirports()
{
    std::cout << "---ALL AIRPORTS(DATA)---" << std::endl;
    for (Airport *airport : atcsAirport)
    {
        airport->displayAirportinfo();
    }
}

void ATCSystem::viewAllAirlines()
{
    std::cout << "---ALL AIRLINES(DATA)---" << std::endl;
    for (Airline *airline : atcsAirline)
    {
        airline->displayFleet();
    }
}

void ATCSystem::updateFlightstatus()
{
    std::string flightNum;
    std::cout << COLOR_BLACK << "ENTER THE FLIGHT NUMBER OF THE FLIGHT THAT YOU WANT TO UPDATE THE STATUS FOR : " << COLOR_RESET << std::endl;
    std::cin >> flightNum;

    for (Flight *flight : atcsFlight)
    {
        if (flightNum == flight->getFlightnumber())
        {
            int newstatus;
            std::cout << "ENTER NEW STATUS (0-SCHEDULED,1-DEPARTED,2-ARRIVED,3-CANCELLED,4-UNKNOWN) : " << std::endl;
            std::cin >> newstatus;

            if (newstatus >= 0 && newstatus <= 4)
            {
                flight->setStatus(newstatus);
                std::cout << "FLIGHT STATUS UPDATED!" << std::endl;

                if ((rand() % 100) < 30)
                {
                    flight->setDelayed(true);
                    playAlertSound();
                    std::cout << COLOR_RED << "ALERT: This flight has been delayed!" << COLOR_RESET << std::endl;
                }
                else
                {
                    flight->setDelayed(false);
                }
            }
            else
            {
                std::cout << COLOR_RED << "INVALID STATUS CODE!" << COLOR_RESET << std::endl;
            }
            return;
        }
    }
    std::cout << COLOR_RED << "FLIGHT NOT FOUND!" << COLOR_RESET << std::endl;
}

void ATCSystem::boardPassengers()
{
    std::string flightNum;
    std::cout << COLOR_BLACK << "ENTER THE NUMBER OF THE FLIGHT IN WHICH PASSENGERS ARE BOARDING-ON : " << COLOR_RESET << std::endl;
    std::cin >> flightNum;

    for (Flight *flight : atcsFlight)
    {
        if (flight->getFlightnumber() == flightNum)
        {
            Aircraft *aircraft = flight->getAircraft();
            if (!aircraft)
            {
                std::cout << COLOR_RED << "NO AIRCRAFT ASSIGNED!" << COLOR_RESET << std::endl;
                return;
            }
            int maxPassengers = aircraft->getMaxPas();
            if (aircraft->getAircraftType() != PASSENGER)
            {
                std::cout << COLOR_RED << "ERROR! NOT A PASSENGER AIRCRAFT." << COLOR_RESET << std::endl;
                return;
            }
            std::cout << "ENTER THE NUMBER OF PASSENGERS TO BOARD (Max-Passengers : " << maxPassengers << ") : " << std::endl;
            int numPassengers;
            std::cin >> numPassengers;
            if (numPassengers <= 0)
            {
                std::cout << COLOR_RED << "INVALID NUMBER OF PASSENGERS!" << COLOR_RESET << std::endl;
            }
            else if (flight->getPassengersonboard() + numPassengers > maxPassengers)
            {
                std::cout << COLOR_RED << "ERROR: PASSENGERS EXCEED MAXIMUM CAPACITY!" << COLOR_RESET << std::endl;
                playAlertSound();
            }
            else
            {
                flight->setPassengersonboard(flight->getPassengersonboard() + numPassengers);
                std::cout << numPassengers << COLOR_GREEN << " PASSENGERS BOARDED!" << COLOR_RESET << std::endl;
            }
            return;
        }
    }
    std::cout << COLOR_RED << "ERROR: FLIGHT NOT FOUND!" << COLOR_RESET << std::endl;
}

void ATCSystem::loadCargo()
{
    std::string flightNum;
    std::cout << COLOR_BLACK << "ENTER THE NUMBER OF THE FLIGHT IN WHICH CARGO IS BEING LOADED : " << COLOR_RESET << std::endl;
    std::cin >> flightNum;

    for (Flight *flight : atcsFlight)
    {
        if (flight->getFlightnumber() == flightNum)
        {
            Aircraft *aircraft = flight->getAircraft();
            if (!aircraft)
            {
                std::cout << COLOR_RED << "ERROR: NO AIRCRAFT ASSIGNED!" << COLOR_RESET << std::endl;
                return;
            }
            double maxcargokg = aircraft->getMaxcargo();
            if (aircraft->getAircraftType() != CARGO)
            {
                std::cout << COLOR_RED << "ERROR: NOT A CARGO AIRCRAFT." << COLOR_RESET << std::endl;
                return;
            }
            std::cout << "ENTER THE WEIGHT(KG) OF CARGO TO LOAD (Max-Cargo : " << maxcargokg << ")" << std::endl;
            double cargoWeight;
            std::cin >> cargoWeight;
            if (cargoWeight <= 0)
            {
                std::cout << COLOR_RED << "INVALID CARGO WEIGHT!" << COLOR_RESET << std::endl;
            }
            else if (flight->getCargoweight() + cargoWeight > maxcargokg)
            {
                std::cout << COLOR_RED << "ERROR: CARGO EXCEEDS MAXIMUM CAPACITY!" << COLOR_RESET << std::endl;
                playAlertSound();
            }
            else
            {
                flight->setCargoweight(flight->getCargoweight() + cargoWeight);
                std::cout << cargoWeight << COLOR_GREEN << " CARGO WEIGHT(KG) LOADED!" << COLOR_RESET << std::endl;
            }
            return;
        }
    }
    std::cout << COLOR_RED << "ERROR: FLIGHT NOT FOUND!" << COLOR_RESET << std::endl;
}

void ATCSystem::unloadPassengers()
{
    std::string flightNum;
    std::cout << COLOR_BLACK << "ENTER THE NUMBER OF THE FLIGHT FROM WHICH PASSENGERS ARE UNLOADING : " << COLOR_RESET << std::endl;
    std::cin >> flightNum;

    for (Flight *flight : atcsFlight)
    {
        if (flight->getFlightnumber() == flightNum)
        {
            Aircraft *aircraft = flight->getAircraft();
            if (!aircraft)
            {
                std::cout << COLOR_RED << "ERROR: NO AIRCRAFT ASSIGNED!" << COLOR_RESET << std::endl;
                return;
            }
            if (aircraft->getAircraftType() != PASSENGER)
            {
                std::cout << COLOR_RED << "ERROR! NOT A PASSENGER AIRCRAFT." << COLOR_RESET << std::endl;
                return;
            }
            int passengersOnboard = flight->getPassengersonboard();
            if (passengersOnboard == 0)
            {
                std::cout << COLOR_YELLOW << "NO PASSENGERS ONBOARD TO UNLOAD." << COLOR_RESET << std::endl;
                return;
            }
            std::cout << "ENTER THE NUMBER OF PASSENGERS TO UNLOAD (Current onboard: " << passengersOnboard << ") : " << std::endl;
            int numPassengers;
            std::cin >> numPassengers;
            if (numPassengers <= 0)
            {
                std::cout << COLOR_RED << "INVALID NUMBER OF PASSENGERS!" << COLOR_RESET << std::endl;
            }
            else if (numPassengers > passengersOnboard)
            {
                std::cout << COLOR_RED << "ERROR: NUMBER OF PASSENGERS TO UNLOAD EXCEEDS CURRENT ONBOARD!" << COLOR_RESET << std::endl;
            }
            else
            {
                flight->setPassengersonboard(passengersOnboard - numPassengers);
                std::cout << numPassengers << COLOR_GREEN << " PASSENGERS UNLOADED!" << COLOR_RESET << std::endl;
            }
            return;
        }
    }
    std::cout << COLOR_RED << "ERROR: FLIGHT NOT FOUND!" << COLOR_RESET << std::endl;
}

void ATCSystem::unloadCargo()
{
    std::string flightNum;
    std::cout << COLOR_BLACK << "ENTER THE NUMBER OF THE FLIGHT FROM WHICH CARGO IS BEING UNLOADED : " << COLOR_RESET << std::endl;
    std::cin >> flightNum;

    for (Flight *flight : atcsFlight)
    {
        if (flight->getFlightnumber() == flightNum)
        {
            Aircraft *aircraft = flight->getAircraft();
            if (!aircraft)
            {
                std::cout << COLOR_RED << "ERROR: NO AIRCRAFT ASSIGNED!" << COLOR_RESET << std::endl;
                return;
            }
            if (aircraft->getAircraftType() != CARGO)
            {
                std::cout << COLOR_RED << "ERROR: NOT A CARGO AIRCRAFT." << COLOR_RESET << std::endl;
                return;
            }
            double cargoWeight = flight->getCargoweight();
            if (cargoWeight == 0.0)
            {
                std::cout << COLOR_YELLOW << "NO CARGO ONBOARD TO UNLOAD." << COLOR_RESET << std::endl;
                return;
            }
            std::cout << "ENTER THE WEIGHT(KG) OF CARGO TO UNLOAD (Current cargo: " << cargoWeight << ") : " << std::endl;
            double unloadWeight;
            std::cin >> unloadWeight;
            if (unloadWeight <= 0)
            {
                std::cout << COLOR_RED << "INVALID CARGO WEIGHT!" << COLOR_RESET << std::endl;
            }
            else if (unloadWeight > cargoWeight)
            {
                std::cout << COLOR_RED << "ERROR: CARGO TO UNLOAD EXCEEDS CURRENT CARGO WEIGHT!" << COLOR_RESET << std::endl;
            }
            else
            {
                flight->setCargoweight(cargoWeight - unloadWeight);
                std::cout << unloadWeight << COLOR_GREEN << " CARGO WEIGHT(KG) UNLOADED!" << COLOR_RESET << std::endl;
            }
            return;
        }
    }
    std::cout << COLOR_RED << "ERROR: FLIGHT NOT FOUND!" << COLOR_RESET << std::endl;
}

void ATCSystem::assignRunwayToFlight()
{
    int choice;
    std::cout << COLOR_BLACK << "CHOOSE OPTION: " << std::endl;
    std::cout << "1. ASSIGN RUNWAYS TO ALL FLIGHTS WITHOUT RUNWAYS" << std::endl;
    std::cout << "2. ASSIGN RUNWAYS TO A SPECIFIC FLIGHT" << std::endl;
    std::cout << "ENTER CHOICE (1 OR 2) : " << COLOR_RESET << std::endl;
    std::cin >> choice;

    if (choice == 1)
    {
        bool anyProcessed = false;
        for (Flight *flight : atcsFlight)
        {
            if (!flight->hasDepartureRunwayAssigned() || !flight->hasArrivalRunwayAssigned())
            {
                Airport *depAirport = flight->getDepartureairport();
                Airport *arrAirport = flight->getArrivalairport();

                std::string depRunway = depAirport->allocateRunway();
                std::string arrRunway = arrAirport->allocateRunway();

                bool depRunwayAllocated = !depRunway.empty();
                bool arrRunwayAllocated = !arrRunway.empty();

                if (depRunwayAllocated && arrRunwayAllocated)
                {
                    flight->setAssignDepartureRunway(depRunway);
                    flight->setAssignArrivalRunway(arrRunway);
                    std::cout << COLOR_GREEN << "RUNWAY ASSIGNED TO FLIGHT " << COLOR_RESET << COLOR_CYAN << flight->getFlightnumber() << COLOR_RESET << std::endl;
                }
                else
                {
                    flight->setStatus(3);
                    std::cout << COLOR_RED << "Flight " << flight->getFlightnumber() << " CANCELLED: " << COLOR_RESET;
                    if (!depRunwayAllocated && !arrRunwayAllocated)
                        std::cout << COLOR_YELLOW << "Departure and Arrival airports have no runways available. Flight grounded." << COLOR_RESET << std::endl;
                    else if (!depRunwayAllocated)
                        std::cout << COLOR_YELLOW << "Departure airport has no runway available. Flight grounded." << COLOR_YELLOW << std::endl;
                    else
                        std::cout << COLOR_YELLOW << "Arrival airport has no runway available. Flight grounded." << COLOR_YELLOW << std::endl;
                }
                anyProcessed = true;
            }
        }
        if (!anyProcessed)
        {
            std::cout << COLOR_GREEN << "All flights already have departure and arrival runways assigned or no flights to assign." << COLOR_RESET << std::endl;
        }
    }
    else if (choice == 2)
    {
        std::string flightNum;
        std::cout << COLOR_BLACK << "ENTER FLIGHT NUMBER TO ASSIGN RUNWAY: " << COLOR_RESET;
        std::cin >> flightNum;

        for (Flight *flight : atcsFlight)
        {
            if (flight->getFlightnumber() == flightNum)
            {
                if (flight->hasDepartureRunwayAssigned() && flight->hasArrivalRunwayAssigned())
                {
                    std::cout << COLOR_GREEN << "Flight " << flightNum << " already has runways assigned for departure and arrival." << COLOR_RESET << std::endl;
                    return;
                }

                Airport *depAirport = flight->getDepartureairport();
                Airport *arrAirport = flight->getArrivalairport();

                std::string depRunway = depAirport->allocateRunway();
                std::string arrRunway = arrAirport->allocateRunway();

                bool depRunwayAllocated = !depRunway.empty();
                bool arrRunwayAllocated = !arrRunway.empty();

                if (depRunwayAllocated && arrRunwayAllocated)
                {
                    flight->setAssignDepartureRunway(depRunway);
                    flight->setAssignArrivalRunway(arrRunway);
                    std::cout << COLOR_GREEN << "RUNWAY ASSIGNED TO FLIGHT " << COLOR_RESET << COLOR_CYAN << flightNum << COLOR_RESET << std::endl;
                }
                else
                {
                    flight->setStatus(3);
                    std::cout << COLOR_RED << "Flight " << flightNum << " CANCELLED: " << COLOR_RESET;
                    if (!depRunwayAllocated && !arrRunwayAllocated)
                        std::cout << COLOR_RED << "Departure and Arrival airports have no runways available. Flight grounded." << COLOR_RESET << std::endl;
                    else if (!depRunwayAllocated)
                        std::cout << COLOR_RED << "Departure airport has no runway available. Flight grounded." << COLOR_RESET << std::endl;
                    else
                        std::cout << COLOR_RED << "Arrival airport has no runway available. Flight grounded." << COLOR_RESET << std::endl;
                }
                return;
            }
        }
        std::cout << COLOR_RED << "FLIGHT NOT FOUND!" << COLOR_RESET << std::endl;
    }
    else
    {
        std::cout << COLOR_RED << "Invalid choice." << COLOR_RESET << std::endl;
    }
}

void ATCSystem::viewcurrentFlightlog()
{
    std::cout << COLOR_BLACK << "-----FLIGHT LOG-----" << COLOR_RESET << std::endl;
    for (Flight *flight : atcsFlight)
    {
        std::cout << COLOR_BLACK << "FLIGHT: " << COLOR_RESET << COLOR_CYAN << flight->getFlightnumber() << COLOR_RESET << COLOR_BLACK << " | STATUS: " << COLOR_RESET;

        switch (flight->getStatus())
        {
        case 0:
            std::cout << COLOR_YELLOW << "SCHEDULED" << COLOR_RESET;
            break;
        case 1:
            std::cout << COLOR_GREEN << "DEPARTED" << COLOR_RESET;
            break;
        case 2:
            std::cout << COLOR_GREEN << "ARRIVED" << COLOR_RESET;
            break;
        case 3:
            std::cout << COLOR_RED << "CANCELLED" << COLOR_RESET;
            break;
        case 4:
            std::cout << COLOR_YELLOW << "UNKNOWN" << COLOR_RESET;
            break;
        default:
            std::cout << COLOR_RED << "INVALID STATUS" << COLOR_RESET;
            break;
        }

        std::cout << COLOR_BLACK << " | PASSENGERS: " << COLOR_RESET << COLOR_CYAN << flight->getPassengersonboard() << COLOR_RESET
                  << COLOR_BLACK << " | CARGO: " << COLOR_RESET << COLOR_CYAN << flight->getCargoweight() << " kg" << COLOR_RESET << std::endl;
    }
}

void ATCSystem::checkFlightConflicts()
{
    bool conflictFound = false;

    for (int i = 0; i < atcsFlight.size(); i++)
    {
        for (int j = i + 1; j < atcsFlight.size(); j++)
        {
            Flight *flight1 = atcsFlight[i];
            Flight *flight2 = atcsFlight[j];

            if (flight1->getDepartureairport() == flight2->getDepartureairport())
            {
                if (flight1->getDeparturetime() == flight2->getDeparturetime())
                {
                    if (flight1->getAssignDepartureRunway() == flight2->getAssignDepartureRunway() && !flight1->getAssignDepartureRunway().empty())
                    {
                        conflictFound = true;
                        playAlertSound();
                        std::cout << COLOR_RED << "FLIGHT CONFLICT: Flights " << flight1->getFlightnumber()
                                  << " and " << flight2->getFlightnumber()
                                  << " share the SAME DEPARTURE RUNWAY "
                                  << flight1->getAssignDepartureRunway()
                                  << " at " << flight1->getDepartureairport()->getAirportn()
                                  << " at time " << flight1->getDeparturetime() << COLOR_RESET << std::endl;
                    }
                    else
                    {
                        std::cout << COLOR_GREEN << "NO CONFLICT: Flights " << flight1->getFlightnumber()
                                  << " and " << flight2->getFlightnumber()
                                  << " have the same DEPARTURE schedule at "
                                  << flight1->getDepartureairport()->getAirportn()
                                  << " but DIFFERENT RUNWAYS assigned." << COLOR_RESET << std::endl;
                    }
                }
            }

            if (flight1->getArrivalairport() == flight2->getArrivalairport())
            {
                if (flight1->getArrivaltime() == flight2->getArrivaltime())
                {
                    if (flight1->getAssignArrivalRunway() == flight2->getAssignArrivalRunway() && !flight1->getAssignArrivalRunway().empty())
                    {
                        conflictFound = true;
                        playAlertSound();
                        std::cout << COLOR_RED << "FLIGHT CONFLICT: Flights " << flight1->getFlightnumber()
                                  << " and " << flight2->getFlightnumber()
                                  << " share the SAME ARRIVAL RUNWAY "
                                  << flight1->getAssignArrivalRunway()
                                  << " at " << flight1->getArrivalairport()->getAirportn()
                                  << " at time " << flight1->getArrivaltime() << COLOR_RESET << std::endl;
                    }
                    else
                    {
                        std::cout << COLOR_GREEN << "NO CONFLICT: Flights " << flight1->getFlightnumber()
                                  << " and " << flight2->getFlightnumber()
                                  << " have the same ARRIVAL schedule at "
                                  << flight1->getArrivalairport()->getAirportn()
                                  << " but DIFFERENT RUNWAYS assigned." << COLOR_RESET << std::endl;
                    }
                }
            }
        }
    }

    if (!conflictFound)
    {
        std::cout << COLOR_GREEN << "SUCCESSFUL SIMULATION EXECUTION: NO FLIGHT CONFLICTS DETECTED" << COLOR_RESET << std::endl;
    }
}

void ATCSystem::viewMaxCapacities()
{
    std::string airlineName;
    std::cout << "ENTER AIRLINE NAME TO CHECK MAX CAPACITIES: ";
    std::cin >> airlineName;
    for (Airline *airline : atcsAirline)
    {
        if (airline->Airlinename == airlineName)
        {
            int maxPassengerCapacity;
            double maxCargoCapacity;
            getMaxCapacities(*airline, maxPassengerCapacity, maxCargoCapacity);
            std::cout << "MAX PASSENGER CAPACITY: " << maxPassengerCapacity << std::endl;
            std::cout << "MAX CARGO CAPACITY: " << maxCargoCapacity << " kg" << std::endl;
            return;
        }
    }
    std::cout << COLOR_RED << "AIRLINE NOT FOUND!" << COLOR_RESET << std::endl;
}

void ATCSystem::copyAirport()
{
    std::string airportName1, airportName2;
    std::cout << COLOR_BLACK << "ENTER THE NAME OF THE AIRPORT TO COPY FROM: " << COLOR_RESET << std::endl;
    std::cin >> airportName1;
    std::cout << COLOR_BLACK << "ENTER THE NAME OF THE AIRPORT TO COPY TO: " << COLOR_RESET << std::endl;
    std::cin >> airportName2;
    for (Airport *airport1 : atcsAirport)
    {
        if (airport1->getAirportn() == airportName1)
        {
            for (Airport *airport2 : atcsAirport)
            {
                if (airport2->getAirportn() == airportName2)
                {
                    *airport2 = *airport1;
                    std::cout << COLOR_GREEN << "Airport copied successfully!" << COLOR_RESET << std::endl;
                    return;
                }
            }
        }
    }
    std::cout << COLOR_RED << "AIRPORT NOT FOUND!" << COLOR_RESET << std::endl;
}

void ATCSystem::cancelFlight()
{
    std::string flightNum;
    std::cout << COLOR_BLACK << "ENTER FLIGHT NUMBER TO CANCEL: " << COLOR_RESET;
    std::cin >> flightNum;

    bool flightFound = false;

    for (Flight *flight : atcsFlight)
    {
        if (flight->getFlightnumber() == flightNum)
        {
            flight->setStatus(3);
            std::cout << COLOR_RED << "Flight " << flightNum << " has been cancelled." << COLOR_RESET << std::endl;
            flightFound = true;
            break;
        }
    }

    if (!flightFound)
    {
        std::cout << COLOR_RED << "FLIGHT NOT FOUND!" << COLOR_RESET << std::endl;
    }
}

void ATCSystem::saveFlightLogToFile()
{
    std::ofstream outFile("flight-log.txt");
    if (!outFile)
    {
        std::cout << COLOR_RED << "Error opening file for writing!" << COLOR_RESET << std::endl;
        return;
    }

    time_t now = time(0);
    char *dt = ctime(&now);

    outFile << "FLIGHT LOG - " << dt << "\n";
    outFile << "========================================\n";

    for (Flight *flight : atcsFlight)
    {
        outFile << "FLIGHT: " << flight->getFlightnumber() << "\n";
        outFile << "STATUS: " << flight->getStatus() << "\n";
        outFile << "DELAYED: " << (flight->getDelayed() ? "YES" : "NO") << "\n";
        outFile << "PASSENGERS: " << flight->getPassengersonboard() << "\n";
        outFile << "CARGO: " << flight->getCargoweight() << " kg\n";
        outFile << "DEPARTURE: " << flight->getDepartureairport()->getAirportn()
                << " at " << flight->getDeparturetime() << "\n";
        outFile << "ARRIVAL: " << flight->getArrivalairport()->getAirportn()
                << " at " << flight->getArrivaltime() << "\n";
        outFile << "----------------------------------------\n";
    }

    outFile.close();
    std::cout << COLOR_GREEN << "Flight log successfully saved to flight-log.txt" << COLOR_RESET << std::endl;
}

void ATCSystem::viewSavedFlightLogs()
{
    std::ifstream inFile("flight-log.txt");

    if (!inFile)
    {
        std::cout << COLOR_RED << "Error opening file for reading!" << COLOR_RESET << std::endl;
        return;
    }
    std::cout << "-----SAVED FLIGHT LOGS-----" << std::endl;
    std::string line;

    while (std::getline(inFile, line))
    {
        std::cout << line << std::endl;
    }

    inFile.close();
    std::cout << "-----------------------------" << std::endl;
}

void ATCSystem::projectDescription()
{
    std::cout << COLOR_BLACK << "*** PROJECT DESCRIPTION ***" << std::endl;
    std::cout << "This project is an Air Traffic Control System simulation." << std::endl;
    std::cout << "It manages various aspects of air traffic, including:" << std::endl;
    std::cout << "1. Managing cities and airports." << std::endl;
    std::cout << "2. Handling different types of aircraft (passenger and cargo)." << std::endl;
    std::cout << "3. Managing flight operations such as boarding passengers, loading cargo," << std::endl;
    std::cout << "   and updating flight statuses." << std::endl;
    std::cout << "4. Checking for flight conflicts and runway assignments." << std::endl;
    std::cout << "5. Saving flight logs to a file and viewing saved logs." << std::endl;
    std::cout << "This system is designed to simulate the operations of an air traffic control system" << std::endl;
    std::cout << "and provide a user-friendly interface for managing flights and airports." << std::endl;
    std::cout << "*****************************" << COLOR_RESET << std::endl;
}

void ATCSystem::devlopersDescription()
{
    std::cout << COLOR_BLACK << "*****TEAM OF DEVELOPERS*****" << std::endl;
    std::cout << "   M.USAIDULLAH REHAN" << std::endl;
    std::cout << "   M.AYAN HAMDANI REHMAN" << std::endl;
    std::cout << "   MUHAMMAD AZEEM" << std::endl;
    std::cout << "****************************" << COLOR_RESET << std::endl;
}

void ATCSystem::playAlertSound()
{
    Beep(2000, 1000);
}

ATCSystem::~ATCSystem()
{
    for (City *city : atcsCity)
        delete city;
    for (Airport *airport : atcsAirport)
        delete airport;
    for (Airline *airline : atcsAirline)
        delete airline;
    for (Flight *flight : atcsFlight)
        delete flight;
}
