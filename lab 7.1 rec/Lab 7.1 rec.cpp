#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std;

void Create(int** t, const int rowCount, const int colCount, const int Low, const int High, int i, int j);
void Print(int** t, const int rowCount, const int colCount, int i, int j);
void Change(int** t, const int row1, const int row2, const int colCount, int j);
void Sort(int** t, const int rowCount, const int colCount, int i0, int i1);
void Calc(int** t, const int rowCount, const int colCount, int& S, int& k, int i, int j);

int main()
{
    srand((unsigned)time(NULL));
    int Low = -17;
    int High = 14;
    int rowCount = 8;
    int colCount = 5;
    int** t = new int* [rowCount];
    for (int i = 0; i < rowCount; i++)
        t[i] = new int[colCount];

    Create(t, rowCount, colCount, Low, High, 0, 0);
    Print(t, rowCount, colCount, 0, 0);

    int row1 = 2; // Example row1
    int row2 = 5; // Example row2
    Change(t, row1, row2, colCount, 0);

    Sort(t, rowCount, colCount, 0, 0);
    Print(t, rowCount, colCount, 0, 0);

    int S = 0;
    int k = 0;
    Calc(t, rowCount, colCount, S, k, 0, 0);
    cout << "S = " << S << endl;
    cout << "k = " << k << endl;
    Print(t, rowCount, colCount, 0, 0);
    for (int i = 0; i < rowCount; i++)
        delete[] t[i];
    delete[] t;

    return 0;
}

void Create(int** t, const int rowCount, const int colCount, const int Low, const int High, int i, int j)
{
    if (i < rowCount)
    {
        if (j < colCount)
        {
            t[i][j] = Low + rand() % (High - Low + 1);
            Create(t, rowCount, colCount, Low, High, i, j + 1);
        }
        else
        {
            Create(t, rowCount, colCount, Low, High, i + 1, 0);
        }
    }
}

void Print(int** t, const int rowCount, const int colCount, int i, int j)
{
    if (i < rowCount)
    {
        if (j < colCount)
        {
            cout << setw(4) << t[i][j];
            Print(t, rowCount, colCount, i, j + 1);
        }
        else
        {
            cout << endl;
            Print(t, rowCount, colCount, i + 1, 0);
        }
    }
    else
    {
        cout << endl;
    }
}

void Change(int** t, const int row1, const int row2, const int colCount, int j)
{
    if (j < colCount)
    {
        int tmp = t[row1][j];
        t[row1][j] = t[row2][j];
        t[row2][j] = tmp;
        Change(t, row1, row2, colCount, j + 1);
    }
}

void Sort(int** t, const int rowCount, const int colCount, int i0, int i1)
{
    if (i0 < rowCount - 1)
    {
        if (i1 < rowCount - i0 - 1)
        {
            if ((t[i1][0] > t[i1 + 1][0])
                ||
                (t[i1][0] == t[i1 + 1][0] &&
                    t[i1][1] > t[i1 + 1][1])
                ||
                (t[i1][0] == t[i1 + 1][0] &&
                    t[i1][1] == t[i1 + 1][1] &&
                    t[i1][3] > t[i1 + 1][3]))
            {
                Change(t, i1, i1 + 1, colCount, 0);
            }
            Sort(t, rowCount, colCount, i0, i1 + 1);
        }
        Sort(t, rowCount, colCount, i0 + 1, 0);
    }
}

void Calc(int** t, const int rowCount, const int colCount, int& S, int& k, int i, int j)
{
    if (i < rowCount)
    {
        if (j < colCount)
        {
            if (t[i][j] < 0 && !(t[i][j] % 4 == 0))
            {
                S += t[i][j];
                k++;
                t[i][j] = 0;
            }
            Calc(t, rowCount, colCount, S, k, i, j + 1);
        }
        Calc(t, rowCount, colCount, S, k, i + 1, 0);
    }
}