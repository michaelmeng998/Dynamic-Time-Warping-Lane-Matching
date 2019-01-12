#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>

using namespace std;

void PrintMatrix(vector<vector<double>> Matrix)
{
    for (vector<double> x : Matrix)
    {
        for (double y : x)
        {
            cout << y << "    |    ";
        }
        cout << endl
             << endl;
    }
}

vector<vector<double>> BottomMatrix(vector<vector<double>> Matrix, int row_size, int num_of_rows)
{

    for (int a = 1; a <= row_size; a++)
    {

        if (a >= 2)
        {
            Matrix[num_of_rows - 1][a] = abs(Matrix[num_of_rows - 1][0] - Matrix[num_of_rows][a]) + Matrix[num_of_rows - 1][a - 1];
        }
        else
        {
            Matrix[num_of_rows - 1][a] = abs(Matrix[num_of_rows - 1][0] - Matrix[num_of_rows][a]);
        }
    }

    return Matrix;
}

vector<vector<double>> LeftMatrix(vector<vector<double>> Matrix, int row_size, int num_of_rows)
{

    for (int a = num_of_rows - 2; a >= 0; a--)
    {
        Matrix[a][1] = abs(Matrix[a][0] - Matrix[num_of_rows][1]) + Matrix[a + 1][1];
    }

    return Matrix;
}

vector<vector<double>> FillMatrix(vector<vector<double>> Matrix, int row_size, int num_of_rows)
{
    double Lowest, Left, Bottom, LeftBottom = 0;

    for (int a = num_of_rows - 2; a >= 0; a--)
    {

        for (int b = 2; b <= row_size; b++)
        {
            Matrix[a][b] = abs(Matrix[num_of_rows][b] - Matrix[a][0]);
            Left = Matrix[a][b - 1];
            Bottom = Matrix[a + 1][b];
            LeftBottom = Matrix[a + 1][b - 1];

            Lowest = Left;

            if (Bottom < Lowest)
            {
                Lowest = Bottom;
            }
            if (LeftBottom < Lowest)
            {
                Lowest = LeftBottom;
            }
            Matrix[a][b] += Lowest;
        }
    }

    return Matrix;
}

vector<vector<double>> MatrixRecursion(vector<vector<double>> Matrix, int row_size, int num_of_rows, int row, int column)
{

    int rowflag = num_of_rows - 1;
    int columnflag = 0;

    if (row != rowflag && column != columnflag)
    {
        double Left, Bottom, LeftBottom, Lowest = 0;
        Left = Matrix[row][column - 1];
        Bottom = Matrix[row + 1][column];
        LeftBottom = Matrix[row + 1][column - 1];

        Lowest = Left;

        if (Bottom == Lowest)
        {
            if ((Bottom == LeftBottom) || (Bottom > LeftBottom))
            {

                Lowest = LeftBottom;
            }
            if (Bottom < LeftBottom)
            {

                Lowest = Bottom;
            }
        }
        else if (LeftBottom == Lowest)
        {
            if (LeftBottom > Bottom)
            {
                Lowest = Bottom;
            }
            if (LeftBottom < Bottom)
            {

                Lowest = LeftBottom;
            }
        }
        else if (LeftBottom == Bottom)
        {
            if (LeftBottom < Lowest)
            {
                Lowest = LeftBottom;
            }
        }

        if (Bottom < Lowest)
        {
            Lowest = Bottom;
        }
        if (LeftBottom < Lowest)
        {
            Lowest = LeftBottom;
        }

        if (Lowest == LeftBottom)
        {
            Matrix[row + 1][column - 1] = Matrix[row + 1][column - 1] * -1;
            return MatrixRecursion(Matrix, row_size, num_of_rows, row + 1, column - 1);
        }
        else if (Lowest == Bottom)
        {
            Matrix[row + 1][column] = Matrix[row + 1][column] * -1;
            return MatrixRecursion(Matrix, row_size, num_of_rows, row + 1, column);
        }
        else
        {
            Matrix[row][column - 1] = Matrix[row][column - 1] * -1;
            return MatrixRecursion(Matrix, row_size, num_of_rows, row, column - 1);
        }
    }
    else
    {
        Matrix[0][row_size] = Matrix[0][row_size] * -1;
        return Matrix;
    }
}

