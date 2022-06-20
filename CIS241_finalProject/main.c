#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//authors: Owen Gibson, Seth Gibson, Jaiden Ortiz
//Professor: Vijay Bhuse
//date: 6/19/2022
//title:CIS241_finalproject
//description: this program is designed to read a file containing SPY options
//data, and use that data to draw conclusion such as bull/bear trend of a
//given time range

#define MAXENTRIES 2500


//Struct to partition each entry into
//the resptive members
//year: year of entry
//month: month of entry
//day: day of entry
//pcRatio: put/call ratio of entry
//pVol: put volume of entry
//cVol: call volume of entry
//totVol: total options volume of entry
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

//Formats output of each member of a particular object in dataBase[]
//i: index of object to be displayed
void printEntry(int i)
{
    printf("\n");
    printf("Date (m-d-y):           %d-%d-%d\n", dataBase[i].year, dataBase[i].month, dataBase[i].day);
    printf("Put/Call Ratio:         %lf\n", dataBase[i].pcRatio);
    printf("Put Volume:             %d\n", dataBase[i].pVol);
    printf("Call Volume:            %d\n", dataBase[i].cVol);
    printf("Total Volume:           %d\n\n", dataBase[i].totVol);
}

//assigns each member of each object in dataBase[]
//using format specifiers in fscanf if file
//can be opened succesfully
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
        printf("Earliest Entry: %d/%d/%d\n", dataBase[0].month, dataBase[0].day, dataBase[0].year);
        printf("Latest Entry: %d/%d/%d\n", dataBase[currentEntries - 1].month, dataBase[currentEntries - 1].day, dataBase[currentEntries - 1].year);
        fclose(dbPtr);
    }
}

//Uses call volume (cVol) of each object in dataBase[] to find
//index of maximum call volume in time range
//year1: year of first date
//month1: month of first date
//day1: day of first date
//year2: year of second date
//month2: month of second date
//day2: day of second date
//return: maxCallIndex
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

//Uses call volume (cVol) of each object in dataBase[] to find
//index of minimum call volume in time range
//year1: year of first date
//month1: month of first date
//day1: day of first date
//year2: year of second date
//month2: month of second date
//day2: day of second date
//return: maxCallIndex
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

//Uses put volume (pVol) of each object in dataBase[] to find
//index of maximum call volume in time range
//year1: year of first date
//month1: month of first date
//day1: day of first date
//year2: year of second date
//month2: month of second date
//day2: day of second date
//return: maxPutIndex
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

//Uses put volume (pVol) of each object in dataBase[] to find
//index of minimum call volume in time range
//year1: year of first date
//month1: month of first date
//day1: day of first date
//year2: year of second date
//month2: month of second date
//day2: day of second date
//return: maxPutIndex
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

//Helper function that returns index of particular date in dataBase[]
//year: year of date to be indexed
//month: month of date to be indexed
//day: day of date to be indexed
//return: date
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

//Calculates average put/call ratio over time range
//given put/call ratio of each object in given time range
//year1: year of first date
//month1: month of first date
//day1: day of first date
//year2: year of second date
//month2: month of second date
//day2: day of second date
//return: 1 if bullish
//return: 2 0 iif bearish
int timeFrameBullBear(int year1, int month1, int day1, int year2, int month2, int day2)
{
    int i, date1, date2;
    double pcRatioSum = 0, pcRatioAvg;
    date1 = dateIndex(year1, month1, day1);
    date2 = dateIndex(year2, month2, day2);

    if(date1 == -1 || date2 == -1){
        printf("Please enter valid date.\n");
        return -1;
    }

    for (i = date1; i <= date2; i++)
    {
        pcRatioSum += dataBase[i].pcRatio;
    }

    pcRatioAvg = (pcRatioSum / ((date2 - date1) + 1));
    printf("Average ratio across timeframe: %.2lf\n", pcRatioAvg);
    if (pcRatioAvg >= 1) return 1;                   //1 if bull
    else return 0;                                  //0 if bear
}

//Calculates average put/call ratio over time range
//given put/call ratio of each object in given time range
//year1: year of first date
//date1: index of first date
//date2: index of second date
//return: 1 if bullish
//return: 2 0 iif bearish
int timeFrameBullBearIndex(int date1, int date2)
{
    int i;
    double pcRatioSum = 0, pcRatioAvg;

    if((date1 > currentEntries) || (date1 < 0) || (date2 > currentEntries) || (date2 < 0)){
        return -1;
    }

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

//finds first and last instance of given month and calls
//timeFrameBullBearIndex to calculate whether trend was bearish
//or bullish across the entered month
//month: integer representing particular month of year
void monthTabular(int month)
{
    int startMonthIndex = 0, endMonthIndex = 0, index = 0, result = 0;
    int nextFlag = 1;

    if(month > 12 || month < 1){
        printf("Please enter a valid quarter.\n");
        return;
    }

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

        printf("%s\n", result ? "Bull" : "Bear");

        nextFlag = 1;
        if((endMonthIndex + 250) > currentEntries) break;
    }
}

