#include <iostream>
#include <string>
using namespace std;

// =====================================================
// BASE CLASS
// =====================================================

class Item
{
protected:
    string itemName;
    string location;
    string date;
    string status;

public:

    // Constructor
    Item(string name, string loc, string d)
    {
        itemName = name;
        location = loc;
        date = d;
        status = "Active";
    }

    // Getter functions
    string getItemName()
    {
        return itemName;
    }

    string getLocation()
    {
        return location;
    }

    string getDate()
    {
        return date;
    }

    string getStatus()
    {
        return status;
    }

    // Change status
    void changeStatus(string newStatus)
    {
        status = newStatus;
    }

    // Virtual function
    virtual void display()
    {
        cout << "\nItem Name : " << itemName;
        cout << "\nLocation  : " << location;
        cout << "\nDate      : " << date;
        cout << "\nStatus    : " << status << endl;
    }

    // Virtual destructor
    virtual ~Item() {}
};


// =====================================================
// LOST ITEM CLASS
// =====================================================

class LostItem : public Item
{
private:
    string ownerName;
    string ownerContact;

public:

    // Constructor
    LostItem(string name, string loc, string d,
             string owner, string contact)
        : Item(name, loc, d)
    {
        ownerName = owner;
        ownerContact = contact;
    }

    // Getter functions
    string getOwnerName()
    {
        return ownerName;
    }

    string getOwnerContact()
    {
        return ownerContact;
    }

    // Function overriding
    void display() override
    {
        cout << "\n----------------------------------------";
        cout << "\nType          : LOST ITEM";
        cout << "\nItem Name     : " << itemName;
        cout << "\nOwner         : " << ownerName;
        cout << "\nOwner Contact : " << ownerContact;
        cout << "\nLost Location : " << location;
        cout << "\nLost Date     : " << date;
        cout << "\nStatus        : " << status;
        cout << "\n----------------------------------------\n";
    }
};


// =====================================================
// FOUND ITEM CLASS
// =====================================================

class FoundItem : public Item
{
private:
    string finderName;
    string finderContact;

public:

    // Constructor
    FoundItem(string name, string loc, string d,
              string finder, string contact)
        : Item(name, loc, d)
    {
        finderName = finder;
        finderContact = contact;

        // Important:
        // Found items must have status "Found"
        status = "Found";
    }

    // Getter functions
    string getFinderName()
    {
        return finderName;
    }

    string getFinderContact()
    {
        return finderContact;
    }

    // Function overriding
    void display() override
    {
        cout << "\n----------------------------------------";
        cout << "\nType           : FOUND ITEM";
        cout << "\nItem Name      : " << itemName;
        cout << "\nFinder         : " << finderName;
        cout << "\nFinder Contact : " << finderContact;
        cout << "\nFound Location : " << location;
        cout << "\nFound Date     : " << date;
        cout << "\nStatus         : " << status;
        cout << "\n----------------------------------------\n";
    }
};


// =====================================================
// MATCHING FUNCTION
// =====================================================

// Only Item Name is used for matching.
// Same Item Name = 100% Match
int calculateMatch(Item* lost, Item* found)
{
    if (lost->getItemName() == found->getItemName())
    {
        return 100;
    }

    return 0;
}


// =====================================================
// MAIN FUNCTION
// =====================================================

