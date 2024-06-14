#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

void homepage();
void menu();

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

// Function to display a car's details
void displayCar(const Car& car) {
    cout << left << "| " << setw(10) << car.rentalID 
         << left << "| " << setw(15) << car.make 
         << left << "| " << setw(15) << car.model 
         << left << "| " << setw(15) << fixed << setprecision(2) << car.rentalPrice 
         << left << "| " << setw(15) << car.carType<< " |" << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
}

// Function to read cars from a text file
vector<Car> readCarsFromFile(const string& filename) {
    vector<Car> cars;
    ifstream infile(filename.c_str());
    int id;
    string make, model, type;
    double price;

    while (infile >> id >> make >> model >> price >> type) {
        cars.push_back(Car(id, make, model, price, type));
    }

    return cars;
}

// Function to write a car to a text file
void writeCarToFile(const string& filename, const Car& car) {
    ofstream outfile(filename.c_str(), ios::app);
    outfile << car.rentalID << " " << car.make << " " << car.model << " " << car.rentalPrice << " " << car.carType << endl;
}

// Function to display the list of cars
void displayCars(const vector<Car>& cars) {
    cout << "\n****************************************\n";
    cout << "\tWelcome to MMU UWU CAR\n";
    cout << "****************************************\n";
    cout << "Available Cars:\n";

    // Display table header
    cout << "==================================================================================" << endl;
    cout << left << "| " << setw(10) << "Rental ID" 
         << left << "| " << setw(15) << "Brand" 
         << left << "| " << setw(15) << "Model" 
         << left << "| " << setw(15) << "Rental Price" 
         << left << "|  " << setw(15) << "Type" << "|";
    cout << "\n==================================================================================" << endl;

    // Display each car's details in a row
    for (size_t i = 0; i < cars.size(); i++) {
        displayCar(cars[i]);
    }
}

bool validateRentalID(const vector<Car>& cars, int id) {
    for (size_t i = 0; i < cars.size(); ++i) {
        if (cars[i].rentalID == id) {
            return false;
        }
    }
    return true;
}


// Function to input cars into the system
void inputCars(const string& filename) {
    vector<Car> cars = readCarsFromFile(filename); // Read the existing cars
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

        // Validate rental ID
        while (true) {
            cout << "Enter details for car " << (i + 1) << ":" << endl;
            cout << "\nRental ID: ";
            cin >> id;

            if (cin.fail()) {
                cin.clear(); // clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
                cout << "Invalid input. Please enter a valid integer for Rental ID.\n";
                continue;
            }

            if (validateRentalID(cars, id)) {
                break;
            } else {
                cout << "Rental ID already exists. Please enter a unique Rental ID.\n";
            }
        }

        cout << "Brand: ";
        cin >> make;
        cout << "Model: ";
        cin >> model;
        cout << "Rental Price: RM ";
        cin >> price;
        cout << "Type (e.g., SUV, Sedan): ";
        cin >> type;

        Car newCar(id, make, model, price, type);
        cars.push_back(newCar);
        writeCarToFile(filename, newCar);
    }
}


// Function sort the array using Cycle sort based on rentalPrice
void cycleSort(vector<Car>& arr) {
    int n = arr.size();
    int writes = 0;

    for (int cycle_start = 0; cycle_start <= n - 2; cycle_start++) {
        Car item = arr[cycle_start];
        int pos = cycle_start;
        for (int i = cycle_start + 1; i < n; i++)
            if (arr[i].rentalPrice < item.rentalPrice)
                pos++;

        if (pos == cycle_start)
            continue;

        while (item.rentalPrice == arr[pos].rentalPrice)
            pos += 1;

        if (pos != cycle_start) {
            swap(item, arr[pos]);
            writes++;
        }

        while (pos != cycle_start) {
            pos = cycle_start;
            for (int i = cycle_start + 1; i < n; i++)
                if (arr[i].rentalPrice < item.rentalPrice)
                    pos += 1;

            while (item.rentalPrice == arr[pos].rentalPrice)
                pos += 1;

            if (item.rentalPrice != arr[pos].rentalPrice) {
                swap(item, arr[pos]);
                writes++;
            }
        }
    }
}

