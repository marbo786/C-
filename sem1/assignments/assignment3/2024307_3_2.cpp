#include <iostream>
using namespace std;
#include <cmath>

int display()
{
    int k = -1;

    do
    {
        cout << "1. Identify the type of matrix (square, scaler, diagonal, identity).\n";
        cout << "2. Identify the order of matrix.\n";
        cout << "3. Find transpose of a matrix.\n";
        cout << "4. Find adjoint of a matrix.\n";
        cout << "5. Find inverse of a matrix.\n";
        cout << "6. Multiply two matrices.\n";
        cout << "7. Quit program.\n";

        cout << "Enter the serial number of operation to perform. Or press 7 to quit.\n";
        cin >> k;
    } while (!(k <= 7 && k >= 1));
    return k;
}

void matrixCreation(double m[], int r, int c)
{

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cout << "Please enter element at (" << i + 1 << ", " << j + 1 << "):\n";
            cin >> m[i * c + j];
        }
    }
}

bool zeroMatrix(double m[], int r, int c)
{
    bool flag = true;
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            if (m[i * c + j])
            {
                flag = false;
                break;
            }
        }
        if (!flag)
            break;
    }
    return flag;
}

int diagonalMatrix(double m[], int r, int c)
{
    if (r != c)
        return 0;
    bool flag = true;
    double arr[r];
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            if (i == j)
                arr[i] = m[i * c + j];
            else
            {
                if (m[i * c + j])
                {
                    flag = false;
                    break;
                }
            }
        }
        if (!flag)
            break;
    }
    if (flag)
    {
        bool flag2 = true;
        for (int i = 0; i < r - 1; i++)
        {
            if (arr[i] != arr[i + 1])
            {
                flag2 = false;
                break;
            }
        }
        if (!flag2)
            return 1;
        else
        {
            if (arr[0] == 1)
                return 2;
            else
                return 3;
        }
    }
    else
        return 0;
}

bool squareMatrix(double m[], int r, int c)
{

    if (r == c)
        return true;
    return false;
}

void checkMatrixType(double m[], int r, int c)
{
    if (zeroMatrix(m, r, c))
        cout << "Zero Matrix.\n\n";
    else if (int k = diagonalMatrix(m, r, c))
    {
        if (k == 1)
            cout << "Diagonal Matrix,\n\n";
        else if (k == 2)
            cout << "Identity Matrix.\n\n";
        else
            cout << "Scaler Matrix.\n\n";
    }
    else if (squareMatrix(m, r, c))
        cout << "Square Matrix.\n\n";
    else
        cout << "None of the specified types.\n\n";
}

void checkMatrixOrder(double m[], int r, int c)
{
    cout << r << "x" << c << endl
         << endl;
}

