#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXENTRIES 2500

struct entry{
    unsigned int year;
    unsigned int month;
    unsigned int day;
    double       pcRatio;
    unsigned int pVol;
    unsigned int cVol;
    unsigned int totVol;
};
struct entry dataBase[MAXENTRIES];
int currentEntries = 0;

void printEntry(int i){
    printf("\n");
    printf("Date:                   %d-%d-%d\n", dataBase[i].year, dataBase[i].month, dataBase[i].day);
    printf("Put/Call Ratio:         %lf\n", dataBase[i].pcRatio);
    printf("Put Volume:             %d\n", dataBase[i].pVol);
    printf("Call Volume:            %d\n", dataBase[i].cVol);
    printf("Total Volume:           %d\n\n", dataBase[i].totVol);
}

void fscanDataBase(void){
    unsigned int t_year;
    unsigned int t_month;
    unsigned int t_day;
    double t_pcRatio;
    unsigned int t_pVol;
    unsigned int t_cVol;
    unsigned int t_totVol;
    char headerStr[120];

    FILE *dbPtr;
    if ((dbPtr = fopen("SPY241Project.txt", "r")) == NULL){
        puts("File could not be opened");
    }
    else{
        currentEntries = 0;
        fgets(headerStr, 112, dbPtr);           //absorb first line
        while(!feof(dbPtr)){
            fscanf(dbPtr, "%d/%d/%d,%lf,%d,%d,%d\n",
                                            &t_year,
                                            &t_month,
                                            &t_day,
                                            &t_pcRatio,
                                            &t_pVol,
                                            &t_cVol,
                                            &t_totVol);

            dataBase[currentEntries].year = t_year;
            dataBase[currentEntries].month = t_month;
            dataBase[currentEntries].day = t_day;
            dataBase[currentEntries].pcRatio = t_pcRatio;
            dataBase[currentEntries].pVol = t_pVol;
            dataBase[currentEntries].cVol = t_cVol;
            dataBase[currentEntries].totVol = t_totVol;

            //printEntry(currentEntries);
            currentEntries++;
        }
        printf("\nDatabase scanned in!\nNumber of Entries: %d\n", currentEntries);
        fclose(dbPtr);
    }
}

int main()
{
    fscanDataBase();
    printEntry(187);
    return 0;
}
