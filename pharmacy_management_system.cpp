// Pharmacy Management System //
// Srishti Kumari //

// Organizing Libraries

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#define max  10
using namespace std;

class pharmacy
{
public:
    void Take_order();    // To take an order
    void Delete_order();  // To delete an order
    void Print_Reciept(); // To print order reciept
    void Show_Data();     // To print medicine details
    void exit();          // To exit the program

    pharmacy()
    {
        // constructor
    }
};

struct Node
{
    int order_number;
    string customer_name;
    string date;
    int quantity[10];
    string med_type = "OTC";
    int nom, menu[10];
    double amount[10];
    string medicine_name[10] = {"Probiotics", "Vitamin C(500mg)", "Acid Free C(500mg)", "Women'S Multivate", "Marino Tablet", "Maxi Cal Tablet",
                                "Amino Zinc Tablet", "Burnex", "Fabuloss 5", "Royal Propollen"};
    double medicine[10] = {2.00, 3.00, 1.00, 4.00, 1.00, 5.00, 7.00, 4.00, 3.00, 5.00};
    double total;

    Node *next;
};

Node *start_ptr;
Node *last;

int main()
{
    // Main Function

    system("COLOR 3F");

    pharmacy pharma;
    start_ptr = last = NULL;
    last = new Node;
    // start_ptr->order_number = 111;
    int choice; // stores option the user has selected
    last->order_number = 111;

    do
    {
        system("cls");
        cout << "\t\t\t Pharmacy Management System\n";
        cout << "\t\t==================================================\n\n";
        cout << "\t\t--------------------------------------------------\n";
        cout << "\t\t||\t1. Take new Medicine order \t\t ||\n";
        cout << "\t\t||\t2. Delete Medicine order\t\t ||\n";
        cout << "\t\t||\t3. Print the Reciept and Make Payment \t ||\n";
        cout << "\t\t||\t4. Daily Summary of total Sale \t\t ||\n";
        cout << "\t\t||\t5. Exit\t\t\t\t\t ||\n";
        cout << "\t\t--------------------------------------------------\n";
        cout << "Enter choice: ";

        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            pharma.Take_order();
            system("PAUSE");
            break;
        }
        case 2:
        {
            pharma.Delete_order();
            system("PAUSE");
            break;
        }
        case 3:
        {
            pharma.Print_Reciept();
            system("PAUSE");
            break;
        }
        case 4:
        {
            pharma.Show_Data();
            system("PAUSE");
            break;
        }
        case 5:
        {
            pharma.exit();
            cout << "Bye, Hope you liked the interface." << endl;
            break;
        }

        default:
        {
            cout << "Your input is invalid.\nRe-enter your choice." << endl;
            system("PAUSE");
            break;
        }
        }

    } while (choice != 5);

    return 0;
}

void pharmacy::Take_order()
{
    system("cls");

    ifstream medfile;
    string line;
    medfile.open("medicines.txt");

    if (medfile.is_open())
    {
        while (getline(medfile, line))
        {
            cout << line << "\n";
        }
        medfile.close();
    }

    Node *temp;
    temp = new Node;

    temp->order_number = (last->order_number)++;
    cout << "Enter Customer Name: ";
    cin >> temp->customer_name;
    cout << "Enter Date (dd/mm/yyyy): ";
    cin >> temp->date;
    cout << "How many medicines would you like to order: " << endl;
    cout << "(Maximum number of medicines per order is 10)" << endl;
    cin >> temp->nom;

    if (temp->nom > max)
    {
        cout << "Maximum amount exceeded!";
        system("PAUSE");
    }
    else
    {
        for (int i = 0; i < temp->nom; i++)
        {
            cout << "Enter drug id: ";
            cin >> temp->menu[i];
            cout << "How many " << temp->medicine_name[temp->menu[i] - 1] << " you want?: ";
            cin >> temp->quantity[i];
            temp->amount[i] = temp->quantity[i] * temp->medicine[temp->menu[i] - 1];
            system("PausE");
        }
        cout << "=============================================================================" << endl;
        cout << "Order Placed Successfully." << endl;
        cout << "=============================================================================" << endl;
        cout << "Go to Reciept Menu to pay the Bill" << endl;
        cout << "=============================================================================" << endl;
        // system("PAUSE");

        temp->next = NULL;
        if (start_ptr != NULL)
        {
            temp->next = start_ptr;
        }
        start_ptr = temp;
        cout << "\nYour order number : " << temp->order_number << endl;
    }
}