vector<vector<double>> MatrixTraverse(vector<vector<double>> Matrix, int row_size, int num_of_rows, int row, int column, vector<vector<double>> WarpPointsVector)
{

    vector<double> WarpPoint;

    int rowflag = num_of_rows - 1;
    int columnflag = 0;

    if (row != rowflag && column != columnflag)
    {
        double Left, Bottom, LeftBottom, Lowest = 0;
        Left = Matrix[row][column - 1];
        Bottom = Matrix[row + 1][column];
        LeftBottom = Matrix[row + 1][column - 1];

        Lowest = Left;

        //first few conditions are checking for when have pairs or all indexes equal to each other
        if (Bottom == Lowest)
        {
            //first case if for when all are equal
            if ((Bottom == LeftBottom) || (Bottom > LeftBottom))
            {
                Lowest = LeftBottom;
            }
            if (Bottom < LeftBottom)
            {
                Lowest = Bottom;
            }
        }
        else if (LeftBottom == Lowest)
        {
            if (LeftBottom > Bottom)
            {
                Lowest = Bottom;
            }
            if (LeftBottom < Bottom)
            {
                Lowest = LeftBottom;
            }
        }
        else if (LeftBottom == Bottom)
        {
            if (LeftBottom < Lowest)
            {
                Lowest = LeftBottom;
            }
        }

        //these last two ifs are for when they are different
        if (Bottom < Lowest)
        {
            Lowest = Bottom;
        }
        if (LeftBottom < Lowest)
        {
            Lowest = LeftBottom;
        }

        if (Lowest == LeftBottom)
        {

            Matrix[row + 1][column - 1] = Matrix[row + 1][column - 1] * -1;
            WarpPoint.push_back(Matrix[num_of_rows][column - 1]);
            WarpPoint.push_back(column - 1);
            WarpPoint.push_back(Matrix[row + 1][0]);
            WarpPoint.push_back(abs(row - num_of_rows) - 1);
            WarpPointsVector.push_back(WarpPoint);

            /*cout << endl
                 << "leftbottom: "
                 << " y1: " << WarpPoint[0] << " , "
                 << "  y2: " << WarpPoint[1] << " x1: " << WarpPoint[2] << "  x2: " << WarpPoint[3] << endl;*/

            return MatrixTraverse(Matrix, row_size, num_of_rows, row + 1, column - 1, WarpPointsVector);
        }
        else if (Lowest == Bottom)
        {
            Matrix[row + 1][column] = Matrix[row + 1][column] * -1;
            WarpPoint.push_back(Matrix[num_of_rows][column]);
            WarpPoint.push_back(column);
            WarpPoint.push_back(Matrix[row + 1][0]);
            WarpPoint.push_back(abs(row - num_of_rows) - 1);

            WarpPointsVector.push_back(WarpPoint);
            /*cout << endl
                 << "Bottom: "
                 << " x1: " << WarpPoint[0] << " , "
                 << " x2: " << WarpPoint[1] << " y1: " << WarpPoint[2] << " y2: " << WarpPoint[3] << endl;*/
            return MatrixTraverse(Matrix, row_size, num_of_rows, row + 1, column, WarpPointsVector);
        }
        else
        {

            Matrix[row][column - 1] = Matrix[row][column - 1] * -1;
            WarpPoint.push_back(Matrix[num_of_rows][column - 1]);
            WarpPoint.push_back(column - 1);
            WarpPoint.push_back(Matrix[row][0]);
            WarpPoint.push_back(abs(row - num_of_rows));

            WarpPointsVector.push_back(WarpPoint);
            /* cout << endl
                 << "left: "
                 << " y1: " << WarpPoint[0] << " , "
                 << "  y2: " << WarpPoint[1] << " x1: " << WarpPoint[2] << " x2: " << WarpPoint[3] << endl;*/
            return MatrixTraverse(Matrix, row_size, num_of_rows, row, column - 1, WarpPointsVector);
        }
    }
    else
    {
        return WarpPointsVector;
    }
}

vector<vector<double>> NewPointsCalculation(vector<vector<double>> WarpPointsVector, vector<vector<double>> MatchedPolynomialPoints, int WarpVectorIndex)
{
    //first determine how many points there are. Take the first two points with correspondance, and find midpoint, then recurse

    double new_x_point = 0;
    double new_y_point = 0;

    vector<double> NewPointsVector;

    if (WarpVectorIndex < WarpPointsVector.size())
    {
        new_x_point = (WarpPointsVector[WarpVectorIndex][0] + WarpPointsVector[WarpVectorIndex][2]) / 2;
        new_y_point = (WarpPointsVector[WarpVectorIndex][1] + WarpPointsVector[WarpVectorIndex][3]) / 2;
        NewPointsVector.push_back(new_x_point);
        NewPointsVector.push_back(new_y_point);
        MatchedPolynomialPoints.push_back(NewPointsVector);
        return NewPointsCalculation(WarpPointsVector, MatchedPolynomialPoints, WarpVectorIndex + 1);
    }
    else
    {
        return MatchedPolynomialPoints;
    }
}

