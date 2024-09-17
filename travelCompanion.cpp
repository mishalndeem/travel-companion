#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <conio.h>
using namespace std;

int numTravelers;
class atm
{
private:
    string accountNumber;
    string pin;
    double balance;

public:
    atm(string accNumber, string pinCode, double initialBalance)
    {
        accountNumber = accNumber;
        pin = pinCode;
        balance = initialBalance;
    }
    void refund(double amount)
    {
        if (amount > 0)
        {
            balance += amount;
            cout << "Amount refunded successfully." << endl;
        }
        else
        {
            cout << "Invalid refund amount." << endl;
        }
    }
    void deduct(double amount)
    {
        if (amount > 0 && amount <= balance)
        {
            balance -= amount;
            cout << "Amount deducted successfully." << endl;
        }
        else
        {
            cout << "Invalid or insufficient funds for deduction." << endl;
            cout << "Your payment will be taken at the spot." << endl;
            exit;
        }
    }
    void displayDetails() const
    {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Balance: pkr" << balance << endl;
    }
};
class Traveler
{
public:
    string name;
    int age;
    string gender;

    Traveler(string n, int a, string g) : name(n), age(a), gender(g) {}
};
class Transport
{
public:
    string vehicle;
    float cost;

    Transport(string v, float c) : vehicle(v), cost(c) {}
};

class Hotel
{
public:
    string name;
    float cost;
    float rating;
    string menu;
    string address;

    Hotel(string n, float c, float r, string m, string a) : name(n), cost(c), rating(r), menu(m), address(a) {}
};
class Enjoyment
{
public:
    string name;
    float cost;

    Enjoyment(string n, float c) : name(n), cost(c) {}
};