int main()
{
    // Arrays of base-class pointers
    Item* lostItems[100];
    Item* foundItems[100];

    int lostCount = 0;
    int foundCount = 0;

    int choice;

    cout << "\n============================================";
    cout << "\n       CAMPUS LOST & FOUND SYSTEM";
    cout << "\n============================================\n";


    do
    {
        cout << "\n============== MAIN MENU ==============\n";
        cout << "1. Report Lost Item\n";
        cout << "2. Report Found Item\n";
        cout << "3. Find My Lost Item\n";
        cout << "4. Claim / Return Item\n";
        cout << "5. Display All Lost Items\n";
        cout << "6. Display All Found Items\n";
        cout << "7. Exit\n";
        cout << "=======================================\n";

        cout << "Enter your choice: ";
        cin >> choice;

        cin.ignore();


        // =================================================
        // 1. REPORT LOST ITEM
        // =================================================

        if (choice == 1)
        {
            string name;
            string owner;
            string contact;
            string location;
            string date;

            cout << "\n========== REPORT LOST ITEM ==========\n";

            cout << "Enter Item Name: ";
            getline(cin, name);

            cout << "Enter Owner Name: ";
            getline(cin, owner);

            cout << "Enter Owner Contact: ";
            getline(cin, contact);

            cout << "Enter Lost Location: ";
            getline(cin, location);

            cout << "Enter Lost Date: ";
            getline(cin, date);

            lostItems[lostCount] =
                new LostItem(
                    name,
                    location,
                    date,
                    owner,
                    contact
                );

            lostCount++;

            cout << "\n======================================";
            cout << "\n Lost item registered successfully!";
            cout << "\n======================================\n";
        }


        // =================================================
        // 2. REPORT FOUND ITEM
        // =================================================

        else if (choice == 2)
        {
            string name;
            string finder;
            string contact;
            string location;
            string date;

            cout << "\n========== REPORT FOUND ITEM ==========\n";

            cout << "Enter Item Name: ";
            getline(cin, name);

            cout << "Enter Finder Name: ";
            getline(cin, finder);

            cout << "Enter Finder Contact: ";
            getline(cin, contact);

            cout << "Enter Found Location: ";
            getline(cin, location);

            cout << "Enter Found Date: ";
            getline(cin, date);

            foundItems[foundCount] =
                new FoundItem(
                    name,
                    location,
                    date,
                    finder,
                    contact
                );

            foundCount++;

            cout << "\n======================================";
            cout << "\n Found item registered successfully!";
            cout << "\n======================================\n";
        }


        // =================================================
        // 3. FIND MY LOST ITEM
        // =================================================

        else if (choice == 3)
        {
            string searchName;

            bool lostRecordFound = false;
            bool matchFound = false;

            cout << "\n========== FIND MY LOST ITEM ==========\n";

            cout << "Enter item name: ";
            getline(cin, searchName);


            // Search lost records
            for (int i = 0; i < lostCount; i++)
            {
                if (lostItems[i]->getItemName() == searchName &&
                    lostItems[i]->getStatus() == "Active")
                {
                    lostRecordFound = true;

                    cout << "\nYour Lost Item:\n";

                    lostItems[i]->display();


                    // Search found records
                    for (int j = 0; j < foundCount; j++)
                    {
                        if (foundItems[j]->getItemName() == searchName &&
                            foundItems[j]->getStatus() == "Found")
                        {
                            int score =
                                calculateMatch(
                                    lostItems[i],
                                    foundItems[j]
                                );


                            if (score == 100)
                            {
                                matchFound = true;

                                // Downcasting
                                FoundItem* found =
                                    dynamic_cast<FoundItem*>(
                                        foundItems[j]
                                    );

                                LostItem* lost =
                                    dynamic_cast<LostItem*>(
                                        lostItems[i]
                                    );


                                cout << "\n";
                                cout << "====================================\n";
                                cout << "          MATCH FOUND!\n";
                                cout << "====================================\n";

                                cout << "Item           : "
                                     << found->getItemName()
                                     << endl;

                                cout << "Owner          : "
                                     << lost->getOwnerName()
                                     << endl;

                                cout << "Owner Contact  : "
                                     << lost->getOwnerContact()
                                     << endl;

                                cout << "Found By       : "
                                     << found->getFinderName()
                                     << endl;

                                cout << "Found Location : "
                                     << found->getLocation()
                                     << endl;

                                cout << "Found Date     : "
                                     << found->getDate()
                                     << endl;

                                cout << "Finder Contact : "
                                     << found->getFinderContact()
                                     << endl;

                                cout << "Match Score    : "
                                     << score << "%"
                                     << endl;

                                cout << "====================================\n";


                                cout << "\nHIGH CONFIDENCE MATCH!\n";

                                cout << "\nThe item name matches your lost item.";
                                cout << "\nYou can contact "
                                     << found->getFinderName()
                                     << " and collect your item from "
                                     << found->getLocation()
                                     << ".\n";
                            }
                        }
                    }
                }
            }


            if (!lostRecordFound)
            {
                cout << "\nNo lost item record found.\n";
            }
            else if (!matchFound)
            {
                cout << "\nNo matching found item is currently available.\n";
            }
        }


        // =================================================
        // 4. CLAIM / RETURN ITEM
        // =================================================

        else if (choice == 4)
        {
            string searchName;
            bool found = false;

            cout << "\n========== CLAIM / RETURN ITEM ==========\n";

            cout << "Enter item name: ";
            getline(cin, searchName);


            for (int i = 0; i < foundCount; i++)
            {
                if (foundItems[i]->getItemName() == searchName &&
                    foundItems[i]->getStatus() == "Found")
                {
                    FoundItem* item =
                        dynamic_cast<FoundItem*>(
                            foundItems[i]
                        );


                    cout << "\n========== ITEM DETAILS ==========\n";

                    cout << "Item       : "
                         << item->getItemName();

                    cout << "\nFound By   : "
                         << item->getFinderName();

                    cout << "\nLocation   : "
                         << item->getLocation();

                    cout << "\nDate       : "
                         << item->getDate();

                    cout << "\nContact    : "
                         << item->getFinderContact();


                    cout << "\n\nHas the owner collected the item? (y/n): ";

                    char answer;

                    cin >> answer;
                    cin.ignore();


                    if (answer == 'y' || answer == 'Y')
                    {
                        foundItems[i]->changeStatus("Returned");

                        cout << "\n====================================";
                        cout << "\n    ITEM RETURNED SUCCESSFULLY!";
                        cout << "\n====================================\n";
                    }
                    else
                    {
                        cout << "\nItem is still waiting to be collected.\n";
                    }

                    found = true;

                    break;
                }
            }


            if (!found)
            {
                cout << "\nNo available matching item found.\n";
            }
        }


        // =================================================
        // 5. DISPLAY ALL LOST ITEMS
        // =================================================

        else if (choice == 5)
        {
            cout << "\n========== ALL LOST ITEMS ==========\n";

            if (lostCount == 0)
            {
                cout << "No lost items registered.\n";
            }
            else
            {
                for (int i = 0; i < lostCount; i++)
                {
                    lostItems[i]->display();
                }
            }
        }


        // =================================================
        // 6. DISPLAY ALL FOUND ITEMS
        // =================================================

        else if (choice == 6)
        {
            cout << "\n========== ALL FOUND ITEMS ==========\n";

            if (foundCount == 0)
            {
                cout << "No found items registered.\n";
            }
            else
            {
                for (int i = 0; i < foundCount; i++)
                {
                    foundItems[i]->display();
                }
            }
        }


        // =================================================
        // 7. EXIT
        // =================================================

        else if (choice == 7)
        {
            cout << "\n============================================";
            cout << "\n Thank you for using Campus Lost & Found!";
            cout << "\n============================================\n";
        }


        else
        {
            cout << "\nInvalid choice! Please try again.\n";
        }

    }
    while (choice != 7);


    // =================================================
    // FREE MEMORY
    // =================================================

    for (int i = 0; i < lostCount; i++)
    {
        delete lostItems[i];
    }

    for (int i = 0; i < foundCount; i++)
    {
        delete foundItems[i];
    }

    return 0;
}
