#pragma once
#include <iostream>
#include <string>
using namespace std;

class Engine {
private:
    int    horsepower;
    string fuelType;
    string engineID;

public:
    Engine(int hp = 0, string fuel = "Petrol", string id = "E-000")
        : horsepower(hp), fuelType(fuel), engineID(id) {}

    void display() const {
        cout << "   EngineID: " << engineID
             << " | HP: " << horsepower
             << " | Fuel: " << fuelType << "\n";
    }

    int    getHP()   const { return horsepower; }
    string getFuel() const { return fuelType;   }

    bool operator==(const Engine& o) const {
        return horsepower == o.horsepower && fuelType == o.fuelType;
    }

    friend bool compareHP(const Engine& a, const Engine& b);
};

inline bool compareHP(const Engine& a, const Engine& b) {
    return a.horsepower > b.horsepower;
}


class InspectionReport {
private:
    string reportID;
    string condition;
    int    rating;

public:
    InspectionReport(string id = "", string cond = "Unknown", int r = 0)
        : reportID(id), condition(cond), rating(r) {}

    void display() const {
        cout << "   Report: " << reportID
             << " | Condition: " << condition
             << " | Rating: " << rating << "/10\n";
    }

    int getRating() const { return rating; }
};


class Vehicle {
protected:
    int    vehicleID;
    string brand;
    string model;
    int    year;
    double price;
    int    mileage;
    bool   approved;
    Engine engine;
    InspectionReport* report;

    static int totalVehicles;

public:
    Vehicle(int id, string b, string m, int y,
            double p, int mil, Engine e)
        : vehicleID(id), brand(b), model(m), year(y),
          price(p), mileage(mil), approved(false),
          engine(e), report(nullptr)
    { totalVehicles++; }

    virtual ~Vehicle() { delete report; }

    int    getID()      const { return vehicleID; }
    string getBrand()   const { return brand;     }
    string getModel()   const { return model;     }
    int    getYear()    const { return year;      }
    double getPrice()   const { return price;     }
    int    getMileage() const { return mileage;   }
    bool   isApproved() const { return approved;  }
    Engine getEngine()  const { return engine;    }

    void approve()                      { approved = true; }
    void setInspectionReport(InspectionReport* r) {
        delete report;
        report = r;
    }

    virtual void displayDetails() const = 0;

    void display() const {
        if (!approved) return;
        displayDetails();
    }

    bool operator==(const Vehicle& o) const {
        return vehicleID == o.vehicleID;
    }

    static int getTotalVehicles() { return totalVehicles; }

    friend void printSummary(const Vehicle& v);
};

int Vehicle::totalVehicles = 0;

inline void printSummary(const Vehicle& v) {
    cout << "[Summary] ID:" << v.vehicleID
         << " | " << v.brand << " " << v.model
         << " | Rs." << v.price
         << " | Approved: " << (v.approved ? "Yes" : "No") << "\n";
}


class Car : public Vehicle {
private:
    int    numDoors;
    string transmission;

public:
    Car(int id, string b, string m, int y, double p, int mil, Engine e,
        int doors = 4, string trans = "Manual")
        : Vehicle(id, b, m, y, p, mil, e),
          numDoors(doors), transmission(trans) {}

    void displayDetails() const override {
        cout << "\n[CAR] ID:" << vehicleID
             << " | " << brand << " " << model
             << " | " << year
             << " | Rs." << price
             << " | " << mileage << "km"
             << " | Doors:" << numDoors
             << " | " << transmission << "\n";
        engine.display();
        if (report) report->display();
    }
};


class Bike : public Vehicle {
private:
    string bikeType;
    int    cc;

public:
    Bike(int id, string b, string m, int y, double p, int mil, Engine e,
         string type = "Standard", int engineCC = 125)
        : Vehicle(id, b, m, y, p, mil, e),
          bikeType(type), cc(engineCC) {}

    void displayDetails() const override {
        cout << "\n[BIKE] ID:" << vehicleID
             << " | " << brand << " " << model
             << " | " << year
             << " | Rs." << price
             << " | " << mileage << "km"
             << " | Type:" << bikeType
             << " | " << cc << "cc\n";
        engine.display();
        if (report) report->display();
    }
};
