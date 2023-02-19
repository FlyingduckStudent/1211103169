 // *******
// Course: TCP1101 PROGRAMMING FUNDAMENTALS
// Year: Trimester 1, 2022/23 (T2215)
// Lab: T14L
// Names: Kalla Deveshwara Rao A/L Rama Rao| Darwin A/L Radhakrishnan | Vimal Rich Selvam
// IDs: 1211103169| 1211104430 | 1211104171
// Emails: 1211103169@student.mmu.edu.my | 1211104430@student.mmu.edu.my | 1211104171@student.mmu.edu.my
// Phones: 0142702915 | 01123676737 | 0125007716
// *******
#include <fstream>
#include <limits.h>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib> // for system()
#include <ctime>   // for time() in srand( time(NULL) );
#include <iomanip> // for setw()
#include <utime.h>
#include <windows.h>
#include <mmsystem.h>
#include <algorithm>
#include <math.h>

using namespace std;

int alienRow, alienCol, attack;
int currentHealth = 200;

// When you pass a function by reference, it means it will not make multiple copies and will just edit the main function itself.
// This is a struct. You can use struct as a datatype. You can declare variables like normal using struct.
// Using struct makes it very easy to organize our zombies we can them like arrays. calling method for their name :  nameofthevariable[indexnumber].number
struct Zombies
{
    int number;
    int life;
    int range;
    int attack;
    int x, y;
};

struct Gamedata{
    vector<vector<string>> board;
    vector<Zombies> zombies;
    int health;
    int damage;
    int alienCol;
    int alienRow;
};


void errorhandling()
{

    // When there is an error in the input stream (cin), it will be flagged as an error. So to clear that we will need to use cin.clear()
    cin.clear();
    // cin.clear() clears the alert, but it does not clear the remaining value inside, so this down here clears data for you
    cin.ignore(INT_MAX, '\n');
}

// For now only to run the game nothing much
int mainmenu()
{
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
    cout << "|    3. Music On                                 |" << endl;
    cout << "|    4. Music Off                                |" << endl;
    cout << "|    5. Exit                                     |" << endl;
    cout << "|================================================|" << endl;

    while (true)
    {
        cout << "Your input -> ";
        int userinput;
        cin >> userinput;
        // test

        // this is when the input stream enters error state
        if (cin.fail())
        {
            cout << "Wrong Input !\n";
            errorhandling();
            continue;
        }

        if (userinput <= 5 && userinput >= 1)
        {
            system("CLS");
            return userinput;
        }
        else
        {
            cout << "Wrong Input !\n";
            continue;
        }
    }
}

// function to draw border
void draw_border(int column)
{
    cout << "|";
    for (int j = 0; j < column; ++j)
    {
        cout << "----+";
        if (j == column - 2)
        {
            cout << "----|" << endl;
            break;
        }
    }
}

// This function is to display the board. It takes in reference variable, so it doesnt make any copy of the function
void displayboard(vector<vector<string>> &board)
{

    int row = board.size();
    int column = board[0].size();

    // this will output the values in the vector i - for rows j for column. They take in index values of the vector and output it
    for (int i = 0; i < row; i++)
    {
        cout << setw(2) << (row - i);
        draw_border(column);
        for (int j = 0; j < column; j++)

        {
            cout << "  | " << board[i][j] << "";
        }
        cout << "  |" << endl;
    }

    // this is to print lowest border of the map
    cout << "  |";
    for (int j = 0; j < column; ++j)
    {
        cout << "----+";
        if (j == column - 2)
        {
            cout << "----|" << endl;
            break;
        }
    }

    // display column number
    cout << "   ";

    for (int j = 0; j < column; ++j)
    {
        int digit = (j + 1) / 10;
        cout << "    ";
        if (digit == 0)
            cout << " ";
        else
            cout << digit;
    }
    cout << endl
         << "   ";

    for (int j = 0; j < column; ++j)
    {
        cout << "    " << (j + 1) % 10;
    }
    cout << endl
         << endl;
    cout << "Commands (up,down,left,right,help,quit,arrow)\n";
}

