// *******
// Course: TCP1101 PROGRAMMING FUNDAMENTALS
// Year: Trimester 1, 2022/23 (T2215)
// Lab: TxxL
// Names: Kalla Deveshwara Rao | Darwin A/L Radhakrishnan | Vimal Rich Selvam
// IDs: 1211103169| 1211104430 | 1211104171
// Emails: 1211103169@student.mmu.edu.my | 1211104430@student.mmu.edu.my | 1211104171@student.mmu.edu.my
// Phones: 0142702915 | 01123676737 | 012-500 7716
// *******

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib> // for system()
#include <ctime>   // for time() in srand( time(NULL) );
#include <iomanip> // for setw()

using namespace std;

int alienRow, alienCol;

void errorhandling(){

    // When there is an error in the input stream (cin), it will be flagged as an error. So to clear that we will need to use cin.clear()
    cin.clear();
    // cin.clear() clears the alert, but it does not clear the remaining value inside, so this down here clears data for you
    cin.ignore(INT_MAX,'\n');
}

//For now only to run the game nothing much
int mainmenu(){
    // for now its alien vs zombie
    cout << "|================================================|" << endl;
    cout << "|        A          V             V    ZZZZZZZZZ |" << endl;
    cout << "|       A A          V           V            Z  |" << endl;
    cout << "|      A   A          V         V            Z   |" << endl;
    cout << "|     AAAAAAA          V       V            Z    |" << endl;
    cout << "|    A       A          V     V            Z     |" << endl;
    cout << "|   A         A          V   V            Z      |" << endl;
    cout << "|  A           A          V V            Z       |" << endl;
    cout << "| A             A          V           ZZZZZZZZZ |" << endl;
    cout << "|================================================|" << endl;
    cout << "| Selection Menu                                 |" << endl;
    cout << "|================================================|" << endl;
    cout << "|                                                |" << endl;
    cout << "|    1. Start Game                               |" << endl;
    cout << "|    2. Load Game                                |" << endl;
    cout << "|    3. Save Game                                |" << endl;
    cout << "|    4. Board Settings                           |" << endl;
    cout << "|    5. Settings                                 |" << endl;
    cout << "|    6. Exit                                     |" << endl;
    cout << "|                                                |" << endl;
    cout << "|================================================|" << endl;

    while(true){
        cout << "Your input -> ";
        int userinput;
        cin >> userinput;
        //test

        //this is when the input stream enters error state
        if(cin.fail()){
            cout << " Wrong Input ! "; 
            errorhandling();
            continue;
        }

        if(userinput <= 6 && userinput >= 0){
            cout << string(100, '\n');
            return userinput;
        }else{
            cout << "Wrong Input !";
            continue;
        }
    }
}

// When you pass a function by reference, it means it will not make multiple copies and will just edit the main function itself.
// This is a struct. You can use struct as a datatype. You can declare variables like normal using struct.
// Using struct makes it very easy to organize our zombies we can them like arrays. calling method for their name :  nameofthevariable[indexnumber].number
struct Zombies
{
    string number;
    int life;
    int range;
    int attack;
};

// function to draw border
void draw_border(int column)
{
    cout << "*";
    for (int j = 0; j < column; ++j)
    {
        cout << "--";
    }
    cout << "*" << endl;
}

// This function is to display the board. It takes in reference variable, so it doesnt make any copy of the function
void displayboard(vector<vector<string>> &board)
{

    int row = board.size();
    int column = board[0].size();

    // this will output the values in the vector i - for rows j for column. They take in index values of the vector and output it
    for (int i = 0; i < row; i++)
    {
        draw_border(column);
        for (int j = 0; j < column; j++)
        {
            cout << "|" << board[i][j] << "";
        }
        cout << "|" << endl;
    }
    draw_border(column);
}

// This is to create gameboard using vector. It takes in user input for row and columnd. The first box is row second is column
vector<vector<string>> creategameboard()
{

    int row, column;
    row = 5;
    column = 9;
    cout << "===========================================" << endl;
    cout << " Do you want to change the number of rows?" << endl;
    cout << " Row number    - > " << row << endl;
    cout << " Column number - > " << column << endl;
    cout << "===========================================" << endl;
    cout << " Your Input - > ";
    string input;
    cin >> input;
    if(input == "Y"){
        while (true)
        {
            cout << "Enter the number of rows: ";
            cin >> row;
            if (row % 2 == 1)
            {
                break;
            }
            cout << "Please enter an odd number." << endl;
        }

        while (true)
        {
            cout << "Enter the number of columns: ";
            cin >> column;
            if (column % 2 == 1)
            {
                break;
            }
            cout << "Please enter an odd number." << endl;
        }
    }else{
        vector<vector<string>> board(row, vector<string>(column));
    }
    // This sets the board size.
    vector<vector<string>> board(row, vector<string>(column));

    // returns the board
    return board;
}

// This is to set all the character and powerups in the board. Takes in by reference
vector<vector<string>> gameboard(vector<vector<string>> &board)
{
    // Since the row and the column is not different for eaech case. You can just take the size of one row and one column
    int row = board.size();
    int column = board[0].size();

    char objects[] = {'^', 'v', '<', '>', 'p', 'h', 'r', ' ', ' ', ' ', ' '};
    int noOfObjects = 11;
    char alien = 'A';
    int centerRow = row / 2;
    int centerCol = column / 2;

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            board[i][j] = objects[rand() % noOfObjects];
            board[centerRow][centerCol] = alien;
        }
    }
    // Set alien position at default, in the middle
    alienRow = centerRow;
    alienCol = centerCol;
    return board;
}

