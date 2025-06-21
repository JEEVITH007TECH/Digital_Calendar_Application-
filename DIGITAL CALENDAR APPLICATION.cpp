#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Event {
    int id, day, month, year;
    string description;
};

vector<Event> events;
int nextId = 1;

void loadEvents() {
    ifstream inFile("events.txt");
    Event e;
    while (inFile >> e.id >> e.day >> e.month >> e.year) {
        inFile.ignore();
        getline(inFile, e.description);
        events.push_back(e);
        nextId = max(nextId, e.id + 1);
    }
}

void saveEvents() {
    ofstream outFile("events.txt");
    for (const auto& e : events) {
        outFile << e.id << ' ' << e.day << ' ' << e.month << ' ' << e.year << ' ' << e.description << "\n";
    }
}

void displayEvents() {
    cout << "\nID | Date       | Description\n";
    for (const auto& e : events) {
        cout << e.id << " | "
             << setw(2) << setfill('0') << e.day << '/'
             << setw(2) << setfill('0') << e.month << '/'
             << e.year << " | " << e.description << "\n";
    }
}

void addEvent() {
    Event e{nextId++};
    cout << "Date (DD MM YYYY): "; cin >> e.day >> e.month >> e.year;
    cin.ignore();
    cout << "Description: "; getline(cin, e.description);
    events.push_back(e);
    saveEvents();
    cout << " The Event is added to your Schedule \n";
}

void updateEvent() {
    displayEvents();
    cout << "Enter ID to update: ";
    int id; cin >> id; cin.ignore();
    for (auto& e : events) {
        if (e.id == id) {
            cout << "New date (DD MM YYYY): "; cin >> e.day >> e.month >> e.year;
            cin.ignore();
            cout << "New description: "; getline(cin, e.description);
            saveEvents();
            cout << " The Event is Updated \n";
            return;
        }
    }
    cout << "ID Doesn't Exists \n";
}

void deleteEvent() {
    displayEvents();
    cout << "Enter ID to delete: ";
    int id; cin >> id;
    auto it = remove_if(events.begin(), events.end(), [id](const Event& e) { return e.id == id; });
    if (it != events.end()) {
        events.erase(it, events.end());
        saveEvents();
        cout << " The Event is Deleted from your Schedule \n";
    } else {
        cout << "ID Doesn't Exists \n";
    }
}

int main() {
    loadEvents();
    char choice;
    do {
        cout << "\n[A]dd [U]pdate [D]elete [V]iew [Q]uit: ";
        cin >> choice;
        switch (toupper(choice)) {
            case 'A': addEvent(); break;
            case 'U': updateEvent(); break;
            case 'D': deleteEvent(); break;
            case 'V': displayEvents(); break;
        }
    } while (toupper(choice) != 'Q');
    return 0;
}
