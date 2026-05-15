#pragma once
#include "User.h"
using namespace std;

class Admin : public User {
public:
    Admin(int id, string n, string e)
        : User(id, n, e) {}

    void approveVehicle(Vehicle* v) {
        string repID, cond;
        int rating;

        cout << "Inspection Report ID: "; cin >> repID;
        cout << "Condition (Good/Fair/Poor): "; cin >> cond;
        cout << "Rating (1-10): "; cin >> rating;

        InspectionReport* r = new InspectionReport(repID, cond, rating);
        v->setInspectionReport(r);
        v->approve();

        cout << "Vehicle #" << v->getID() << " approved!\n";
    }

    void menu() override {
        cout << "\n--- Admin Panel (" << name << ") ---\n";
        cout << "1.Add Vehicle  2.Approve Vehicle  3.Delete Vehicle\n";
        cout << "4.View All  5.Search  6.Stats\n";
    }
};
