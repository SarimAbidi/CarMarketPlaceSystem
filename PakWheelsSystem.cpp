#include <iostream>
#include <string>
#include "Admin.h"
#include "User.h"    
#include "Vehicle.h"
using namespace std;

const int MAX_VEHICLES = 100;

class PakWheelsSystem {
private:
    Vehicle* vehicles[MAX_VEHICLES];
    int      vehicleCount;

public:
    PakWheelsSystem() : vehicleCount(0) {}

    ~PakWheelsSystem() {
        for (int i = 0; i < vehicleCount; i++)
            delete vehicles[i];
    }

    void addVehicle(Vehicle* v) {
        if (vehicleCount >= MAX_VEHICLES) {
            cout << "Marketplace full.\n"; return;
        }
        vehicles[vehicleCount++] = v;
        cout << "Vehicle added.\n";
    }

    Vehicle* getVehicle(int id) {
        for (int i = 0; i < vehicleCount; i++)
            if (vehicles[i]->getID() == id)
                return vehicles[i];
        return nullptr;
    }

    void deleteVehicle(int id) {
        for (int i = 0; i < vehicleCount; i++) {
            if (vehicles[i]->getID() == id) {
                delete vehicles[i];
                for (int j = i; j < vehicleCount - 1; j++)
                    vehicles[j] = vehicles[j + 1];
                vehicleCount--;
                cout << "Vehicle deleted.\n";
                return;
            }
        }
        cout << "Vehicle not found.\n";
    }

    
    void listAll() const {
        if (vehicleCount == 0) { cout << "No vehicles.\n"; return; }
        cout << "\n===== All Vehicles (" << vehicleCount << ") =====\n";
        for (int i = 0; i < vehicleCount; i++)
            vehicles[i]->displayDetails();
    }

    void listApproved() const {
        bool found = false;
        cout << "\n===== Approved Listings =====\n";
        for (int i = 0; i < vehicleCount; i++) {
            if (vehicles[i]->isApproved()) {
                vehicles[i]->display();
                found = true;
            }
        }
        if (!found) cout << "No approved listings yet.\n";
    }

    void advancedSearch() {
        int option;
        cout << "\nSearch By:\n";
        cout << "1.Brand  2.Model  3.Price Range  4.Mileage  5.Year\n";
        cin >> option;

        if (option == 1) {
            string b; cout << "Brand: "; cin >> b;
            for (int i = 0; i < vehicleCount; i++)
                if (vehicles[i]->isApproved() && vehicles[i]->getBrand() == b)
                    vehicles[i]->display();
        }
        else if (option == 2) {
            string m; cout << "Model: "; cin >> m;
            for (int i = 0; i < vehicleCount; i++)
                if (vehicles[i]->isApproved() && vehicles[i]->getModel() == m)
                    vehicles[i]->display();
        }
        else if (option == 3) {
            double mn, mx;
            cout << "Min Price: "; cin >> mn;
            cout << "Max Price: "; cin >> mx;
            for (int i = 0; i < vehicleCount; i++)
                if (vehicles[i]->isApproved() &&
                    vehicles[i]->getPrice() >= mn &&
                    vehicles[i]->getPrice() <= mx)
                    vehicles[i]->display();
        }
        else if (option == 4) {
            int mx; cout << "Max Mileage: "; cin >> mx;
            for (int i = 0; i < vehicleCount; i++)
                if (vehicles[i]->isApproved() && vehicles[i]->getMileage() <= mx)
                    vehicles[i]->display();
        }
        else if (option == 5) {
            int y; cout << "Year: "; cin >> y;
            for (int i = 0; i < vehicleCount; i++)
                if (vehicles[i]->isApproved() && vehicles[i]->getYear() == y)
                    vehicles[i]->display();
        }
    }

    void showStats() const {
        int approved = 0;
        for (int i = 0; i < vehicleCount; i++)
            if (vehicles[i]->isApproved()) approved++;
        cout << "\n===== Stats =====\n";
        cout << "Total vehicles  : " << vehicleCount  << "\n";
        cout << "Approved        : " << approved       << "\n";
        cout << "Pending         : " << (vehicleCount - approved) << "\n";
        cout << "=================\n";
    }
};


