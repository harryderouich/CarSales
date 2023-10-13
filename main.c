#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
// Adds getchar() function
#include <conio.h>
// Windows header
#include <Windows.h>

// Function to display the menu containing stock levels and prices
void displayMenu(int priceOne, int priceTwo, int priceThree, int stockOne, int stockTwo, int stockThree) {
    printf("Our current stock is:\n");
    printf("1. BMW 1-Series. Price: £%d. Stock Level: %d\n", priceOne, stockOne);
    printf("2. Audi A3. Price £%d. Stock Level: %d\n", priceTwo, stockTwo);
    printf("3. Mercedes A-Class. Price £%d. Stock Level: %d\n", priceThree, stockThree);
}

void purchaseReceipt(char discounted, short totalValue) {
    printf("\nThank you for visiting\n");

    // Display cars purchased
    printf("\n________________________________\n");
    printf("SALES RECEIPT\n");

    // Calculate and display total spend
    printf("You Spent:\n");
    if (discounted == 'y' || discounted == 'Y') {
        printf("Total RRP: £%.0d\n", totalValue);
        printf("Total Saving: £%.0f\n", totalValue*0.2);
        printf("Your Total: £%.0f\n", totalValue*0.8);
    }
    else {
        printf("Total: £%.0hd\n", totalValue);
    }
    printf("________________________________\n");
}

void displayDiscountedPrice(int carPrice) {
    printf("Discount Applied!\n\n");
    printf("RRP: £%.0d\n", carPrice);
    printf("Discount: £%.0f\n", (int)carPrice*0.2);
    printf("Your Price: £%.0f\n\n", (int)carPrice*0.8);
}

int main() {

    // Set console to output UTF-8 characters (£)
    SetConsoleOutputCP(CP_UTF8);

    // Variables (changeable)
    short bmwStock = 3, audiStock = 2, mercStock = 1, userChoice, finished = 0, totalSpend = 0, purchaseCount = 0;

    // Constants (fixed)
    #define BMW_PRICE 10000
    #define AUDI_PRICE 12000
    #define MERC_PRICE 14000

    // Initial welcome message and listing stock
    printf("\nHello and welcome to Harry's Wholesale Automotive!\n");

    // Discount check
    printf("\nDo you have a loyalty card? Y/N\n");
    char discountAnswer;
    scanf("\n%c", &discountAnswer);

    // Loop the purchase system until stock is depleted or until the user has indicated they are finished
    while (finished != 1 && ( bmwStock + audiStock + mercStock > 0 )) {

        // Display the menu using a function
        displayMenu(BMW_PRICE, AUDI_PRICE, MERC_PRICE, bmwStock, audiStock, mercStock);

        // Prompt and user input
        printf("\nPlease enter the number of the car you wish to purchase: ");
        scanf("%hd", &userChoice);

        // Display user's choice and price
        if (userChoice == 1 && bmwStock > 0) {
            printf("You chose: ");
            printf("BMW 1-Series\n");

            // Check if discount should be applied
            if ( discountAnswer == 'y' || discountAnswer == 'Y') {
                displayDiscountedPrice(BMW_PRICE);
            } else {
                printf("Price: £%d\n", BMW_PRICE);
            }

            // Prompt user for input to confirm purchase
            printf("Press Enter to purchase");
            _getch();

            // Adjust stock level
            bmwStock -= 1;
            // Add spend to running total
            totalSpend += BMW_PRICE;

            printf("\nThank you for your purchase\n\n");

        } else if (userChoice == 2 && audiStock > 0) {
            printf("You chose: ");
            printf("Audi A3\n");

            // Check if discount should be applied
            if ( discountAnswer == 'y' || discountAnswer == 'Y') {
                displayDiscountedPrice(AUDI_PRICE);
            } else {
                printf("Price: £%d\n", AUDI_PRICE);
            }

            // Prompt user for input to confirm purchase
            printf("Press Enter to purchase");
            _getch();

            // Adjust stock level
            audiStock -= 1;
            // Add spend to running total
            totalSpend += AUDI_PRICE;

            printf("\nThank you for your purchase\n\n");

        } else if (userChoice == 3 && mercStock > 0) {
            printf("You chose: ");
            printf("Mercedes A-Class\n");

            // Check if discount should be applied
            if ( discountAnswer == 'y' || discountAnswer == 'Y') {
                displayDiscountedPrice(MERC_PRICE);
            } else {
                printf("Price: £%d\n", MERC_PRICE);
            }

            // Prompt user for input to confirm purchase
            printf("Press Enter to purchase");
            _getch();

            // Adjust stock level
            mercStock -= 1;
            // Add spend to running total
            totalSpend += MERC_PRICE;

            printf("\nThank you for your purchase\n\n");

        } else { // User has inputted an invalid choice, or their chosen choice is out of stock
            printf("Selection invalid, please try again.\n\n");
        }

        // User prompt to repeat or exit the loop
        printf("Press 1 to purchase another car or 0 to exit: ");

        int userInput;
        scanf("%d", &userInput);

        if (userInput == 0) {
            finished = 1; // Satisfies criteria to exit the while loop

            // Display Receipt
            purchaseReceipt( discountAnswer, totalSpend);


        }
    }

    // Re-display the menu once the user is finished or sum of stock is 0
    displayMenu(BMW_PRICE, AUDI_PRICE, MERC_PRICE, bmwStock, audiStock, mercStock);

    // Display additional message if all stock is zero
    if ( bmwStock + audiStock + mercStock <= 0 ) {
        printf("\nWe have no more stock. Please come back later.\n");
    }

    return 0;
}
