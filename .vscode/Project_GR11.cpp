#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>
#include <queue>
#include <unistd.h>
#include <Windows.h>

using namespace std;

void MainPage();
void homepage();
void UserHomepage();
void rantalcarmenu();
void customerinput(int rentalID) ;

void loading() 
{
    cout << "Loading";
    for (int i = 0; i < 3; i++) 
	{
        cout << ".";
        usleep(250000); // Sleep for 0.5 seconds (500000 microseconds)
    }
    cout << endl;
}

struct User 
{
    string username;
    string password;
};

class receipt 
{
	
	public:
	    void generateGrandReceipt(const string& carsDetails, string name, string contact, int day, int month, int year) 
		{
	        ofstream outputFile("grand_receipt.txt", ios::app);
	        if (outputFile.is_open()) 
			{
				system("cls");
            	loading();
            	system("cls");
	            outputFile << "\n>>>> RECEIPT <<<<" << endl;
	            outputFile << "User Name: " << name << endl;
	            outputFile << "User Contact: " << contact << endl;
	            outputFile << "Date of rental: " << day << "/" << month << "/" << year << endl;
	            outputFile << "============================================================================================================" << endl;
	            outputFile << "\t\t\tCars Details" << endl;
	            outputFile << "============================================================================================================" << endl;
	            outputFile << left << setw(15) << "Rental ID" << setw(15) << "Brand" << setw(15) << "Model" << setw(15) << "Rental Price" << endl;
	            outputFile << "---------------------------------------------" << endl;
	
	            // Parse carsDetails and format as table
	            istringstream iss(carsDetails);
	            string rentalID, brand, model, rentalPrice;
	            while (iss >> rentalID >> brand >> model >> rentalPrice) 
				{
	                outputFile << left << " |" << setw(15) << rentalID << setw(15) << brand << setw(15) << model << setw(15) << rentalPrice << endl;
	            }
	
	            outputFile << endl;
	            outputFile.close();
	        } 
			else 
			{
	            cout << "Failed to open the file for saving." << endl;
	        }
	    }
	
	    void generateReceipt(const string& carsDetails, string name, string contact, int day, int month, int year) 
		{
	        ofstream outputFile("receipt.txt");
	        if (outputFile.is_open()) 
			{
	            outputFile << "\n>>>> RECEIPT <<<<" << endl;
	            outputFile << "Customer Name: " << name << endl;
	            outputFile << "Customer Contact: " << contact << endl;
	            outputFile << "Date of rental: " << day << "/" << month << "/" << year << endl;
	            outputFile << "===========================================================================" << endl;
	            outputFile << "\t\t\tCars Details" << endl;
	            outputFile << "===========================================================================" << endl;
	            outputFile << left << setw(15) << "Rental ID" << setw(15) << "Brand" << setw(15) << "Model" << setw(15) << "Rental Price" << endl;
	            outputFile << "---------------------------------------------------------------------------" << endl;
	
	            // Parse carsDetails and format as table
	            istringstream iss(carsDetails);
	            string rentalID, brand, model, rentalPrice;
	            while (iss >> rentalID >> brand >> model >> rentalPrice) 
				{
	                outputFile << left << " |" << setw(15) << rentalID << setw(15) << brand << setw(15) << model << setw(15) << rentalPrice << endl;
	            }
	
	            outputFile << endl;
	            outputFile.close();
	        } 
			else 
			{
	            cout << "Failed to open the file for saving." << endl;
	        }
	    }
	
	    void displayReceipt() 
		{
	        ifstream receipt("receipt.txt");
	        if (!receipt) 
			{
	            cout << "Failed to print receipt." << endl;
	            return;
	        }
	
	        string line;
	        while (getline(receipt, line)) 
			{
	            cout << line << endl;
	        }
	
	        receipt.close();
	    }
};

queue<User> users;
const string filename = "users.txt";

void LoadUsers() 
{
    ifstream file(filename.c_str());  // Use c_str() to convert string to const char*
    if (file.is_open()) 
	{
        User user;
        while (file >> user.username >> user.password) 
		{
            users.push(user);
        }
        file.close();
    }
}