//finds first (monthMin) and last instance (monthMax) of given quarter and calls
//timeFrameBullBearIndex to calculate whether trend was bearish
//or bullish across the entered quarter
//quarter: integer representing particular quarter of year
void quarterTabular(int quarter){
    //represent first, second, and third months of given quarter
    int monthMin, monthMid, monthMax;
    switch(quarter){ //assigns each variable to particular month index based on quarter
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

        printf("%s\n", result ? "Bull" : "Bear");

        nextFlag = 1;
        if((endMonthIndex + 250) > currentEntries) break;
    }
}

//Driver for functions based on menu option selection
int main()
{
    int userChoice = 0;
    int userYear1 = -1;
    int userDay1 = -1;
    int userMonth1 = -1;
    int userYear2 = -1;
    int userDay2 = -1;
    int userMonth2 = -1;
    int userQuarter = -1;

    fscanDataBase();

    while(userChoice != -1)
    {

        //Menu options
        puts("\n1. Highest Call Volume");
        puts("2. Lowest Call Volume");
        puts("3. Highest Put Volume");
        puts("4. Lowest Put Volume");
        puts("5. Put/Call Ratio");
        puts("6. Put/Call Ratio (Month)");
        puts("7. Put/Call Ratio (Quarter)\n");

        printf("Please enter option number (-1 to quit): ");
        scanf("%d", &userChoice);

        //Selecting menu option based on user choice
        switch (userChoice)
        {
        case 1:
            printf("Enter first year (Last two digits): ");
            scanf("%d", &userYear1);
            printf("Enter first month (numerically): ");
            scanf("%d", &userMonth1);
            printf("Enter first day of month: ");
            scanf("%d", &userDay1);

            printf("Enter second year (Last two digits): ");
            scanf("%d", &userYear2);
            printf("Enter second month (numerically): ");
            scanf("%d", &userMonth2);
            printf("Enter second day of month: ");
            scanf("%d", &userDay2);

            printf("Highest call volume during this time range was: %d\n",
                   dataBase[maxCall(userYear1, userMonth1, userDay1, userYear2, userMonth2, userDay2)].cVol);
            break;
        case 2:
            printf("Enter first year (Last two digits): ");
            scanf("%d", &userYear1);
            printf("Enter first month (numerically): ");
            scanf("%d", &userMonth1);
            printf("Enter first day of month: ");
            scanf("%d", &userDay1);

            printf("Enter second year (Last two digits): ");
            scanf("%d", &userYear2);
            printf("Enter second month (numerically): ");
            scanf("%d", &userMonth2);
            printf("Enter second day of month: ");
            scanf("%d", &userDay2);

            printf("Lowest call volume during this time range was: %d\n",
                   dataBase[minCall(userYear1, userMonth1, userDay1, userYear2, userMonth2, userDay2)].cVol);
            break;
        case 3:
            printf("Enter first year (Last two digits): ");
            scanf("%d", &userYear1);
            printf("Enter first month (numerically): ");
            scanf("%d", &userMonth1);
            printf("Enter first day of month: ");
            scanf("%d", &userDay1);

            printf("Enter second year (Last two digits): ");
            scanf("%d", &userYear2);
            printf("Enter second month (numerically): ");
            scanf("%d", &userMonth2);
            printf("Enter second day of month: ");
            scanf("%d", &userDay2);

            printf("Highest put volume during this time range was: %d\n",
                   dataBase[maxPut(userYear1, userMonth1, userDay1, userYear2, userMonth2, userDay2)].pVol);
            break;
        case 4:
            printf("Enter first year (Last two digits): ");
            scanf("%d", &userYear1);
            printf("Enter first month (numerically): ");
            scanf("%d", &userMonth1);
            printf("Enter first day of month: ");
            scanf("%d", &userDay1);

            printf("Enter second year (Last two digits): ");
            scanf("%d", &userYear2);
            printf("Enter second month (numerically): ");
            scanf("%d", &userMonth2);
            printf("Enter second day of month: ");
            scanf("%d", &userDay2);

            printf("Lowest put volume during this time range was: %d\n",
                   dataBase[minPut(userYear1, userMonth1, userDay1, userYear2, userMonth2, userDay2)].pVol);
            break;
        case 5:
            printf("Enter first year (Last two digits): ");
            scanf("%d", &userYear1);
            printf("Enter first month (numerically): ");
            scanf("%d", &userMonth1);
            printf("Enter first day of month: ");
            scanf("%d", &userDay1);

            printf("Enter second year (Last two digits): ");
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
        case 7:
            printf("Enter a quarter (numerically): ");
            scanf("%d", &userQuarter);
            quarterTabular(userQuarter);
            break;
        default:
            printf("Please enter a valid user input.\n");
        }


    }

//    puts("\nOLD STUFF");
//    printf("%d\n", timeFrameBullBear(10, 7, 15, 10, 7, 19));
//    monthTabular(7);        // Gives the stats for a specific month out of every year available

    return 0;
}
