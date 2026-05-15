#pragma once
#include <iostream>
#include <string>
#include "Vehicle.h"
using namespace std;

const int MAX_REVIEWS   = 50;
const int MAX_MESSAGES  = 100;
const int MAX_FAVORITES = 20;

class Review {
private:
    string reviewerName;
    int    rating;
    string comment;

public:
    Review(string n = "", int r = 0, string c = "")
        : reviewerName(n), rating(r), comment(c) {}

    void display() const {
        cout << "   " << reviewerName
             << " rated " << rating << "/10 : "
             << comment << "\n";
    }

    int    getRating()   const { return rating;       }
    string getReviewer() const { return reviewerName; }

    bool operator==(const Review& o) const {
        return reviewerName == o.reviewerName;
    }
};


class Message {
private:
    string sender;
    string receiver;
    string text;

public:
    Message(string s = "", string r = "", string t = "")
        : sender(s), receiver(r), text(t) {}

    void display() const {
        cout << "   " << sender << " -> " << receiver
             << " : " << text << "\n";
    }
};


class User {
protected:
    int    userID;
    string name;
    string email;

public:
    User(int id, string n, string e)
        : userID(id), name(n), email(e) {}

    virtual ~User() {}

    string getName()  const { return name;   }
    int    getID()    const { return userID; }
    string getEmail() const { return email;  }

    virtual void menu() = 0;

    bool operator==(const User& o) const {
        return userID == o.userID;
    }

    friend void printUserInfo(const User& u);
};

inline void printUserInfo(const User& u) {
    cout << "[UserInfo] ID:" << u.userID
         << " | Name:" << u.name
         << " | Email:" << u.email << "\n";
}


class Buyer : public User {
private:
    Vehicle* favorites[MAX_FAVORITES];
    Message  messages[MAX_MESSAGES];
    int favCount;
    int msgCount;

public:
    Buyer(int id, string n, string e)
        : User(id, n, e), favCount(0), msgCount(0) {}

    void addFavorite(Vehicle* v) {
        if (favCount >= MAX_FAVORITES) {
            cout << "Favorites list full.\n"; return;
        }
        favorites[favCount++] = v;
        cout << "Added to favorites!\n";
    }

    void showFavorites() const {
        if (favCount == 0) { cout << "No favorites yet.\n"; return; }
        cout << "\n-- Favorites of " << name << " --\n";
        for (int i = 0; i < favCount; i++)
            favorites[i]->display();
    }

    void sendMessage(string to, string text) {
        if (msgCount >= MAX_MESSAGES) return;
        messages[msgCount++] = Message(name, to, text);
        cout << "Message sent!\n";
    }

    void showMessages() const {
        if (msgCount == 0) { cout << "No messages.\n"; return; }
        cout << "\n-- Messages of " << name << " --\n";
        for (int i = 0; i < msgCount; i++)
            messages[i].display();
    }

    void menu() override {
        cout << "\n--- Buyer Menu (" << name << ") ---\n";
        cout << "1.Browse  2.Add Favorite  3.View Favorites\n";
        cout << "4.Send Message  5.View Messages\n";
    }
};


class Seller : public User {
private:
    Review reviews[MAX_REVIEWS];
    int    reviewCount;

public:
    Seller(int id, string n, string e)
        : User(id, n, e), reviewCount(0) {}

    void addReview(Review r) {
        if (reviewCount >= MAX_REVIEWS) return;
        reviews[reviewCount++] = r;
    }

    void showReviews() const {
        if (reviewCount == 0) { cout << "No reviews yet.\n"; return; }
        cout << "\n-- Reviews for " << name << " --\n";
        for (int i = 0; i < reviewCount; i++)
            reviews[i].display();
    }

    friend double calcAvgRating(const Seller& s);

    void menu() override {
        cout << "\n--- Seller Menu (" << name << ") ---\n";
        cout << "1.List Vehicle  2.View My Reviews\n";
    }
};

inline double calcAvgRating(const Seller& s) {
    if (s.reviewCount == 0) return 0.0;
    double total = 0;
    for (int i = 0; i < s.reviewCount; i++)
        total += s.reviews[i].getRating();
    return total / s.reviewCount;
}
