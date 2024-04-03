//
// Created by harry on 27/11/2023.
//

#ifndef HARRYSCARSALES_HARRYCARSALES_H
#define HARRYSCARSALES_HARRYCARSALES_H

#define DISCOUNT_AMOUNT 0.2

extern void displayMainMenu(char currentUserName[50], char discountApplied, short userAge) ;

extern short calcMaxStringLength(unsigned short numOfItems, char stringArray[][25]);

extern void displayStockTable(char carMakes[][25], char carModels[][25], int carYears[], double carPrices[], short carStock[], unsigned short numOfCars, short isFinished);

extern void purchaseReceipt(double totalValue, double amountDiscounted);

extern void displayDiscountedPrice(double carPrice);

extern void displayCarChoice(char *carMake, char *carModel);

extern void checkDiscountDisplayPrices(char applyDiscount, double carPrice);

extern void pressEnterPrompt(char message[200]);

extern int sumOfArray(short arrayToSum[], unsigned short numberOfElement);

extern void clearConsole();

extern short captureUserAge();

#endif //HARRYSCARSALES_HARRYCARSALES_H