// This is to create gameboard using vector. It takes in user input for row and columnd. The first box is row second is column
vector<vector<string>> creategameboard()
{

    int row, column;
    row = 7;
    column = 13;
    system("cls");
    cout << "===============================================" << endl;
    cout << " Do you want to change the number of rows Y/N ?" << endl;
    cout << " Row number    - > " << row << endl;
    cout << " Column number - > " << column << endl;
    cout << "===============================================" << endl;
    bool runtheloop = true;

    while (runtheloop)
    {
        cout << "Your Input - > ";
        string input;
        cin >> input;

        if (input == "Y" || input == "y")
        {
            while (true)
            {
                cout << "Enter the number of rows: ";
                cin >> row;
                if (row % 2 == 1)
                {
                    break;
                }
                else if (cin.fail())
                {
                    errorhandling();
                    cout << "Wrong Input !" << endl;
                }
                else
                {
                    cout << "Please enter an odd number." << endl;
                }
            }

            while (true)
            {
                cout << "Enter the number of columns: ";
                cin >> column;
                if (column % 2 == 1)
                {
                    runtheloop = false;
                    break;
                }
                else if (cin.fail())
                {
                    errorhandling();
                    cout << "Wrong Input !" << endl;
                }
                else
                {
                    cout << "Please enter an odd number." << endl;
                }
            }
        }
        else if (input == "N" || input == "n")
        {
            vector<vector<string>> board(row, vector<string>(column));
            system("cls");
            break;
        }
        else if (cin.fail())
        {
            errorhandling();
            cout << "Wrong Input !\n"
                 << endl;
        }
        else
        {
            cout << "Wrong Input !\n"
                 << endl;
        }
    }
    // This sets the board size.
    vector<vector<string>> board(row, vector<string>(column));
    system("cls");
    // returns the board
    return board;
}

void trailtoitem(int row,int column,vector<vector<string>> &board)

{
    char objects[] = {'^', 'v', '<', '>', 'p', 'h', 'r','k',' ',' ',' '};
    int noOfObjects = 11;

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            if (board[i][j] == ".")
        {
            board[i][j] = objects[rand() % noOfObjects];

        }

    }

    }
}


// This is to set all the character and powerups in the board. Takes in by reference
vector<vector<string>> gameboard(vector<vector<string>> &board)
{
    // Since the row and the column is not different for eaech case. You can just take the size of one row and one column
    int row = board.size();
    int column = board[0].size();

    char objects[] = {' ', ' ', '^', 'v', '<', '>', 'p', 'h', 'r', ' ', ' ', ' ', ' ','k'};
    int noOfObjects = 14;
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

    while (true)
    {
        cout << "==============================" << endl;
        cout << "How many zombies? 1 ~ 9 Only!" << endl;
        cout << "==============================" << endl;
        cout << "Your Input - > ";
        cin >> amount;
        if (cin.fail())
        {
            errorhandling();
            cout << endl << "Wrong Input !\n"<< endl;
        }
        else if((amount > 0) & (amount <= 9))
        {
            break;
        }
        else
        {
            cout << endl << "Wrong Input ! 1 ~ 9 Only! \n"<< endl;
        }
    }

    system("cls");
    // Preset amount of hp to choose from
    int liferange[5] = {100, 150, 200, 250, 300};
    // Preset amount of range to choose from. It compares both of them, and sees which one is higher, then it will take te largest.
    int maxrange = max(row, column);
    // Preset amount of damage to choose from
    int damagerange[4] = {5, 10, 15, 20};

    // Calling the struct vector
    vector<Zombies> zombie;

    // This is to get the size of the vector so that we can limit the for loop. Ask kalla for more explanation
    zombie.resize(amount);

    // It goes through one by one in the struct vector.
    for (int i = 0; i < amount; i++)
    {
        // this is to name the zombies
        // zombie[i].number = "Z" + to_string(i); Only use this for debugging purposes!
        zombie[i].number = i+1;
        // this is to set the hp using the limit above
        zombie[i].life = liferange[rand() % 5];
        // this is to set the range using the limit above
        zombie[i].range = rand() % maxrange;
        // this is to set the damage using the limit above
        zombie[i].attack = damagerange[rand() % 4];
    }
    // this is to prevent zombies replacing zombies in the gameboard
    vector<vector<string>> unallowedcoordinates(row, vector<string>(column));
    unallowedcoordinates[row / 2][column / 2] = "Taken !";
    // It will randomly generate zombies based on the amount the user inputs
    for (int i = 0; i < amount; ++i)
    {
        // This will randomize the location of zombies by making use of the rand() func. It will also limit the row and column size to user input, so it wont generate a random number that is too big
        int random1 = rand() % row;
        int random2 = rand() % column;
        // this will check if got z in the string or not. if dont have means it will proceed with the zombie placement
        if (!(unallowedcoordinates[random1][random2] == "Taken !"))
        {
            board[random1][random2] = to_string(zombie[i].number);
            zombie[i].x = random1;
            zombie[i].y = random2;
        }
        else
        {
            // if got z means it will do minus one the decrement so that it can run the loop again
            i--;
        }
        // Once the thing is done placing the zombies, it will place the coordinates in the unallowedcoordinates vector so that in the for loop it will be able to prevent from using the same coordinate
        unallowedcoordinates[random1][random2] = "Taken !";
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
        cout << "Zombie " << zombie[i].number << " : Life " << zombie[i].life << ", Attack " << zombie[i].attack << ", Range " << zombie[i].range << ", Coordinates " << zombie[i].x << "  " << zombie[i].y << endl;
    }
}