class TravelPlanner
{
    Traveler *travelers[100];
    int travelerCount;
    float budget;
    // string startDate;
    // string endDate;
    string cityOptions[5] = {"Naran/Kaghan/Shogran", "Swat/Kalam", "Skardu", "Kashmir", "Hunza"};
    Hotel *hotelOptions[5][5];
    Transport *transportOptions[5][3];
    Enjoyment *enjoymentOptions[5][3];
    string selectedCity;
    Hotel *selectedHotel;
    Transport *selectedTransport;
    Enjoyment *selectedEnjoyment;
    float totalExpense;

public:
    TravelPlanner() : travelerCount(0), budget(0.0f), totalExpense(0.0f)
    {
        // Initializing hotel options with name, cost, rating, and menu
        // Address Jawa Building , GPO Chowk , The MALL, Murree //parking,free breakfast,gym
        hotelOptions[0][0] = new Hotel("Swiss Wood Cottages", 19759.0f, 4.8, "Desi Cuisine", "Manshera - Naran - jalkha- chilas Raod, Naran Bazaar, Naran, Mansehra, KPK");
        hotelOptions[0][1] = new Hotel("Rose Valley Hotel Naran", 9825.0f, 4.9, "International Cuisine", "Jheel Saif ul Malook Road, Naran");
        hotelOptions[0][2] = new Hotel("Hotel Silver Oaks Naran", 12649.0f, 4.7, "Asian Cuisine", "Molvi Zardullah Road, Main Bazar Naran, Mansehra, KPK");
        hotelOptions[0][3] = new Hotel("Fairy Meadows Hotel", 19203.0f, 4.7, "Asian Cuisine", "Bazar, Naran, Mansehra, KPK");
        hotelOptions[0][4] = new Hotel("Snow Crest Lodges", 13339.0f, 4.8, "Indian Cuisine", "Snow Crest Lodges,Katha,Naran,Mansehra,KPK 21200");

        hotelOptions[1][0] = new Hotel("Woodridge Cottages", 9344.0f, 4.8, "French Cuisine", "Main Bazar just before the Exit Bridge Mall Road, Kalam");
        hotelOptions[1][1] = new Hotel("Walnut Heights by Roomy", 21600.0f, 4.7, "International Cuisine", "FH8F+2V4, Kalam, Swat, KPK");
        hotelOptions[1][2] = new Hotel("The Nature Resort Hotel Kalam", 5357.0f, 4.9, "Asian Cuisine", "Kalam, Swat, KPK");
        hotelOptions[1][3] = new Hotel("Relax Cottage", 5350.0f, 4.1, "Asian Cuisine", "Utrar Road, Kalam, Swat, KPK");
        hotelOptions[1][4] = new Hotel("Hotel Birmingham Palace", 13339.0f, 4.5, "Asian Cuisine", "Bahrain Rd, Kalam, Swat, KPK");

        hotelOptions[2][0] = new Hotel("Heaven Hotel Skardu", 11499.0f, 4.4, "Desi Cuisine", "Airport Rd Skardu, Astana, Skardu, Gilgit");
        hotelOptions[2][1] = new Hotel("Oasis Resort Katpana Skardu", 17950.0f, 4.8, "International Cuisine", "desert skardu, Oasis Resort, Katpana, Skardu, 16100");
        hotelOptions[2][2] = new Hotel("Baltistan Continental Hotel", 6957.0f, 4.0, "Asian Cuisine", "Alamdar Rd, Hassan Colony, Skardu, Gilgit");
        hotelOptions[2][3] = new Hotel("BYARSA HOTEL", 19896.0f, 4.4, "Desi Cuisine", "Lower Kachura, Shangrila Road, Gulshan Abad, Skardu");
        hotelOptions[2][4] = new Hotel("Ibex Homestay", 4589.0f, 4.5, "Asian Cuisine", "Ali abad, near Alamdar chowk, Hasnain Nagar, Skardu");

        hotelOptions[3][0] = new Hotel("Hotel Kashmir Inn", 6506.0f, 4.0, "Indian Cuisine", "Khayam Chowk, Opposite Khyber Hospital, dal lake Bilal Colony, Srinagar, Jammu and Kashmir");
        hotelOptions[3][1] = new Hotel("Hotel Kashmir Orient", 6730.0f, 4.7, "International Cuisine", "Khona Khan, New Khona Khan Road, Dalgate Bridge, Srinagar, Jammu and Kashmir");
        hotelOptions[3][2] = new Hotel("Hotel Star of Kashmir", 6810.0f, 4.1, "Asian Cuisine", "Airport Rd, Ibrahim Colony, Hyderpora, Srinagar, Jammu and Kashmir");
        hotelOptions[3][3] = new Hotel("Hotel Luxury Inn", 7852.0f, 4.0, "Desi Cuisine", "Hamza Lane 5, near Post office Masjid, Ikhrajpora, Rajbagh, Srinagar, Jammu and Kashmir");
        hotelOptions[3][4] = new Hotel("Hotel Curio's Srinagar", 8329.0f, 4.4, "Asian Cuisine", "Ex-Change Road, Barbar Shah, Srinagar, Jammu and Kashmir");

        hotelOptions[4][0] = new Hotel("Osho Beyaak", 8046.0f, 3.9, "Desi Cuisine", "Main Bazar,Hunza,Gilgit-Baltistan 15700");
        hotelOptions[4][1] = new Hotel("Old Hunza Inn", 4514.0f, 4.3, "International Cuisine", "Hunza, Karimabad, Gilgit-Baltistan 15700");
        hotelOptions[4][2] = new Hotel("Caravanserai Hunza", 6578.0f, 4.6, "Asian Cuisine", "8M83+XP5, Bridge, Chel Ganish Hunza, Ganish, Gilgit");
        hotelOptions[4][3] = new Hotel("LOKAL Rooms x Hunza", 18360.0f, 4.6, "Asian Cuisine", "8M9R+PVJ, Hunza, Hunza Nagar");
        hotelOptions[4][4] = new Hotel("Hard Rock Hunza-High Rock Hunza Resort & Villas", 25500.0f, 4.6, "Desi Cuisine", "Eagles nest view point Duiker Altit Hunza, Hunza Valley");
        //---------------------------------------------------------------------------------------------------------------------------------------------------
        enjoymentOptions[0][0] = new Enjoyment("Hiking", 0.0f);
        enjoymentOptions[0][1] = new Enjoyment("Nature and Wildlife Tours", 1000.0f);
        enjoymentOptions[0][2] = new Enjoyment("Historical Tours", 1200.0f);

        enjoymentOptions[1][0] = new Enjoyment("Chilam Choli Festivals", 0.0f);
        enjoymentOptions[1][1] = new Enjoyment("Unique Cultural Trip", 4000.0f);
        enjoymentOptions[1][2] = new Enjoyment("Sporting Events", 5000.0f);

        enjoymentOptions[2][0] = new Enjoyment("K2 Base Camp Trek", 8000.0f);
        enjoymentOptions[2][1] = new Enjoyment("Trango Adventure", 7200.0f);
        enjoymentOptions[2][2] = new Enjoyment("Upper Kachura Lake", 0.0f);

        enjoymentOptions[3][0] = new Enjoyment("Sight-seeing(Castles/Waterfalls)", 0.0f);
        enjoymentOptions[3][1] = new Enjoyment("Ancient Ruins", 0.0f);
        enjoymentOptions[3][2] = new Enjoyment("Hiking Trails", 0.0f);

        enjoymentOptions[4][0] = new Enjoyment("Karakoram Highway Cycling Tour", 3000.0f);
        enjoymentOptions[4][1] = new Enjoyment("Parasailing", 1500.0f);
        enjoymentOptions[4][2] = new Enjoyment("Paragliding", 1700.0f);

        //-------------------------------------------------------------------------------------------
        transportOptions[0][0] = new Transport("Rental Car", 26410.0f);
        transportOptions[0][1] = new Transport("Bus", 14734.0f);
        transportOptions[0][2] = new Transport("Plane", 63384.0f);

        transportOptions[1][0] = new Transport("Rental Car", 26410.0f);
        transportOptions[1][1] = new Transport("Bus", 6116.0f);
        transportOptions[1][2] = new Transport("Plane", 53000.0f);

        transportOptions[2][0] = new Transport("Rental Car", 18000.0f);
        transportOptions[2][1] = new Transport("Bus", 9200.0f);
        transportOptions[2][2] = new Transport("Plane", 56990.0f);

        transportOptions[3][0] = new Transport("Rental Car", 11120.0f);
        transportOptions[3][1] = new Transport("Bus", 5000.0f);
        transportOptions[3][2] = new Transport("Plane", 83400.0f);

        transportOptions[4][0] = new Transport("Rental Car", 23900.0f);
        transportOptions[4][1] = new Transport("Bus", 7500.0f);
        transportOptions[4][2] = new Transport("Plane", 62828.0f);
    }

