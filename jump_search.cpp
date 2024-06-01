#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

class Car {
public:
    int rentalID;
    string make;
    string model;
    double rentalPrice;
    string carType;

    Car() : rentalID(0), make(""), model(""), rentalPrice(0.0), carType("") {}

    Car(int id, string mk, string mdl, double price, string type) 
        : rentalID(id), make(mk), model(mdl), rentalPrice(price), carType(type) {}
};

// Comparator function for sorting cars by rentalID
bool compareCars(const Car& a, const Car& b) {
    return a.rentalID < b.rentalID;
}

// Function to perform Jump Search on a sorted array of cars by rentalID
int jumpSearch(Car cars[], int n, int rentalID) {
    int step = sqrt(n);
    int prev = 0;

    // Finding the block where the element is present (if it is present)
    while (prev < n && cars[min(step, n) - 1].rentalID < rentalID) {
        prev = step;
        step += sqrt(n);
        if (prev >= n) {
            return -1;
        }
    }

    // Performing a linear search within the block
    for (int i = prev; i < min(step, n); i++) {
        if (cars[i].rentalID == rentalID) {
            return i;
        }
    }

    return -1;
}

// Function to display a car's details
void displayCar(const Car& car) {
    cout << "\nRental ID: " << car.rentalID << endl;
    cout << "Brand: " << car.make << endl;
    cout << "Model: " << car.model << endl;
    cout << "Rental Price: RM " << car.rentalPrice << endl;
    cout << "Type: " << car.carType << endl; // Display car type
}

// Function to display the list of cars
void displayCars(Car cars[], int n) {
    cout << "\n****************************************\n";
    cout << "\tWelcome to MMU UWU CAR\n";
    cout << "****************************************\n";
    cout << "Available Cars:\n";
    for (int i = 0; i < n; ++i) {
        cout << "\nRental ID: " << cars[i].rentalID 
             << "\nBrand: " << cars[i].make 
             << "\nModel: " << cars[i].model 
             << "\nRental Price: RM " << cars[i].rentalPrice 
             << "\nType: " << cars[i].carType << endl; // Display car type
    }
}

// Function to input cars into the system
void inputCars(Car cars[], int& n) {
    int count;
    cout << "\n****************************************\n";
    cout << "\tWelcome to MMU UWU CAR\n";
    cout << "****************************************\n";
    cout << "Enter the number of cars to add: ";
    cin >> count;

    for (int i = 0; i < count; i++) {
        int id;
        string make, model, type;
        double price;
        cout << "Enter details for car " << (n + 1) << ":" << endl;
        cout << "\nRental ID: ";
        cin >> id;
        cout << "Brand: ";
        cin >> make;
        cout << "Model: ";
        cin >> model;
        cout << "Rental Price: RM ";
        cin >> price;
        cout << "Type (e.g., SUV, Sedan): "; // Prompt for car type
        cin >> type;
        cars[n++] = Car(id, make, model, price, type);
    }

    // Sorting cars by rentalID to ensure it is suitable for Jump Search
    sort(cars, cars + n, compareCars);
}

// Main menu to demonstrate the car rental system
void menu() {
    const int MAX_CARS = 100;
    Car cars[MAX_CARS] = {
        Car(101, "Toyota", "Camry", 450.00, "Sedan"),
        Car(102, "Honda", "Accord", 400.00, "Sedan"),
        Car(103, "Ford", "Mustang", 750.00, "Coupe"),
        Car(104, "Tesla", "Model S", 1200.00, "Sedan"),
        Car(105, "Chevrolet", "Camaro", 1000.00, "Coupe")
    };
    int n = 5;  // Initial number of cars

    bool exit = false;

    while (!exit) {
        int choice;
        cout << "\n****************************************\n";
        cout << "\tWelcome to MMU UWU CAR\n";
        cout << "****************************************\n";
        cout << "1. Display available cars\n";
        cout << "2. Add new cars\n";
        cout << "3. Search for a car by rental ID\n";
        cout << "4. Exit\n";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayCars(cars, n);
                break;
            case 2: 
                inputCars(cars, n);
                break;
            case 3: {
                int rentalID;
                cout << "\n****************************************\n";
                cout << "\tWelcome to MMU UWU CAR\n";
                cout << "****************************************\n";
                cout << "Enter the rental ID to search: ";
                cin >> rentalID;

                int index = jumpSearch(cars, n, rentalID);

                if (index != -1) {
                    cout << "\nCar found:";
                    displayCar(cars[index]);
                } else {
                    cout << "\nCar with rental ID " << rentalID << " not found." << endl;
                }
                break;
            }
            case 4:
                exit = true;
                cout << "\nThank you for using our system. Have a nice day!" << endl;
                continue;
            default:
                cout << "\nInvalid choice. Please try again." << endl;
        }
    }
}

//Main menu for Car Rental System
int main() {
    menu();
    return 0;
}
