# PakWheels Car Marketplace — Assignment 02

**Subject:** Object-Oriented Programming  
**Instructor:** Talha Shahid  
**Due:** 18-May-2026

---

## File Structure

```
A2/
├── Vehicle.h           — Engine, InspectionReport, Vehicle (abstract), Car, Bike
├── User.h              — Review, Message, User (abstract), Buyer, Seller
├── Admin.h             — Admin
└── PakWheelsSystem.cpp — PakWheelsSystem class + main()
```

---

## How to Compile & Run

```bash
g++ -std=c++17 PakWheelsSystem.cpp -o pakwheels
./pakwheels
```

---

## OOP Concepts Used

### 1. Inheritance (8 marks)

Five inheritance relationships are implemented:

| Derived | Base | Why |
|---------|------|-----|
| `Car` | `Vehicle` | A car is a vehicle with extra fields (doors, transmission) |
| `Bike` | `Vehicle` | A bike is a vehicle with extra fields (type, CC) |
| `Buyer` | `User` | A buyer is a user who can favourite vehicles and send messages |
| `Seller` | `User` | A seller is a user who receives reviews |
| `Admin` | `User` | An admin is a user who can approve/delete vehicles |

All derived classes inherit the common fields (`id`, `name`, `email` / `vehicleID`, `brand`, etc.) from their base and only add what is specific to their role.

---

### 2. Polymorphism (5 marks)

**Function overriding with virtual functions:**

`Vehicle` declares `displayDetails()` as pure virtual:
```cpp
virtual void displayDetails() const = 0;
```

`Car` and `Bike` each override it to print their own type-specific fields:

```cpp
// Car override — shows doors and transmission
void displayDetails() const override {
    cout << "[CAR] ... Doors:" << numDoors << " | " << transmission << "\n";
}

// Bike override — shows type and CC
void displayDetails() const override {
    cout << "[BIKE] ... Type:" << bikeType << " | " << cc << "cc\n";
}
```

`User` declares `menu()` as pure virtual, and `Buyer`, `Seller`, `Admin` each override it to show role-specific options.

**Function overloading** is used in `PakWheelsSystem` — `listAll()` and `listApproved()` are separate overloads serving admin vs public views.

---

### 3. Abstraction (10 marks)

`Vehicle` and `User` are both abstract classes — they cannot be instantiated directly because they have pure virtual functions. This hides implementation details and forces derived classes to provide the right behaviour.

```cpp
// Cannot do:  Vehicle v(...);   — compiler error
// Must use:   Car c(...);  or  Bike b(...);
```

Header files separate the interface (what the class exposes) from the implementation, keeping each class's internals hidden from unrelated code.

---

### 4. Operator Overloading (7 marks)

Four `operator==` overloads are implemented:

| Class | `operator==` checks |
|-------|---------------------|
| `Engine` | same horsepower AND same fuel type |
| `Vehicle` | same vehicleID (duplicate check) |
| `Review` | same reviewer name (prevent double review) |
| `User` | same userID |

**Usage in the demo (option 15):**
```cpp
Engine e1(150, "Petrol", "E-001");
Engine e2(150, "Petrol", "E-002");
cout << (e1 == e2);   // true  — same HP and fuel

Car c1(101, ...);
Car c2(101, ...);
cout << (c1 == c2);   // true  — same vehicleID
```

---

### 5. Friend Functions (5 marks)

Four friend functions are used, each justified by a specific need:

| Function | Declared friend of | Why it needs private access |
|----------|-------------------|-----------------------------|
| `compareHP(a, b)` | `Engine` | Compares raw `horsepower` field — no getter exposed for it |
| `printSummary(v)` | `Vehicle` | Prints internal `vehicleID` and `price` for admin audit log |
| `printUserInfo(u)` | `User` | Diagnostic dump of private `userID` and `email` |
| `calcAvgRating(s)` | `Seller` | Iterates private `reviews[]` array to compute the average |

**Example:**
```cpp
// calcAvgRating accesses Seller's private reviews[] and reviewCount directly
friend double calcAvgRating(const Seller& s);

// Called in main after showing reviews:
cout << "Average Rating: " << calcAvgRating(seller) << "/10\n";
```

---

### 6. Integration with Assignment 01 (5 marks)

All original features from Assignment 01 are preserved and extended:

- `Engine` and `InspectionReport` composition inside `Vehicle` — unchanged
- `Vehicle::totalVehicles` static counter — unchanged  
- `Admin::approveVehicle()` attaches an `InspectionReport` and marks approved — unchanged
- Advanced search (brand, model, price range, mileage, year) — unchanged
- Buyer favorites, messaging, seller reviews — unchanged

New additions on top:
- `Car` and `Bike` derived types with their own display
- `listAll()` (admin) vs `listApproved()` (public) split
- Stats view
- Demo option (15) that runs all operator overloading and friend function examples live

---

## Menu Options Quick Reference

```
1.  Add Car
2.  Add Bike
3.  Approve Vehicle        (admin enters inspection details)
4.  Search                 (brand / model / price range / mileage / year)
5.  Delete Vehicle
6.  View All               (admin — shows pending too)
7.  View Approved Listings (public view)
8.  Add to Favorites
9.  View Favorites
10. Send Message
11. View Messages
12. Add Seller Review
13. Show Seller Reviews    (also prints average rating via friend function)
14. Stats
15. Demo: Operator Overloading + Friend Functions
0.  Exit
```
