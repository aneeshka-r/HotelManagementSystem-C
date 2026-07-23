/*
    Project Title: Hotel Management System

    Description:
    A C-based hotel reservation and guest management system designed
    to digitize the process of managing guest information, reservations,
    and hotel records.

    Features:
    - Employee login authentication
    - Add, view, update, delete, and search reservations
    - Manage guest information
    - Store and retrieve guest records using files

    Language:
    C Programming Language

    Original Project:
    CAPE Computer Science Unit 1 IA
    Completed: April 4, 2024

    Rebuilt:
    Started: July 23, 2026
    Purpose: To improve C programming skills and practice software
    design, data structures, and file handling.
*/

// Header files
#include <stdio.h>      // Allows the use of input and output functions
#include <stdlib.h>     // Allows the use of standard library functions
#include <string.h>     // Allows the use of string manipulation functions
#include <time.h>       // Allows the use of time and date functions

// Global Variables
#define MAX_NUMBER_OF_GUESTS 1000    // Maximum number of guests that can be stored in the system

int numberOfGuests = 0;              // Current number of guests stored in the system
int returnToMainMenu = 0;            // Flag to control navigation to the main menu
int numberOfEmployees = 0;           // Current number of employees stored in the system
int maxLoginAttempts = 3;            // Maximum number of login attempts allowed
int loginAttempts = 0;               // Current number of login attempts made by the user
int loggedIn = 0;                    // Flag to indicate if a user is logged in (1 = logged in, 0 = not logged in)
char username[20];                   // Stores the username entered during login
char password[20];                   // Stores the password entered during login

/* Structures */
// Structure to store guest reservation and personal information
struct GuestInformation
{
    // Reservation Information
    int reservationNumber;
    int durationOfStay;
    char checkInDate[20];
    char checkOutDate[20];

    // Personal Information
    char name[50];
    char email[75];
    char phoneNumber[15];
    char address[150];

    // Room Information
    char roomType[50];
    int numberOfAdults;
    int numberOfChildren;
    char roomNumber[20];

    // Payment Information
    char paymentMethod[20];
    char paymentInformation[25];
    char paymentStatus[20];
};

// Creates an array to store multiple guest records
struct GuestInformation guests[MAX_NUMBER_OF_GUESTS];


// Structure to store employee login information
struct Employee
{
    char username[20];
    char password[20];
};


// Structure to store guest check-in information
struct CheckInInformation
{
    int reservationNumber;
    char name[50];
    char roomNumber[20];
    char checkInDate[20];
};


// Stores employee login credentials
struct Employee employees[] =
{
    {"manager1", "code1"},
    {"manager2", "code2"},
    {"manager3", "code3"},
    {"receptionist1", "code4"},
    {"receptionist2", "code5"},
    {"admin", "password1"}
};

// Function Prototypes
int validateLogin(struct Employee employees[], int numberOfEmployees, char *username, char *password);
void displayLoginScreen(void);
void displayMainMenu(void);
void mainMenu(void);
void displayManageReservationsMenu(void);
void manageReservations(void);
void readGuestData(struct GuestInformation guests[], int *numberOfGuests);
void viewReservations(void);
void addReservation(void);
void updateReservation(void);
void searchReservation(void);
void deleteReservation(void);
void returnToMenu(void);
void guestCheckIn(void);
void guestCheckOut(int durationOfStay);
void viewOccupiedRooms(void);
void returnToLoginScreen(void);

/* Functions */
// Validates the login credentials entered by the user against the list of employee usernames and passwords. (Returns: 1 - Login successful 0 - Login failed)
int validateLogin(struct Employee employees[], int numberOfEmployees, char *username, char *password)
{
    for (int i = 0; i < numberOfEmployees; i++)
    {
        if (strcmp(username, employees[i].username) == 0 &&
            strcmp(password, employees[i].password) == 0)
        {
            return 1; // Login successful
        }
    }

    return 0; // Login failed
}

// Displays the login screen for the hotel management system.
void displayLoginScreen(void)
{
    printf("|----------------------------------------------|\n");
    printf("|        Portal Hotel's Login Menu             |\n");
    printf("|______________________________________________|\n");
}

// Displays the main menu options for the hotel management system.
void displayMainMenu(void)
{
    printf("\n|----------------------------------------------|\n");
    printf("\n|              Hotel's Main Menu               |\n");
    printf("\n|----------------------------------------------|\n");
    printf("\n| 1. Manage Reservations                       |\n");
    printf("\n| 2. Guest Check-In                            |\n");
    printf("\n| 3. Guest Check-Out                           |\n");
    printf("\n| 4. View Occupied Rooms                       |\n");
    printf("\n| 5. Return to Login Screen                    |\n");
    printf("\n| 6. Exit                                      |\n");
    printf("\n|----------------------------------------------|\n");
}

