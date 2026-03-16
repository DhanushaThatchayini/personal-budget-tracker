#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Transaction {
    char date[15];
    char type[50];
    float amount;
};

void addSalary();
void addFixedExpense();
void addDailyExpense();
void addIncome();
void showStatement();
void showBalance();
void showMonthlySummary();
void searchByDate();
void deleteTransaction();

void addSalary() {

    FILE *fp = fopen("transactions.dat", "ab");

    if (!fp) {
        printf("File could not be opened.\n");
        return;
    }

    struct Transaction t;

    printf("Enter the date (dd/mm/yyyy): ");
    scanf("%14s", t.date);

    strcpy(t.type, "Salary");

    printf("Enter the Salary Amount: ");
    scanf("%f", &t.amount);

    fwrite(&t, sizeof(t), 1, fp);
    fclose(fp);

    printf("Salary recorded successfully.\n");
}

void addFixedExpense() {

    FILE *fp = fopen("transactions.dat", "ab");

    if (!fp) {
        printf("File could not be opened.\n");
        return;
    }

    struct Transaction t;
    char choice;

    printf("Enter the date (dd/mm/yyyy): ");
    scanf("%14s", t.date);

    do {

        printf("Enter the category (Rent/EMI/Loan/Subscription/Other): ");
        scanf("%49s", t.type);

        printf("Enter the Amount spent: ");
        scanf("%f", &t.amount);

        t.amount = -t.amount;

        fwrite(&t, sizeof(t), 1, fp);

        printf("Add another fixed expense? (y/n): ");
        scanf(" %c", &choice);

    } while (choice == 'y' || choice == 'Y');

    fclose(fp);

    printf("Fixed expenses added successfully!\n");
}

void addDailyExpense() {

    FILE *fp = fopen("transactions.dat", "ab");

    if (!fp) {
        printf("File could not be opened.\n");
        return;
    }

    struct Transaction t;
    char choice;

    printf("Enter the date (dd/mm/yyyy): ");
    scanf("%14s", t.date);

    do {

        printf("Enter the category (Food/Travel/Other): ");
        scanf("%49s", t.type);

        printf("Enter the Amount spent: ");
        scanf("%f", &t.amount);

        t.amount = -t.amount;

        fwrite(&t, sizeof(t), 1, fp);

        printf("Add another daily expense? (y/n): ");
        scanf(" %c", &choice);

    } while (choice == 'y' || choice == 'Y');

    fclose(fp);

    printf("Daily expenses added successfully!\n");
}

void addIncome() {

    FILE *fp = fopen("transactions.dat", "ab");

    if (!fp) {
        printf("File could not be opened.\n");
        return;
    }

    struct Transaction t;
    char choice;

    printf("Enter the date (dd/mm/yyyy): ");
    scanf("%14s", t.date);

    do {

        printf("Enter income source (Bonus/Freelance/Other): ");
        scanf("%49s", t.type);

        printf("Enter the amount received: ");
        scanf("%f", &t.amount);

        fwrite(&t, sizeof(t), 1, fp);

        printf("Add another income? (y/n): ");
        scanf(" %c", &choice);

    } while (choice == 'y' || choice == 'Y');

    fclose(fp);

    printf("Income added successfully!\n");
}

void showStatement() {

    FILE *fp = fopen("transactions.dat", "rb");

    if (!fp) {
        printf("No records found.\n");
        return;
    }

    struct Transaction t;

    printf("\n===== ACCOUNT STATEMENT =====\n");
    printf("%-12s %-15s %-10s\n", "Date", "Category", "Amount");

    while (fread(&t, sizeof(t), 1, fp) == 1) {
        printf("%-12s %-15s %10.2f\n", t.date, t.type, t.amount);
    }

    fclose(fp);
}

void showBalance() {

    FILE *fp = fopen("transactions.dat", "rb");

    if (!fp) {
        printf("File not found.\n");
        return;
    }

    struct Transaction t;
    float balance = 0;

    while (fread(&t, sizeof(t), 1, fp) == 1) {
        balance += t.amount;
    }

    fclose(fp);

    printf("Current Balance: %.2f\n", balance);
}

void showMonthlySummary() {

    FILE *fp = fopen("transactions.dat", "rb");

    if (!fp) {
        printf("No records found.\n");
        return;
    }

    struct Transaction t;

    float totalIncome = 0;
    float totalExpense = 0;

    while (fread(&t, sizeof(t), 1, fp) == 1) {

        if (t.amount > 0)
            totalIncome += t.amount;
        else
            totalExpense += t.amount;
    }

    fclose(fp);

    printf("\n===== MONTHLY SUMMARY =====\n");
    printf("Total Income   : %.2f\n", totalIncome);
    printf("Total Expenses : %.2f\n", -totalExpense);
    printf("Total Savings  : %.2f\n", totalIncome + totalExpense);
}

void searchByDate() {

    FILE *fp = fopen("transactions.dat", "rb");

    if (!fp) {
        printf("No records found.\n");
        return;
    }

    char searchDate[15];
    struct Transaction t;
    int found = 0;

    printf("Enter date to search (dd/mm/yyyy): ");
    scanf("%14s", searchDate);

    printf("\nTransactions on %s:\n", searchDate);
    printf("%-12s %-15s %-10s\n", "Date", "Category", "Amount");

    while (fread(&t, sizeof(t), 1, fp) == 1) {

        if (strcmp(t.date, searchDate) == 0) {
            printf("%-12s %-15s %10.2f\n", t.date, t.type, t.amount);
            found = 1;
        }
    }

    if (!found) {
        printf("No transactions found for this date.\n");
    }

    fclose(fp);
}

void deleteTransaction() {

    FILE *fp, *temp;
    struct Transaction t;
    char deleteDate[15];
    int found = 0;

    fp = fopen("transactions.dat", "rb");

    if (!fp) {
        printf("No records found.\n");
        return;
    }

    temp = fopen("temp.dat", "wb");

    printf("Enter date to delete (dd/mm/yyyy): ");
    scanf("%14s", deleteDate);

    while (fread(&t, sizeof(t), 1, fp) == 1) {

        if (strcmp(t.date, deleteDate) != 0) {
            fwrite(&t, sizeof(t), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("transactions.dat");
    rename("temp.dat", "transactions.dat");

    if (found)
        printf("Transactions on %s deleted successfully.\n", deleteDate);
    else
        printf("No transactions found for this date.\n");
}

int main() {

    int choice;

    while (1) {

        printf("\n==== Personal Budget Tracker ====\n");
        printf("1. Add Salary\n");
        printf("2. Add Fixed Expense\n");
        printf("3. Add Daily Expense\n");
        printf("4. Add Extra Income\n");
        printf("5. Show Statement\n");
        printf("6. Show Current Balance\n");
        printf("7. Show Monthly Summary\n");
        printf("8. Search by Date\n");
        printf("9. Delete Transaction by Date\n");
        printf("10. Exit\n");

        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1: addSalary(); break;
            case 2: addFixedExpense(); break;
            case 3: addDailyExpense(); break;
            case 4: addIncome(); break;
            case 5: showStatement(); break;
            case 6: showBalance(); break;
            case 7: showMonthlySummary(); break;
            case 8: searchByDate(); break;
            case 9: deleteTransaction(); break;

            case 10:
                printf("Exiting program...\n");
                exit(0);

            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}