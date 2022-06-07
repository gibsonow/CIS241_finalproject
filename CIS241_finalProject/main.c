#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXENTRIES 2000

struct entry{
    unsigned int year;
    unsigned int month;
    unsigned int day;
    double SP500;
    double dividend;
    double earnings;
    double consumerPriceIndex;
    double longInterestRate;
    double realPrice;
    double realDividend;
    double realEarnings;
};
struct entry dataBase[MAXENTRIES];
int currentEntries = 0;

void printEntry(int i){
    printf("\n");
    printf("Date:                   %d-%d-%d\n", dataBase[i].year, dataBase[i].month, dataBase[i].day);
    printf("S&P500:                 %lf\n", dataBase[i].SP500);
    printf("Dividend:               %lf\n", dataBase[i].dividend);
    printf("Earnings:               %lf\n", dataBase[i].earnings);
    printf("Consumer Price Index:   %lf\n", dataBase[i].consumerPriceIndex);
    printf("Long Interest Rate:     %lf\n", dataBase[i].longInterestRate);
    printf("Real Price:             %lf\n", dataBase[i].realPrice);
    printf("Real Dividend:          %lf\n", dataBase[i].realDividend);
    printf("Real Earnings:          %lf\n\n", dataBase[i].realEarnings);
}

void fscanDataBase(void){
    unsigned int tyear;
    unsigned int tmonth;
    unsigned int tday;
    double tSP500;
    double tdividend;
    double tearnings;
    double tconsumerPriceIndex;
    double tlongInterestRate;
    double trealPrice;
    double trealDividend;
    double trealEarnings;
    char headerStr[120];

    FILE *dbPtr;
    if ((dbPtr = fopen("hardware.dat", "r")) == NULL){
        puts("File could not be opened");
    }
    else{
        currentEntries = 0;
        fgets(headerStr, 112, dbPtr);           //absorb first line
        while(!feof(dbPtr)){
            fscanf(dbPtr, "%d-%d-%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,\n",
                                            &tyear,
                                            &tmonth,
                                            &tday,
                                            &tSP500,
                                            &tdividend,
                                            &tearnings,
                                            &tconsumerPriceIndex,
                                            &tlongInterestRate,
                                            &trealPrice,
                                            &trealDividend,
                                            &trealEarnings);

            dataBase[currentEntries].year               = tyear              ;
            dataBase[currentEntries].month              = tmonth             ;
            dataBase[currentEntries].day                = tday               ;
            dataBase[currentEntries].SP500              = tSP500             ;
            dataBase[currentEntries].dividend           = tdividend          ;
            dataBase[currentEntries].earnings           = tearnings          ;
            dataBase[currentEntries].consumerPriceIndex = tconsumerPriceIndex;
            dataBase[currentEntries].longInterestRate   = tlongInterestRate  ;
            dataBase[currentEntries].realPrice          = trealPrice         ;
            dataBase[currentEntries].realDividend       = trealDividend      ;
            dataBase[currentEntries].realEarnings       = trealEarnings      ;

            printEntry(currentEntries);
            currentEntries++;
        }
        printf("\nDatabase scanned in!\nNumber of Entries: %d\n", currentEntries);
        fclose(dbPtr);
    }
}

int main()
{
    printf("Hello world!\n");
    return 0;
}