    ~TravelPlanner()
    {
        // Clean up allocated hotel objects
        for (int i = 0; i < 5; ++i)
        {
            for (int j = 0; j < 5; j++)
            {
                delete hotelOptions[i][j];
            }
        }
        for (int i = 0; i < 5; ++i)
        {
            for (int j = 0; j < 3; j++)
            {
                // delete hotelOptions[i][j];
                delete enjoymentOptions[i][j];
            }
        }
    }

    void addTraveler(string name, int age, string gender)
    {
        while (gender != "m" && gender != "f" && gender != "F" && gender != "M")
        {
            cout << "Invalid gender. Please enter 'm' or 'f': ";
            cin >> gender;
        }
        travelers[travelerCount++] = new Traveler(name, age, gender);
    }

    void setBudget(float b)
    {
        while (b <= 0)
        {
            cout << "Budget cannot be zero or negative. Please enter a valid budget: ";
            cin >> b;
        }
        budget = b;
    }

    bool validateDateFormat(const string &date)
    {
        regex datePattern("^\\d{4}-\\d{2}-\\d{2}$");
        return regex_match(date, datePattern);
    }

    // Function to get today's date and store it in year, month, day variables
    void getTodaysDate(int &year, int &month, int &day)
    {
        time_t now = time(0);
        tm *ltm = localtime(&now);

        year = 1900 + ltm->tm_year;
        month = 1 + ltm->tm_mon;
        day = ltm->tm_mday;
    }