void SaveUser(const User& user) 
{
    ofstream file(filename.c_str(), ios::app);  // Use c_str() to convert string to const char*
    if (file.is_open()) 
	{
        file << user.username << " " << user.password << endl;
        file.close();
    }
}

void Register() 
{
    User newUser;
    cout << "\n****************************************\n";
    cout << "\tUser Register\n";
    cout << "****************************************\n";
	cout << "\nEnter username: ";
    cin >> newUser.username;
    fflush(stdin);
    cout << "\nEnter password: ";
    cin >> newUser.password;

    // Save to file and queue
    users.push(newUser);
    SaveUser(newUser);

    cout << "\nRegistration successful!" << endl;
}

void Login() 
{
    if (users.empty()) 
	{
        cout << "\nNo users registered. Please register first." << endl;
        return;
    }

    string username, password;
    cout << "\n****************************************\n";
    cout << "\tUser Login\n";
    cout << "****************************************\n";
	cout << "\nEnter username: ";
    cin >> username;
    fflush(stdin);
    cout << "\nEnter password: ";
    cin >> password;

    queue<User> tempQueue = users;
    bool loggedIn = false;
    while (!tempQueue.empty()) 
	{
        User currentUser = tempQueue.front();
        tempQueue.pop();
        if (currentUser.username == username && currentUser.password == password) 
		{
            cout << "\nLogin successful!" << endl;
            loggedIn = true;
            system("cls");
            loading();
            system("cls");
            UserHomepage();
            break;
        }
    }

    if (!loggedIn) 
	{
        cout << "\nInvalid username or password." << endl;
    }
}

void UserMenu() 
{
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

        switch (choice) 
		{
            case 1:
            	system("cls");
            	loading();
            	system("cls");
                Register();
                break;
            case 2:
            	system("cls");
            	loading();
            	system("cls");
                Login();
                break;
            case 0:
            	system("cls");
            	loading();
            	system("cls");
                MainPage();
                break;
            default:
                cout << "\nInvalid choice. Please try again." << endl;
        }
    } while (choice != 0);
}

struct Admin 
{
    string username;
    string password;
};

queue<Admin> admins;
const string adminsFilename = "admins.txt";  // Unique filename for admins

void LoadAdmins() 
{
    ifstream file(adminsFilename.c_str());
    if (file.is_open()) 
	{
        Admin admin;
        while (file >> admin.username >> admin.password) 
		{
            admins.push(admin);
        }
        file.close();
    }
}

