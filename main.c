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

//Header files
#include <stdio.h>      //Allows the use of input and output functions
#include <stdlib.h>     //Allows the use of standard library functions
#include <string.h>     //Allows the use of string manipulation functions
#include <time.h>       //Allows the use of time and date functions

//Global Variables
#define MAX_NUMBER_OF_GUESTS 1000    // Maximum number of guests that can be stored in the system
int numberOfGuests = 0;              // Current number of guests stored in the system
int returnToMainMenu = 0;            // Flag to control navigation to the main menu
int numberOfEmployees = 0;           // Current number of employees in the system
int maxLoginAttempts = 3;            // Maximum number of login attempts allowed
int loginAttempts = 0;               // Current number of login attempts made by the user
int loggedIn = 0;                    // Flag to indicate if a user is logged in (1 = logged in, 0 = not logged in)
char username[20];                   // Stores the username entered during login
char password[20];                   // Stores the password entered during login
int reservationNumber;               // Stores the reservation number for a guest
