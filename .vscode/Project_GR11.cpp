#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include<ctime>
#include<queue>
using namespace std;

void MainPage();
void homepage();
void UserHomepage();
void menu();
void rantalcarmenu();
void customerinput() ;

struct User {
    string username;
    string password;
};

class receipt{
	public:
	    void generateGrandReceipt(const string& houseDetails, string name, int contact, int day, int month, int year) {
	        ofstream outputFile("grand_receipt.txt", ios::app);
	        if (outputFile.is_open()) {
	            outputFile << ">>>> RECEIPT <<<<" << endl;
	            outputFile << "Customer Name: " << name << endl;
	            outputFile << "Customer Contact: " << contact << endl;
	            outputFile << "Date of rental: " << day << "/" << month << "/" << year << endl;
	            outputFile << "==================================" << endl;
	            outputFile << "House Details" << std::endl;
	            outputFile << "==================================" << endl;
	            outputFile << left << setw(25) << "House Number" << setw(25) << "House Type" << setw(45) << "House Address" << setw(25) << "Number of Room" << setw(25) << "House Location" << setw(25) << "Price per Night" << endl;
	            outputFile << "----------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	            outputFile << houseDetails << endl;
	            outputFile << "----------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	            outputFile << endl;
	            outputFile.close();
	        } else {
	            cout << "Failed to open the file for saving." << endl;
	        }
	    }
	
	    void generateReceipt(const string& houseDetails, string name, int contact, int day, int month, int year) {
	        ofstream outputFile("receipt.txt");
	        if (outputFile.is_open()) {
	            outputFile << ">>>> RECEIPT <<<<" << endl;
	            outputFile << "Customer Name: " << name << endl;
	            outputFile << "Customer Contact: " << contact << endl;
	            outputFile << "Date of rental: " << day << "/" << month << "/" << year << endl;
	            outputFile << "==================================" << endl;
	            outputFile << "House Details" << endl;
	            outputFile << "==================================" << endl;
	            outputFile << left << setw(25) << "House Number" << setw(25) << "House Type" << setw(45) << "House Address" << setw(25) << "Number of Room" << setw(25) << "House Location" << setw(25) << "Price per Night" << endl;
	            outputFile << "----------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	            outputFile << houseDetails << endl;
	            outputFile << "----------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	            outputFile << endl;
	            outputFile.close();
	        } else {
	            cout << "Failed to open the file for saving." << endl;
	        }
	    }
	
	    void displayReceipt() {
	        ifstream receipt("receipt.txt");
	        if (!receipt) {
	            cout << "Failed to print receipt." << endl;
	        }
	
	        string line;
	        while (getline(receipt, line)) {
	            cout << line << endl;
	        }
	
	        receipt.close();
			}
};

queue<User> users;
const string filename = "users.txt";

void LoadUsers() {
    ifstream file(filename.c_str());  // Use c_str() to convert string to const char*
    if (file.is_open()) {
        User user;
        while (file >> user.username >> user.password) {
            users.push(user);
        }
        file.close();
    }
}

void SaveUser(const User& user) {
    ofstream file(filename.c_str(), ios::app);  // Use c_str() to convert string to const char*
    if (file.is_open()) {
        file << user.username << " " << user.password << endl;
        file.close();
    }
}

void Register() {
    User newUser;
    cout << "\n****************************************\n";
    cout << "\tUser Register\n";
    cout << "****************************************\n";
	cout << "\nEnter username: ";
    cin >> newUser.username;
    cout << "\nEnter password: ";
    cin >> newUser.password;

    // Save to file and queue
    users.push(newUser);
    SaveUser(newUser);

    cout << "\nRegistration successful!" << endl;
}