vector<vector<double>> MatrixCreate(vector<double> SeriesA, vector<double> SeriesB)
{
    vector<vector<double>> WarpPointsVector;
    vector<double> WarpPointInitial;
    vector<vector<double>> NewMatchedPoints;

    int temp = 0;
    int row_size = SeriesB.size();
    int num_of_rows = SeriesA.size();
    vector<double> row(row_size + 1, 0);
    vector<vector<double>> Matrix(num_of_rows + 1, row);

    cout << endl
         << endl
         << "Number of rows is: " << num_of_rows << endl
         << "Number of columns is: " << row_size << endl;

    for (double x : SeriesB)
    {
        Matrix[num_of_rows][temp + 1] = x;
        temp += 1;
    }

    for (int a = num_of_rows; a >= 1; a--)
    {
        Matrix[a - 1][0] = SeriesA[num_of_rows - a];
    }

    Matrix = BottomMatrix(Matrix, row_size, num_of_rows);

    Matrix = LeftMatrix(Matrix, row_size, num_of_rows);

    Matrix = FillMatrix(Matrix, row_size, num_of_rows);

    //initialpushback

    WarpPointInitial.push_back(Matrix[num_of_rows][row_size]);
    WarpPointInitial.push_back(row_size);
    WarpPointInitial.push_back(Matrix[0][0]);
    WarpPointInitial.push_back(num_of_rows);
    WarpPointsVector.push_back(WarpPointInitial);

    WarpPointsVector = MatrixTraverse(Matrix, row_size, num_of_rows, 0, row_size, WarpPointsVector);

    cout << endl;
    Matrix = MatrixRecursion(Matrix, row_size, num_of_rows, 0, row_size);

    NewMatchedPoints = NewPointsCalculation(WarpPointsVector, NewMatchedPoints, 0);

    int MatchedPointsSize = NewMatchedPoints.size();

    cout << endl
         << "NEW MATCHED POINTS!: " << endl;

    for (int i = 0; i < MatchedPointsSize - 1; i++)
    {
        cout << "x: " << NewMatchedPoints[i][0] << "  and y: " << NewMatchedPoints[i][1] << endl;
    }

    cout << endl
         << "Matched Lane Points List Format:" << endl;
    for (vector<double> x : NewMatchedPoints)
    {
        for (double y : x)
        {
            cout << y << "  ";
        }
        cout << endl;
    }

    cout << endl;

    cout << endl
         << "Matrix Visualizer (Negative Represents Optimal Matrix Traversal Path): " << endl
         << "The left column represents series A and the bottom row represents Series B, the 0 at the bottom left is a placeholder"
         << endl
         << endl
         << endl
         << endl;

    PrintMatrix(Matrix);

    return Matrix;
}

int main()
{
    vector<vector<double>> Matrix;

    //vector<double> SeriesA(5, 1);
    //vector<double> SeriesB(5, 2);

    //test case from youtube video used for algorithm development
    vector<double> SeriesA{1, 3, 4, 9, 8, 2, 1, 5, 7, 3};
    vector<double> SeriesB{1, 6, 2, 3, 0, 9, 4, 3, 6, 3};

    //vector<double> SeriesA{5, 5, 6, 6, 5, 4, 4, 5, 6, 6, 4, 5};
    //vector<double> SeriesB{2, 2, 2, 2, 3, 3, 1, 3, 4, 1, 2, 2};

    //vector<double> SeriesA{1, 1, 3, 1, 2, 1, 1};
    //vector<double> SeriesB{1, 3, 1, 2, 1, 1, 1};

    cout << "series A is: ";
    for (double x : SeriesA)
    {
        cout << x << " ";
    }
    cout << endl;
    cout << "series B is: ";
    for (double y : SeriesB)
    {
        cout << y << " ";
    }

    Matrix = MatrixCreate(SeriesA, SeriesB);

    return 0;
}