// This is a struct vector function. This is to set zombie values. Only the number of zombies user inputs. The other attributes it will choose from the preset values
vector<Zombies> zombie(vector<vector<string>> &board)
{

    // Since all rows should have the same number of columns, you can just use size() here
    int row = board.size();
    int column = board[0].size();

    int amount;
    cout << "How many zombies?" << endl;
    cout << " Your Input - > ";
    cin >> amount;

    // Preset amount of hp to choose from
    int liferange[5] = {100, 150, 200, 250, 300};
    // Preset amount of range to choose from. It compares both of them, and sees which one is higher, then it will take te largest.
    int maxrange = max(row, column);
    // Preset amount of damage to choose from
    int damagerange[4] = {50, 100, 150, 200};

    // Calling the struct vector
    vector<Zombies> zombie;

    // This is to get the size of the vector so that we can limit the for loop. Ask kalla for more explanation
    zombie.resize(amount);

    // It goes through one by one in the struct vector.
    for (int i = 0; i < amount; i++)
    {
        // this is to name the zombies
        zombie[i].number = "Z" + to_string(i);
        // this is to set the hp using the limit above
        zombie[i].life = liferange[rand() % 5];
        // this is to set the range using the limit above
        zombie[i].range = rand() % maxrange;
        // this is to set the damage using the limit above
        zombie[i].attack = damagerange[rand() % 4];
    }

    // It will randomly generate zombies based on the amount the user inputs
    for (int i = 0; i < amount; ++i)
    {
        // This will randomize the location of zombies by making use of the rand() func. It will also limit the row and column size to user input, so it wont generate a random number that is too big
        int random1 = rand() % row;
        int random2 = rand() % column;

        // this will check if got z in the string or not. if dont have means it will proceed with the zombie placement
        if (board[random1][random2] != "Z" || board[random1][random2].find('Z') == string::npos)
        {
            board[random1][random2] = zombie[i].number;
        }
        else
        {
            // if got z means it will do minus one the decrement so that it can run the loop again
            i--;
        }
    }
    // displaying the board
    return zombie;
}

// So that we dont have to show it in ugly for loop code in the middle, i did it in a void function. So all we have to do is just use this function for displaying.
// It takes in struct vector datatype, in our case our Zombies Struct.
void displayzombie(vector<Zombies> &zombie)
{
    for (int i = 0; i < zombie.size(); i++)
    {
        cout << "Zombie " + zombie[i].number + " : Life " << zombie[i].life << ", Attack " << zombie[i].attack << ", Range " << zombie[i].range << endl;
    }
}

// This is for the alien to move. It takes both board and zombie by reference
void alienmove(vector<vector<string>> &board, vector<Zombies> &zombies)
{
    // board and row size from the refernced board variable
    int row = board.size();
    int column = board[0].size();

    // Sets default and max health for the alien. Attack by default is zero, it will only gain attack power in the game by picking up arrows
    int maxHealth = 100;
    int currentHealth = 80;
    int attack = 0;

    // Setting the struct vector zombies and 2d vector game

    // clears the screen from all the previous output
    system("cls");
    cout << "Enter a direction to move the alien (up,down,left,right,q):" << endl;
    // Im assuming vimal will put something here
    // cout << "Type ctrl for game controls \n \n";
    displayboard(board);

    cout << "  " << endl;

    // Display zombie and alien
    cout << "Alien : Life " << currentHealth << ", Attack " << attack << endl;
    displayzombie(zombies);

    while (true)
    {
        // Need to put the controls under while loop so that we can do it multiple times
        string direction;
        cout << "Enter a direction to move the alien (up,down,left,right,q):";

        // The > and < symbols are to keep it from going out of bounds. The dot is to leave trails. The code will stop working once we type in 'q'
        cin >> direction;
        if (direction == "up")
        {
            if (alienRow > 0)
            {
                board[alienRow][alienCol] = '.';
                alienRow--;
            }
        }
        else if (direction == "left")
        {
            if (alienCol > 0)
            {
                board[alienRow][alienCol] = '.';
                alienCol--;
            }
        }
        else if (direction == "down")
        {
            if (alienRow < row - 1)
            {
                board[alienRow][alienCol] = '.';
                alienRow++;
            }
        }
        else if (direction == "right")
        {
            if (alienCol < column - 1)
            {
                board[alienRow][alienCol] = '.';
                alienCol++;
            }
        }

        else if (direction == "q")
        {
            break;
        }

        // Updated alien postion from the selection statement
        board[alienRow][alienCol] = 'A';

        // clears the output so that it looks clean for the next output
        system("cls");

        // By now you should know what this does
        displayboard(board);
        cout << "Alien : Life " << currentHealth << ", Attack " << attack << endl;
        displayzombie(zombies);
    }
}




int main()
{
    // Sets the seed random by using our time. So random will be extra random
    srand(time(NULL));
    // 2d vector variable to start the program
    int userinput = mainmenu();
    //only one main menu

    if (userinput == 1)
    {
        vector<vector<string>> game = creategameboard();
        // this is to set all the characters in the gameboard
        gameboard(game);
        // This is the struct vector function, it setst all the zombies location and attributes
        vector<Zombies> zombies = zombie(game);
        // It takes the new zombie values and the board and uses it in the alienmove function
        alienmove(game, zombies);
    }else if(userinput == 6)
    {
        exit(0);
    }
    
}