// Function to sort cars by rental price using Cycle Sort
void sortCarsByPrice(vector<Car>& cars) {
    cycleSort(cars);
    cout << "\nCars sorted by rental price:\n";
    displayCars(cars);
}

// Function sort the array using Cycle sort based on car make
void cycleSortByName(vector<Car>& arr) {
    int n = arr.size();
    int writes = 0;

    for (int cycle_start = 0; cycle_start <= n - 2; cycle_start++) {
        Car item = arr[cycle_start];
        int pos = cycle_start;
        for (int i = cycle_start + 1; i < n; i++)
            if (arr[i].make < item.make)
                pos++;

        if (pos == cycle_start)
            continue;

        while (item.make == arr[pos].make)
            pos += 1;

        if (pos != cycle_start) {
            swap(item, arr[pos]);
            writes++;
        }

        while (pos != cycle_start) {
            pos = cycle_start;
            for (int i = cycle_start + 1; i < n; i++)
                if (arr[i].make < item.make)
                    pos += 1;

            while (item.make == arr[pos].make)
                pos += 1;

            if (item.make != arr[pos].make) {
                swap(item, arr[pos]);
                writes++;
            }
        }
    }
}

// Function to sort cars by name using Cycle Sort
void sortCarsByName(vector<Car>& cars) {
    cycleSortByName(cars);
    cout << "\nCars sorted by name:\n";
    displayCars(cars);
}

void cycleSortByID(vector<Car>& arr) {
    int n = arr.size();
    int writes = 0;

    for (int cycle_start = 0; cycle_start <= n - 2; cycle_start++) {
        Car item = arr[cycle_start];
        int pos = cycle_start;

        for (int i = cycle_start + 1; i < n; i++)
            if (arr[i].rentalID < item.rentalID)
                pos++;

        if (pos == cycle_start)
            continue;

        while (item.rentalID == arr[pos].rentalID)
            pos++;

        if (pos != cycle_start) {
            swap(item, arr[pos]);
            writes++;
        }

        while (pos != cycle_start) {
            pos = cycle_start;

            for (int i = cycle_start + 1; i < n; i++)
                if (arr[i].rentalID < item.rentalID)
                    pos++;

            while (item.rentalID == arr[pos].rentalID)
                pos++;

            if (item.rentalID != arr[pos].rentalID) {
                swap(item, arr[pos]);
                writes++;
            }
        }
    }
}

// Function to sort cars by rental ID using Cycle Sort
void sortCarsByID(vector<Car>& cars) {
    cycleSortByID(cars);
    cout << "\nCars sorted by rental ID:\n";
    displayCars(cars);
}

void cycleSortMenu()
{
	int choice;
	vector<Car> cars = readCarsFromFile("cars.txt");
		
	cout << "\n****************************************\n";
    cout << "\tWelcome to MMU UWU CAR\n";
    cout << "****************************************\n";
	cout << "\n1. Sort car by ID";
    cout << "\n2. Sort car by Car Brand";
    cout << "\n3. Sort car by Car Price";
    cout << "\n0. Back to Menu";
    cout << "\n\nEnter your choice: ";
    cin >> choice;
    
    switch(choice)
    {
    	case 1:
    		sortCarsByID(cars);
        	break;
	    case 2:
	        sortCarsByName(cars);
	        break;
	    case 3:
	    	sortCarsByPrice(cars);
	    	break;
	    case 0:
	    	menu();
	    	break;
	    default:
	    	cout<<"Invalid choice"<<endl;
	}
	
	cycleSortMenu();
    
}