void calculateMatrixTranspose(double m[], int r, int c)
{

    double temp[r][c];
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            temp[i][j] = m[i * c + j];
        }
    }

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            m[i * c + j] = temp[j][i];
        }
    }

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cout << m[i * c + j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void calculateMatrixAdjoint(double *m, int r, int c)
{

    if (r == 2)
    {
        cout << m[3] << " " << -m[1] << endl;
        cout << -m[2] << " " << m[0] << endl;
        cout << endl;
    }
    else
    {
        cout << (m[4] * m[8] - m[5] * m[7]) << " "
             << -(m[3] * m[8] - m[5] * m[6]) << " "
             << (m[3] * m[7] - m[4] * m[6]) << endl;

        cout << -(m[1] * m[8] - m[2] * m[7]) << " "
             << (m[0] * m[8] - m[2] * m[6]) << " "
             << -(m[0] * m[7] - m[1] * m[6]) << endl;

        cout << (m[1] * m[5] - m[2] * m[4]) << " "
             << -(m[0] * m[5] - m[2] * m[3]) << " "
             << (m[0] * m[4] - m[1] * m[3]) << endl;
        cout << endl;
    }
}

void calculateMatrixInverse(double *m, int r, int c)
{
    if (r == 2)
    {

        double det = m[0] * m[3] - m[1] * m[2];
        if (fabs(det) < 1e-9)
            cout << "Singular Matrix; determinant is zero.\n";
        else
        {
            det = 1 / det;

            cout << det * m[3] << " " << det * -m[1] << endl;
            cout << det * -m[2] << " " << det * m[0] << endl;
            cout << endl;
        }
    }
    else
    {
        double det = m[0] * (m[4] * m[8] - m[5] * m[7]) - m[1] * (m[3] * m[8] - m[5] * m[6]) + m[2] * (m[3] * m[7] - m[4] * m[6]);

        if (fabs(det) < 1e-9)
            cout << "Singular Matrix; determinant is zero.\n";
        else
        {
            det = 1 / det;
            cout << det * (m[4] * m[8] - m[5] * m[7]) << " "
                 << det * -(m[3] * m[8] - m[5] * m[6]) << " "
                 << det * (m[3] * m[7] - m[4] * m[6]) << endl;

            cout << det * -(m[1] * m[8] - m[2] * m[7]) << " "
                 << det * (m[0] * m[8] - m[2] * m[6]) << " "
                 << det * -(m[0] * m[7] - m[1] * m[6]) << endl;

            cout << det * (m[1] * m[5] - m[2] * m[4]) << " "
                 << det * -(m[0] * m[5] - m[2] * m[3]) << " "
                 << det * (m[0] * m[4] - m[1] * m[3]) << endl;
        }
    }
}

void multiplyMatrices(double m1[], double m2[], int r1, int c1, int r2, int c2)
{

    if (c1 != r2)
        cout << "Multiplicaiton not possible. Invalid matrix orders.\n";
    else
    {
        double ans[r1][c2];
        for (int i = 0; i < r1; i++)
        {
            for (int j = 0; j < c2; j++)
            {
                ans[i][j] = 0;
                for (int k = 0; k < c1; k++)
                {
                    ans[i][j] += (m1[i * c1 + k] * m2[k * c2 + j]);
                }
            }
        }

        for (int i = 0; i < r1; i++)
        {
            for (int j = 0; j < c2; j++)
            {
                cout << ans[i][j] << " ";
            }
            cout << endl;
        }
    }
}

bool ask()
{

    int k = -1;
    do
    {
        cout << "Press 0 to use the previous (or default) matrix. Press 1 to define a matrix.\n";
        cin >> k;
        if (k != 0 || k != 1)
            cout << "Invalid keypress.\n";
    } while (k != 0 && k != 1);

    return k;
}

int main()
{

    // double m1[] = {1, 2, 3, 4, 5, 6};
    // double m2[] = {1, 2, 3, 4, 5, 6};
    // multiplyMatrices(m1, m2, 3, 2, 2, 3);
    int choice;
    double m1[100];
    double m2[100];

    for (int i = 0; i < 100; i++)
    {
        m1[i] = i + 1;
        m2[i] = i + 1;
    }

    int r = 10, c = 10, r2 = 10, c2 = 10;

    do
    {

        choice = display();
        switch (choice)
        {
        case 1:

            if (ask())
            {
                cout << "Enter row and column count.\n";
                cin >> r >> c;
                matrixCreation(m1, r, c);
            }
            checkMatrixType(m1, r, c);
            break;

        case 2:
            if (ask())
            {
                cout << "Enter row and column count.\n";
                cin >> r >> c;
                matrixCreation(m1, r, c);
            }
            checkMatrixOrder(m1, r, c);
            break;
        case 3:
            if (ask())
            {
                cout << "Enter row and column count.\n";
                cin >> r >> c;
                matrixCreation(m1, r, c);
            }
            calculateMatrixTranspose(m1, r, c);
            break;
        case 4:
            if (ask())
            {
                cout << "Enter row and column count.\n";
                cin >> r >> c;
                matrixCreation(m1, r, c);
            }
            if (r != c || r > 3 || r < 2)
                cout << "Invalid matrix order.\n";
            else
                calculateMatrixAdjoint(m1, r, c);
            break;
        case 5:
            if (ask())
            {
                cout << "Enter row and column count.\n";
                cin >> r >> c;
                matrixCreation(m1, r, c);
            }
            if (r != c || r > 3 || r < 2)
                cout << "Invalid matrix order.\n";
            else
                calculateMatrixInverse(m1, r, c);

            break;
        case 6:
            if (ask())
            {
                cout << "Enter row and column count for first matrix.\n";
                cin >> r >> c;
                matrixCreation(m1, r, c);
                cout << "Enter row and column count for second matrix.\n";
                cin >> r2 >> c2;
                matrixCreation(m2, r2, c2);
            }

            multiplyMatrices(m1, m2, r, c, r2, c2);
            break;

        default:
            break;
        }

    } while (choice != 7);

    return 0;
}