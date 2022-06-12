#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXENTRIES 2500

struct entry {
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

void printEntry(int i) {
    printf("\n");
    printf("Date (m-d-y):           %d-%d-%d\n", dataBase[i].year, dataBase[i].month, dataBase[i].day);
    printf("Put/Call Ratio:         %lf\n", dataBase[i].pcRatio);
    printf("Put Volume:             %d\n", dataBase[i].pVol);
    printf("Call Volume:            %d\n", dataBase[i].cVol);
    printf("Total Volume:           %d\n\n", dataBase[i].totVol);
}

void fscanDataBase(void) {
    unsigned int t_year;
    unsigned int t_month;
    unsigned int t_day;
    double t_pcRatio;
    unsigned int t_pVol;
    unsigned int t_cVol;
    unsigned int t_totVol;
    char headerStr[120];

    FILE* dbPtr;
    if ((dbPtr = fopen("SPY241Project.txt", "r")) == NULL) {
        puts("File could not be opened");
    }
    else {
        currentEntries = 0;
        fgets(headerStr, 112, dbPtr);           //absorb first line
        while (!feof(dbPtr)) {
            fscanf(dbPtr, "%d/%d/%d,%lf,%d,%d,%d\n",
                &t_month,
                &t_day,
                &t_year,
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

int maxCall(int year1, int month1, int day1, int year2, int month2, int day2) {         //assumes cleaned data, date1 comes before date2
    int i, date1 = 0, date2 = 0, maxCall = 0, maxCallIndex = 0;
    date1 = dateIndex(year1, month1, day1);
    date2 = dateIndex(year2, month2, day2);

    for (i = date1; i <= date2; i++) {
        if (dataBase[i].cVol > maxCall) {
            maxCall = dataBase[i].cVol;
            maxCallIndex = i;
        }
    }
    return maxCallIndex;
}

int minCall(int year1, int month1, int day1, int year2, int month2, int day2) {         //assumes cleaned data, date1 comes before date2
    int i, date1 = 0, date2 = 0, minCall = 1000000, minCallIndex = 0;
    date1 = dateIndex(year1, month1, day1);
    date2 = dateIndex(year2, month2, day2);

    for (i = date1; i <= date2; i++) {
        if (dataBase[i].cVol < minCall) {
            minCall = dataBase[i].cVol;
            minCallIndex = i;
        }
    }
    return minCallIndex;
}

int maxPut(int year1, int month1, int day1, int year2, int month2, int day2) {         //assumes cleaned data, date1 comes before date2
    int i, date1 = 0, date2 = 0, maxPut = 0, maxPutIndex = 0;
    date1 = dateIndex(year1, month1, day1);
    date2 = dateIndex(year2, month2, day2);

    for (i = date1; i <= date2; i++) {
        if (dataBase[i].pVol > maxPut) {
            maxPut = dataBase[i].pVol;
            maxPutIndex = i;
        }
    }
    return maxPutIndex;
}

int minPut(int year1, int month1, int day1, int year2, int month2, int day2) {         //assumes cleaned data, date1 comes before date2
    int i, date1 = 0, date2 = 0, minPut = 1000000, minPutIndex = 0;
    date1 = dateIndex(year1, month1, day1);
    date2 = dateIndex(year2, month2, day2);

    for (i = date1; i <= date2; i++) {
        if (dataBase[i].cVol < minPut) {
            minPut = dataBase[i].pVol;
            minPutIndex = i;
        }
    }
    return minPutIndex;
}

int dateIndex(int year, int month, int day) {
    int i, date = -1;
    for (i = 0; i < currentEntries; i++) {
        if (year == dataBase[i].year && month == dataBase[i].month && day == dataBase[i].day) {
            date = i;
        }
    }
    return date;
}

int timeFrameBullBear(int year1, int month1, int day1, int year2, int month2, int day2) {
    int i, date1, date2;
    double pcRatioSum = 0, pcRatioAvg;
    date1 = dateIndex(year1, month1, day1);
    date2 = dateIndex(year2, month2, day2);

    for (i = date1; i <= date2; i++) {
        pcRatioSum += dataBase[i].pcRatio;
    }

    pcRatioAvg = (pcRatioSum / ((date2 - date1) + 1));
    printf("Average ratio across timeframe: %.2lf\n", pcRatioAvg);
    if (pcRatioAvg >= 1) return 1;                   //1 if bull
    else return 0;                                  //0 if bear
}

int timeFrameBullBearIndex(int date1, int date2) {
    int i;
    double pcRatioSum = 0, pcRatioAvg;

    for (i = date1; i <= date2; i++) {
        pcRatioSum += dataBase[i].pcRatio;
    }

    pcRatioAvg = (pcRatioSum / ((date2 - date1) + 1));
    printf("%d/%d: Avg. Put/Call Ratio: %.2lf, B/B: ", dataBase[date1].month, dataBase[date1].year, pcRatioAvg);

    if (pcRatioAvg >= 1) return 1;                   //1 if bull
    else return 0;                                   //0 if bear
}

void monthTabular(int month) {
    int startMonthIndex = 0, endMonthIndex = 0, index = 0, result = 0;;
    int nextFlag = 1;
    while (index != currentEntries) {
        if (nextFlag) {
            nextFlag = 0;
            while (dataBase[index].month != month)
                index++;
            startMonthIndex = index ;
        }

        while (dataBase[index].month == month)
            index++;
        endMonthIndex = index - 1;

        result = timeFrameBullBearIndex(startMonthIndex, endMonthIndex);

        printf("%d\n", result);

        nextFlag = 1;
    }
}

int main()
{
    fscanDataBase();
    printf("%d\n", timeFrameBullBear(10, 7, 15, 10, 7, 19));
    monthTabular(7);        // Gives the stats for a specific month out of every year available

    return 0;
}