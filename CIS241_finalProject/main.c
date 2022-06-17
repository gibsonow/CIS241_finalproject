#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXENTRIES 2500

struct entry
{
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

void printEntry(int i)
{
    printf("\n");
    printf("Date (m-d-y):           %d-%d-%d\n", dataBase[i].year, dataBase[i].month, dataBase[i].day);
    printf("Put/Call Ratio:         %lf\n", dataBase[i].pcRatio);
    printf("Put Volume:             %d\n", dataBase[i].pVol);
    printf("Call Volume:            %d\n", dataBase[i].cVol);
    printf("Total Volume:           %d\n\n", dataBase[i].totVol);
}

void fscanDataBase(void)
{
    unsigned int t_year;
    unsigned int t_month;
    unsigned int t_day;
    double t_pcRatio;
    unsigned int t_pVol;
    unsigned int t_cVol;
    unsigned int t_totVol;
    char headerStr[120];

    FILE* dbPtr;
    if ((dbPtr = fopen("SPY241Project.txt", "r")) == NULL)
    {
        puts("File could not be opened");
    }
    else
    {
        currentEntries = 0;
        fgets(headerStr, 112, dbPtr);           //absorb first line
        while (!feof(dbPtr))
        {
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

int maxCall(int year1, int month1, int day1, int year2, int month2, int day2)           //assumes cleaned data, date1 comes before date2
{
    int i, date1 = 0, date2 = 0, maxCall = 0, maxCallIndex = 0;
    date1 = dateIndex(year1, month1, day1);
    date2 = dateIndex(year2, month2, day2);

    for (i = date1; i <= date2; i++)
    {
        if (dataBase[i].cVol > maxCall)
        {
            maxCall = dataBase[i].cVol;
            maxCallIndex = i;
        }
    }
    return maxCallIndex;
}

int minCall(int year1, int month1, int day1, int year2, int month2, int day2)           //assumes cleaned data, date1 comes before date2
{
    int i, date1 = 0, date2 = 0, minCall = 1000000, minCallIndex = 0;
    date1 = dateIndex(year1, month1, day1);
    date2 = dateIndex(year2, month2, day2);

    for (i = date1; i <= date2; i++)
    {
        if (dataBase[i].cVol < minCall)
        {
            minCall = dataBase[i].cVol;
            minCallIndex = i;
        }
    }
    return minCallIndex;
}

int maxPut(int year1, int month1, int day1, int year2, int month2, int day2)           //assumes cleaned data, date1 comes before date2
{
    int i, date1 = 0, date2 = 0, maxPut = 0, maxPutIndex = 0;
    date1 = dateIndex(year1, month1, day1);
    date2 = dateIndex(year2, month2, day2);

    for (i = date1; i <= date2; i++)
    {
        if (dataBase[i].pVol > maxPut)
        {
            maxPut = dataBase[i].pVol;
            maxPutIndex = i;
        }
    }
    return maxPutIndex;
}

int minPut(int year1, int month1, int day1, int year2, int month2, int day2)           //assumes cleaned data, date1 comes before date2
{
    int i, date1 = 0, date2 = 0, minPut = 1000000, minPutIndex = 0;
    date1 = dateIndex(year1, month1, day1);
    date2 = dateIndex(year2, month2, day2);

    for (i = date1; i <= date2; i++)
    {
        if (dataBase[i].cVol < minPut)
        {
            minPut = dataBase[i].pVol;
            minPutIndex = i;
        }
    }
    return minPutIndex;
}

/*
* Helper function that returns database index (int) based on given day, month, and year
*/
int dateIndex(int year, int month, int day)
{
    int i, date = -1;
    for (i = 0; i < currentEntries; i++)
    {
        if (year == dataBase[i].year && month == dataBase[i].month && day == dataBase[i].day)
        {
            date = i;
        }
    }
    return date;
}

int timeFrameBullBear(int year1, int month1, int day1, int year2, int month2, int day2)
{
    int i, date1, date2;
    double pcRatioSum = 0, pcRatioAvg;
    date1 = dateIndex(year1, month1, day1);
    date2 = dateIndex(year2, month2, day2);

    for (i = date1; i <= date2; i++)
    {
        pcRatioSum += dataBase[i].pcRatio;
    }

    pcRatioAvg = (pcRatioSum / ((date2 - date1) + 1));
    printf("Average ratio across timeframe: %.2lf\n", pcRatioAvg);
    if (pcRatioAvg >= 1) return 1;                   //1 if bull
    else return 0;                                  //0 if bear
}

int timeFrameBullBearIndex(int date1, int date2)
{
    int i;
    double pcRatioSum = 0, pcRatioAvg;

    for (i = date1; i <= date2; i++)
    {
        pcRatioSum += dataBase[i].pcRatio;
    }

    pcRatioAvg = (pcRatioSum / ((date2 - date1) + 1));
    printf("%d/%d/%d - %d/%d/%d: Avg. Put/Call Ratio: %.2lf, B/B: ", dataBase[date1].month, dataBase[date1].day, dataBase[date1].year,
                                                                    dataBase[date2].month, dataBase[date2].day, dataBase[date2].year, pcRatioAvg);

    if (pcRatioAvg >= 1) return 1;                   //1 if bull
    else return 0;                                   //0 if bear
}

void monthTabular(int month)
{
    int startMonthIndex = 0, endMonthIndex = 0, index = 0, result = 0;
    int nextFlag = 1;
    while (index != currentEntries)
    {
        if (nextFlag)
        {
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
        if((endMonthIndex + 250) > currentEntries) break;
    }
}

void quarterTabular(int quarter){
    int monthMin, monthMid, monthMax;
    switch(quarter){
        case(1):
            monthMin = 1;
            monthMid = 2;
            monthMax = 3;
            break;
        case(2):
            monthMin = 4;
            monthMid = 5;
            monthMax = 6;
            break;
        case(3):
            monthMin = 7;
            monthMid = 8;
            monthMax = 9;
            break;
        case(4):
            monthMin = 10;
            monthMid = 11;
            monthMax = 12;
            break;
        default:
            printf("Please enter a valid quarter.\n");
            return;
    }

    int startMonthIndex = 0, endMonthIndex = 0, index = 0, result = 0;
    int nextFlag = 1;
    while (index != currentEntries) {
        if (nextFlag) {
            nextFlag = 0;
            while (dataBase[index].month != monthMin)
                index++;
            startMonthIndex = index ;
        }

        while (dataBase[index].month == monthMax || dataBase[index].month == monthMid || dataBase[index].month == monthMin)
            index++;
        endMonthIndex = index - 1;

        result = timeFrameBullBearIndex(startMonthIndex, endMonthIndex);

        printf("%d\n", result);

        nextFlag = 1;
        if((endMonthIndex + 250) > currentEntries) break;
    }
}

int main()
{
    int userChoice = 0;
    int userYear1 = -1;
    int userDay1 = -1;
    int userMonth1 = -1;
    int userYear2 = -1;
    int userDay2 = -1;
    int userMonth2 = -1;


    fscanDataBase();

    while(userChoice != -1)
    {

        //Menu options
        puts("\n1. Highest Call Volume");
        puts("2. Lowest Call Volume");
        puts("3. Highest Put Volume");
        puts("4. Lowest Put Volume");
        puts("5. Put/Call Ratio");
        puts("6. Put/Call Ratio (Month)\n");

        printf("Please enter option number (-1 to quit): ");
        scanf("%d", &userChoice);

        //Selecting menu option based on user choice
        switch (userChoice)
        {
        case 1:
            printf("Enter first year: ");
            scanf("%d", &userYear1);
            printf("Enter first month (numerically): ");
            scanf("%d", &userMonth1);
            printf("Enter first day of month: ");
            scanf("%d", &userDay1);

            printf("Enter second year: ");
            scanf("%d", &userYear2);
            printf("Enter second month (numerically): ");
            scanf("%d", &userMonth2);
            printf("Enter second day of month: ");
            scanf("%d", &userDay2);

            printf("Highest call volume during this time range was: %d", maxCall(userYear1, userMonth1, userDay1, userYear2, userMonth2, userDay2));
            break;
        case 2:
            printf("Enter first year: ");
            scanf("%d", &userYear1);
            printf("Enter first month (numerically): ");
            scanf("%d", &userMonth1);
            printf("Enter first day of month: ");
            scanf("%d", &userDay1);

            printf("Enter second year: ");
            scanf("%d", &userYear2);
            printf("Enter second month (numerically): ");
            scanf("%d", &userMonth2);
            printf("Enter second day of month: ");
            scanf("%d", &userDay2);

            printf("Lowest call volume during this time range was: %d", minCall(userYear1, userMonth1, userDay1, userYear2, userMonth2, userDay2));
            break;
        case 3:
            printf("Enter first year: ");
            scanf("%d", &userYear1);
            printf("Enter first month (numerically): ");
            scanf("%d", &userMonth1);
            printf("Enter first day of month: ");
            scanf("%d", &userDay1);

            printf("Enter second year: ");
            scanf("%d", &userYear2);
            printf("Enter second month (numerically): ");
            scanf("%d", &userMonth2);
            printf("Enter second day of month: ");
            scanf("%d", &userDay2);

            printf("Highest put volume during this time range was: %d", maxPut(userYear1, userMonth1, userDay1, userYear2, userMonth2, userDay2));
            break;
        case 4:
            printf("Enter first year: ");
            scanf("%d", &userYear1);
            printf("Enter first month (numerically): ");
            scanf("%d", &userMonth1);
            printf("Enter first day of month: ");
            scanf("%d", &userDay1);

            printf("Enter second year: ");
            scanf("%d", &userYear2);
            printf("Enter second month (numerically): ");
            scanf("%d", &userMonth2);
            printf("Enter second day of month: ");
            scanf("%d", &userDay2);

            printf("Lowest put volume during this time range was: %d", minPut(userYear1, userMonth1, userDay1, userYear2, userMonth2, userDay2));
            break;
        case 5:
            printf("Enter first year: ");
            scanf("%d", &userYear1);
            printf("Enter first month (numerically): ");
            scanf("%d", &userMonth1);
            printf("Enter first day of month: ");
            scanf("%d", &userDay1);

            printf("Enter second year: ");
            scanf("%d", &userYear2);
            printf("Enter second month (numerically): ");
            scanf("%d", &userMonth2);
            printf("Enter second day of month: ");
            scanf("%d", &userDay2);

            timeFrameBullBear(userYear1, userMonth1, userDay1, userYear2, userMonth2, userDay2) ? puts("This suggests a Bullish sentiment") :
            puts("This suggests a Bearish sentiment");
            break;
        case 6:
            printf("Enter a month (numerically): ");
            scanf("%d", &userMonth1);
            monthTabular(userMonth1);
            break;
        }


    }

    puts("\nOLD STUFF");
    printf("%d\n", timeFrameBullBear(10, 7, 15, 10, 7, 19));
    monthTabular(7);        // Gives the stats for a specific month out of every year available

    return 0;
}