void Login() {
    if (users.empty()) {
        cout << "\nNo users registered. Please register first." << endl;
        return;
    }

    string username, password;
    cout << "\n****************************************\n";
    cout << "\tUser Login\n";
    cout << "****************************************\n";
	cout << "\nEnter username: ";
    cin >> username;
    cout << "\nEnter password: ";
    cin >> password;

    queue<User> tempQueue = users;
    bool loggedIn = false;
    while (!tempQueue.empty()) {
        User currentUser = tempQueue.front();
        tempQueue.pop();
        if (currentUser.username == username && currentUser.password == password) {
            cout << "\nLogin successful!" << endl;
            loggedIn = true;
            UserHomepage();
            break;
        }
    }

    if (!loggedIn) {
        cout << "\nInvalid username or password." << endl;
    }
}

void UserMenu() {
    int choice;
    do {
        cout << "\n****************************************\n";
        cout << "\tWelcome to MMU UWU CAR\n";
        cout << "****************************************\n";
        cout << "\n1. Register";
        cout << "\n2. Login";
        cout << "\n0. Back";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                Register();
                break;
            case 2:
                Login();
                break;
            case 0:
                MainPage();
                break;
            default:
                cout << "\nInvalid choice. Please try again." << endl;
        }
    } while (choice != 0);
}

struct Admin {
    string username;
    string password;
};

queue<Admin> admins;
const string adminsFilename = "admins.txt";  // Unique filename for admins

void LoadAdmins() {
    ifstream file(adminsFilename.c_str());
    if (file.is_open()) {
        Admin admin;
        while (file >> admin.username >> admin.password) {
            admins.push(admin);
        }
        file.close();
    }
}

void AdminLogin() {
    if (admins.empty()) {
        cout << "\nNo admins registered." << endl;
        return;
    }

    string username, password;
    cout << "\n****************************************\n";
    cout << "\tAdmin Login\n";
    cout << "****************************************\n";
    cout << "\nEnter admin username: ";
    cin >> username;
    cout << "\nEnter admin password: ";
    cin >> password;

    queue<Admin> tempQueue = admins;
    bool loggedIn = false;
    while (!tempQueue.empty()) {
        Admin currentAdmin = tempQueue.front();
        tempQueue.pop();
        if (currentAdmin.username == username && currentAdmin.password == password) {
            cout << "\nAdmin login successful!" << endl;
            loggedIn = true;
            homepage();
            break;
        }
    }

    if (!loggedIn) {
        cout << "\nInvalid admin username or password." << endl;
    }
}

void AdminMenu() {
    int choice;
    do {
        cout << "\n****************************************\n";
        cout << "\tWelcome to MMU UWU CAR\n";
        cout << "****************************************\n";
        cout << "\n1. Login"; 
        cout << "\n0. Back";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                AdminLogin();
                break;
            case 0:
                MainPage();
                break;
            default:
                cout << "\nInvalid choice. Please try again." << endl;
        }
    } while (choice != 0);
}

class Car 
{
	public:
	    int rentalID;
	    string make;
	    string model;
	    double rentalPrice;
	    string carType;
	    string carBrand;
	
	    Car() : rentalID(0), make(""), model(""), rentalPrice(0.0), carType("") {}
	
	    Car(int id, string mk, string mdl, double price, string type) 
	        : rentalID(id), make(mk), model(mdl), rentalPrice(price), carType(type) {}
	    
	// Accessor methods
    int getRentalID() const { return rentalID; }
    string getMake() const { return make; }
    string getModel() const { return model; }
    double getRentalPrice() const { return rentalPrice; }
    string getCarType() const { return carType; }
};

// Comparator function for sorting cars by rentalID
bool compareCars(const Car& a, const Car& b) 
{
    return a.rentalID < b.rentalID;
}

// Function to display a car's details
void displayCar(const Car& car) 
{
    cout << left << "| " << setw(10) << car.rentalID 
         << left << "| " << setw(15) << car.make 
         << left << "| " << setw(15) << car.model 
         << left << "| " << setw(15) << fixed << setprecision(2) << car.rentalPrice 
         << left << "| " << setw(15) << car.carType<< " |" << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
}