// Function to perform Counting Sort on an array of cars by rentalID
void countingSort(vector<Car>& cars) {
    if (cars.empty()) return;

    // Find the maximum rentalID in the array
    int maxElement = cars[0].rentalID;
    for (size_t i = 1; i < cars.size(); i++) {
        if (cars[i].rentalID > maxElement) {
            maxElement = cars[i].rentalID;
        }
    }

    // Create a count array to store the count of each unique rentalID
    vector<int> count(maxElement + 1, 0);

    // Store the count of each rentalID
    for (size_t i = 0; i < cars.size(); i++) {
        count[cars[i].rentalID]++;
    }

    // Modify the count array by adding the previous counts
    for (size_t i = 1; i < count.size(); i++) {
        count[i] += count[i - 1];
    }

    // Create an output array to store the sorted cars
    vector<Car> output(cars.size());

    // Build the output array
    for (int i = cars.size() - 1; i >= 0; i--) {
        output[count[cars[i].rentalID] - 1] = cars[i];
        count[cars[i].rentalID]--;
    }

    // Copy the sorted cars back to the original array
    cars = output;
}

// Function to sort cars by rental ID using Counting Sort
void sortCarsByIDCountingSort(vector<Car>& cars) 
{
    countingSort(cars);
    cout << "\nCars sorted by rental ID (Counting Sort):\n";
    displayCars(cars);
}

void countingSortByBrand(vector<Car>& cars) {
    if (cars.empty()) return;

    // Find the maximum ASCII value of the first character in the brand
    int maxElement = cars[0].make[0];
    for (size_t i = 1; i < cars.size(); i++) {
        if (cars[i].make[0] > maxElement) {
            maxElement = cars[i].make[0];
        }
    }

    // Create a count array to store the count of each unique character
    vector<int> count(maxElement + 1, 0);

    // Store the count of each brand's first character
    for (size_t i = 0; i < cars.size(); i++) {
        count[cars[i].make[0]]++;
    }

    // Modify the count array by adding the previous counts
    for (size_t i = 1; i < count.size(); i++) {
        count[i] += count[i - 1];
    }

    // Create an output array to store the sorted cars
    vector<Car> output(cars.size());

    // Build the output array
    for (int i = cars.size() - 1; i >= 0; i--) {
        output[count[cars[i].make[0]] - 1] = cars[i];
        count[cars[i].make[0]]--;
    }

    // Copy the sorted cars back to the original array
    cars = output;
}

void sortCarsByBrandCountingSort(vector<Car>& cars) {
    countingSortByBrand(cars);
    cout << "\nCars sorted by brand (Counting Sort):\n";
    displayCars(cars);
}


void countingSortByPrice(vector<Car>& cars) {
    if (cars.empty()) return;

    int scale = 100; // assuming prices have two decimal places
    int maxElement = cars[0].rentalPrice * scale;
    for (size_t i = 1; i < cars.size(); i++) {
        if (cars[i].rentalPrice * scale > maxElement) {
            maxElement = cars[i].rentalPrice * scale;
        }
    }

    // Create a count array to store the count of each scaled price
    vector<int> count(maxElement + 1, 0);

    // Store the count of each scaled price
    for (size_t i = 0; i < cars.size(); i++) {
        count[int(cars[i].rentalPrice * scale)]++;
    }

    // Modify the count array by adding the previous counts
    for (size_t i = 1; i < count.size(); i++) {
        count[i] += count[i - 1];
    }

    // Create an output array to store the sorted cars
    vector<Car> output(cars.size());

    // Build the output array
    for (int i = cars.size() - 1; i >= 0; i--) {
        output[count[int(cars[i].rentalPrice * scale)] - 1] = cars[i];
        count[int(cars[i].rentalPrice * scale)]--;
    }

    // Copy the sorted cars back to the original array
    cars = output;
}

void sortCarsByPriceCountingSort(vector<Car>& cars) {
    countingSortByPrice(cars);
    cout << "\nCars sorted by rental price (Counting Sort):\n";
    displayCars(cars);
}


void countingSortMenu()
{
	int choice;
	vector<Car> cars = readCarsFromFile("cars.txt");
	
	cout << "\n****************************************\n";
    cout << "\tWelcome to MMU UWU CAR\n";
    cout << "****************************************\n";
	cout << "\n1. Sort car by ID";
    cout << "\n2. Sort car by Car Brand";
    cout << "\n3. Sort car by Car Price";
    cout << "\n0. Back to Menu";
    cout << "\n\nEnter your choice: ";
    cin >> choice;
    
    switch(choice)
    {
    	case 1:
    		sortCarsByIDCountingSort(cars);
        	break;
	    case 2:
	    	sortCarsByBrandCountingSort(cars);
    		break;
		case 3:
    		sortCarsByPriceCountingSort(cars);
    		break;
	    case 0:
	    	menu();
	    	break;
	    default:
	    	cout<<"Invalid choice"<<endl;
	}
	
	countingSortMenu();
}

