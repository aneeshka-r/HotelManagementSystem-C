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