int main() {

    PakWheelsSystem system;

    Admin  admin(1,  "Admin", "admin@mail.com");
    Buyer  buyer(2,  "Ali",   "ali@mail.com");
    Seller seller(3, "Ahmed", "ahmed@mail.com");

    int choice;

    do {
        cout << "\n==== PakWheels CLI ====\n";
        cout << "1.  Add Car\n";
        cout << "2.  Add Bike\n";
        cout << "3.  Approve Vehicle\n";
        cout << "4.  Search\n";
        cout << "5.  Delete Vehicle\n";
        cout << "6.  View All (Admin)\n";
        cout << "7.  View Approved Listings\n";
        cout << "8.  Add to Favorites\n";
        cout << "9.  View Favorites\n";
        cout << "10. Send Message\n";
        cout << "11. View Messages\n";
        cout << "12. Add Seller Review\n";
        cout << "13. Show Seller Reviews\n";
        cout << "14. Stats\n";
        cout << "Choice: ";
        cin  >> choice;

        if (choice == 1) {
            int id, year, hp, mileage, doors;
            string brand, model, fuel, engineID, trans;
            double price;

            cout << "ID: ";        cin >> id;
            cout << "Brand: ";     cin >> brand;
            cout << "Model: ";     cin >> model;
            cout << "Year: ";      cin >> year;
            cout << "Price: ";     cin >> price;
            cout << "Mileage: ";   cin >> mileage;
            cout << "HP: ";        cin >> hp;
            cout << "Fuel: ";      cin >> fuel;
            cout << "Engine ID: "; cin >> engineID;
            cout << "Doors: ";     cin >> doors;
            cout << "Trans (Manual/Automatic): "; cin >> trans;

            Engine e(hp, fuel, engineID);
            system.addVehicle(new Car(id, brand, model, year, price, mileage, e, doors, trans));
        }

        else if (choice == 2) {
            int id, year, hp, mileage, cc;
            string brand, model, fuel, engineID, btype;
            double price;

            cout << "ID: ";        cin >> id;
            cout << "Brand: ";     cin >> brand;
            cout << "Model: ";     cin >> model;
            cout << "Year: ";      cin >> year;
            cout << "Price: ";     cin >> price;
            cout << "Mileage: ";   cin >> mileage;
            cout << "HP: ";        cin >> hp;
            cout << "Fuel: ";      cin >> fuel;
            cout << "Engine ID: "; cin >> engineID;
            cout << "Bike Type (Sport/Cruiser/Standard): "; cin >> btype;
            cout << "CC: ";        cin >> cc;

            Engine e(hp, fuel, engineID);
            system.addVehicle(new Bike(id, brand, model, year, price, mileage, e, btype, cc));
        }

        else if (choice == 3) {
            int id; cout << "Vehicle ID: "; cin >> id;
            Vehicle* v = system.getVehicle(id);
            if (v) admin.approveVehicle(v);
            else   cout << "Vehicle not found.\n";
        }

        else if (choice == 4) {
            system.advancedSearch();
        }

        else if (choice == 5) {
            int id; cout << "Vehicle ID: "; cin >> id;
            system.deleteVehicle(id);
        }

        else if (choice == 6) {
            system.listAll();
        }

        else if (choice == 7) {
            system.listApproved();
        }

        else if (choice == 8) {
            int id; cout << "Vehicle ID: "; cin >> id;
            Vehicle* v = system.getVehicle(id);
            if (v && v->isApproved()) buyer.addFavorite(v);
            else                      cout << "Vehicle not available.\n";
        }

        else if (choice == 9) {
            buyer.showFavorites();
        }

        else if (choice == 10) {
            string msg;
            cin.ignore();
            cout << "Message to Ahmed: ";
            getline(cin, msg);
            buyer.sendMessage("Ahmed", msg);
        }

        else if (choice == 11) {
            buyer.showMessages();
        }

        else if (choice == 12) {
            int rating; string comment;
            cout << "Rating (1-10): "; cin >> rating;
            cin.ignore();
            cout << "Comment: "; getline(cin, comment);
            seller.addReview(Review("Ali", rating, comment));
        }

        else if (choice == 13) {
            seller.showReviews();
            cout << "Average Rating: " << calcAvgRating(seller) << "/10\n";
        }

        else if (choice == 14) {
            system.showStats();
        }

        else if (choice == 15) {
            cout << "\n--- Demo: Operator Overloading & Friend Functions ---\n";

            Engine e1(150, "Petrol", "E-001");
            Engine e2(150, "Petrol", "E-002");
            Engine e3(200, "Diesel", "E-003");

            cout << "Engine e1 == e2 (same HP+fuel): "
                 << (e1 == e2 ? "true" : "false") << "\n";
            cout << "Engine e1 == e3 (different): "
                 << (e1 == e3 ? "true" : "false") << "\n";

            cout << "e3 has more HP than e1: "
                 << (compareHP(e3, e1) ? "true" : "false") << "\n";

            Car c1(101, "Toyota", "Corolla", 2020, 2500000, 30000, e1);
            Car c2(101, "Honda",  "Civic",   2021, 2800000, 20000, e2);
            Car c3(102, "Suzuki", "Swift",   2022, 1800000, 10000, e3);

            cout << "\nVehicle c1 == c2 (same ID 101): "
                << (c1 == c2 ? "true" : "false") << "\n";
            cout << "Vehicle c1 == c3 (diff ID): " << (c1 == c3 ? "true" : "false") << "\n";

            cout << "\nFriend printSummary(c1):\n";
            printSummary(c1);
            cout << "Friend printSummary(c3):\n";
            printSummary(c3);

            Review r1("Ali", 8, "Great seller");
            Review r2("Ali", 9, "Fast reply");
            cout << "\nReview r1 == r2 (same reviewer name): " << (r1 == r2 ? "true" : "false") << "\n";
                
            cout << "admin == buyer (different IDs): " << (admin == (User&)buyer ? "true" : "false") << "\n";

            cout << "\nFriend printUserInfo(buyer):\n";
            printUserInfo(buyer);

            cout << "--- End Demo ---\n";
        }

    } while (choice != 0);

    return 0;
}
