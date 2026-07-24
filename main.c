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

    Purpose:
    To improve C programming skills and practice software design,
    data structures, and file handling.
*/

// Header files
#include <stdio.h>      // Allows the use of input and output functions
#include <stdlib.h>     // Allows the use of standard library functions
#include <string.h>     // Allows the use of string manipulation functions
#include <time.h>       // Allows the use of time and date functions

// Global Variables
#define MAX_NUMBER_OF_GUESTS 1000   // Maximum number of guest records allowed

int numberOfGuests = 0;             // Current number of guests stored
int numberOfEmployees;              // Number of employees stored
int maxLoginAttempts = 3;            // Maximum login attempts allowed
int loginAttempts = 0;               // Current login attempts
int loggedIn = 0;                     // Login status (1 = logged in, 0 = logged out)
int returnToMainMenu = 0;             // Controls returning to the main menu

char username[20];                    // Stores entered username
char password[20];                    // Stores entered password

// Structures
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
void displayManageReservationsMenu(void);
void manageReservations(void);
void readGuestData(struct GuestInformation guests[], int *numberOfGuests);
void viewReservations(void);
void addReservation(void);
void updateReservation(void);
void searchReservation(void);
void deleteReservation(void);
void guestCheckIn(void);
void guestCheckOut(int durationOfStay);
void viewOccupiedRooms(void);
void returnToLoginScreen(void);
void exitProgram(void);

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
                exitProgram();
                break;

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
                return;

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

    // Check if there are no reservations stored
    if (numberOfGuests == 0)
    {
        printf("\nNo reservations found.\n");
        return;
    }

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

// Allows the user to add a new guest reservation and the reservation details are saved to the GuestInformation.txt file.
void addReservation(void)
{
    printf("\nAdd Reservation Option Selected.\n");

    // Creates a temporary guest record to store the new reservation
    struct GuestInformation newReservation;

    printf("\nEnter reservation details without spaces.\n");
    printf("Example: FirstnameLastname\n\n");

    printf("Reservation Number: ");
    scanf("%d", &newReservation.reservationNumber);

    printf("Name: ");
    scanf("%49s", newReservation.name);

    printf("Email: ");
    scanf("%74s", newReservation.email);

    printf("Phone Number: ");
    scanf("%14s", newReservation.phoneNumber);

    printf("Address: ");
    scanf("%149s", newReservation.address);

    printf("Duration of Stay: ");
    scanf("%d", &newReservation.durationOfStay);

    printf("Check-in Date (DD/MM/YYYY): ");
    scanf("%19s", newReservation.checkInDate);

    printf("Check-out Date (DD/MM/YYYY): ");
    scanf("%19s", newReservation.checkOutDate);

    printf("Room Type: ");
    scanf("%49s", newReservation.roomType);

    printf("Number of Adults: ");
    scanf("%d", &newReservation.numberOfAdults);

    printf("Number of Children: ");
    scanf("%d", &newReservation.numberOfChildren);

    printf("Room Number: ");
    scanf("%19s", newReservation.roomNumber);

    printf("Payment Method: ");
    scanf("%19s", newReservation.paymentMethod);

    printf("Payment Information: ");
    scanf("%24s", newReservation.paymentInformation);

    printf("Payment Status: ");
    scanf("%19s", newReservation.paymentStatus);

    // Opens file in append mode to add the new reservation
    FILE *file = fopen("GuestInformation.txt", "a");

    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    // Writes the new reservation details to the file
    fprintf(file,
            "%d %s %s %s %s %d %s %s %s %d %d %s %s %s %s\n",
            newReservation.reservationNumber,
            newReservation.name,
            newReservation.email,
            newReservation.phoneNumber,
            newReservation.address,
            newReservation.durationOfStay,
            newReservation.checkInDate,
            newReservation.checkOutDate,
            newReservation.roomType,
            newReservation.numberOfAdults,
            newReservation.numberOfChildren,
            newReservation.roomNumber,
            newReservation.paymentMethod,
            newReservation.paymentInformation,
            newReservation.paymentStatus);

    fclose(file);

    printf("\nReservation added successfully.\n");

    // Reload guest data so the program has the updated information
    readGuestData(guests, &numberOfGuests);
}