// Custom comparison functions
bool compareByID(const Car& a, const Car& b) {
    return a.rentalID < b.rentalID;
}

bool compareByType(const Car& a, const Car& b) {
    return a.carType < b.carType;
}

bool compareByBrand(const Car& a, const Car& b) {
    return a.make < b.make;
}

// Function to perform Meta Binary Search on a sorted array of cars by rentalID
int metaBinarySearch(const vector<Car>& cars, int rentalID) {
    int n = cars.size();
    int lg = log2(n - 1) + 1;
    int pos = 0;

    for (int i = lg; i >= 0; --i) {
        if (cars[pos].rentalID == rentalID) {
            return pos;
        }

        int new_pos = pos | (1 << i);
        if (new_pos < n && cars[new_pos].rentalID <= rentalID) {
            pos = new_pos;
        }
    }

    if (cars[pos].rentalID == rentalID) {
        return pos;
    }
    return -1;
}

// Manual sorting function based on comparator
void manualSort(vector<Car>& cars, bool (*compare)(const Car&, const Car&)) {
    for (size_t i = 0; i < cars.size() - 1; ++i) {
        for (size_t j = 0; j < cars.size() - i - 1; ++j) {
            if (!compare(cars[j], cars[j + 1])) {
                swap(cars[j], cars[j + 1]);
            }
        }
    }
}

// Search by car type using Meta Binary Search
void searchByType(vector<Car>& cars, const string& type) {
    manualSort(cars, compareByType);
    bool found = false; // Flag to track if any car of the given type is found

    cout << "\nCars found with type " << type << ":\n";
    for (size_t i = 0; i < cars.size(); i++) {
        if (cars[i].carType == type) {
            int index = metaBinarySearch(cars, cars[i].rentalID);
            if (index != -1) {
                displayCar(cars[index]);
                found = true; // Set flag to true if at least one car is found
            }
        }
    }

    if (!found) {
        cout << "\nNo cars with type " << type << " found.\n";
    }
}

// Search by car brand using Meta Binary Search
void searchByBrand(vector<Car>& cars, const string& brand) {
    manualSort(cars, compareByBrand);
    bool found = false; // Flag to track if any car of the given brand is found

    cout << "\nCars found with brand " << brand << ":\n";
    for (size_t i = 0; i < cars.size(); i++) {
        if (cars[i].make == brand) {
            int index = metaBinarySearch(cars, cars[i].rentalID);
            if (index != -1) {
                displayCar(cars[index]);
                found = true; // Set flag to true if at least one car is found
            }
        }
    }

    if (!found) {
        cout << "\nNo cars with brand " << brand << " found.\n";
    }
}

// Meta Binary Search Menu
void searchMetaBinaryMenu() {
    string filename = "cars.txt";
    vector<Car> cars = readCarsFromFile(filename);
    
    int choice;
    
    while (true) 
	{
        cout << "\n****************************************\n";
    	cout << "\tWelcome to MMU UWU CAR\n";
    	cout << "****************************************\n";
		cout << "\n1. Search car by ID";
        cout << "\n2. Search car by Car type";
        cout << "\n3. Search car by Car Brand";
        cout << "\n0. Back to Menu";
        cout << "\n\nEnter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: {
                int rentalID;
                cout << "Enter Rental ID to search: ";
                cin >> rentalID;
                manualSort(cars, compareByID); // Ensure cars are sorted by ID
                int index = metaBinarySearch(cars, rentalID);
                if (index != -1) {
                    cout << "\nCar found:\n";
                    displayCar(cars[index]);
                } else {
                    cout << "\nCar with Rental ID " << rentalID << " not found.\n";
                }
                break;
            }
            case 2: {
                 string carType;
                cout << "Enter Car Type to search: ";
                cin >> carType;
                searchByType(cars, carType);
                break;
            }
            case 3: {
               string carBrand;
                cout << "Enter Car Brand to search: ";
                cin >> carBrand;
                searchByBrand(cars, carBrand);
                break;
            }
            case 0:
            	menu();
                break;
            default:
                cout << "\nInvalid choice. Please try again.\n";
        }
        
        searchMetaBinaryMenu();
    }
}