// Uses pythagorusrusruse theorem to calculate the distance between a and z
void attackalien(vector<vector<string>> &board, vector<Zombies> &zombies, int &attack, int x, int y)
{
    vector<int> nearest;
    nearest.resize(zombies.size());
    for (int i = 0; i < zombies.size(); i++)
    {
        // takes the distance of each zombies and adds it to the nearest vector
        int distance = sqrt(pow((zombies[i].x - x), 2) + pow((zombies[i].y - y), 2));
        nearest[i] = distance;
    }
    // small block of code to find the smallest distance index value and attack the zombie with the right index value ;
    auto smallest = min_element(nearest.begin(), nearest.end());
    int index = distance(nearest.begin(), smallest);
    zombies[index].life -= 20;
    cout << "Zombie " << to_string(zombies[index].number) << " took 20 damage!" << endl;
}

//this is a function to check whether zombies are alive or not.
//if their health reaches 0, then we will have to remove it from the vector and the gameboard
void checkZombiealive(vector<vector<string>> &board, vector<Zombies> &zombies)
{

//basically this is a for loop that i learnt recently, it goes through the entire zombie vector
    for (auto it = zombies.begin(); it != zombies.end();)
    {
        //when one of the zombie's life reaches 0 it will just remove the zombie from the vector and replace the zombies location with an ampty space
        if (it->life <= 0)
        {
            board[it->x][it->y] = " ";
            it = zombies.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

// this function checks the surrounding of the alien to see if there is any powerups
bool checksurrounding(vector<vector<string>> &board, int powerrow, int powercolumn, int &maxHealth, int &currentHealth, vector<Zombies> &zombie, int &attack)
{
    int zombiesize = zombie.size();
    if (board[powerrow][powercolumn] == "^" || board[powerrow][powercolumn] == "<" || board[powerrow][powercolumn] == ">" || board[powerrow][powercolumn] == "v")
    {
        return true;
    }
    else if (board[powerrow][powercolumn] == "h")
    {
        if (currentHealth < maxHealth)
        {
            currentHealth = currentHealth + 20;
        }
    }
    else if (board[powerrow][powercolumn] == "k")
    {   if (currentHealth <= maxHealth)
        currentHealth = currentHealth - 20;
    }
    else if (board[powerrow][powercolumn] == "p")
    {
        cout << "========== INFORMATION UPDATE ==========" << endl;
        cout << "You hit a pod! \n";
        attackalien(board, zombie, attack, powerrow, powercolumn);
        Sleep(3000);
    }
    return false;
}

//checks for rock in the gameboard
bool checkrock(vector<vector<string>> &board, int powerrow, int powercolumn)
{
    if (board[powerrow][powercolumn] == "r")
    {
        return true;
    }
    return false;
}

//this is to check whether there is a zombie near the alien.
bool Checkzombie(vector<vector<string>> &board, vector<Zombies> &zombies, int currentrow, int currentcol, int &attack)
{
    int zombiesize = zombies.size();
    for (int i = 0; i < zombiesize; i++)
    {
        //if got zombie on the location it will minus the zombie's life  and return false
        if (board[zombies[i].x][zombies[i].y] == board[currentrow][currentcol])
        {
            cout << "Zombie Detected!" << endl;
            zombies[i].life = zombies[i].life - attack;
            Sleep(1000);
            cout << "Zombie takes " << attack << " damage!" << endl;
            attack = 0;
            cout << "Returning in 3..." << endl;
            Sleep(3000);
            return false;
            break;
        }
    }
    return true;
}

void savegame(vector<vector<string>> &board, vector<Zombies> &zombies, int &health, int &damage){
        string savename;
        cout << "File Name - > " << endl;
        cin >> savename;
        savename = savename + ".txt";

        ifstream checkfile;
        checkfile.open(savename);
        if(!(checkfile)){

            ofstream savedgame(savename);
            savedgame << "Game Board Data" << endl;

            for(int i = 0; i < board.size(); i ++){

                for(int j = 0; j < board[i].size(); j++){
                    savedgame << board[i][j];
                }
                savedgame << "\n";
            }

            savedgame << "Zombie Data" << endl;
            for(int i = 0; i < zombies.size(); i++){
                savedgame << zombies[i].number <<"\n";
                savedgame << zombies[i].life <<"\n";
                savedgame << zombies[i].range <<"\n";
                savedgame << zombies[i].attack <<"\n";
                savedgame << zombies[i].x <<"\n";
                savedgame << zombies[i].y <<"\n";
            }

            savedgame << "Alien Data" << endl;
            savedgame << alienCol << "\n";
            savedgame << alienRow << "\n";
            savedgame << health << "\n";
            savedgame << damage;

            cout << "File saved successfully!\n";

        }else{
            cout << "File already exists!\n";
            Sleep(3000);
        }

}
bool loadgame(Gamedata &gameData, string filename) {

    ifstream savedgame(filename + ".txt");
    if(!savedgame) {
        return false;
    }

    string line;
    getline(savedgame, line); // read the first line

    // Read the board data
    vector<vector<string>> board;
    while (getline(savedgame, line)) {
        if (line == "Zombie Data") {
            break;
        }
        vector<string> row;
        for(int j = 0; j < line.size(); j++) {
            row.push_back(string(1, line[j]));
        }
        board.push_back(row);
    }

    // Read the zombie data
    vector<Zombies> zombies;
    while (getline(savedgame, line)) {
        if (line == "Alien Data") {
            break;
        }
        Zombies zombie;
        zombie.number = atoi(line.c_str());
        getline(savedgame, line);
        zombie.life = stoi(line);
        getline(savedgame, line);
        zombie.range = stoi(line);
        getline(savedgame, line);
        zombie.attack = stoi(line);
        getline(savedgame, line);
        zombie.x = stoi(line);
        getline(savedgame, line);
        zombie.y = stoi(line);
        zombies.push_back(zombie);
    }

    // Read the alien data
    getline(savedgame, line);
    gameData.alienCol = stoi(line);
    getline(savedgame, line);
    gameData.alienRow = stoi(line);
    getline(savedgame, line);
    gameData.health = stoi(line);
    getline(savedgame, line);
    gameData.damage = stoi(line);

    gameData.board = board;
    gameData.zombies = zombies;
    cout << "file found!";
    Sleep(3000);
    return true;
}



//this is to use the continue to move thingy
string objectmove(string &object, vector<vector<string>> &board, string &movement)
{

    if (object == "<")
    {
        return "left";
    }
    else if (object == ">")
    {
        return "right";
    }
    else if (object == "^")
    {
        return "up";
    }
    else if (object == "v")
    {
        return "down";
    }
    else if (object == "h")
    {
        board[alienRow][alienCol] = 'A';
    }
    else
    {
        return "false";
    }
}


//this is for the game to output victory/lost message
bool gamestatus(vector<Zombies> &zombies)
{
    if ((zombies.size() == 0) || (zombies.size() == NULL))
    {
        system("CLS");
        cout << "========== INFORMATION UPDATE ==========" << endl;
        cout << "                YOU WON!    " << endl;
        cout << "            CONGRATULATIONS    " << endl;

        cout << " Returning in 3..." << endl;
        Sleep(1000);
        cout << " Returning in 2..." << endl;
        Sleep(1000);
        cout << " Returning in 1..." << endl;
        Sleep(1000);
        system("CLS");
        return false;
    }
    else
    {
        return true;
    }
}

//this is for the zombie to move
void movezombie(vector<vector<string>> &board, vector<Zombies> &zombies)
{
    int zombienum = zombies.size();
    int oldx, oldy;

    for (int i = 0; i < zombienum; i++)
    {
        //it will choose between these three numbers up/left, stay, down/right
        int randomnum[3] = {-1, 0, 1};

        //temp variable to store the zombie's old location
        oldx = zombies[i].x;
        oldy = zombies[i].y;

        //to choose between horizontal and vertical movement
        int randomMove = rand() % 2;
        //horizontal movement
        if (randomMove == 1)
        {
            int randomx = randomnum[rand() % 2];
            //will check four times even though 2 times is enough to check idk why i did this dont ask me.
            for (int j = 0; j < 4; j++)
            {   //will check if got any empty space or not. have to use absolute cause index value cant take in negative value
                if (board[abs(oldx + randomx)][abs(oldy)] == " ")
                {
                    //zombie's new location
                    zombies[i].x = abs(randomx + oldx);
                    //setting the new zombie's location
                    board[zombies[i].x][zombies[i].y] = to_string(zombies[i].number);
                    //old location becomes empty
                    board[oldx][oldy] = " ";
                    break;
                }
            }
        }
        //exactly like horizontal movement,but vertically
        else if (randomMove == 0)
        {
            int randomy = randomnum[rand() % 2];
            for (int j = 0; j < 4; j++)
            {

                if (board[abs(oldx)][abs(oldy + randomy)] == " ")
                {
                    zombies[i].y = abs(randomy + oldy);
                    board[zombies[i].x][zombies[i].y] = to_string(zombies[i].number);
                    board[oldx][oldy] = " ";
                    break;
                }
            }
        }
    }
}

//this is for the zombies to attack
void zombieattack(vector<vector<string>> &board, vector<Zombies> &zombies, int &alienhealth)
{
    int row, column, maxrange, zombiesize;
    row = board.size();
    column = board[0].size();
    zombiesize = zombies.size();
    cout << endl;
    cout << "========== INFORMATION UPDATE ==========" << endl;
    cout << "You hit a rock / border / zombie!\n";

    for (int i = 0; i < zombiesize; i++)
    {
        maxrange = zombies[i].range;
        //to see if zombie is with alien or not
        if ((zombies[i].x == alienRow) || (zombies[i].y == alienCol))
        {
            //changes the alien trail with new stuff
            trailtoitem(row,column,board);
            //to check whether it is within the zombie's range to attack
            if ((abs(zombies[i].x - alienRow) < maxrange) || (abs(zombies[i].y - alienRow) < maxrange))
            {
                cout << endl
                     << "Zombie " << zombies[i].number << " attacks for " << zombies[i].attack << " HP" << endl;
                Sleep(1000);
                //attack stuff
                alienhealth = alienhealth - zombies[i].attack;
            }
        }
    }
    cout << "Alien Health : " << alienhealth << endl;
    Sleep(3000);
}
// this is to check if the player intentionally choooses to go out of bounds
bool checkboundary(vector<vector<string>> &board, string input, vector<Zombies> &zombies, int &currentHealth, int &attack)
{
    int row, column;
    row = board.size();
    column = board[0].size();
    //this is if the player intentionally chooses to go out of bounds
    if (alienRow == 0 && input == "up")
    {
        cout << "Out Of Boundary! Cant move further above! Returning in 3..." << endl;
        Sleep(3000);
        attack = 0;
        trailtoitem(row,column,board);
        movezombie(board, zombies);
        zombieattack(board, zombies, currentHealth);
        return false;
    }
    else if (alienCol == 0 && input == "left")
    {
        cout << "Out Of Boundary! Cant move further left! Returning in 3..." << endl;
        Sleep(3000);
        attack = 0;
        trailtoitem(row,column,board);
        movezombie(board, zombies);
        zombieattack(board, zombies, currentHealth);
        return false;
    }
    else if (alienRow == row - 1 && input == "down")
    {
        cout << "Out Of Boundary! Cant move further below! Returning in 3..." << endl;
        Sleep(3000);
        attack = 0;
        trailtoitem(row,column,board);
        movezombie(board, zombies);
        zombieattack(board, zombies, currentHealth);
        return false;
    }
    else if (alienCol == column - 1 && input == "right")
    {
        cout << "Out Of Boundary! Cant move further right! Returning in 3..." << endl;
        Sleep(3000);
        attack = 0;
        trailtoitem(row,column,board);
        movezombie(board, zombies);
        zombieattack(board, zombies, currentHealth);
        return false;
    }
    else
    {
        return true;
    }
}

// This is for the alien to move. It takes both board and zombie by reference
bool alienmove(vector<vector<string>> &board, vector<Zombies> &zombies)
{
    // board and row size from the refernced board variable
    int row = board.size();
    int column = board[0].size();

    // Sets default and max health for the alien. Attack by default is zero, it will only gain attack power in the game by picking up arrows
    int maxHealth = 400;

    // This is to let the Alien move by itself for just 1 key to move
    // Continue Up
    string movement, object, cont;
    char confirm;

    while (true)
    {
        //to see if all the zombies are still alive or not, or if you are dead and the zombies are alive
        checkZombiealive(board, zombies);
        if (gamestatus(zombies) == false){
            return false;
        }

        if (currentHealth <= 0)
        {
            system("CLS");
            cout << "    Game Over!    " << endl;
            cout << " Returning in 3..." << endl;
            Sleep(1000);
            cout << " Returning in 2..." << endl;
            Sleep(1000);
            cout << " Returning in 1..." << endl;
            Sleep(1000);
            system("CLS");
            return false;
        }


        char objects[] = {'^', 'v', '<', '>', 'p', 'h','k',' ', ' ', ' ', ' '};
        int noOfObjects = 11;

        system("cls");
        // clears the screen from all the previous output
        displayboard(board);
        // Display zombie and alien
        cout << "Alien : Life " << currentHealth << ", Attack " << attack << endl;
        displayzombie(zombies);

        if (objectmove(object, board, movement) == "false")
        {
            cin >> movement;
        }
        else if (objectmove(object, board, movement) != "false")
        {
            movement = objectmove(object, board, movement);
            object = "nothing";
        }

        if (movement == "up" && checkboundary(board, movement, zombies, currentHealth, attack))
        {
            while (true)
            {
                cout << "Press C to continue ..." << endl;
                cin >> cont;

                if((cont != "C") || cin.fail()){
                    errorhandling();
                    cout << "\n Wrong input! \n";
                    continue;
                }

                if (checkrock(board, alienRow - 1, alienCol) == true)
                {
                    board[alienRow - 1][alienCol] = objects[rand() % noOfObjects];
                    movezombie(board, zombies);
                    zombieattack(board, zombies, currentHealth);
                    trailtoitem(row,column,board);
                    cout << "Reveals the hidden game object" << endl;
                    break;
                }
                if (Checkzombie(board, zombies, alienRow - 1, alienCol, attack) == false)
                {
                    movezombie(board, zombies);
                    zombieattack(board, zombies, currentHealth);
                    break;
                }
                if (checksurrounding(board, alienRow - 1, alienCol, maxHealth, currentHealth, zombies, attack) == false)
                {
                    if (cont == "C")
                    {
                        bool check = gamestatus(zombies);
                        if (check == false)
                        {
                            return false;
                        }
                        if (alienCol >= 0)
                        {
                            board[alienRow][alienCol] = '.';
                            alienRow--;
                        }
                    }
                }
                else if (checksurrounding(board, alienRow - 1, alienCol, maxHealth, currentHealth, zombies, attack) == true)
                {
                    bool check = gamestatus(zombies);
                    if (check == false)
                    {
                        return false;
                    }
                    object = board[alienRow - 1][alienCol];
                    cout << "========== INFORMATION UPDATE ==========" << endl;
                    cout << "Alien Picked up " << object;
                    Sleep(2000);
                    board[alienRow][alienCol] = '.';
                    alienRow--;
                    attack = attack + 20;
                    board[alienRow][alienCol] = 'A';

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

                if (alienRow < 1)
                {
                    system("cls");
                    attack = 0;
                    displayboard(board);
                    movezombie(board, zombies);
                    zombieattack(board, zombies, currentHealth);
                    system("cls");
                    break;
                };
            }
        }
        // Continues Left
        else if (movement == "left" && checkboundary(board, movement, zombies, currentHealth,attack))
        {

            while (true)
            {
                cout << "Press C to continue ..." << endl;
                cin >> cont;

                if((cont != "C") || cin.fail()){
                    errorhandling();
                    cout << "\n Wrong input! \n";
                    continue;
                }

                if (checkrock(board, alienRow, alienCol - 1) == true)
                {
                    board[alienRow][alienCol - 1] = objects[rand() % noOfObjects];
                    movezombie(board, zombies);
                    zombieattack(board, zombies, currentHealth);
                    trailtoitem(row,column,board);
                    cout << "Reveals the hidden game object" << endl;
                    Sleep(2000);
                    break;
                }
                if (Checkzombie(board, zombies, alienRow, alienCol - 1,attack) == false)
                {
                    movezombie(board, zombies);
                    zombieattack(board, zombies, currentHealth);
                    break;
                }
                if (checksurrounding(board, alienRow, alienCol - 1, maxHealth, currentHealth, zombies, attack) == false)
                {
                    if (cont == "C")
                    {
                        bool check = gamestatus(zombies);
                        if (check == false)
                        {
                            return false;
                        }
                        if (alienCol >= 0)
                        {
                            board[alienRow][alienCol] = '.';
                            alienCol--;
                        }
                    }
                }
                else if (checksurrounding(board, alienRow, alienCol - 1, maxHealth, currentHealth, zombies, attack) == true)
                {
                    bool check = gamestatus(zombies);
                    if (check == false)
                    {
                        return false;
                    }

                    object = board[alienRow][alienCol - 1];
                    cout << "========== INFORMATION UPDATE ==========" << endl;
                    cout << "Alien Picked up " << object;
                    Sleep(2000);
                    board[alienRow][alienCol] = '.';
                    alienCol--;
                    attack = attack + 20;
                    board[alienRow][alienCol] = 'A';
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
                if (alienCol < 1)
                {
                    system("cls");
                    attack = 0;
                    displayboard(board);
                    movezombie(board, zombies);
                    zombieattack(board, zombies, currentHealth);
                    system("cls");
                    break;
                };
            }
        }
        // Continues Down
        else if (movement == "down" && checkboundary(board, movement, zombies, currentHealth,attack))
        {

            while (true)
            {   cout << "Press C to continue ..." << endl;
                cin >> cont;
                if((cont != "C") || cin.fail()){
                    errorhandling();
                    cout << "\n Wrong input! \n";
                    continue;
                }


                if (checkrock(board, alienRow + 1, alienCol) == true)
                {
                    board[alienRow + 1][alienCol] = objects[rand() % noOfObjects];
                    movezombie(board, zombies);
                    zombieattack(board, zombies, currentHealth);
                    trailtoitem(row,column,board);
                    cout << "Reveals the hidden game object" << endl;
                    Sleep(2000);
                    break;
                }
                if (Checkzombie(board, zombies, alienRow + 1, alienCol,attack) == false)
                {
                    movezombie(board, zombies);
                    zombieattack(board, zombies, currentHealth);
                    break;
                }
                if (checksurrounding(board, alienRow + 1, alienCol, maxHealth, currentHealth, zombies, attack) == false)
                {
                    if (cont == "C")
                    {
                        bool check = gamestatus(zombies);
                        if (check == false)
                        {
                            return false;
                        }
                        if (alienCol >= 0)
                        {
                            board[alienRow][alienCol] = '.';
                            alienRow++;
                        }
                    }
                }
                else if (checksurrounding(board, alienRow + 1, alienCol, maxHealth, currentHealth, zombies, attack) == true)
                {
                    bool check = gamestatus(zombies);
                    if (check == false)
                    {
                        return false;
                    }

                    object = board[alienRow + 1][alienCol];
                    cout << "========== INFORMATION UPDATE ==========" << endl;
                    cout << "Alien Picked up " << object;
                    Sleep(2000);
                    board[alienRow][alienCol] = '.';
                    alienRow++;
                    attack = attack + 20;
                    board[alienRow][alienCol] = 'A';
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
                if (alienRow > row - 2)
                {
                    system("cls");
                    attack = 0;
                    displayboard(board);
                    movezombie(board, zombies);
                    zombieattack(board, zombies, currentHealth);
                    system("cls");
                    break;
                }
            }
        }
        // Continue Right
        else if (movement == "right" && checkboundary(board, movement, zombies, currentHealth,attack))
        {
            while (true)
            {   cout << "Press C to continue ..." << endl;
                cin >> cont;
                if((cont != "C") || cin.fail()){
                    errorhandling();
                    cout << "\n Wrong input! \n";
                    continue;
                }
                if (checkrock(board, alienRow, alienCol + 1) == true)
                {
                    board[alienRow][alienCol + 1] = objects[rand() % noOfObjects];
                    movezombie(board, zombies);
                    zombieattack(board, zombies, currentHealth);
                    trailtoitem(row,column,board);
                    cout << "Reveals the hidden game object" << endl;
                    Sleep(2000);
                    break;
                }
                if (Checkzombie(board, zombies, alienRow, alienCol + 1,attack) == false)
                {
                    movezombie(board, zombies);
                    zombieattack(board, zombies, currentHealth);
                    break;
                }
                if (checksurrounding(board, alienRow, alienCol + 1, maxHealth, currentHealth, zombies, attack) == false)
                {
                    if (cont == "C")
                    {
                        bool check = gamestatus(zombies);
                        if (check == false)
                        {
                            return false;
                        }
                        if (alienCol >= 0)
                        {
                            board[alienRow][alienCol] = '.';
                            alienCol++;
                        }
                    }
                }
                else if (checksurrounding(board, alienRow, alienCol + 1, maxHealth, currentHealth, zombies, attack) == true)
                {

                    object = board[alienRow][alienCol + 1];
                    cout << "========== INFORMATION UPDATE ==========" << endl;
                    cout << " Alien Picked up " << object;
                    Sleep(2000);
                    board[alienRow][alienCol] = '.';
                    alienCol++;
                    attack = attack + 20;
                    board[alienRow][alienCol] = 'A';
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
                if (alienCol > column - 2)
                {
                    system("cls");
                    attack = 0;
                    displayboard(board);
                    movezombie(board, zombies);
                    zombieattack(board, zombies, currentHealth);
                    system("cls");
                    break;
                }
            }
        }
        //to change the arrows in the board
        else if (movement == "arrow")
        {
            while (true)
            {
                int x, y;
                cout << "Select coordinate to change (row, column): ";
                cin >> x >> y;

                if(cin.fail()){
                    errorhandling();
                    cout << "\n Wrong input! \n";
                    continue;
                }

                if (x >= 0 && x < board.size() && y >= 0 && y < board[0].size()) // check if the selected coordinate is within the board range
                {
                  if (board[x][y] == "^" || board[x][y] == "v" || board[x][y] == "<" || board[x][y] == ">" ) // check if the selected coordinate already has an arrow symbol
                    {
                        cout << "This coordinate is valid" << endl;
                        string arrowType;
                        cout << "Enter arrow type (^, v, >, <): ";
                        cin >> arrowType;
                        if(cin.fail()){
                            errorhandling();
                            cout << "\n Wrong input! \n";
                            continue;
                        }
                        if (arrowType == "^" || arrowType == "v" || arrowType == ">" || arrowType == "<") // check if the input arrow type is valid
                        {

                            if (arrowType == "^")
                            {
                                board[x][y] = '^';
                            }
                            else if (arrowType == "v")
                            {
                                board[x][y] = 'v';
                            }
                            else if (arrowType == ">")
                            {
                                board[x][y] = '>';
                            }
                            else if (arrowType == "<")
                            {
                                board[x][y] = '<';
                            }

                            system("cls");
                            displayboard(board);

                            string confirm;
                            cout << "Arrow symbol updated. Do you want to continue changing arrows? (y/n): ";
                            cin >> confirm;

                            if (confirm == "n")
                            {
                                break;
                            }
                        }
                        else
                        {
                            cout << "Invalid arrow type. Please enter a valid arrow type." << endl;
                        }
                    }
                    else
                    {
                        cout << "Invalid coordinate. Please enter a valid coordinate." << endl;
                    }
                }
            }
        }
        // to provide the user with control helps idk
        else if (movement == "help")
        {
            cout << endl;
            cout << "|-------------------------------------------------------|" << endl;
            cout << "|     Command    |            Description               |" << endl;
            cout << "|-------------------------------------------------------|" << endl;
            cout << "|       up       |   Alien to move up.                  |" << endl;
            cout << "|----------------|--------------------------------------|" << endl;
            cout << "|      down      |   Alien to move down.                |" << endl;
            cout << "|----------------|--------------------------------------|" << endl;
            cout << "|      left      |   Alien to move left.                |" << endl;
            cout << "|----------------|--------------------------------------|" << endl;
            cout << "|      right     |   Alien to move right.               |" << endl;
            cout << "|----------------|--------------------------------------|" << endl;
            cout << "|      arrow     |   Switch the direction of an arrow   |" << endl;
            cout << "|                |   object in the game board.          |" << endl;
            cout << "|----------------|--------------------------------------|" << endl;
            cout << "|      help      |   List and describe commands that    |" << endl;
            cout << "|                |   the player can use in the game.    |" << endl;
            cout << "|----------------|--------------------------------------|" << endl;
            cout << "|      save      |   Save the current game to a file.   |" << endl;
            cout << "|----------------|--------------------------------------|" << endl;
            cout << "|      load      |   Load a saved game from a file.     |" << endl;
            cout << "|----------------|--------------------------------------|" << endl;
            cout << "|      quit      |   Quit the game while still in play. |" << endl;
            cout << "|----------------|--------------------------------------|\n"<< endl;
            for(int i = 10; i > 0; i--){
                Sleep(1000);
                cout << "Timer : " << i << " Seconds" << endl;
            }


        }
        // to quit
        else if (movement == "quit")
        {
            cout << "Are you sure you wish to quit the game? Enter y/n. " << endl;
            cin >> confirm;
            if (confirm == 'y')
            {
                system("cls");
                return false;
            }

            else if (confirm == 'n')
            {
                system("cls");
            }
        }else if(movement == "save"){
            savegame(board,zombies,currentHealth,attack);
            Sleep(3000);
        }

        else if(movement=="load") {
            cout << "Would you like to save this game first? y/n?" << endl;
            cin >> confirm;
            if (confirm == 'y')
            {
                savegame(board,zombies,currentHealth,attack);
                cout << "You will now be taken to the main menu, please enter the load menu from there." << endl;
                Sleep(2000);
                system("cls");
                return false;
            }
            else if (confirm =='n')
            {
                cout << "You will now be taken to the main menu, please enter the load menu from there." << endl;
                Sleep(2000);
                system("cls");
                return false;
            }
        }else if(cin.fail()){
            errorhandling();
            cout << "Wrong Input!" << endl;
            Sleep(1000);

    }
}
}

int main()
{
    // Sets the seed random by using our time. So random will be extra random
    srand(time(NULL));


    while (true)
    {
        // 2d vector variable to start the program
        int userinput = mainmenu();
        // only one main menu
        if (userinput == 1)
        {
            vector<vector<string>> game = creategameboard();
            // this is to set all the characters in the gameboard
            gameboard(game);
            // This is the struct vector function, it setst all the zombies location and attributes
            vector<Zombies> zombies = zombie(game);
            // It takes the new zombie values and the board and uses it in the alienmove function
            bool run = alienmove(game, zombies);
            if (run == false)
            {
                continue;
            }
        }
        else if(userinput == 2)
        {
            boolean runfunction = true;
            while(true){
                Gamedata gameData;
                string filename;
                system("CLS");
                cout << "       Load Menu\n";
                cout << "=======================\n";
                cout << "Name of the file? or q\n";
                cout << "=======================\n";
                cout << "Your Input ->";
                cin >> filename;

                if(cin.fail()){
                    errorhandling;
                    cout << "Wrong Input" << endl;
                    continue;
                }else if((filename == "Q")||(filename == "q")){
                    system("CLS");
                    break;
                }else{
                    bool run = loadgame(gameData, filename);
                    if(run==true){
                        system("CLS");
                        runfunction = false;
                    }else if(run == false){
                        cout << "No File Found!";
                        Sleep(3000);
                        system("CLS");
                        main();
                    }
                }

                vector<vector<string>> game = gameData.board;
                // This is the struct vector function, it setst all the zombies location and attributes
                vector<Zombies> zombies = gameData.zombies;
                alienCol = gameData.alienCol;
                alienRow = gameData.alienRow;
                currentHealth = gameData.health;
                attack = gameData.damage;
                cout << gameData.health;
                // It takes the new zombie values and the board and uses it in the alienmove function
                bool run = alienmove(game, zombies);
                if (run == false)
                {
                    continue;
                }
            }
        }

        else if (userinput == 3)
                {
                    PlaySound(TEXT("music.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); //start playing sound
                }

        else if (userinput == 4)

                {
                    PlaySound(NULL, NULL, 0); // stop playing sound
                }
        else if (userinput == 5)
               {
            exit(0);
               }

    }
}