//Updates an existing guest reservation. Searches for a reservation number, changes the information, and saves the updated records back to the file.
void updateReservation(void)
{
    printf("\nUpdate Reservation Option Selected.\n");

    // Load current guest records
    readGuestData(guests, &numberOfGuests);

    int reservationNumber;
    int found = 0;

    printf("Enter reservation number to update: ");
    scanf("%d", &reservationNumber);

    // Search for reservation
    for (int i = 0; i < numberOfGuests; i++)
    {
        if (guests[i].reservationNumber == reservationNumber)
        {
            found = 1;

            printf("\nEnter new reservation details without spaces.\n");


            printf("Reservation Number: ");
            scanf("%d", &guests[i].reservationNumber);

            printf("Name: ");
            scanf("%49s", guests[i].name);

            printf("Email: ");
            scanf("%74s", guests[i].email);

            printf("Phone Number: ");
            scanf("%14s", guests[i].phoneNumber);

            printf("Address: ");
            scanf("%149s", guests[i].address);

            printf("Duration of Stay: ");
            scanf("%d", &guests[i].durationOfStay);

            printf("Check-in Date: ");
            scanf("%19s", guests[i].checkInDate);

            printf("Check-out Date: ");
            scanf("%19s", guests[i].checkOutDate);

            printf("Room Type: ");
            scanf("%49s", guests[i].roomType);

            printf("Number of Adults: ");
            scanf("%d", &guests[i].numberOfAdults);

            printf("Number of Children: ");
            scanf("%d", &guests[i].numberOfChildren);

            printf("Room Number: ");
            scanf("%19s", guests[i].roomNumber);

            printf("Payment Method: ");
            scanf("%19s", guests[i].paymentMethod);

            printf("Payment Information: ");
            scanf("%24s", guests[i].paymentInformation);

            printf("Payment Status: ");
            scanf("%19s", guests[i].paymentStatus);

            break;
        }
    }

    if (!found)
    {
        printf("\nReservation not found.\n");
        return;
    }

    // Rewrite the file with updated information
    FILE *file = fopen("GuestInformation.txt", "w");

    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < numberOfGuests; i++)
    {
        fprintf(file,
                "%d %s %s %s %s %d %s %s %s %d %d %s %s %s %s\n",
                guests[i].reservationNumber,
                guests[i].name,
                guests[i].email,
                guests[i].phoneNumber,
                guests[i].address,
                guests[i].durationOfStay,
                guests[i].checkInDate,
                guests[i].checkOutDate,
                guests[i].roomType,
                guests[i].numberOfAdults,
                guests[i].numberOfChildren,
                guests[i].roomNumber,
                guests[i].paymentMethod,
                guests[i].paymentInformation,
                guests[i].paymentStatus);
    }

    fclose(file);

    printf("\nReservation updated successfully.\n");
}

// Searches for a guest reservation using the reservation number. Displays the reservation details if a matching record is found.
void searchReservation(void)
{
    int reservationNumber;
    int found = 0;

    printf("\nEnter the reservation number you would like to search for: ");
    scanf("%d", &reservationNumber);

    // Open guest information file for reading
    FILE *file = fopen("GuestInformation.txt", "r");

    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    struct GuestInformation currentReservation;

    // Search through each reservation in the file
    while (fscanf(file,
                  "%d %49s %74s %14s %149s %d %19s %19s %49s %d %d %19s %19s %24s %19s",
                  &currentReservation.reservationNumber,
                  currentReservation.name,
                  currentReservation.email,
                  currentReservation.phoneNumber,
                  currentReservation.address,
                  &currentReservation.durationOfStay,
                  currentReservation.checkInDate,
                  currentReservation.checkOutDate,
                  currentReservation.roomType,
                  &currentReservation.numberOfAdults,
                  &currentReservation.numberOfChildren,
                  currentReservation.roomNumber,
                  currentReservation.paymentMethod,
                  currentReservation.paymentInformation,
                  currentReservation.paymentStatus) == 15)
    {
        if (currentReservation.reservationNumber == reservationNumber)
        {
            found = 1;

            printf("\nReservation Found:\n");
            printf("------------------------------\n");
            printf("Reservation Number: %d\n", currentReservation.reservationNumber);
            printf("Name: %s\n", currentReservation.name);
            printf("Email: %s\n", currentReservation.email);
            printf("Phone Number: %s\n", currentReservation.phoneNumber);
            printf("Address: %s\n", currentReservation.address);
            printf("Duration of Stay: %d\n", currentReservation.durationOfStay);
            printf("Check-in Date: %s\n", currentReservation.checkInDate);
            printf("Check-out Date: %s\n", currentReservation.checkOutDate);
            printf("Room Type: %s\n", currentReservation.roomType);
            printf("Number of Adults: %d\n", currentReservation.numberOfAdults);
            printf("Number of Children: %d\n", currentReservation.numberOfChildren);
            printf("Room Number: %s\n", currentReservation.roomNumber);
            printf("Payment Method: %s\n", currentReservation.paymentMethod);
            printf("Payment Information: %s\n", currentReservation.paymentInformation);
            printf("Payment Status: %s\n", currentReservation.paymentStatus);

            break;
        }
    }

    fclose(file);

    if (!found)
    {
        printf("\nReservation not found.\n");
    }
}