void pharmacy::Print_Reciept()
{
    system("cls");
    int odn;
    Node *temp;
    temp = start_ptr;

    cout << "Enter order number: ";
    cin >> odn;

    if (temp == NULL)
    {
        cout << "No orders to print reciept" << endl;
    }
    while (temp != NULL)
    {
        if (temp->order_number == odn)
        {
            cout << "Order Number: " << temp->order_number << endl;
            cout << "Customer Name: " << temp->customer_name << endl;
            cout << "Order Date: " << temp->date << endl;
            cout << "_____________________________________________________________________________" << endl;

            cout << "===============================================================================" << endl;
            cout << "|  Medicine Type |     Medicine Name    |  	Quantity     |    Total Price |" << endl;
            cout << "=======++==================++================++===============++===============" << endl;

            for (int i = 0; i < temp->nom; i++)
            {
                cout << temp->med_type << " \t\t";
                cout << temp->medicine_name[temp->menu[i] - 1] << "\t\t\t  ";
                cout << temp->quantity[i] << "\t\t";
                cout << temp->amount[i] << "INR" << endl;
                cout << "_________________________________________________________________________________" << endl;
            }

            for (int j = 0; j < 10; j++)
            {
                temp->total = temp->total + temp->amount[j];
            }

            cout << "Total Bill is : " << temp->total << endl;
            cout << "Type 'y' to confirm payment: ";
            string w;
            cin >> w;
            cout << "\n\nPayment Done\nThak You\n\n";
            cout << "_________________________________________________________________________________" << endl;
            return;
        }
        else
        {
            temp = temp->next;
        }
    }
}

void pharmacy::Delete_order()
{
    system("cls");
    int odn;
    Node *temp;
    temp = start_ptr;
    Node *prev = NULL;

    cout << "Enter your order number to delete: ";
    cin >> odn;

    if (start_ptr == NULL)
    {
        cout << "No orders to delete"<<endl;
    }
    else
    {
        if (temp != NULL && temp->order_number == odn)
        {
            start_ptr = temp->next;
            delete temp;
            cout << "Order deleted successfully." << endl;
            return;
        }
        else
        {
            while (temp != NULL && temp->order_number != odn)
            {
                prev = temp;
                temp = temp->next;
            }
            if (temp == NULL)
            {
                cout << "Wrong Order Number." << endl;
                return;
            }
            prev->next = temp->next;
            delete temp;
            cout << "Order Deleted Successfully." << endl;
        }
    }
}

void pharmacy::Show_Data()
{
    system("cls");
    Node *temp;
    temp = start_ptr;

    if (temp == NULL)
    {
        cout << "There is no order to show.\n";
    }
    else
    {
        cout << "\n";
        cout << "===========================================================================" << endl;
        cout << " \t\tHere is the Daily Summary of All Orders \n";
        cout << "===========================================================================" << endl;

        while (temp != NULL)
        {
            cout << "Order Number: " << temp->order_number << endl;
            cout << "Customer Name: " << temp->customer_name << endl;
            cout << "Order Date: " << temp->date << endl;

            cout << "____________________________________________________________________________" << endl;

            cout << "==========================================================================" << endl;
            cout << "|  Medicine Type |   Medicine Name    |    Quantity     |    Total Price |" << endl;
            cout << "=======++==================++================++===============++==========" << endl;

            for (int i = 0; i < temp->nom; i++)
            {
                cout << temp->med_type << "\t\t";
                cout << temp->medicine_name[temp->menu[i] - 1] << "\t\t" << temp->quantity[i] << "\t\t" << temp->amount[i] << " INR" << endl;
                cout << "_____________________________________________________________________________" << endl;
            }

            for (int j = 0; j < 10; j++)
            {
                temp->total = temp->total + temp->amount[j];
            }

            cout << "Total Bill is : " << temp->total;

            cout << "\n\n\n_______________________________________________________________________________\n";

            temp = temp->next;
        }
    }
}

void pharmacy::exit()
{
    cout << "You choosed to exit." << endl;
}