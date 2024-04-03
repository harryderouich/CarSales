#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
// Adds getchar() function
#include <conio.h>
// Windows header for SetConsoleOutput
#include <Windows.h>
// String Functions
#include <string.h>
// Date and time
#include <time.h>
// Custom Functions
#include "harryCarSales.h"

int main() {
    // Set console to output UTF-8 characters (£)
    SetConsoleOutputCP(CP_UTF8);

    // Variables
    short inputValid = 0, mainMenuChoice, stockMenuChoice, finished = 0, arrayPosition = 0, userAge;
    char discountAnswer = 'n'; // default to no discount
    double totalSpend = 0.0f;
    double amountDiscounted = 0.0f;
    int validateCheck;

    // Constants for array sizes
    #define NUM_OF_CARS 6
    #define MAX_CAR_STR_LEN 25
    #define MAX_NAME_LEN 50

    // Constants for menu choices
    #define MAIN_MENU_BUY_CARS 1
    #define MAIN_MENU_ENABLE_DISCOUNT 2
    #define MAIN_MENU_NAME 3
    #define MAIN_MENU_RECORD_FEEDBACK 4
    #define MAIN_MENU_VIEW_DATA_EXIT 0

    // Arrays
    char carMakes[NUM_OF_CARS][MAX_CAR_STR_LEN] = {"BMW", "Audi", "Mercedes", "Bugatti", "Volkswagen","Mini"};
    char carModels[NUM_OF_CARS][MAX_CAR_STR_LEN] = {"1-Series", "A3", "A-Class", "Veyron", "Polo","Hatch"};
    int carYears[NUM_OF_CARS] = {2015, 2016, 2014, 2008, 2020, 2015};
    double carPrices[NUM_OF_CARS] = {10000.00f, 12000.00f, 14000.00f, 1100000.00f, 12500.00f, 13500.00f};
    short carStock[NUM_OF_CARS] = {2, 1, 3, 5, 9, 1};
    short amountOfCarSold[NUM_OF_CARS] = {0,0,0,0,0, 0};
    double valueOfCarSold[NUM_OF_CARS] = {0, 0, 0, 0, 0, 0};
    short initialOrder[NUM_OF_CARS] = {1, 2, 3, 4, 5, 6}; // To revert sort order for sales file
    char userName[MAX_NAME_LEN];

    // Initial calculation of car stock
    unsigned short carStockTotal = sumOfArray(carStock, NUM_OF_CARS);
    #define CAR_STOCK_TOTAL 100

    // Purchase arrays for sales data/reporting
    char whoPurchased[CAR_STOCK_TOTAL][MAX_NAME_LEN] = {};
    char carsPurchased[CAR_STOCK_TOTAL][2*MAX_CAR_STR_LEN+1] = {}; // Combines make and model with a space so can be at the most 2*max+1 characters
    short agePurchased[CAR_STOCK_TOTAL] = {};
    char datePurchased[CAR_STOCK_TOTAL][20] = {};

    // Request initial user name, validate for empty names
    do {
        printf("Welcome, please enter your name: ");
        fgets(userName, MAX_NAME_LEN, stdin);
        userName[strlen(userName)-1]='\0'; // remove newline character
        if (userName[0] == '\0' ) {
            pressEnterPrompt("Please enter a name. Press enter to try again...");
            clearConsole();
        } else {
            inputValid = 1;
        }
    } while (inputValid == 0);
    inputValid = 0; // reset inputValid for future use

    // Initial user age
    userAge = captureUserAge();

    // MAIN MENU/PURCHASE LOOP BELOW
    // Loop the system until stock is depleted or until the user has indicated they are finished
    while (finished != 1 && (carStockTotal > 0 )) {
        // Display the main menu and prompt for user input, looping whilst input is invalid
        do {
            // Display Main Menu and prompt user input
            clearConsole();
            displayMainMenu(userName, discountAnswer, userAge);
            scanf("%hd", &mainMenuChoice);

            // Validate the chosen menu choice exists
            if ( mainMenuChoice == MAIN_MENU_BUY_CARS || mainMenuChoice == MAIN_MENU_ENABLE_DISCOUNT
                || mainMenuChoice == MAIN_MENU_NAME || mainMenuChoice == MAIN_MENU_RECORD_FEEDBACK
                || mainMenuChoice == MAIN_MENU_VIEW_DATA_EXIT) {
                inputValid = 1;
            } else {
                pressEnterPrompt("Selection invalid, press enter to try again...\n");
            }
        } while (inputValid == 0);

        // Clear inputValid for future use
        inputValid = 0;
        // TODO rigorous testing throughout with unexpected entry e.g chars when int expected. Strings for chars etc

        // PURCHASE CARS
        if (mainMenuChoice == MAIN_MENU_BUY_CARS) {
            do {
                // Sorting of car arrays by year
                for (int i = 0; i < NUM_OF_CARS - 1; i++) {
                    for (int j = 0; j < NUM_OF_CARS - 1 - i; j++) {
                        // Compare adjacent elements
                        if (carYears[j] < carYears[j+1]) { // Criteria to sort all arrays by - Years descending

                            // Car Makes
                            char tempCarString[MAX_CAR_STR_LEN];
                            strcpy(tempCarString, carMakes[j]);
                            strcpy(carMakes[j], carMakes[j+1]);
                            strcpy(carMakes[j+1], tempCarString);

                            // Car Models
                            strcpy(tempCarString, carModels[j]);
                            strcpy(carModels[j], carModels[j+1]);
                            strcpy(carModels[j+1], tempCarString);

                            // Car Prices
                            double tempPriceVariable = carPrices[j];
                            carPrices[j] = carPrices[j+1];
                            carPrices[j+1] = tempPriceVariable;

                            // Car Years
                            int tempYearVariable = carYears[j];
                            carYears[j] = carYears[j+1];
                            carYears[j+1] = tempYearVariable;

                            // Car Stock
                            short tempCarStock = carStock[j];
                            carStock[j] = carStock[j+1];
                            carStock[j+1] = tempCarStock;

                            // Initial Order (to revert before writing the file)
                            short tempInitialOrder = initialOrder[j];
                            initialOrder[j] = initialOrder[j+1];
                            initialOrder[j+1] = tempInitialOrder;

                            // Amount of car sold
                            short tempAmountSold = amountOfCarSold[j];
                            amountOfCarSold[j] = amountOfCarSold[j+1];
                            amountOfCarSold[j+1] = tempAmountSold;

                            // Value of car sold
                            double tempValueSold = valueOfCarSold[j];
                            valueOfCarSold[j] = valueOfCarSold[j+1];
                            valueOfCarSold[j+1] = tempValueSold;

                        }
                    }
                }

                // Display stock menu
                clearConsole();
                displayStockTable(carMakes, carModels, carYears, carPrices, carStock, NUM_OF_CARS, 0);

                // Prompt and user input
                printf("\nPlease enter the number of the car you wish to purchase: ");
                getchar();
                scanf("%hd", &stockMenuChoice);
                // todo entering char enters infinite loop - fixed but weird still on 1st time failing because it becomes 0 and exits to menu

                // Validate the chosen menu choice exists
                if ( (stockMenuChoice >= 0 && stockMenuChoice <= NUM_OF_CARS) ) { // NUM_OF_CARS being used here to represent the greatest ID that can be selected
                    inputValid = 1;
                } else {
                    pressEnterPrompt("Selection invalid, press enter to try again\n");
                }
            } while (inputValid == 0);

            // Reset inputValid for future use
            inputValid = 0;

            // Reduce stockMenuChoice by 1 so that it now lines up with the array indexes
            stockMenuChoice--;

            // Display user's choice and price based on menu choice
            // Check chosen car has stock greater than zero
            if (carStock[stockMenuChoice] > 0 && stockMenuChoice != -1) {
                displayCarChoice(carMakes[stockMenuChoice],carModels[stockMenuChoice]);
                checkDiscountDisplayPrices(discountAnswer, carPrices[stockMenuChoice]);
                pressEnterPrompt("Press Enter to purchase");

                // Adjust stock level and amount of car sold
                carStock[stockMenuChoice] -= 1;
                amountOfCarSold[stockMenuChoice] += 1;

                // Add spend to running total, discounted or not as applicable
                if (discountAnswer == 'y') {
                    totalSpend += carPrices[stockMenuChoice]*(1-DISCOUNT_AMOUNT);
                    amountDiscounted += carPrices[stockMenuChoice]*DISCOUNT_AMOUNT;
                    valueOfCarSold[stockMenuChoice] += carPrices[stockMenuChoice]*(1-DISCOUNT_AMOUNT);
                } else {
                    totalSpend += carPrices[stockMenuChoice];
                    valueOfCarSold[stockMenuChoice] += carPrices[stockMenuChoice];
                }

                // Add car name to array
                strcpy(carsPurchased[arrayPosition],carMakes[stockMenuChoice]);
                strcat(carsPurchased[arrayPosition]," ");
                strcat(carsPurchased[arrayPosition],carModels[stockMenuChoice]);

                // Add customer name to array, with "Discounted" flag if applicable
                strcpy(whoPurchased[arrayPosition], userName);
                if (discountAnswer == 'y') {
                    strcat(whoPurchased[arrayPosition], " (Discounted)");
                }
                // Add customer age to array
                agePurchased[arrayPosition] = userAge;

                // Add purchase date/time to array
                time_t timeNow = time(NULL);
                strftime(datePurchased[arrayPosition], 20, "%Y-%m-%d %H:%M:%S", localtime(&timeNow));

                // Recalculate total stock level
                carStockTotal = sumOfArray(carStock, NUM_OF_CARS);

                // Increment position in sales record arrays
                arrayPosition += 1;

                pressEnterPrompt("\n\nPurchase successful!\nPress enter to return to the menu...");
            } else if ( stockMenuChoice == -1 ) { // user selected option 0 (return to menu) before variable was reduced by 1 to -1
                // Do nothing, just return to menu
            } else { // User has inputted an invalid choice, or their chosen choice is out of stock
                printf("Selection invalid. Reason: ");

                if (carStock[stockMenuChoice] <= 0) {
                    printf("Chosen vehicle is out of stock.\n");
                } else if (stockMenuChoice < 0 || stockMenuChoice > NUM_OF_CARS) {
                    printf("Chosen ID does not exist.\n");
                }

                pressEnterPrompt("Press enter to return to the menu and try again...");
            }


        } else if (mainMenuChoice == MAIN_MENU_ENABLE_DISCOUNT) {
            // Enable discount
            clearConsole();
            printf("Do you have a loyalty card? Y/N\n");
            scanf("\n%c", &discountAnswer);
            discountAnswer = tolower(discountAnswer);

            if (discountAnswer == 'y') {
                pressEnterPrompt("\nThank you, discount applied!\nPress enter to return to the menu...");
                inputValid = 1;
            } else {
                pressEnterPrompt("\nNo discount applied. Press enter to return to the menu...");
            }

        } else if (mainMenuChoice == MAIN_MENU_NAME) {
            // Change customer name
            do {
                clearConsole();
                printf("Please enter the new customer name: \n");
                getchar();
                fgets(userName, 50, stdin);
                // todo failing the first entry and then entering a name cuts the first char

                // Check if user provides an empty string. Remove newline character if input is valid
                if (userName[0] != '\0' && userName[0] != '\n') {
                    userName[strlen(userName)-1]='\0'; // remove newline character
                    inputValid = 1;
                } else {
                    pressEnterPrompt("\nInvalid input, press enter to return to try again...");
                }
            } while (inputValid == 0);
            // Reset inputValid for future use
            inputValid = 0;

            // New user age
            userAge = captureUserAge();
            pressEnterPrompt("\nName and age changed, press enter to return to menu...");

            // Reset discount upon new customer name
            discountAnswer = 'n';

        } else if (mainMenuChoice == MAIN_MENU_RECORD_FEEDBACK) {
            clearConsole();
            /* Check if username is in whoPurchased list
               If not, fail validation and send back to main menu to purchase
               Begin by calculating the total amount of cars sold thus far, so we only have to loop the
               whoPurchased array a minimal amount of times. */
            int totalCarsSold = 0;
            for (int i = 0; i < NUM_OF_CARS; i++) {
                totalCarsSold += amountOfCarSold[i];
            }

            // Check if current username exists in whoPurchased
            for (int i = 0; i < totalCarsSold; i++) {
                char alternativeUserName[50];
                strcpy(alternativeUserName, userName);
                strcat(alternativeUserName, " (Discounted)"); // Check for regular username or username plus ' (Discounted)'
                if (strcmp(userName, whoPurchased[i]) == 0 || strcmp(alternativeUserName, whoPurchased[i]) == 0) {
                    inputValid = 1;
                }
            }

            if (inputValid == 1) {
                FILE* myFile;
                // Initially open the file in read mode to check if it is empty or not
                myFile = fopen("customer_feedback.csv", "r");

                // Check if file is empty or not and open as appropriate
                int nextChar = fgetc(myFile);
                if (nextChar == EOF) {
                    // File is empty, open in write mode and add heading rows
                    myFile = fopen("customer_feedback.csv", "w");
                    char headings[40] = {"Name,Rating,Feedback,Car Purchased\n"};
                    fprintf(myFile, "%s", headings); // Header row
                } else {
                    // File already contains data, open in append mode
                    myFile = fopen("customer_feedback.csv", "a");
                }

                if (myFile != NULL) {
                    char userRating[2];
                    short userRatingShort;
                    inputValid = 0;
                    do {
                        clearConsole();
                        // Instructions to user
                        printf("We invite you to leave feedback about your purchase.\n"
                               "Please first leave a rating 1-5\n"
                               "Rating (1-5): ");
                        getchar();
                        validateCheck = scanf("%hd", &userRatingShort);
                        if (userRatingShort >= 1 && userRatingShort <= 5 && validateCheck == 1) {
                            inputValid = 1;
                        } else {
                            pressEnterPrompt("Please enter a rating between 1 and 5. Press enter to try again...\n");
                        }
                    } while (inputValid == 0);
                    // reset inputValid for future use
                    inputValid = 0;

                    printf("\nThank you. Please enter a short comment about your purchase experience. "
                           "Press enter once you have finished.\n\n"
                           "Feedback: ");
                    itoa(userRatingShort,userRating, 10);

                    char userFeedback[2001];
                    // Capture the input
                    getchar();
                    fgets(userFeedback, 2000, stdin);
                    userFeedback[strlen(userFeedback)-1]='\0'; // remove newline character

                    // Loop name string to check and replace commas
                    char stringClean = 'n';
                    do {
                        for (int i = 0; i < sizeof(userName) / sizeof(userName[0]); i++) {
                            if (userName[i] == ',') {
                                for (int j = i; j < (sizeof(userName) / sizeof(userName[0])) - 1; j++) {
                                    userName[j] = userName[j + 1];
                                }
                            }
                            userName[(sizeof(userName) / sizeof(userName[0])) - 1] = '\0';
                        }
                        // check
                        if (strchr(userName, ',') == NULL) { // userName doesn't contain a comma
                            stringClean = 'y';
                        }
                    } while (stringClean == 'n');
                    // Reset stringClean for future use
                    stringClean = 'n';

                    // Loop user feedback string to check and replace commas
                    do {
                        for (int i = 0; i < sizeof(userFeedback) / sizeof(userFeedback[0]); i++) {
                            if (userFeedback[i] == ',') {
                                for (int j = i; j < (sizeof(userFeedback) / sizeof(userFeedback[0])) - 1; j++) {
                                    userFeedback[j] = userFeedback[j + 1];
                                }
                            }
                            userFeedback[(sizeof(userFeedback) / sizeof(userFeedback[0])) - 1] = '\0';
                        }
                        // check
                        if (strchr(userFeedback, ',') == NULL) { // userName doesn't contain a comma
                            stringClean = 'y';
                        }
                    } while (stringClean == 'n');

                    // Check if any of the required data is missing, if so skip writing the file and return an error
                    if (userFeedback[0] != '\0' && userName[0] != '\0' /*&& userRating[0] != '\0'*/ ) { // the 3 parts of the feedback row are present
                        // String to store concatenated username and user feedback into a single row
                        char fullFeedbackRow[2110];
                        strcpy(fullFeedbackRow, userName);
                        strcat(fullFeedbackRow,",");
                        strcat(fullFeedbackRow, userRating);
                        strcat(fullFeedbackRow,",");
                        strcat(fullFeedbackRow, userFeedback);
                        strcat(fullFeedbackRow,",");
                        strcat(fullFeedbackRow, carsPurchased[arrayPosition-1]); // Most recently purchased car

                        // Write feedback row to file
                        fprintf(myFile, "%s\n", fullFeedbackRow);

                        // Close the file
                        fclose(myFile);
                        pressEnterPrompt("Thank you for your valued feedback! Press enter to return to the main menu...");
                    } else {
                        fclose(myFile);
                        pressEnterPrompt("Part of your submission is empty, please try again later. Press enter to return to the main menu...\n");
                    }
                } else {
                    printf("File cannot be read/created\n");
                    printf( "Error code opening file: %d\n", errno );
                    printf( "Error opening file: %s\n", strerror( errno ) );
                    pressEnterPrompt("Return to menu...");
                }

            } else {
                pressEnterPrompt("Please first purchase a car before leaving feedback. Press enter to return to the main menu...");
            }

            // Reset inputValid for future use
            inputValid = 0;

        } else if (mainMenuChoice == MAIN_MENU_VIEW_DATA_EXIT) {
            // Sort car arrays by total sale amount (descending)
            for (int i = 0; i < NUM_OF_CARS - 1; i++) {
                for (int j = 0; j < NUM_OF_CARS - 1 - i; j++) {
                    // Compare adjacent elements
                    if (amountOfCarSold[j] < amountOfCarSold[j+1]) { // Criteria to sort all arrays by - Amount of car sold (descending)

                        // Car Makes
                        char tempCarString[MAX_CAR_STR_LEN];
                        strcpy(tempCarString, carMakes[j]);
                        strcpy(carMakes[j], carMakes[j+1]);
                        strcpy(carMakes[j+1], tempCarString);

                        // Car Models
                        strcpy(tempCarString, carModels[j]);
                        strcpy(carModels[j], carModels[j+1]);
                        strcpy(carModels[j+1], tempCarString);

                        // Car Prices
                        double tempPriceVariable = carPrices[j];
                        carPrices[j] = carPrices[j+1];
                        carPrices[j+1] = tempPriceVariable;

                        // Car Years
                        int tempYearVariable = carYears[j];
                        carYears[j] = carYears[j+1];
                        carYears[j+1] = tempYearVariable;

                        // Car Stock
                        short tempCarStock = carStock[j];
                        carStock[j] = carStock[j+1];
                        carStock[j+1] = tempCarStock;

                        // Initial Order (to revert before writing the file)
                        short tempInitialOrder = initialOrder[j];
                        initialOrder[j] = initialOrder[j+1];
                        initialOrder[j+1] = tempInitialOrder;

                        // Amount of car sold
                        short tempAmountSold = amountOfCarSold[j];
                        amountOfCarSold[j] = amountOfCarSold[j+1];
                        amountOfCarSold[j+1] = tempAmountSold;

                        // Value of car sold
                        double tempValueSold = valueOfCarSold[j];
                        valueOfCarSold[j] = valueOfCarSold[j+1];
                        valueOfCarSold[j+1] = tempValueSold;
                    }
                }
            }
            clearConsole();
            printf("Transaction Breakdown:\n\n");
            for (int i = 0; i < arrayPosition; i++) {
                printf("%i. %s (%hd)\n%s\n%s\n\n", i+1, whoPurchased[i], agePurchased[i], datePurchased[i], carsPurchased[i]);
            }
            // Display financial summary
            printf("________________________________\n");
            printf("FINANCIAL SUMMARY\n");

            // Per car summary
            for (int i=0; i < NUM_OF_CARS; i++) {
                if (amountOfCarSold[i] > 0 ) {
                    printf("%s %s\n", carMakes[i], carModels[i]);
                    printf("%hd Sold / £%.2f Total\n\n",amountOfCarSold[i],valueOfCarSold[i]);
                }
            }

            // Display financial total
            purchaseReceipt(totalSpend, amountDiscounted);
            do {
                printf("Press 1 to return to the main menu or 0 to view remaining stock and exit: ");
                getchar();
                validateCheck = scanf("%hd", &mainMenuChoice);
                printf("\n");

                if (mainMenuChoice == MAIN_MENU_VIEW_DATA_EXIT && validateCheck == 1) {
                    finished = 1; // Satisfies criteria to exit the while loop
                    inputValid = 1;
                } else if (mainMenuChoice == 1) {
                    finished = 0;
                    inputValid = 1;
                } else {
                    pressEnterPrompt("Invalid input, please enter 1 or 0 only. Press enter to try again...\n\n");
                }
            } while (inputValid == 0);
        } else {
            // invalid input
            printf("Invalid input, please try again");
        }
    }

    // Display message if all stock is zero
    if (carStockTotal == 0 ) {
        printf("\nWe have no more stock. Please come back later.\n");
    } else { // Stock isn't 0
        printf("Our remaining stock is:\n");
    }

    // Re-display the stock menu once the user is finished or sum of stock is 0
    displayStockTable(carMakes, carModels, carYears, carPrices, carStock, NUM_OF_CARS, finished);
    pressEnterPrompt("\nPress enter to exit...");

    // Write/update sales data to file
    // Revert sort order to the initial declared order so that order of cars in the file is always consistent
    for (int i = 0; i < NUM_OF_CARS - 1; i++) {
        for (int j = 0; j < NUM_OF_CARS - 1 - i; j++) {
            // Compare adjacent elements
            if (initialOrder[j] > initialOrder[j+1]) { // Criteria to sort all arrays by - Initial Order (ascending)

                // Car Makes
                char tempCarString[MAX_CAR_STR_LEN];
                strcpy(tempCarString, carMakes[j]);
                strcpy(carMakes[j], carMakes[j+1]);
                strcpy(carMakes[j+1], tempCarString);

                // Car Models
                strcpy(tempCarString, carModels[j]);
                strcpy(carModels[j], carModels[j+1]);
                strcpy(carModels[j+1], tempCarString);

                // Car Prices
                double tempPriceVariable = carPrices[j];
                carPrices[j] = carPrices[j+1];
                carPrices[j+1] = tempPriceVariable;

                // Car Years
                int tempYearVariable = carYears[j];
                carYears[j] = carYears[j+1];
                carYears[j+1] = tempYearVariable;

                // Car Stock
                short tempCarStock = carStock[j];
                carStock[j] = carStock[j+1];
                carStock[j+1] = tempCarStock;

                // Initial Order (to revert before writing the file)
                short tempInitialOrder = initialOrder[j];
                initialOrder[j] = initialOrder[j+1];
                initialOrder[j+1] = tempInitialOrder;

                // Amount of car sold
                short tempAmountSold = amountOfCarSold[j];
                amountOfCarSold[j] = amountOfCarSold[j+1];
                amountOfCarSold[j+1] = tempAmountSold;

                // Value of car sold
                double tempValueSold = valueOfCarSold[j];
                valueOfCarSold[j] = valueOfCarSold[j+1];
                valueOfCarSold[j+1] = tempValueSold;
            }
        }
    }

    FILE* salesDataFile;
    // Initially open the file in read mode to check if it is empty or not

    salesDataFile = fopen("sales_data.csv", "r");

    // Check if file is empty or not and open as appropriate
    int nextChar = fgetc(salesDataFile);
    if (nextChar != -1) {
        // File already contains data, proceed with tokenization and merging file values to program variables
        char row[MAXCHAR];
        char *fileMake, *fileModel, *fileAmountSold, *fileValueSold;
        short shortAmountSold;
        double doubleValueSold;

        for (int i = 0; i < (NUM_OF_CARS + 1); i++) {
            // Read the row
            fgets(row, MAXCHAR, salesDataFile);

            // Tokenization
            fileMake = strtok(row, ",");
            fileModel = strtok(NULL, ",");
            fileAmountSold = strtok(NULL, ",");
            fileValueSold = strtok(NULL, ",");

            if (i > 0) { // if i = 0 then it's the header row so skip merging
                shortAmountSold = atoi(fileAmountSold);
                doubleValueSold = atof(fileValueSold);

                amountOfCarSold[i-1] += (short)shortAmountSold;
                valueOfCarSold[i-1] += doubleValueSold;
            }
        }
    }

    salesDataFile = fopen("sales_data.csv", "w");
    // Header row
    fprintf(salesDataFile,"Make,Model,Amount Sold,Total Value\n");

    for (int i=0; i < NUM_OF_CARS; i++) {
        fprintf(salesDataFile, "%s,%s,%hd,%.2f\n",carMakes[i],carModels[i],amountOfCarSold[i], valueOfCarSold[i]);
    }

    fclose(salesDataFile);

    return 0;
}