// Deletes an existing guest reservation. A temporary file is used to rewrite the guest records without the deleted reservation.
void deleteReservation(void)
{
    printf("\nDelete Reservation Option Selected.\n");

    int reservationNumber;
    int found = 0;

    printf("Enter reservation number to delete: ");
    scanf("%d", &reservationNumber);

    FILE *file = fopen("GuestInformation.txt", "r");
    FILE *tempFile = fopen("tempFile.txt", "w");

    if (file == NULL || tempFile == NULL)
    {
        printf("Error opening files.\n");
        return;
    }

    struct GuestInformation currentReservation;

    while (fscanf(file,
                  "%d %49s %74s %14s %149s %d %19s %19s %49s %d %d %19s %19s %24s %19s",
                  &currentReservation.reservationNumber,
                  currentReservation.name,
                  currentReservation.email,
                  currentReservation.phoneNumber,
                  currentReservation.address,
                  &currentReservation.durationOfStay,
                  currentReservation.checkInDate,
                  currentReservation.checkOutDate,
                  currentReservation.roomType,
                  &currentReservation.numberOfAdults,
                  &currentReservation.numberOfChildren,
                  currentReservation.roomNumber,
                  currentReservation.paymentMethod,
                  currentReservation.paymentInformation,
                  currentReservation.paymentStatus) == 15)
    {

        // Copy all reservations except the one being deleted
        if (currentReservation.reservationNumber != reservationNumber)
        {
            fprintf(tempFile,
                    "%d %s %s %s %s %d %s %s %s %d %d %s %s %s %s\n",
                    currentReservation.reservationNumber,
                    currentReservation.name,
                    currentReservation.email,
                    currentReservation.phoneNumber,
                    currentReservation.address,
                    currentReservation.durationOfStay,
                    currentReservation.checkInDate,
                    currentReservation.checkOutDate,
                    currentReservation.roomType,
                    currentReservation.numberOfAdults,
                    currentReservation.numberOfChildren,
                    currentReservation.roomNumber,
                    currentReservation.paymentMethod,
                    currentReservation.paymentInformation,
                    currentReservation.paymentStatus);
        }
        else
        {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    remove("GuestInformation.txt");
    rename("tempFile.txt", "GuestInformation.txt");

    if (found)
    {
        printf("\nReservation deleted successfully.\n");
    }
    else
    {
        printf("\nReservation with number %d was not found.\n", reservationNumber);
    }

    // Reload guest data after deletion
    readGuestData(guests, &numberOfGuests);
}

// Checks a guest into the hotel. Stores check-in details and automatically records the current date.
void guestCheckIn(void)
{
    printf("\nGuest Check-In Option Selected.\n");

    char searchName[50];
    char searchRoomNumber[20];
    int searchReservationNumber;

    printf("Enter guest name: ");
    scanf("%49s", searchName);

    printf("Enter room number: ");
    scanf("%19s", searchRoomNumber);

    printf("Enter reservation number: ");
    scanf("%d", &searchReservationNumber);

    // Gets current date
    time_t currentTime;
    struct tm *localTime;

    time(&currentTime);
    localTime = localtime(&currentTime);

    char checkInDate[20];

    strftime(checkInDate,
             sizeof(checkInDate),
             "%d/%m/%Y",
             localTime);

    FILE *file = fopen("CheckInInformation.txt", "a");

    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    fprintf(file,
            "Guest Name: %s, Room Number: %s, Reservation Number: %d, Check-in Date: %s\n",
            searchName,
            searchRoomNumber,
            searchReservationNumber,
            checkInDate);

    fclose(file);

    printf("\nGuest checked in successfully.\n");
}

// Checks a guest out of the hotel. Records the checkout details and automatically saves the checkout date.
void guestCheckOut(int durationOfStay)
{
    printf("\nGuest Check-Out Option Selected.\n");

    char searchName[50];
    char searchRoomNumber[20];
    int searchReservationNumber;

    printf("Enter guest name: ");
    scanf("%49s", searchName);

    printf("Enter room number: ");
    scanf("%19s", searchRoomNumber);

    printf("Enter guest's reservation number: ");
    scanf("%d", &searchReservationNumber);

    // Gets current date
    time_t currentTime;
    struct tm *localTime;

    time(&currentTime);
    localTime = localtime(&currentTime);

    char checkOutDate[20];

    strftime(checkOutDate,
             sizeof(checkOutDate),
             "%d/%m/%Y",
             localTime);

    // Opens checkout file
    FILE *file = fopen("CheckOutInformation.txt", "a");

    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    // Writes checkout information
    fprintf(file,
            "Guest Name: %s, Room Number: %s, Reservation Number: %d, Check-out Date: %s, Duration of Stay: %d\n",
            searchName,
            searchRoomNumber,
            searchReservationNumber,
            checkOutDate,
            durationOfStay);

    fclose(file);

    printf("\nGuest checked out successfully.\n");
}

// Displays all currently occupied hotel rooms. Reads check-in information from the CheckInInformation.txt file.
void viewOccupiedRooms(void)
{
    printf("\nView Occupied Rooms Option Selected.\n");

    FILE *file = fopen("CheckInInformation.txt", "r");

    if (file == NULL)
    {
        printf("\nNo occupied rooms found.\n");
        return;
    }

    printf("\nOccupied Rooms:\n");
    printf("------------------------------\n");

    struct CheckInInformation checkIn;

    while (fscanf(file,
                  "%49s %19s %d %19s",
                  checkIn.name,
                  checkIn.roomNumber,
                  &checkIn.reservationNumber,
                  checkIn.checkInDate) == 4)
    {
        printf("Guest Name: %s\n", checkIn.name);
        printf("Room Number: %s\n", checkIn.roomNumber);
        printf("Reservation Number: %d\n", checkIn.reservationNumber);
        printf("Check-in Date: %s\n\n", checkIn.checkInDate);
    }

    fclose(file);
}

// Returns the user to the login screen by logging them out and clearing the stored login information. 
void returnToLoginScreen(void)
{
    printf("\nReturning to Login Screen...\n");

    // Reset login status
    loggedIn = 0;

    // Clear username and password
    username[0] = '\0';
    password[0] = '\0';
}

// Ends the hotel management system. Displays an exit message before closing the program.
void exitProgram(void)
{
    printf("\nExiting Hotel Management System...\n");

    exit(0);
}

int main(void)
{
    int menuOption;
    int durationOfStay;

    while (1)
    {
        // Login loop
        while (!loggedIn)
        {
            displayLoginScreen();
            printf("Enter your username: ");
            scanf("%19s", username);

            printf("Enter your password: ");
            scanf("%19s", password);

            loggedIn = validateLogin(employees,
                                     numberOfEmployees,
                                     username,
                                     password);

            if (loggedIn)
            {
                printf("\nLogin successful!\n");
                loginAttempts = 0;
            }
            else
            {
                loginAttempts++;

                if (loginAttempts >= maxLoginAttempts)
                {
                    printf("\nMaximum login attempts reached. Exiting program.\n");
                    return 1;
                }

                printf("\nInvalid username or password. Please try again.\n");
            }
        }

        // Main menu loop
        while (loggedIn)
        {
            displayMainMenu();

            printf("\nEnter Menu Option: ");
            scanf("%d", &menuOption);

            switch(menuOption)
            {
                case 1:
                    manageReservations();
                    break;

                case 2:
                    guestCheckIn();
                    break;

                case 3:
                    printf("Enter duration of stay (days): ");
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
                    exitProgram();
                    break;

                default:
                    printf("\nInvalid menu option. Please try again.\n");
            }
        }
    }

    return 0;
}