    // Function to set trip start and end dates
    void setTripDates()
    {
        string startDate, endDate;
        int currentYear, currentMonth, currentDay;

        // Get today's date
        getTodaysDate(currentYear, currentMonth, currentDay);
        cout << "Today's date: " << currentYear << "-" << currentMonth << "-" << currentDay << endl;

        // Validate and set start date
        do
        {
            cout << "Enter start date (YYYY-MM-DD): ";
            cin >> startDate;
            cin.ignore(); // Ignore the '\n' character

            if (!validateDateFormat(startDate))
            {
                cout << "Invalid date format. Please enter a valid date in YYYY-MM-DD format." << endl;
                continue;
            }

            int year, month, day;
            sscanf(startDate.c_str(), "%d-%d-%d", &year, &month, &day);

            if (year < currentYear || (year == currentYear && month < currentMonth) || (year == currentYear && month == currentMonth && day < currentDay))
            {
                cout << "Error: The start date cannot be before today's date." << endl;
                continue;
            }

            break; // Exit loop if start date is valid
        } while (true);

        // Validate and set end date
        do
        {
            cout << "Enter end date (YYYY-MM-DD): ";
            cin >> endDate;
            cin.ignore(); // Ignore the '\n' character

            if (!validateDateFormat(endDate))
            {
                cout << "Invalid date format. Please enter a valid date in YYYY-MM-DD format." << endl;
                continue;
            }

            int startYear, startMonth, startDay;
            sscanf(startDate.c_str(), "%d-%d-%d", &startYear, &startMonth, &startDay);
            int endYear, endMonth, endDay;
            sscanf(endDate.c_str(), "%d-%d-%d", &endYear, &endMonth, &endDay);

            if (endYear < startYear || (endYear == startYear && endMonth < startMonth) || (endYear == startYear && endMonth == startMonth && endDay <= startDay))
            {
                cout << "Error: The end date must be after the start date." << endl;
                continue;
            }

            break; // Exit loop if end date is valid
        } while (true);

        // Proceed with the trip planner functionalities using startDate and endDate
        cout << "Trip dates set successfully:" << endl;
        cout << "Start date: " << startDate << endl;
        cout << "End date: " << endDate << endl;

        // Add other travel planner functionalities here
    }
    // void displayTripDates(){

    //     cout << "Start date: " <<startDate << endl;
    //     cout << "End date: " << endDate << endl;
    // }

    void suggestCities()
    {
        cout << "Cities Options:" << endl;
        cout << "\t1. Naran/Kaghan/Shogran" << endl;
        cout << "\t2. Swat/Kalam" << endl;
        cout << "\t3. Skardu" << endl;
        cout << "\t4. Kashmir" << endl;
        cout << "\t5. Hunza" << endl;
    }

    void chooseCity()
    {
        suggestCities();
        int choice;
        do
        {
            cout << "Enter your choice (1-5) or '0' to exit: ";
            cin >> choice;
            if (choice < 0 || choice > 5)
            {
                cout << "Invalid choice. Please select a valid city option or enter '0' to exit: ";
            }
        } while (choice < 0 || choice > 5);

        if (choice == 0)
        {
            exit;
        }

        selectedCity = cityOptions[choice - 1];
    }

    void chooseHotel()
    {
        cout << "Choose a hotel in " << selectedCity << " from the following options:" << endl;
        int cityIndex = 0;
        for (int i = 0; i < 5; i++)
        {
            if (selectedCity == cityOptions[i])
            {
                cityIndex = i;
                break;
            }
        }

        float avgBudget = budget / numTravelers;
        int suggestedHotelIndex = 0;
        for (int i = 0; i < 5; i++)
        {
            if (hotelOptions[cityIndex][i]->cost <= avgBudget)
            {
                suggestedHotelIndex = i;
            }
        }
        cout << endl;
        for (int i = 0; i < 5; i++)
        {
            cout << "\t" << i + 1 << ". " << hotelOptions[cityIndex][i]->name << "\n\t\t"
                 << " - Price: pkr" << hotelOptions[cityIndex][i]->cost << "\n\t\t"
                 << " - Rating: " << hotelOptions[cityIndex][i]->rating << "\n\t\t"
                 << " - Menu: " << hotelOptions[cityIndex][i]->menu << "\n\t\t" << " - Address: " << hotelOptions[cityIndex][i]->address;
            if (i == suggestedHotelIndex)
            {
                cout << "\n[Hotel " << i + 1 << " Suggested according to your budget]";
            }
            cout << endl;
        }

        int choice;
        do
        {
            cout << "Enter your choice (1-5) or '0' to exit: ";
            cin >> choice;
            if (choice < 0 || choice > 5)
            {
                cout << "Invalid choice. Please select a valid hotel option or enter '0' to exit: ";
            }
        } while (choice < 0 || choice > 5);

        if (choice == 0)
        {
            exit;
        }

        selectedHotel = hotelOptions[cityIndex][choice - 1];

        // Adding hotel cost to total expense and checking budget
        totalExpense += selectedHotel->cost * travelerCount;
        checkBudget();
        cout << "Total expense after choosing hotel: pkr" << totalExpense << endl;
    }