// Function to read cars from a text file
vector<Car> readCarsFromFile(const string& filename) 
{
    vector<Car> cars;
    ifstream infile(filename.c_str());
    string line;

    while (getline(infile, line)) 
    {
        stringstream ss(line);
        int id;
        string make, model, type;
        double price;

        if (ss >> id >> make >> model >> price >> type) 
        {
            cars.push_back(Car(id, make, model, price, type));
        } 
        else 
        {
            cout << "Error reading line: " << line << endl; 
        }
    }

    
    if (infile.eof()) 
    {
        cout << "Reached end of file." << endl;
    } 
    else if (infile.fail()) 
    {
        cout << "File reading error!" << endl;
    }

    return cars;
}

// Function to write a car to a text file
void writeCarToFile(const string& filename, const Car& car) 
{
    ofstream outfile(filename.c_str(), ios::app);
    outfile << car.rentalID << " " << car.make << " " << car.model << " " << car.rentalPrice << " " << car.carType << endl;
}

// Function to display the list of cars
void displayCars(const vector<Car>& cars) 
{
    cout << "\n****************************************\n";
    cout << "\tCar Lists\n";
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
    for (size_t i = 0; i < cars.size(); i++) 
	{
        displayCar(cars[i]);
    }
}

bool validateRentalID(const std::vector<Car>& cars, int id) {
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

            if(cin.fail()) 
			{
                cin.clear(); // clear the error flag
                cout << "Invalid input. Please enter a valid integer for Rental ID.\n";
                continue;
            }

            if (validateRentalID(cars, id)) 
			{
                break;
            } 
			else {
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
void deleteCar(vector<Car>& cars, int rentalID) {
    bool found = false;
    for (size_t i = 0; i < cars.size(); ++i) {
        if (cars[i].getRentalID() == rentalID) {
            cars.erase(cars.begin() + i); 

            
           ofstream outfile("cars.txt");
for (size_t i = 0; i < cars.size(); ++i) {
    outfile << cars[i].rentalID << " " << cars[i].make << " " << cars[i].model << " " << cars[i].rentalPrice << " " << cars[i].carType << endl;
}
outfile.close();

            found = true;
            cout << "\nCar with Rental ID " << rentalID << " has been deleted.\n";
            break;
        }
    }
    if (!found) {
        cout << "\nCar with Rental ID " << rentalID << " not found.\n";
    }
}

void deleteCarMenu(vector<Car>& cars) {
    int rentalID;
    cout << "Enter Rental ID of the car to delete: ";
    cin >> rentalID;

    deleteCar(cars, rentalID); 
}


// Function sort the array using Cycle sort based on rentalPrice
void cycleSort(vector<Car>& arr) 
{
    int n = arr.size();
    int writes = 0;

    for (int cycle_start = 0; cycle_start <= n - 2; cycle_start++) 
	{
        Car item = arr[cycle_start];
        int pos = cycle_start;
        for (int i = cycle_start + 1; i < n; i++)
            if (arr[i].rentalPrice < item.rentalPrice)
                pos++;

        if (pos == cycle_start)
            continue;

        while (item.rentalPrice == arr[pos].rentalPrice)
            pos += 1;

        if (pos != cycle_start) 
		{
            swap(item, arr[pos]);
            writes++;
        }

        while (pos != cycle_start) 
		{
            pos = cycle_start;
            for (int i = cycle_start + 1; i < n; i++)
                if (arr[i].rentalPrice < item.rentalPrice)
                    pos += 1;

            while (item.rentalPrice == arr[pos].rentalPrice)
                pos += 1;

            if (item.rentalPrice != arr[pos].rentalPrice) 
			{
                swap(item, arr[pos]);
                writes++;
            }
        }
    }
}

// Function to sort cars by rental price using Cycle Sort
void sortCarsByPrice(vector<Car>& cars) 
{
    cycleSort(cars);
    cout << "\nCars sorted by rental price:\n";
    displayCars(cars);
}

// Function sort the array using Cycle sort based on car make
void cycleSortByName(vector<Car>& arr) 
{
    int n = arr.size();
    int writes = 0;

    for (int cycle_start = 0; cycle_start <= n - 2; cycle_start++) 
	{
        Car item = arr[cycle_start];
        int pos = cycle_start;
        for (int i = cycle_start + 1; i < n; i++)
            if (arr[i].make < item.make)
                pos++;

        if (pos == cycle_start)
            continue;

        while (item.make == arr[pos].make)
            pos += 1;

        if (pos != cycle_start) 
		{
            swap(item, arr[pos]);
            writes++;
        }

        while (pos != cycle_start) 
		{
            pos = cycle_start;
            for (int i = cycle_start + 1; i < n; i++)
                if (arr[i].make < item.make)
                    pos += 1;

            while (item.make == arr[pos].make)
                pos += 1;

            if (item.make != arr[pos].make) 
			{
                swap(item, arr[pos]);
                writes++;
            }
        }
    }
}

// Function to sort cars by name using Cycle Sort
void sortCarsByName(vector<Car>& cars) 
{
    cycleSortByName(cars);
    cout << "\nCars sorted by name:\n";
    displayCars(cars);
}

void cycleSortByID(vector<Car>& arr) 
{
    int n = arr.size();
    int writes = 0;

    for (int cycle_start = 0; cycle_start <= n - 2; cycle_start++) 
	{
        Car item = arr[cycle_start];
        int pos = cycle_start;

        for (int i = cycle_start + 1; i < n; i++)
            if (arr[i].rentalID < item.rentalID)
                pos++;

        if (pos == cycle_start)
            continue;

        while (item.rentalID == arr[pos].rentalID)
            pos++;

        if (pos != cycle_start) 
		{
            swap(item, arr[pos]);
            writes++;
        }

        while (pos != cycle_start) 
		{
            pos = cycle_start;

            for (int i = cycle_start + 1; i < n; i++)
                if (arr[i].rentalID < item.rentalID)
                    pos++;

            while (item.rentalID == arr[pos].rentalID)
                pos++;

            if (item.rentalID != arr[pos].rentalID) 
			{
                swap(item, arr[pos]);
                writes++;
            }
        }
    }
}

// Function to sort cars by rental ID using Cycle Sort
void sortCarsByID(vector<Car>& cars) 
{
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
void countingSort(vector<Car>& cars) 
{
    if (cars.empty()) return;

    // Find the maximum rentalID in the array
    int maxElement = cars[0].rentalID;
    for (size_t i = 1; i < cars.size(); i++) 
	{
        if (cars[i].rentalID > maxElement) 
		{
            maxElement = cars[i].rentalID;
        }
    }

    // Create a count array to store the count of each unique rentalID
    vector<int> count(maxElement + 1, 0);

    // Store the count of each rentalID
    for (size_t i = 0; i < cars.size(); i++) 
	{
        count[cars[i].rentalID]++;
    }

    // Modify the count array by adding the previous counts
    for (size_t i = 1; i < count.size(); i++) 
	{
        count[i] += count[i - 1];
    }

    // Create an output array to store the sorted cars
    vector<Car> output(cars.size());

    // Build the output array
    for (int i = cars.size() - 1; i >= 0; i--) 
	{
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

void countingSortByBrand(vector<Car>& cars) 
{
    if (cars.empty()) return;

    // Find the maximum ASCII value of the first character in the brand
    int maxElement = cars[0].make[0];
    for (size_t i = 1; i < cars.size(); i++) 
	{
        if (cars[i].make[0] > maxElement) 
		{
            maxElement = cars[i].make[0];
        }
    }

    // Create a count array to store the count of each unique character
    vector<int> count(maxElement + 1, 0);

    // Store the count of each brand's first character
    for (size_t i = 0; i < cars.size(); i++) 
	{
        count[cars[i].make[0]]++;
    }

    // Modify the count array by adding the previous counts
    for (size_t i = 1; i < count.size(); i++) 
	{
        count[i] += count[i - 1];
    }

    // Create an output array to store the sorted cars
    vector<Car> output(cars.size());

    // Build the output array
    for (int i = cars.size() - 1; i >= 0; i--) 
	{
        output[count[cars[i].make[0]] - 1] = cars[i];
        count[cars[i].make[0]]--;
    }

    // Copy the sorted cars back to the original array
    cars = output;
}

void sortCarsByBrandCountingSort(vector<Car>& cars) 
{
    countingSortByBrand(cars);
    cout << "\nCars sorted by brand (Counting Sort):\n";
    displayCars(cars);
}


void countingSortByPrice(vector<Car>& cars) 
{
    if (cars.empty()) return;

    int scale = 100; // assuming prices have two decimal places
    int maxElement = cars[0].rentalPrice * scale;
    for (size_t i = 1; i < cars.size(); i++) 
	{
        if (cars[i].rentalPrice * scale > maxElement) 
		{
            maxElement = cars[i].rentalPrice * scale;
        }
    }

    // Create a count array to store the count of each scaled price
    vector<int> count(maxElement + 1, 0);

    // Store the count of each scaled price
    for (size_t i = 0; i < cars.size(); i++) 
	{
        count[int(cars[i].rentalPrice * scale)]++;
    }

    // Modify the count array by adding the previous counts
    for (size_t i = 1; i < count.size(); i++) 
	{
        count[i] += count[i - 1];
    }

    // Create an output array to store the sorted cars
    vector<Car> output(cars.size());

    // Build the output array
    for (int i = cars.size() - 1; i >= 0; i--) 
	{
        output[count[int(cars[i].rentalPrice * scale)] - 1] = cars[i];
        count[int(cars[i].rentalPrice * scale)]--;
    }

    // Copy the sorted cars back to the original array
    cars = output;
}

void sortCarsByPriceCountingSort(vector<Car>& cars) 
{
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
bool compareByID(const Car& a, const Car& b) 
{
    return a.rentalID < b.rentalID;
}

bool compareByType(const Car& a, const Car& b) 
{
    return a.carType < b.carType;
}

bool compareByBrand(const Car& a, const Car& b) 
{
    return a.make < b.make;
}

// Function to perform Meta Binary Search on a sorted array of cars by rentalID
int metaBinarySearch(const vector<Car>& cars, int rentalID) 
{
    int n = cars.size();
    int lg = log2(n - 1) + 1;
    int pos = 0;

    for (int i = lg; i >= 0; --i) 
	{
        if (cars[pos].rentalID == rentalID) 
		{
            return pos;
        }

        int new_pos = pos | (1 << i);
        if (new_pos < n && cars[new_pos].rentalID <= rentalID) 
		{
            pos = new_pos;
        }
    }

    if (cars[pos].rentalID == rentalID) 
	{
        return pos;
    }
    return -1;
}

// Manual sorting function based on comparator
void manualSort(vector<Car>& cars, bool (*compare)(const Car&, const Car&)) 
{
    for (size_t i = 0; i < cars.size() - 1; ++i) 
	{
        for (size_t j = 0; j < cars.size() - i - 1; ++j) 
		{
            if (!compare(cars[j], cars[j + 1])) 
			{
                swap(cars[j], cars[j + 1]);
            }
        }
    }
}

// Search by car type using Meta Binary Search
void searchByType(vector<Car>& cars, const string& type) 
{
    manualSort(cars, compareByType);
    bool found = false; // Flag to track if any car of the given type is found

    cout << "\nCars found with type " << type << ":\n";
    for (size_t i = 0; i < cars.size(); i++) 
	{
        if (cars[i].carType == type) 
		{
            int index = metaBinarySearch(cars, cars[i].rentalID);
            if (index != -1) 
			{
                displayCar(cars[index]);
                found = true; // Set flag to true if at least one car is found
            }
        }
    }

    if (!found) 
	{
        cout << "\nNo cars with type " << type << " found.\n";
    }
}

// Search by car brand using Meta Binary Search
void searchByBrand(vector<Car>& cars, const string& brand) 
{
    manualSort(cars, compareByBrand);
    bool found = false; // Flag to track if any car of the given brand is found

    cout << "\nCars found with brand " << brand << ":\n";
    for (size_t i = 0; i < cars.size(); i++) 
	{
        if (cars[i].make == brand) 
		{
            int index = metaBinarySearch(cars, cars[i].rentalID);
            if (index != -1) 
			{
                displayCar(cars[index]);
                found = true; // Set flag to true if at least one car is found
            }
        }
    }

    if (!found) 
	{
        cout << "\nNo cars with brand " << brand << " found.\n";
    }
}

// Meta Binary Search Menu
void searchMetaBinaryMenu()
{
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
        
        switch (choice) 
		{
            case 1: 
			{
                int rentalID;
                cout << "Enter Rental ID to search: ";
                cin >> rentalID;
                manualSort(cars, compareByID); // Ensure cars are sorted by ID
                int index = metaBinarySearch(cars, rentalID);
                if (index != -1) 
				{
                    cout << "\nCar found:\n";
                    displayCar(cars[index]);
                } 
				else 
				{
                    cout << "\nCar with Rental ID " << rentalID << " not found.\n";
                }
                break;
            }
            case 2: 
			{
                string carType;
                cout << "Enter Car Type to search: ";
                cin >> carType;
                searchByType(cars, carType);
                break;
            }
            case 3: 
			{
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
int jumpSearch(vector<Car>& cars, int rentalID) 
{
    int n = cars.size();
    int step = sqrt(n);
    int prev = 0;

    while (prev < n && cars[min(step, n) - 1].rentalID < rentalID) 
	{
        prev = step;
        step += sqrt(n);
        if (prev >= n) 
		{
            return -1;
        }
    }

    for (int i = prev; i < min(step, n); i++) 
	{
        if (cars[i].rentalID == rentalID) 
		{
            return i;
        }
    }

    return -1;
}

void searchJumpMenu() 
{
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
        
        switch (choice) 
		{
            case 1: 
			{
                int rentalID;
                cout << "Enter Rental ID to search: ";
                cin >> rentalID;
                manualSort(cars, compareByID); // Ensure cars are sorted by ID
                int index = jumpSearch(cars, rentalID);
                if (index != -1) 
				{
                    cout << "\nCar found:\n";
                    displayCar(cars[index]);
                } 
				else 
				{
                    cout << "\nCar with Rental ID " << rentalID << " not found.\n";
                }
                break;
            }
            case 2: 
			{
                string carType;
                cout << "Enter Car Type to search: ";
                cin >> carType;
                searchByType(cars, carType);
                break;
            }
            case 3: 
			{
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
    cout << "\n0. Back";
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
    	cout << "\tAdmin Panel\n";
    	cout << "****************************************\n";
        cout << "\n1. Display Cars";
        cout << "\n2. Add New Cars";
        cout << "\n3. Delete Cars";
        cout << "\n4. Assignment";
        cout << "\n0. Back";
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
            	
              deleteCarMenu(cars);
            	break;
            case 4:
            	menu();
            case 0:
                MainPage();
                break;
            default:
                cout << "\nInvalid choice. Please try again.\n";
        }
    }

}

void UserHomepage()
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
        cout << "\n2. Rental Cars";
        cout << "\n0. Back";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayCars(cars);
                break;
            case 2:
            	rantalcarmenu();
            case 0:
                UserMenu();
                break;
            default:
                cout << "\nInvalid choice. Please try again.\n";
        }
    }

}

bool isDateValid(int day, int month, int year) {
    // Get the current date
    time_t currentTime = time(0);
    struct tm* localTime = localtime(&currentTime);
    int currentYear = localTime->tm_year + 1900;
    int currentMonth = localTime->tm_mon + 1;
    int currentDay = localTime->tm_mday;

    // Check if the entered date is in the future
    if (year < currentYear || (year == currentYear && month < currentMonth) ||
        (year == currentYear && month == currentMonth && day <= currentDay)) {
        return false;
    }

    // Check if the entered date is valid
    bool leapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    int daysInMonth[] = { 31, 28 + leapYear, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (month < 1 || month > 12 || day < 1 || day > daysInMonth[month - 1]) {
        return false;
    }

return true;
}

void customerinput(int rentalID) {
    string name;
    int contact;
    int day, month, year;

    receipt rp;  // Assuming you have a receipt class or structure

    cout << "==================================" << endl;
    cout << "Customer Details" << endl;
    cout << "==================================" << endl;
    cin.ignore();
    cout << "Enter your name: ";
    getline(cin, name);
    cout << "Enter your contact number: ";
    cin >> contact;
    bool validDate = false;
    cout << "Date of rental" << endl;
    cout << "==================================" << endl;
    do {
        cout << "Enter the day: ";
        cin >> day;
        cout << "Enter the month: ";
        cin >> month;
        cout << "Enter the year: ";
        cin >> year;

        if (!isDateValid(day, month, year)) {
            cout << "Invalid date! Please enter a future date." << endl;
        } else {
            validDate = true;
        }
    } while (!validDate);

    cout << "Date entered: " << day << "/" << month << "/" << year << endl;

    ifstream inputFile("cars.txt");
    if (inputFile.is_open()) {
        ofstream rentedFile("rented_cars.txt", ios::app);  // Open the file in append mode

        if (rentedFile.is_open()) {
            ofstream tempFile("temp_cars.txt");

            if (tempFile.is_open()) {
                string line;
                bool found = false;

                while (getline(inputFile, line)) {
                    stringstream ss(line);
                    int currentRentalID;
                    ss >> currentRentalID;

                    // Check if the rental ID matches
                    if (currentRentalID == rentalID) {
                        found = true;
                        rp.generateGrandReceipt(line, name, contact, day, month, year);
                        rp.generateReceipt(line, name, contact, day, month, year);
                        rentedFile << line << " " << day << "/" << month << "/" << setw(4) << year << endl; // Save the car details to "rented_cars.txt"
                        rp.displayReceipt();
                        cout << "Receipt generated" << endl;
                    } else {
                        tempFile << line << endl;  // Write the car details to the temporary file
                    }
                }

                inputFile.close();
                tempFile.close();

                if (!found) {
                    cout << endl;
                    cout << "Car with rental ID " << rentalID << " was not found." << endl;
                    cout << "Failed to generate receipt" << endl;
                } else {
                    // Remove the original "cars.txt" file
                    remove("cars.txt");

                    // Rename the temporary file to replace the original "cars.txt" file
                    if (rename("temp_cars.txt", "cars.txt") != 0) {
                        cout << "Failed to update the car details." << endl;
                    }
                }
            } else {
                cout << "Failed to open the temporary file." << endl;
            }
        } else {
            cout << "Failed to open the \"rented_cars.txt\" file." << endl;
        }
    } else {
        cout << "Failed to open the input file." << endl;
    }
}

void rentalcar() {
    string filename = "cars.txt";
    vector<Car> cars = readCarsFromFile(filename); 
    char c;
    string carType;
    int rentalID;
    bool carFound = false;

    cout << "-------------------------------" << endl;
    cout << "1. SUV" << endl;
    cout << "2. Sedan" << endl;
    cout << "-------------------------------" << endl;
    cout << "Enter Car Type to search [e.g SUV]: ";
    cin >> carType;

    // Filter cars by type
    vector<Car> filteredCars;
    for (int i = 0; i < cars.size(); ++i) {
        if (cars[i].carType == carType) {
            filteredCars.push_back(cars[i]);
        }
    }

    if (filteredCars.empty()) {
        cout << "\nNo cars found with type " << carType << ".\n";
    }

    // Display filtered cars (optional step)
    cout << "\nCars found with type " << carType << ":\n";
    for (int i = 0; i < filteredCars.size(); ++i) {
        displayCar(filteredCars[i]);
    }

    // Prompt for rental ID
    while (true) {
        cout << "Enter Rental ID to choose: ";
        cin >> rentalID;

        // Ensure cars are sorted by ID
        manualSort(filteredCars, compareByID);

        // Search by rental ID after filtering by type
        int index = metaBinarySearch(filteredCars, rentalID);
        if (index != -1) {
            cout << "\nCar found:\n";
            displayCar(filteredCars[index]);
            carFound = true;
            break; 
        } else {
            cout << "\nCar with Rental ID " << rentalID << " not found for type " << carType << ". Please try again.\n";
        }
    }

    if (!carFound) {
        cout << "\nCar with Rental ID " << rentalID << " not found for type " << carType << ".\n";
    } else {
        cout << "Do you want to rent car ID[" << rentalID << "]? [Y/N]: ";
        cin >> c;

        if (c == 'Y' || c == 'y') {
            customerinput(rentalID);  // Pass rentalID to customerinput function
        } else {
            rantalcarmenu();
        }
    }
}


void rantalcarmenu()
{
	string filename = "cars.txt";
    vector<Car> cars = readCarsFromFile(filename);

    int choice;
     while (true) 
	{
        cout << "\n****************************************\n";
    	cout << "\tWelcome to MMU UWU CAR\n";
    	cout << "****************************************\n";
		cout << "\n1. Search car by Car type";
        cout << "\n2. Search car by Car Brand";
        cout << "\n0. Back to Menu";
        cout << "\n\nEnter your choice: ";
        cin >> choice;
        switch (choice) 
		{
            case 1: 
			{ 
			  rentalcar();
                break;
            }
            case 2: 
			{
    string carBrand;
    string Brand;
    int rentalID;
    bool carFound = false;
	cout<<"--------------------------------"<<endl;
	cout<<"1.Toyota"<<endl;
	cout<<"2.Nissan"<<endl;
    cout << "-------------------------------" << endl;
    cout << "Enter Car Brand to search [e.g Toyota]: ";
    cin >> carBrand;

    // Filter cars by brand
    vector<Car> filteredCars;
    for (int i = 0; i < cars.size(); ++i) {
        if (cars[i]. carBrand==carBrand ) {
            filteredCars.push_back(cars[i]);
        }
    }

    if (filteredCars.empty()) {
        cout << "\nNo cars found with brand " << Brand << ".\n";
        break;
    }

    // Display filtered s (optional step)
    cout << "\nCars found with brand " << carBrand << ":\n";
    for (int i = 0; i < filteredCars.size(); ++i) {
        displayCar(filteredCars[i]);
    }

    // Prompt for rental ID
    while (true) {
        cout << "Enter Rental ID to choose: ";
        cin >> rentalID;

        // Ensure cars are sorted by ID
        manualSort(filteredCars, compareByID);

        // Search by rental ID after filtering by brand
        int index = metaBinarySearch(filteredCars, rentalID);
        if (index != -1) {
            cout << "\nCar found:\n";
            displayCar(filteredCars[index]);
            carFound = true;
            break; // Exit while loop
        } else {
            cout << "\nCar with Rental ID " << rentalID << " not found for brand " << carBrand << ". Please try again.\n";
        }
    }

    if (!carFound) {
        cout << "\nCar with Rental ID " << rentalID << " not found for brand " << carBrand << ".\n";
    }

    break;
}
            case 0:
            	UserHomepage();
                break;
            default:
                cout << "\nInvalid choice. Please try again.\n";
        }
        
}
}
void MainPage()
{
	LoadUsers();
	LoadAdmins();
	
    int choice;
    do {
        cout << "\n****************************************\n";
        cout << "\tWelcome to MMU UWU CAR\n";
        cout << "****************************************\n";
        cout << "\n1. User";
        cout << "\n2. Admin";
        cout << "\n0. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                UserMenu();
                break;
            case 2:
                AdminMenu();
                break;
            case 0:
                exit(0);
                break;
            default:
                cout << "\nInvalid choice. Please try again." << endl;
        }
    } while (choice != 0);
}


int main() 
{
  	MainPage();
}