// Displays the main menu and handles user selections.
void mainMenu(void)
{
    int menuOption;
    int durationOfStay;

    while (1)
    {
        displayMainMenu();

        printf("\nEnter Menu Option: ");
        scanf("%d", &menuOption);

        switch (menuOption)
        {
            case 1:
                manageReservations();
                break;

            case 2:
                guestCheckIn();
                break;

            case 3:
                printf("Enter the duration of stay (in days): ");
                scanf("%d", &durationOfStay);

                guestCheckOut(durationOfStay);
                break;

            case 4:
                viewOccupiedRooms();
                break;

            case 5:
                returnToLoginScreen();
                break;

            case 6:
                printf("\nExiting Hotel Management System...\n");
                exit(0);

            default:
                printf("\nInvalid Menu Option. Please select a number between 1 and 6.\n");
        }
    }
}

// Displays the manage reservations menu options.
void displayManageReservationsMenu(void)
{
    printf("\n|----------------------------------------------|\n");
    printf("\n|          Manage Reservations Menu            |\n");
    printf("\n|----------------------------------------------|\n");
    printf("\n| 1. View Reservation                          |\n");
    printf("\n| 2. Add Reservation                           |\n");
    printf("\n| 3. Update Reservation                        |\n");
    printf("\n| 4. Search Reservation                        |\n");
    printf("\n| 5. Cancel Reservation                        |\n");
    printf("\n| 6. Return to Main Menu                       |\n");
    printf("\n|----------------------------------------------|\n");
}

// Displays and manages the reservation menu options.
void manageReservations(void)
{
    int submenuOption;

    do
    {
        displayManageReservationsMenu();

        printf("\nEnter Menu Option: ");
        scanf("%d", &submenuOption);

        switch (submenuOption)
        {
            case 1:
                viewReservations();
                break;

            case 2:
                addReservation();
                break;

            case 3:
                updateReservation();
                break;

            case 4:
                searchReservation();
                break;

            case 5:
                deleteReservation();
                break;

            case 6:
                returnToMenu();
                break;

            default:
                printf("\nInvalid Menu Option. Please select a number between 1 and 6.\n");
        }

        if (returnToMainMenu)
        {
            returnToMainMenu = 0;
            break;
        }

    } while (1);
}

// Reads guest information from the GuestInformation.txt file and stores the records in the guest array.
void readGuestData(struct GuestInformation guests[], int *numberOfGuests)
{
    int count = 0;

    FILE *file = fopen("GuestInformation.txt", "r");

    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    while (fscanf(file,
                  "%d %49s %74s %14s %149s %d %19s %19s %49s %d %d %19s %19s %24s %19s",
                  &guests[count].reservationNumber,
                  guests[count].name,
                  guests[count].email,
                  guests[count].phoneNumber,
                  guests[count].address,
                  &guests[count].durationOfStay,
                  guests[count].checkInDate,
                  guests[count].checkOutDate,
                  guests[count].roomType,
                  &guests[count].numberOfAdults,
                  &guests[count].numberOfChildren,
                  guests[count].roomNumber,
                  guests[count].paymentMethod,
                  guests[count].paymentInformation,
                  guests[count].paymentStatus) == 15)
    {
        count++;

        if (count >= MAX_NUMBER_OF_GUESTS)
        {
            printf("Maximum number of guests reached.\n");
            break;
        }
    }

    *numberOfGuests = count;

    fclose(file);

    printf("Guest information read successfully.\n");
}

// Displays all guest reservations and information stored in the system.
void viewReservations(void)
{
    printf("\nView Reservations Option Selected.\n");

    // Update guest array with information from file
    readGuestData(guests, &numberOfGuests);

    printf("\nReservation Details:\n");

    for (int i = 0; i < numberOfGuests; i++)
    {
        printf("Reservation Number: %d\n", guests[i].reservationNumber);
        printf("Name: %s\n", guests[i].name);
        printf("Email: %s\n", guests[i].email);
        printf("Phone Number: %s\n", guests[i].phoneNumber);
        printf("Address: %s\n", guests[i].address);
        printf("Duration of Stay: %d\n", guests[i].durationOfStay);
        printf("Check-in Date: %s\n", guests[i].checkInDate);
        printf("Check-out Date: %s\n", guests[i].checkOutDate);
        printf("Room Type: %s\n", guests[i].roomType);
        printf("Number of Adults: %d\n", guests[i].numberOfAdults);
        printf("Number of Children: %d\n", guests[i].numberOfChildren);
        printf("Room Number: %s\n", guests[i].roomNumber);
        printf("Payment Method: %s\n", guests[i].paymentMethod);
        printf("Payment Information: %s\n", guests[i].paymentInformation);
        printf("Payment Status: %s\n", guests[i].paymentStatus);
    }
}