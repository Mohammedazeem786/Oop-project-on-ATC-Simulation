#ifndef ATCSP_H
#define ATCSP_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <windows.h>
#include <ctime>

#define COLOR_RESET "\033[0m"
#define COLOR_BLACK "\033[30m"
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE "\033[34m"
#define COLOR_CYAN "\033[36m"

enum AircraftType
{
    PASSENGER,
    CARGO
};

class City
{
protected:
    std::string cityname;

public:
    City();
    City(std::string cityN);
    void setName(std::string cityN);
    std::string getCityname();
    void displayCityinfo();
    virtual ~City() = default;
};

class Airport : public City
{
protected:
    std::string airportName;
    int totalRunways;
    int availableRunways;
    std::vector<std::string> runwayNames;
    std::vector<bool> runwayOccupied;
    static int airportCount;

public:
    Airport();
    Airport(std::string cityN, std::string airportN, int totalRunw, int availableRunw);
    void setAirportn(std::string airportN);
    std::string getAirportn();
    void setTotalrunw(int totalRunw);
    int getTotalrunw();
    void setAvailablerunw(int availableRunw);
    int getAvailablerunw();
    void initializeRunways();
    std::string allocateRunway();
    void freeRunway(const std::string &runwayName);
    bool isrunwayAvailable();
    void displayAirportinfo();
    static int getAirportCount();
};

class Aircraft
{
protected:
    std::string aircraftModel;
    std::string registrationNumber;
    bool isundermaintenance;

public:
    Aircraft();
    Aircraft(std::string aircraftM, std::string regNum, bool maintenance);
    void setAircraftmodel(std::string aircraftM);
    std::string getAircraftm() const;
    void setRegnum(std::string regNum);
    std::string getRegnum() const;
    void setMaintenance(bool maintenance);
    virtual AircraftType getAircraftType() const = 0;
    virtual int getMaxPas() const { return 0; }
    virtual double getMaxcargo() const { return 0.0; }
    bool toggleMaintenance();
    void updateMaintenancestatus(bool status);
    bool getMaintenanceStatus() const;
    virtual void displayAircraftinfo() const;
    virtual ~Aircraft() = default;
};

class PassengerAircraft : public Aircraft
{
protected:
    int maxPassengers;

public:
    PassengerAircraft();
    PassengerAircraft(std::string aircraftM, std::string regNum, bool maintenance, int maxP);
    void setMaxPas(int maxP);
    int getMaxPas() const override;
    AircraftType getAircraftType() const override;
    void displayAircraftinfo() const override;
};

class CargoAircraft : public Aircraft
{
protected:
    double maxcargokg;

public:
    CargoAircraft();
    CargoAircraft(std::string aircraftM, std::string regNum, bool maintenance, double maxCargo);
    void setMaxcargo(double maxCargo);
    double getMaxcargo() const override;
    AircraftType getAircraftType() const override;
    void displayAircraftinfo() const override;
};

class Airline
{
protected:
    std::vector<Aircraft *> fleet;

public:
    std::string Airlinename;
    Airline();
    Airline(std::string Airlinen);
    void addAircraft(Aircraft *aircraft);
    void displayFleet();
    friend void getMaxCapacities(const Airline &airline, int &maxPassengerCapacity, double &maxCargoCapacity);
};

class Flight
{
protected:
    std::string flightNumber;
    Aircraft *aircraft;
    Airport *departureAirport;
    Airport *arrivalAirport;
    std::string departureTime;
    std::string arrivalTime;
    int status;
    int passengersOnboard;
    double cargoWeight;
    bool isDelayed;
    std::string assignDepartureRunway;
    std::string assignArrivalRunway;

public:
    Flight();
    Flight(std::string flightN, Aircraft *AC, Airport *depA, Airport *arrA, std::string depT, std::string arrT, int stat, int passOnb, double cargoW, std::string asgndeprunw, std::string asgnarrrunw);
    void setFlightnumber(std::string flightN);
    std::string getFlightnumber() const;
    void setAircraft(Aircraft *AC);
    Aircraft *getAircraft() const;
    void setDepartureairport(Airport *depA);
    Airport *getDepartureairport() const;
    void setArrivalairport(Airport *arrA);
    Airport *getArrivalairport() const;
    void setDeparturetime(std::string deptT);
    std::string getDeparturetime() const;
    void setArrivaltime(std::string arrT);
    std::string getArrivaltime() const;
    void setStatus(int stat);
    int getStatus() const;
    void setPassengersonboard(int passOnb);
    int getPassengersonboard() const;
    void setCargoweight(double cargoW);
    double getCargoweight() const;
    void setDelayed(bool delayed);
    bool getDelayed() const;
    void setAssignDepartureRunway(const std::string &runway);
    std::string getAssignDepartureRunway() const;
    void setAssignArrivalRunway(const std::string &runway);
    std::string getAssignArrivalRunway() const;
    bool hasDepartureRunwayAssigned() const;
    bool hasArrivalRunwayAssigned() const;
    void displayFlightinfo() const;
};

class ATCSystem
{
protected:
    std::vector<City *> atcsCity;
    std::vector<Airport *> atcsAirport;
    std::vector<Airline *> atcsAirline;
    std::vector<Flight *> atcsFlight;

public:
    void initializeData();
    void showMainmenu();
    void run();
    void viewAllFlights();
    void viewAllAirports();
    void viewAllAirlines();
    void updateFlightstatus();
    void boardPassengers();
    void loadCargo();
    void unloadPassengers();
    void unloadCargo();
    void assignRunwayToFlight();
    void viewcurrentFlightlog();
    void checkFlightConflicts();
    void viewMaxCapacities();
    void copyAirport();
    void cancelFlight();
    void saveFlightLogToFile();
    void viewSavedFlightLogs();
    void projectDescription();
    void devlopersDescription();
    void playAlertSound();
    ~ATCSystem();
};

#endif