    void chooseTransport()
    {
        cout << endl;
        cout << "Choose a transport option for " << selectedCity << " from the following:" << endl;
        int cityIndex = 0;
        for (int i = 0; i < 5; i++)
        {
            if (selectedCity == cityOptions[i])
            {
                cityIndex = i;
                break;
            }
        }
        // Suggesting a transport option based on budget
        float avgBudget = budget / numTravelers;
        //================================================
        int suggestedTransportIndex = 0;
        for (int i = 0; i < 3; i++)
        {
            if (transportOptions[cityIndex][i]->cost <= avgBudget)
            {
                suggestedTransportIndex = i;
            }
        }

        for (int i = 0; i < 3; i++)
        {
            cout << "\t" << i + 1 << ". " << transportOptions[cityIndex][i]->vehicle << "\n\t\t" << " - Price: pkr" << transportOptions[cityIndex][i]->cost;
            if (i == suggestedTransportIndex)
            {
                cout << "\n[Transport " << i + 1 << " Suggested according to your budget]";
            }
            cout << endl;
        }

        int choice;
        do
        {
            cout << "Enter your choice (1-3) or '0' to exit: ";
            cin >> choice;
            if (choice < 0 || choice > 3)
            {
                cout << "Invalid choice. Please select a valid enjoyment option or enter '0' to exit: ";
            }
        } while (choice < 0 || choice > 3);

        if (choice == 0)
        {
            exit;
        }

        selectedTransport = transportOptions[cityIndex][choice - 1];
        totalExpense += selectedTransport->cost * travelerCount;
        checkBudget();
        cout << "Total expense after choosing transport: pkr" << totalExpense << endl;
    }
    void chooseEnjoyment()
    {
        cout << endl;
        cout << "Choose an activity in " << selectedCity << " from the following options:" << endl;
        int cityIndex = 0;
        for (int i = 0; i < 5; i++)
        {
            if (selectedCity == cityOptions[i])
            {
                cityIndex = i;
                break;
            }
        }
        // Suggesting an enjoyment option based on budget
        float avgBudget = budget / numTravelers;
        int suggestedEnjoymentIndex = 0;
        for (int i = 0; i < 3; i++)
        {
            if (enjoymentOptions[cityIndex][i]->cost <= avgBudget)
            {
                suggestedEnjoymentIndex = i;
            }
        }

        for (int i = 0; i < 3; i++)
        {
            cout << "\t" << i + 1 << ". " << enjoymentOptions[cityIndex][i]->name << "\n\t\t" << " - Price: pkr" << enjoymentOptions[cityIndex][i]->cost;
            if (i == suggestedEnjoymentIndex)
            {
                cout << "\n[Activity " << i + 1 << " Suggested according to your budget]";
            }
            cout << endl;
        }

        int choice;
        do
        {
            cout << "Enter your choice (1-3) or '0' to exit: ";
            cin >> choice;
            if (choice < 0 || choice > 3)
            {
                cout << "Invalid choice. Please select a valid enjoyment option or enter '0' to exit: ";
            }
        } while (choice < 0 || choice > 3);

        if (choice == 0)
        {
            exit;
        }

        selectedEnjoyment = enjoymentOptions[cityIndex][choice - 1];
        totalExpense += selectedEnjoyment->cost * travelerCount;
        checkBudget();
        cout << "Total expense after choosing enjoyment: pkr" << totalExpense << endl;
    }

    void checkBudget()
    {
        if (totalExpense > budget)
        {
            cout << "\nWarning: Your total expenses exceed your budget!" << endl;
        }
    }

