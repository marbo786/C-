#include <iostream>
using namespace std;

struct UniverseCoordinate {
    int s_number;
    int x_position;
    int y_position;
    bool is_snake;
};


void freeMemory(UniverseCoordinate** universe, int rows) 
{
    if(universe != nullptr) 
    {
        for(int i = 0; i < rows; i++) 
        {
            delete[] universe[i];
        }
        delete[] universe;
    }
}

void initializeUniverse(UniverseCoordinate** &universe, int &rows, int &cols) 
{
    rows = 2;
    cols = 2;
    
    universe = new UniverseCoordinate*[rows];
    for(int i = 0; i < rows; i++) 
    {
        universe[i] = new UniverseCoordinate[cols];
        for(int j = 0; j < cols; j++) 
        {
            universe[i][j].x_position = j;
            universe[i][j].y_position = i;
            universe[i][j].is_snake = false;
            universe[i][j].s_number = 0;
        }
    }
}

void expandUniverse(UniverseCoordinate** &universe, int &rows, int &cols, int newRows, int newCols) 
{
    UniverseCoordinate** newUniverse = new UniverseCoordinate*[newRows];
    for(int i = 0; i < newRows; i++) 
    {
        newUniverse[i] = new UniverseCoordinate[newCols];
        for(int j = 0; j < newCols; j++) 
        {
            if(i < rows && j < cols) 
            {
                newUniverse[i][j] = universe[i][j];
            } else 
            {
                newUniverse[i][j].x_position = j;
                newUniverse[i][j].y_position = i;
                newUniverse[i][j].is_snake = false;
                newUniverse[i][j].s_number = 0;
            }
        }
    }
    
    freeMemory(universe, rows);
    universe = newUniverse;
    rows = newRows;
    cols = newCols;
}

void addSnake(UniverseCoordinate** &universe, int &rows, int &cols, int &snakeCount) 
{
   int x, y;
cout << "Enter X position: ";
cin >> x;
cout << "Enter Y position: ";
cin >> y;

if(x < 0 || y < 0) 
    {
    return;
}

int newRows = rows;
int newCols = cols;

if(y >= rows) 
    {
    newRows = y + 1;
}

if(x >= cols) 
    {
    newCols = x + 1;
}

if(x >= cols || y >= rows) 
    {
    expandUniverse(universe, rows, cols, newRows, newCols);
}

    if(universe[y][x].is_snake) 
    {
    return;
    }
    
    snakeCount++;
    universe[y][x].is_snake = true;
    universe[y][x].s_number = snakeCount;
}

void displayUniverse(UniverseCoordinate** universe, int rows, int cols) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if(universe[i][j].is_snake) 
            {
                cout << "#" << universe[i][j].s_number << " ";
            } else 
            {
                cout << "0 ";
            }
        }
        cout << endl;
    }
}


int main() {
    UniverseCoordinate** UniverseData = nullptr;
    int rows = 0, cols = 0;
    int snakeCount = 0;
    int choice;
    
    initializeUniverse(UniverseData, rows, cols);
    
    do 
    {
        cout << "1. Add Snake\n2. Display\n3. Expand\n4. Exit\nChoice: ";
        cin >> choice;
        
        switch(choice) {
            case 1:
                addSnake(UniverseData, rows, cols, snakeCount);
                break;
            case 2:
                displayUniverse(UniverseData, rows, cols);
                break;
            case 3:
                int newRows, newCols;
                cout<<"Enter no of rows followed by columns: ";
                cin >> newRows >> newCols;
                expandUniverse(UniverseData, rows, cols, newRows, newCols);
                break;
            case 4:
                break;
        }
    } while(choice != 4);
    
    freeMemory(UniverseData, rows);
    
    return 0;
}