//
// Created by harry on 27/11/2023.
//

// #define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
// Adds getchar() function
#include <conio.h>
// Windows header for SetConsoleOutput
#include <Windows.h>
// String Functions
#include <string.h>

#define DISCOUNT_AMOUNT 0.2

void displayMainMenu(char currentUserName[50], char discountApplied, short userAge) {
    // Initial welcome message and listing stock
    printf("Welcome to Harry's Wholesale Automotive!\n\n");
    printf("Customer: %s (%hd)\n", currentUserName, userAge);
    printf("Discount Applied: ");

    if (discountApplied == 'y') {
        printf("Yes");
    } else {
        printf("No");
    }

    // Print main menu
    printf("\n\nPlease select from one of the following options\n\n");
    printf("ID|Menu Option\n");
    printf(" 1|View car stock & purchase\n");
    printf(" 2|Enable discount\n");
    printf(" 3|Change customer's name\n");
    printf(" 4|Record customer feedback\n");
    printf(" 0|View Sales Data/Exit\n");
}

short calcMaxStringLength(unsigned short numOfItems, char stringArray[][25]) {
    short stringMaxLength = 0;
    for (int i = 0; i < numOfItems; i++) {
        if (strlen(stringArray[i]) > stringMaxLength) {
            stringMaxLength = (short)(strlen(stringArray[i]));
        }
    }

    // Add 1 additional space to allow for the minimum 1 space added to the header title
    stringMaxLength += 1;
    return stringMaxLength;
}

void displayStockTable(char carMakes[][25], char carModels[][25], int carYears[], double carPrices[], short carStock[], unsigned short numOfCars, short isFinished) {
    // Car Makes
    short carMakesMaxLength = calcMaxStringLength(numOfCars, carMakes);

    // Car Models
    short carModelsMaxLength = calcMaxStringLength(numOfCars, carModels);

    // Price
    unsigned int carPriceMaxValue = 0;
    unsigned short carPriceDigits = 0;

    // Calculate largest price
    for (int i = 0; i < numOfCars; i++) {
        if (carPrices[i] > carPriceMaxValue) {
            carPriceMaxValue = (int)(carPrices[i]);
        }
    }

    // Calculate number of digits in largest value
    unsigned int carPriceMaxValueDiv = carPriceMaxValue;
    do {
        carPriceMaxValueDiv /= 10;
        carPriceDigits += 1;
    } while (carPriceMaxValueDiv > 0);

    // Add 1 additional space to allow for the minimum 1 space added to the header title
    carPriceDigits += 1;

    // Stock
    unsigned int carStockMaxValue = 0;
    unsigned short carStockDigits = 0;

    // Calculate largest stock digits
    for (int i = 0; i < numOfCars; i++) {
        if (carStock[i] > carStockMaxValue) {
            carStockMaxValue = carStock[i];
        }
    }

    // Calculate number of digits in largest value
    unsigned int carStockMaxValueDiv = carStockMaxValue;
    do {
        carStockMaxValueDiv /= 10;
        carStockDigits += 1;
    } while (carStockMaxValueDiv > 0);

    // Add 1 additional space to allow for the minimum 1 space added to the header title
    carStockDigits += 1;

    // Ensure carStockDigits is not lower than 6 to not be narrower than "Stock " heading
    if (carStockDigits < 6) {
        carStockDigits = 6;
    }

    // Header Row
    printf("ID");
    printf("|Make");
    printf("%*c", carMakesMaxLength - 4, ' ');
    printf("|Model");
    printf("%*c", carModelsMaxLength - 5, ' ');
    printf("|Year ");
    printf("|Price");
    printf("%*c", carPriceDigits - 1, ' ');
    printf("|Stock");
    printf("%*c", carStockDigits - 5, ' ');
    printf("|\n");

    printf("%.*s\n", carMakesMaxLength + carModelsMaxLength + carPriceDigits + carStockDigits + 17, "======================================================================");

    for (int i = 0; i < numOfCars; i++) {
        printf(" %i", i+1);
        printf("|");
        printf("%s", carMakes[i]);
        printf("%*c", (int)(carMakesMaxLength - strlen(carMakes[i])), ' ');
        printf("|");
        printf("%s", carModels[i]);
        printf("%*c", (int)(carModelsMaxLength - strlen(carModels[i])), ' ');
        printf("|");
        printf("%i |", carYears[i]);
        printf("£%.2f", carPrices[i]);
        char int_string[10];
        printf("%*c", (int)(carPriceDigits - strlen(itoa((int)carPrices[i],int_string,10))), ' ');
        printf("|");
        printf("%hi", carStock[i]);
        char int_string_2[10];
        printf("%*c", (int)(carStockDigits - strlen(itoa(carStock[i],int_string_2,10))), ' ');
        printf("|\n");
    }

    // Print exit to menu row (if not already exiting)
    if (isFinished != 1) {
        printf(" 0|");
        printf("%*c", (carMakesMaxLength + carModelsMaxLength + carPriceDigits + carStockDigits - 6) / 2, ' ');
        printf("RETURN TO MAIN MENU");
        printf("%*c", (carMakesMaxLength + carModelsMaxLength + carPriceDigits + carStockDigits - 5) / 2, ' ');
        printf("|");
    }
}

void purchaseReceipt(double totalValue, double amountDiscounted) {
    // Calculate and display total spend
    printf("Total Revenue: £%.2f\n", totalValue);
    if (amountDiscounted > 0 ) {
        printf("(Amount Discounted: £%.2f)\n", amountDiscounted);
    }
    printf("________________________________\n\n");
}

void displayCarChoice(char *carMake, char *carModel) {
    printf("You chose: ");
    printf("%s %s\n",carMake, carModel);
}

void checkDiscountDisplayPrices(char applyDiscount, double carPrice) {
    // Check if discount should be applied
    if (applyDiscount == 'y') {
        printf("Discount Applied!\n\n");
        printf("RRP: £%.2f\n", carPrice);
        printf("Discount: £%.2f\n", carPrice*0.2);
        printf("Your Price: £%.2f\n\n", carPrice*0.8);
    } else {
        printf("Price: £%.2f\n", carPrice);
    }
}

void pressEnterPrompt(char message[200]) {
    // Prompt user for input to confirm purchase
    printf("%s", message);
    _getch();
}

int sumOfArray(short arrayToSum[], unsigned short numberOfElement) {
    int sum = 0;
    for (int i = 0; i < numberOfElement; i++) {
        sum += arrayToSum[i];
    }
    return sum;
}

void clearConsole() {
    system("cls");
}

short captureUserAge() {
    while (1) {
        short capturedUserAge;
        int validateCheck;
        printf("\nPlease enter your age: ");
        validateCheck = scanf("%hd", &capturedUserAge);
        if (capturedUserAge >= 17 && validateCheck == 1) {
            return capturedUserAge;
        } else if (validateCheck == 0) {
            getchar();
            printf("Invalid input, please enter a number. Press enter to try again..");
        } else {
            pressEnterPrompt("Sorry, you must be at least 17 years old to purchase a car. Press enter to exit...\n");
            exit(0);
        }
    }

    /*// from here
    short enteredUserAge;
    short ageValid = 0;
    int validateResult = 0;
    do {
        printf("\nPlease enter your age: ");
        // getchar();
        validateResult = scanf("%hd", &enteredUserAge);
        if (enteredUserAge >= 17 && validateResult == 1) {
            ageValid = 1;
            return enteredUserAge;
        } else if (validateResult != 1) {
            printf("Please enter a numerical value. Press enter to try again\n");
            break;
        } else {

        }
    } while (ageValid == 0 || validateResult == 0);*/
}