    float calculateExpenses()
    {
        float hotelCost;
        if (selectedHotel)
        {
            hotelCost = selectedHotel->cost;
        }
        else
        {
            hotelCost = 0.0f;
        }
        float enjoymentCost;
        if (selectedEnjoyment)
        {
            enjoymentCost = selectedEnjoyment->cost;
        }
        else
        {
            enjoymentCost = 0.0f;
        }
        float transportCost;
        if (selectedTransport)
        {
            transportCost = selectedTransport->cost;
        }
        else
        {
            transportCost = 0.0f;
        }

        cout << "Expenses breakdown:" << endl;
        cout << "Hotel Cost: pkr" << hotelCost << endl;
        cout << "Transport Cost: pkr" << transportCost << endl;
        cout << "Enjoyment Cost: pkr" << enjoymentCost << endl;

        float totalExpense = (hotelCost + transportCost + enjoymentCost) * travelerCount;
        return totalExpense;
    }
    void showSummary()
    {
        system("cls");
        cout << "\n\t\t\t\t\t\t   ________________________________________";
        cout << "\n\t\t\t\t\t\t  |                                        |";
        cout << "\n\t\t\t\t\t\t  |              TRIP SUMMARY              |";
        cout << "\n\t\t\t\t\t\t  |________________________________________|";
        cout << "\n Travelers:" << endl;
        for (int i = 0; i < travelerCount; i++)
        {
            cout << "  Name: " << travelers[i]->name << ", Age: " << travelers[i]->age << ", Gender: " << travelers[i]->gender << endl;
        }
        cout << "\tBudget: pkr" << budget << endl;
        // displayTripDates();
        cout << "\tSelected Hotel: " << selectedHotel->name << " - pkr" << selectedHotel->cost << " per night" << endl;
        cout << "\tSelected Transport: " << selectedTransport->vehicle << " - pkr" << selectedTransport->cost << endl;
        cout << "\tSelected Enjoyment: " << selectedEnjoyment->name << " - pkr" << selectedEnjoyment->cost << endl;
        cout << "\tTotal Expense: pkr" << totalExpense << endl;
    }