void AdminLogin() 
{
    if (admins.empty()) 
	{
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
    while (!tempQueue.empty()) 
	{
        Admin currentAdmin = tempQueue.front();
        tempQueue.pop();
        if (currentAdmin.username == username && currentAdmin.password == password) 
		{
            cout << "\nAdmin login successful!" << endl;
            loggedIn = true;
            system("cls");
            loading();
            system("cls");
            homepage();
            break;
        }
    }

    if (!loggedIn) 
	{
        cout << "\nInvalid admin username or password." << endl;
    }
}

void AdminMenu() 
{
    int choice;
    do {
        cout << "\n****************************************\n";
        cout << "\tWelcome to MMU UWU CAR\n";
        cout << "****************************************\n";
        cout << "1. Login"; 
        cout << "\n0. Back";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) 
		{
            case 1:
				system("cls");
            	loading();
            	system("cls");
                AdminLogin();
                break;
            case 0:
            	system("cls");
            	loading();
            	system("cls");
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
    string getName() const { return make; }
    float getPrice() const { return rentalPrice; }
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
        cout << ""<< endl;
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

bool validateRentalID(const std::vector<Car>& cars, int id) 
{
    for (size_t i = 0; i < cars.size(); ++i) 
	{
        if (cars[i].rentalID == id) 
		{
            return false;
        }
    }
    return true;
}

// Function to input cars into the system
void inputCars(const string& filename) 
{
    vector<Car> cars = readCarsFromFile(filename); // Read the existing cars
    int count;
    cout << "\n****************************************\n";
    cout << "\tWelcome to MMU UWU CAR\n";
    cout << "****************************************\n";
    cout << "Enter the number of cars to add: ";
    cin >> count;

    for (int i = 0; i < count; i++) 
	{
        int id;
        string make, model, type;
        double price;

        // Validate rental ID
        while (true) 
		{
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
void deleteCar(vector<Car>& cars, int rentalID) 
{
    bool found = false;
    for (size_t i = 0; i < cars.size(); ++i) 
	{
        if (cars[i].getRentalID() == rentalID) 
		{
            cars.erase(cars.begin() + i); 

            
           ofstream outfile("cars.txt");
			for (size_t i = 0; i < cars.size(); ++i) 
			{
		    	outfile << cars[i].rentalID << " " << cars[i].make << " " << cars[i].model << " " << cars[i].rentalPrice << " " << cars[i].carType << endl;
			}
			outfile.close();
			
			found = true;
		    cout << "\nCar with Rental ID " << rentalID << " has been deleted.\n";
		    break;
        }
    }
    if (!found) 
	{
        cout << "\nCar with Rental ID " << rentalID << " not found.\n";
    }
}

void deleteCarMenu(vector<Car>& cars) 
{
    int rentalID;
    displayCars(cars);
    cout << "Enter Rental ID of the car to delete: ";
    cin >> rentalID;

    deleteCar(cars, rentalID); 
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


// Function to sort the array using Selection Sort based on rentalPrice
void selectionSortByPrice(vector<Car>& arr) 
{
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) 
	{
        int minIndex = i;
        for (int j = i + 1; j < n; j++) 
		{
            if (arr[j].rentalPrice < arr[minIndex].rentalPrice) 
			{
                minIndex = j;
            }
        }
        if (minIndex != i) 
		{
            swap(arr[i], arr[minIndex]);
        }
    }
}

// Function to sort cars by rental price using Selection Sort
void sortCarsByPrice(vector<Car>& cars) 
{
    selectionSortByPrice(cars);
    cout << "\nCars sorted by rental price:\n";
    displayCars(cars);
}

// Function to sort the array using Selection Sort based on car make
void selectionSortByName(vector<Car>& arr) 
{
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) 
	{
        int minIndex = i;
        for (int j = i + 1; j < n; j++) 
		{
            if (arr[j].make < arr[minIndex].make) 
			{
                minIndex = j;
            }
        }
        if (minIndex != i) 
		{
            swap(arr[i], arr[minIndex]);
        }
    }
}

// Function to sort cars by name using Selection Sort
void sortCarsByName(vector<Car>& cars) 
{
    selectionSortByName(cars);
    cout << "\nCars sorted by name:\n";
    displayCars(cars);
}

// Function to sort the array using Selection Sort based on rentalID
void selectionSortByID(vector<Car>& arr) 
{
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) 
	{
        int minIndex = i;
        for (int j = i + 1; j < n; j++) 
		{
            if (arr[j].rentalID < arr[minIndex].rentalID)
			{
                minIndex = j;
            }
        }
        if (minIndex != i) 
		{
            swap(arr[i], arr[minIndex]);
        }
    }
}

// Function to sort cars by rental ID using Selection Sort
void sortCarsByID(vector<Car>& cars) 
{
    selectionSortByID(cars);
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
    cout << "\n1. Sort cars by ID";
    cout << "\n2. Sort cars by Car Brand";
    cout << "\n3. Sort cars by Car Price";
    cout << "\n0. Back to Menu";
    cout << "\n\nEnter your choice: ";
    cin >> choice;

    switch(choice) 
	{
        case 1:
        	system("cls");
            loading();
            system("cls");
            sortCarsByID(cars);
            break;
        case 2:
        	system("cls");
            loading();
            system("cls");
            sortCarsByName(cars);
            break;
        case 3:
        	system("cls");
            loading();
            system("cls");
            sortCarsByPrice(cars);
            break;
        case 0:
            rantalcarmenu();
            return; // Return instead of recursive call
        default:
            cout << "Invalid choice" << endl;
            cycleSortMenu(); // Allow retry for invalid choice
            return;
    }

    cout << "Enter Rental ID to choose: ";
    int rentalID;
    cin >> rentalID;

    cout << "Do you want to rent car ID[" << rentalID << "]? [Y/N]: ";
    char c;
    cin >> c;

    if (c == 'Y' || c == 'y') 
	{
        customerinput(rentalID);  // Pass rentalID to customerinput function
    } 
	else 
	{
        rantalcarmenu();
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
        cout << "\n0. Back";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) 
		{
            case 1:
            	system("cls");
            	loading();
            	system("cls");
                displayCars(cars);
                break;
            case 2:
            	system("cls");
            	loading();
            	system("cls");
                inputCars(filename);
                cars = readCarsFromFile(filename); // Update the vector after adding new cars
                break;
            case 3:
            	system("cls");
            	loading();
            	system("cls");
              deleteCarMenu(cars);
            	break;
            case 0:
            	system("cls");
            	loading();
            	system("cls");
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
    vector<string> rentalHistoryDetails;

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

        switch (choice) 
		{
            case 1:
            	system("cls");
            	loading();
            	system("cls");
                displayCars(cars);
                break;
            case 2:
            	system("cls");
            	loading();
            	system("cls");
            	rantalcarmenu();
            case 0:
            	system("cls");
            	loading();
            	system("cls");
                UserMenu();
                break;
            default:
                cout << "\nInvalid choice. Please try again.\n";
        }
    }

}

bool isDateValid(int day, int month, int year) 
{
    // Get the current date
    time_t currentTime = time(0);
    struct tm* localTime = localtime(&currentTime);
    int currentYear = localTime->tm_year + 1900;
    int currentMonth = localTime->tm_mon + 1;
    int currentDay = localTime->tm_mday;

    // Check if the entered date is in the future
    if (year < currentYear || (year == currentYear && month < currentMonth) ||
        (year == currentYear && month == currentMonth && day <= currentDay)) 
	{
        return false;
    }

    // Check if the entered date is valid
    bool leapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    int daysInMonth[] = { 31, 28 + leapYear, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (month < 1 || month > 12 || day < 1 || day > daysInMonth[month - 1]) 
	{
        return false;
    }

return true;
}

void customerinput(int rentalID) 
{
    string name;
    string contact;
    int day, month, year;

    receipt rp;  // Assuming you have a receipt class or structure
	system("cls");
    loading();
    system("cls");
    cout << "==================================" << endl;
    cout << "User Details" << endl;
    cout << "==================================" << endl;
    cin.ignore();
    cout << "Enter your name: ";
    getline(cin, name);
    cout << "Enter your contact number: ";
    cin >> contact;
    bool validDate = false;
    cout << "Date of rental" << endl;
    cout << "==================================" << endl;
    do 
	{
		fflush(stdin);
        cout << "Enter the day: ";
        cin >> day;
        cout << "Enter the month: ";
        cin >> month;
        cout << "Enter the year: ";
        cin >> year;

        if (!isDateValid(day, month, year)) 
		{
            cout << "Invalid date! Please enter a future date." << endl;
        } 
		else 
		{
            validDate = true;
        }
    } while (!validDate);

    cout << "Date entered: " << day << "/" << month << "/" << year << endl;

    ifstream inputFile("cars.txt");
    if (inputFile.is_open()) 
	{
        ofstream rentedFile("rented_cars.txt", ios::app);  // Open the file in append mode

        if (rentedFile.is_open()) 
		{
            ofstream tempFile("temp_cars.txt");

            if (tempFile.is_open()) 
			{
                string line;
                bool found = false;

                while (getline(inputFile, line)) 
				{
                    stringstream ss(line);
                    int currentRentalID;
                    ss >> currentRentalID;

                    // Check if the rental ID matches
                    if (currentRentalID == rentalID) 
					{
                        found = true;
                        rp.generateGrandReceipt(line, name, contact, day, month, year);
                        rp.generateReceipt(line, name, contact, day, month, year);
                        rentedFile << line << " " << day << "/" << month << "/" << setw(4) << year << endl; // Save the car details to "rented_cars.txt"
                        rp.displayReceipt();
                        cout << "Receipt generated" << endl;
                    } 
					else 
					{
                        tempFile << line << endl;  // Write the car details to the temporary file
                    }
                }

                inputFile.close();
                tempFile.close();

                if (!found) 
				{
                    cout << endl;
                    cout << "Car with rental ID " << rentalID << " was not found." << endl;
                    cout << "Failed to generate receipt" << endl;
                } 
				else 
				{
                    // Remove the original "cars.txt" file
                    remove("cars.txt");

                    // Rename the temporary file to replace the original "cars.txt" file
                    if (rename("temp_cars.txt", "cars.txt") != 0) 
					{
                        cout << "Failed to update the car details." << endl;
                    }
                }
            } 
			else 
			{
                cout << "Failed to open the temporary file." << endl;
            }
        } 
		else 
		{
            cout << "Failed to open the \"rented_cars.txt\" file." << endl;
        }
    } 
	else 
	{
        cout << "Failed to open the input file." << endl;
    }
}

void rentalcar() 
{
    string filename = "cars.txt";
    vector<Car> cars = readCarsFromFile(filename); 
    char c;
    string carType;
    int rentalID;
    bool carFound = false;
    bool validCarType = false;

    // Display car type options
    cout << "-------------------------------" << endl;
    cout << "1. SUV" << endl;
    cout << "2. Sedan" << endl;
    cout << "-------------------------------" << endl;

    // Prompt for car type with validation
    while (!validCarType) 
	{
        cout << "Enter Car Type to search [SUV or Sedan]: ";
        cin >> carType;

        if (carType == "SUV" || carType == "Sedan") 
		{
            validCarType = true;
        } 
		else 
		{
            cout << "\nInvalid car type. Please enter either 'SUV' or 'Sedan'.\n";
        }
    }

    // Filter cars by type
    vector<Car> filteredCars;
    for (int i = 0; i < cars.size(); ++i) 
	{
        if (cars[i].carType == carType) 
		{
            filteredCars.push_back(cars[i]);
        }
    }

    if (filteredCars.empty()) 
	{
        cout << "\nNo cars found with type " << carType << ".\n";
    } 
	else 
	{
        // Display filtered cars (optional step)
        cout << "\nCars found with type " << carType << ":\n";
        for (int i = 0; i < filteredCars.size(); ++i) 
		{
            displayCar(filteredCars[i]);
        }

        // Prompt for rental ID
        while (true) 
		{
            cout << "Enter Rental ID to choose: ";
            cin >> rentalID;

            // Ensure cars are sorted by ID
            manualSort(filteredCars, compareByID);

            // Search by rental ID after filtering by type
            int index = metaBinarySearch(filteredCars, rentalID);
            if (index != -1) 
			{
                cout << "\nCar found:\n";
                displayCar(filteredCars[index]);
                carFound = true;
                break; 
            } 
			else
			{
                cout << "\nCar with Rental ID " << rentalID << " not found for type " << carType << ". Please try again.\n";
            }
        }
    }

    if (!carFound) 
	{
        cout << "\nCar with Rental ID " << rentalID << " not found for type " << carType << ".\n";
    } 
	else 
	{
        cout << "Do you want to rent car ID[" << rentalID << "]? [Y/N]: ";
        cin >> c;

        if (c == 'Y' || c == 'y') 
		{
            customerinput(rentalID);  // Pass rentalID to customerinput function
        } 
		else 
		{
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
        cout << "\n2. Sort rental cars: ";
        cout << "\n0. Back to Menu";
        cout << "\n\nEnter your choice: ";
        cin >> choice;
        
        switch (choice) 
		{
            case 1: 
			{ 
				system("cls");
            	loading();
            	system("cls");
				rentalcar();
                break;
            }
            case 2: 
			{
				system("cls");
            	loading();
            	system("cls");
			    cycleSortMenu(); 
			    break;
			}
            case 0:
            {
            	system("cls");
            	loading();
            	system("cls");
            	UserHomepage();
                break;
			}
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
    do 
	{
        cout << "\n****************************************\n";
        cout << "\tWelcome to MMU UWU CAR\n";
        cout << "****************************************\n";
        cout << "1. User";
        cout << "\n2. Admin";
        cout << "\n0. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) 
		{
            case 1:
            	system("cls");
            	loading();
            	system("cls");
                UserMenu();
                break;
            case 2:
            	system("cls");
            	loading();
            	system("cls");
                AdminMenu();
                break;
            case 0:
            	cout << "\n>_< Thank you using our system. See you soon! >_<" << endl;
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