// Function to perform Jump Search on a sorted array of cars by rentalID
int jumpSearch(vector<Car>& cars, int rentalID) {
    int n = cars.size();
    int step = sqrt(n);
    int prev = 0;

    while (prev < n && cars[min(step, n) - 1].rentalID < rentalID) {
        prev = step;
        step += sqrt(n);
        if (prev >= n) {
            return -1;
        }
    }

    for (int i = prev; i < min(step, n); i++) {
        if (cars[i].rentalID == rentalID) {
            return i;
        }
    }

    return -1;
}

void searchJumpMenu() {
	string filename = "cars.txt";
    vector<Car> cars = readCarsFromFile(filename);
    
    int choice;
    
    while (true) 
	{
        cout << "\n****************************************\n";
    	cout << "\tWelcome to MMU UWU CAR\n";
    	cout << "****************************************\n";
		cout << "\n1. Search car by ID";
        cout << "\n2. Search car by Car type";
        cout << "\n3. Search car by Car Brand";
        cout << "\n0. Back to Menu";
        cout << "\n\nEnter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: {
                int rentalID;
                cout << "Enter Rental ID to search: ";
                cin >> rentalID;
                manualSort(cars, compareByID); // Ensure cars are sorted by ID
                int index = jumpSearch(cars, rentalID);
                if (index != -1) {
                    cout << "\nCar found:\n";
                    displayCar(cars[index]);
                } else {
                    cout << "\nCar with Rental ID " << rentalID << " not found.\n";
                }
                break;
            }
            case 2: {
                 string carType;
                cout << "Enter Car Type to search: ";
                cin >> carType;
                searchByType(cars, carType);
                break;
            }
            case 3: {
               string carBrand;
                cout << "Enter Car Brand to search: ";
                cin >> carBrand;
                searchByBrand(cars, carBrand);
                break;
            }
            case 0:
            	menu();
                break;
            default:
                cout << "\nInvalid choice. Please try again.\n";
        }
    }
}

void menu()
{
	int choice;
	vector<Car> cars = readCarsFromFile("cars.txt");
	
	cout << "\n****************************************\n";
    cout << "\tWelcome to MMU UWU CAR\n";
    cout << "****************************************\n";
    cout << "\n1. Cycle Sort";
    cout << "\n2. Counting Sort";
    cout << "\n3. Meta Binary Search";
    cout << "\n4. Jump Search";
    cout << "\n0. Back to homepage";
    cout << "\nEnter your choice: ";
    cin >> choice;
   	
	switch(choice)
	{
		case 1:
    		cycleSortMenu();
        	break;
	    case 2:
	        countingSortMenu();
	        break;
	    case 3:
	    	searchMetaBinaryMenu();
	        break;
	    case 4:
	        searchJumpMenu();
	        break;
		case 0:
	        homepage();
	} 
		
}

void homepage()
{
	string filename = "cars.txt";
    vector<Car> cars = readCarsFromFile(filename);

    int choice;
    while (true) 
	{
		cout << "\n****************************************\n";
    	cout << "\tWelcome to MMU UWU CAR\n";
    	cout << "****************************************\n";
        cout << "\n1. Display Cars";
        cout << "\n2. Add New Cars";
        cout << "\n3. Assignment";
        cout << "\n0. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayCars(cars);
                break;
            case 2:
                inputCars(filename);
                cars = readCarsFromFile(filename); // Update the vector after adding new cars
                break;
            case 3:
            	menu();
            case 0:
                exit(0);
                break;
            default:
                cout << "\nInvalid choice. Please try again.\n";
        }
    }

}

int main() 
{
  homepage();
}