    void userInputLoop(TravelPlanner &planner)
    {
        string username, password;
        cout << "Create a username: ";
        cin >> username;
        cout << "Enter the password you want to you use or rewrite the suggested password" << endl;
        const string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%";
        srand(time(0));
        for (int i = 0; i < 6; ++i)
        {
            password += chars[rand() % chars.size()];
        }
        cout << "Suggested password: " << password << endl;
        cout << "Password: ";
        cin >> password;
        cout << "Account created successfully! Please log in." << endl;
        system("cls");
        string enteredUsername, enteredPassword;
        do
        {
            cout << "Username: ";
            cin >> enteredUsername;
            cout << "Password: ";
            cin >> enteredPassword;
            if (enteredUsername != username || enteredPassword != password)
            {
                cout << "Invalid username or password. Please try again." << endl;
            }
        } while (enteredUsername != username || enteredPassword != password);

        cout << "Login successful!" << endl;
        system("cls");

        // Collecting Travel Information
        int travelType;
        cout << "Select travel type:" << endl;
        cout << "1. Solo" << endl;
        cout << "2. Partner" << endl;
        cout << "3. Family" << endl;
        cout << "4. Friends" << endl;
        do
        {
            cout << "Enter your choice (1-4): ";
            cin >> travelType;
            if (travelType < 1 || travelType > 4)
            {
                cout << "Invalid choice. Please select a valid travel type (1-4): ";
            }
        } while (travelType < 1 || travelType > 4);

        // int numTravelers;
        if (travelType == 1)
        {
            numTravelers = 1;
        }
        if (travelType == 2)
        {
            numTravelers = 2;
        }
        else
        {
            cout << "Enter the number of people traveling: ";
            cin >> numTravelers;
        }

        for (int i = 0; i < numTravelers; i++)
        {
            string name, gender;
            int age;
            cout << "Enter name: ";
            cin >> name;
            cout << "Enter age: ";
            cin >> age;
            cout << "Enter gender (m/f): ";
            cin >> gender;
            system("cls");
            planner.addTraveler(name, age, gender);
        }

        float budget;
        cout << "Tell us your budget (Enter amount)\nHigh (pkr100000 or above)\nMedium (pkr60000 - pkr99999)\nLow (pkr59999 or less)\n";
        cin >> budget;
        planner.setBudget(budget);

        // Setting Trip Dates
        planner.setTripDates();

        // Choosing Travel Options
        planner.chooseCity();
        planner.chooseHotel();
        planner.chooseTransport();
        planner.chooseEnjoyment();

        // Calculating and Displaying Total Expenses
        float totalExpense = planner.calculateExpenses();
        cout << "Total expense for the trip: pkr" << totalExpense << endl;
        if (totalExpense > budget)
        {
            cout << "Warning: Your total expenses exceed your budget!" << endl;
        } //------------------------------------------------------------------------------
        planner.showSummary();
        // system("cls");
        cout << "You have successfully planned a trip!Just the payment step is left." << endl;
        // cout << "Congratulations!You are all set for the trip. We hope you enjoyed planning the trip with us as much as we did." << endl;

        cout << "Select a payment method:" << endl;
        int p;
        string accountNumber;
        string pin;
        double initialAmount = 0;
        double deductAmount = totalExpense;
        //double refundAmount = deductAmount;
        cout << "1.Online payment" << endl;
        cout << "2.On spot payment" << endl;
        cin >> p;
        if (p == 1)
        {

            cout << " ATM card details:" << endl;
            do
            {

                cout << "Enter 10 digits Account Number: ";
                cin >> accountNumber;
                for (char c : accountNumber)
                {
                    if (c < '0' || c > '9')
                    {
                        cout << "";
                    }
                }
            } while (accountNumber.length() != 10);
            cout << "Account Number: " << accountNumber << endl;
            do
            {

                cout << "Enter 4 digits Pin: ";
                cin >> pin;
                for (char c : pin)
                {
                    if (c < '0' || c > '9')
                    {
                        cout << "";
                    }
                }
            } while (pin.length() != 4);
            cout << "Pin: " << pin << endl;
            while (initialAmount < budget || initialAmount < 0)
            {
                cout << "Enter Initial Amount (Note:Initial Amount cannot be negative or less than your budget): ";
                cin >> initialAmount;
            }

            atm account(accountNumber, pin, initialAmount);

            account.deduct(deductAmount);
            cout << "\nAccount Details:" << endl;
            account.displayDetails();
        }
        else if (p == 2)
        {
            cout << "Sure! You can pay at the spot for everything." << endl;
        }
        else
        {
            cout << "Invalid option selected! Enter 1 or 2 according to your choice.";
        }
        cout << "Congratulations!You are all set for the trip. We hope you enjoyed planning the trip with us as much as we did." << endl;
    }
};

int main()
{
    system("cls");
    system("Color F0");
    vector<TravelPlanner> users;
    int addUser;
    cout << "\t\t\t\t\t _____________________________________________________________\n";
    cout << "\t\t\t\t\t|                                                             |\n";
    cout << "\t\t\t\t\t|                WELCOME TO THE TRAVEL COMPANION              |" << endl;
    cout << "\t\t\t\t\t|_____________________________________________________________|" << endl
         << endl
         << endl
         << endl
         << endl;
    do
    {
        cout << "\n\t\t\t\t\t\t   ________________________________________";
        cout << "\n\t\t\t\t\t\t  |                                        |";
        cout << "\n\t\t\t\t\t\t  |                 MENU                   |";
        cout << "\n\t\t\t\t\t\t  |________________________________________|";
        cout << "\n\t\t\t\t\t\t  | 1. PLAN A TRIP                         |";
        cout << "\n\t\t\t\t\t\t  | 0. EXIT                                |";
        cout << "\n\t\t\t\t\t\t  |________________________________________|";
        cout << "\n\n\t\t\t\t\t\t\t    Enter your choice:";
        cin >> addUser;
        system("cls");
        system("Color 24");
        if (addUser == 1)
        {
            TravelPlanner planner;
            planner.userInputLoop(planner);
            users.push_back(planner);
            system("pause");
        }
        else if (addUser == 0)
        {
            cout << "Exiting the program. Thank you!" << endl;
        }
        else
        {
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (addUser != 0);
    return 0;
}
