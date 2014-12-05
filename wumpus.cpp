/******************************************************
    This programs Is a game I, Daniel Cortez, Made
    where you are a player in a cave of size nxn where you
    decide the amount of n (between 10-20). And during your course
    through the cave you can find weapons, gold, pits, and monsters.
    each find has different outcomes.

*********************************************************/

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

void delay(clock_t sec)
{
    // delay output function
    clock_t start_time = clock();
    clock_t end_time = sec* 1000000 + start_time;

    while (clock() != end_time);
};

void update(int n)
{
    // updates the output by multiplying multiple endl
    for(int i = 0; i < n; i++)
        cout << "\n";
};

void instructions()
{
    // instruction set.
    cout << "*********************************" << endl;
    cout << " Here are the meanings of the symbols to help\n"
         << " you understand the game better.\n" << endl;
    cout << " @ -  This is the hero's marker. " << endl;
    cout << " ? - Unexplored room that could contain a multitute of mysteries." << endl;
    cout << " # - This is a wall." << endl;
    cout << " $ - Gold in a room you have already explored but didn't loot" << endl;
    cout << " . - An previously explored room." << endl;
    cout << " ^ - the entrance to the cave and only exit." << endl;
    cout << " if at any point you feel lost," << endl;
    cout << " Enter (?) into an input and this menu will pop up." << endl;
    cout << " Good Luck!" << endl;
    cout << "*********************************" << endl;
    cout << "\n\n";

};

void gameIntro()
{
    // output the title and the instrucitons
    cout << "*************************************" << endl;
    cout << "*                                   *" << endl;
    cout << "*          Wumpus Cave!             *" << endl;
    cout << "*                                   *" << endl;
    cout << "*************************************" << endl;
    cout << "\n\n";

    //instructions
    instructions();

};

void weapon_to_money(int** key, int n)
{
    // change all the weapons in the cave to money

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            if(char(key[i][j] == '*'))
                key[i][j] = '$';

}
void setInput(int ** cave, int** key, int& row, int& col, bool& weapon, bool& dead, int& points, int n)
{
    // set the input after it has passed the error checking in getInput()

    char ans = ' '; // value that will be inputed for wether a room will be looted or not.
    string gearUp = "You have come across a mighty sword,\nit is now part of your gear!";
    string wumpus = "The foul stentch of the Wumpus has filled the room! \nlook out!";
    string wumpus_defeat = "you have slayed the wumpus!";
    string wumpus_death = "You have been slayed by the Wumpus! \nLoser!";
    string money = "You have found money!\nDo you want to loot it? ( (y)es or (n)o? )\n>";
    string empty = "This room is empty!";
    string stars = "********************************************************************";
    string cons= "CONSEQUENCES OF YOUR MOVE:";


    //delay the print for a second
    delay(1);

    cout << cons << endl;

    // delay the print for a second
    delay(1);

    cout << stars << endl;

    // current position cases.
    switch( char( key[row][col]) )
    {
        case '$':
                cout << money << endl;
                cin >> ans;
                if (toupper(ans) == 'Y')
                {
                    key[row][col] = '.';
                    points += 5;
                }
                else if (toupper(ans) == 'N')
                {
                    points += 0;
                    cout << "You have not looted the gold!\nAre you sure you read the instructions?" << endl;
                }
                break;
        case '*':
                cout << gearUp << endl;
                points += 5;
                weapon = true;
                key[row][col] = '.';
                weapon_to_money(key, n);
                break;
        case 'W':
                cout << wumpus << endl;
                delay(1);
                if (weapon == true)
                {
                    cout << wumpus_defeat << endl;
                    points += 10;
                }
                else
                {
                    cout << wumpus_death << endl;
                    dead = true;
                }
                break;
        case 'O':
                cout << "You fell to your death ! LOSER! " << endl;
                dead = true;
                break;
        case '.':
                cout << empty << endl;
                points += 1;
                break;
    }

    cout << stars << endl;

    // delay before it updates one more time
    delay(5);

};

bool checkValid(int** cave, int row, int col)
{
    // checks for wall from input.
    if(char(cave[row][col]) != '#')
        return true;
    else
        return false;

};

void getInput(int** cave, int** key, int& row, int& col, bool& v_input)
{
    // get input and error check.

    char move = ' ';                // input holder.

    // string to output if you go somewhere you can't go.
    string dummy = "You can't go there dummy! There is a wall there!";

    cout << endl;
    cout << "----------------------------------------------------------------" << endl;
    cout << "If you input multiple things, only the first value is evaluated." << endl;
    cout << "Please enter your next move" << endl;
    cout << "----------------------------------------------------------------\n" << endl;
    cout << "( (u)p, (d)own, (r)ight, (l)eft (?)instructions):\n>";
    cin >> move;

    move = toupper(move);           // uppercase of all input.


    // make the move and set the cells that the hero was in before to it's proper values.
    // then move the hero to the new cell
    if( move == 'U' || move == 'L' || move == 'R' || move == 'D' || move == '?')
    {
        v_input = true;
        switch(move)
        {
            case 'U':
                    if(checkValid(cave, row -1, col))
                    {
                        if (char (key[row][col]) != '^' && char(key[row][col]) != 'O' && char(key[row][col]) != '$')
                            cave[row][col] = '.';
                        else
                            cave[row][col] = key[row][col];

                        row--;
                        cave[row][col] = '@';
                    }
                    else
                        cout << dummy << endl;
                    break;
            case 'D':
                    if(checkValid(cave,row + 1,col))
                    {
                        if (char (key[row][col]) != '^' && char(key[row][col]) != 'O' && char(key[row][col]) != '$')
                            cave[row][col] = '.';
                        else
                            cave[row][col] = key[row][col];

                        row++;
                        cave[row][col] = '@';
                    }
                    else
                        cout << dummy << endl;
                    break;
            case 'R':
                    if(checkValid(cave,row,col + 1))
                    {
                        if (char (key[row][col]) != '^' && char(key[row][col]) != 'O' && char(key[row][col]) != '$')
                            cave[row][col] = '.';
                        else
                            cave[row][col] = key[row][col];

                        col++;
                        cave[row][col] = '@';
                    }
                    else
                        cout << dummy << endl;
                    break;
            case 'L':
                    if(checkValid(cave,row,col - 1))
                    {
                        if (char (key[row][col]) != '^' && char(key[row][col]) != 'O' && char(key[row][col]) != '$')
                            cave[row][col] = '.';
                        else
                            cave[row][col] = key[row][col];

                        col--;
                        cave[row][col] = '@';
                    }
                    else
                        cout << dummy << endl;
                    break;
            case '?':
                    instructions();
                    delay(5);
                    break;
        }// END SWITCH
    }// END IF
    else
    {
        v_input = false;
        cout << "Invalid entry" << endl;
    }

    // incase there is more things in the command line, this gets rid of them.
    while(true)
    {
        move = cin.peek();

        if (move == '\n')
            break;
        else
            move = cin.get();
    }

};

void surroundings(char val)
{
    // print various statements depending on the value of
    cout << endl;

    delay(2);
    switch (val)
    {
        case 'W':
            cout << "There is a wretched smell coming from a room nearby... Be careful!\n";
            break;
        case '$':
            cout << "There are riches to be looted close by!\n";
            break;
        case '*':
            cout << "A powerful weapon to fight the wretched Wumpus is near...\n";
            break;
        case 'O':
            cout << "Watch your step, we don't want you FALLING!\n";
            break;
    }

};

void print(int** key, int** cave, int i, int j)
{
    // function prints the surroundings of the hero

    bool wumpus = false;
    bool weapon = false;
    bool gold = false;
    bool pit = false;
    string stars = "********************************************************";

    for( int row = i - 1; row <= i + 1; row++)
    {
        cout << endl;
        cout << setw(20) << right;
        for( int col = j - 1; col <= j + 1; col++ )
        {
            cout << char(cave[row][col]) << " ";

            // check to see next rooms containment
            switch( char(key[row][col]) )
            {
                case 'W':
                        wumpus = true;
                        break;
                case 'O':
                        pit = true;
                        break;
                case '$':
                        gold = true;
                        break;
                case '*':
                        weapon = true;
                        break;
            }// end switch

        }// END FOR
        cout << endl;
    }// END FOR

    cout << left << endl;

    cout << endl;
    cout << stars;

    //output surroundings
    if (wumpus == true)
        surroundings('W');
    if (gold == true)
        surroundings('$');
    if (weapon == true)
        surroundings('*');
    if(pit == true)
        surroundings('O');

    cout << stars << endl;
};

void start(int** key, int** cave, int n, int& row, int& col)
{
    // initialize the starting point
   int x = 0;
   int y = 0;

   while (true)
   {
       x = rand() % (n - 1) + 1;
       y = rand() % (n - 1) + 1;

       if( cave[x][y] == '?')
       {
            cave[x][y] = '@';
            key[x][y] = '^';
            row = x;
            col = y;
            break;
       }
   }
}

void setCave(int** cave, int n)
{
    // set the rooms in the cave (composes 25 percent of the cave

    int wumpusVal = int( n * n * .15 );         // wumpus amount
    int pitVal = int(n * n * .05);              // pit amount
    int gold = int(n * n * .15);                // gold amount
    int weapon = int(n * n * .15);              // weapon amount
    int x = 0;                                  // random x cordinate in the 2d array
    int y = 0;                                  // random y cordinate in the 2d array

    // set the rooms with wumpus
    while( wumpusVal > 0)
    {
        x = rand() % (n - 1) + 1;
        y = rand() % (n - 1) + 1;

        if(cave[x][y] == '?')
        {
            cave[x][y] = 'W';
            wumpusVal--;
        }
    }

    // set the rooms with pits
    while( pitVal > 0)
    {
        x = rand() % (n - 1) + 1;
        y = rand() % (n - 1) + 1;

        if(cave[x][y] == '?')
        {
            cave[x][y] = 'O';
            pitVal--;
        }
    }

    // set rooms with gold
    while( gold > 0)
    {
        x = rand() % (n - 1) + 1;
        y = rand() % (n - 1) + 1;

        if(cave[x][y] == '?')
        {
            cave[x][y] = '$';
            gold--;
        }
    }

    // set rooms with weapons
    while( weapon > 0)
    {
        x = rand() % (n - 1) + 1;
        y = rand() % (n - 1) + 1;

        if(cave[x][y] == '?')
        {
            cave[x][y] = '*';
            weapon--;
        }
    }

    // set empty rooms (remaining rooms)
    for(int i = 1; i < n-1 ;i++ )
        for(int j = 1; j < n-1; j++)
        {
            if(cave[i][j] == '?')
                cave[i][j] = '.';
        }


};
void createCave(int** cave, int n)
{
    // initialize the cave with # for edges.
    for( int j = 0; j < n; j++ )
        for( int m = 0; m < n; m++ )
        {
            // top margin
            if ( j == 0 )
                cave[j][m] = '#';
            // left margin
            else if ( m == 0 )
                cave[j][m] = '#';

            // bot margin
            else if( j == n-1 )
                cave[j][m] = '#';

            //right margin
            else if( m == n-1)
                cave[j][m] = '#';
            //rest
            else
                cave[j][m] = '?';

        }//END INSIDE FOR

    //add the rooms depicted as '#'
};

void playGame(int n)
{
    // fucntion plays the game
    int** keyCave = new int*[n];                // initialization of the cave  using a 2D array
                                                // this will be the key that contains everything in the cave
    for(int i = 0; i < n; i++)
        keyCave[i] = new int[n];

    int** gameCave = new int*[n];               // game cave to show the user.

    for(int i = 0; i < n; i++)
        gameCave[i] = new int[n];

    int row = 0;                                // start x coordinate
    int col = 0;                                // start y coordinate
    int points = 0;                             // point score
    bool dead = false;                          // flag to see if you are still alive.
    bool leave = false;                         // flag for if the user went back to the entrance
    bool weapon = false;                        // weapon equipped.
    bool valid_input = true;

    string equipped = "None";                   // string that prints what is equiped by the user

    //create the keycave (make 2D array)
    createCave(keyCave, n);

    // this makes the key for the cave
    setCave(keyCave, n);

    // make the gameCave
    createCave(gameCave, n);

    // initialize the start position
    start( keyCave, gameCave, n, row, col );

    //****************************
    // the key of the cave
    //****************************
    /*for(int i = 0; i < n; i++)
    {
        cout << endl;
        for(int j = 0; j < n; j++)
            cout << " " << char(keyCave[i][j]) ;

        cout << endl;
    }
    */

    while(true)
    {
        if (weapon == true)
            equipped = "Sword";

        delay(2);

        //print \n a few times to show new board.
        update(50);

        // output the board
        cout << left;
        cout << "Score:" << points << left;
        cout << setw(40) << right << "Equipped Weapon:"<< equipped << endl;

        print(keyCave, gameCave, row, col);

        // ask for input and when valid calls setInput within this function
        getInput( gameCave, keyCave, row, col, valid_input);
        cout << endl;

        //ask for action if there is something in the room.
        if(valid_input)
        {
            setInput(gameCave, keyCave, row, col, weapon, dead, points, n);

            if (char(keyCave[row][col] == '^'))
                leave = true;

            if (dead == true || leave == true)
            {
                cout << "You have died or left the cave." << endl;
                cout << "Your points were: " << points << endl;
                cout << "Play again sometime" << endl;
            break;
            }
        }

    }

    cout << "\n\n";

}

int main()
{
    int n;              // room size = n x n;
    string noInt = "There was no integer value entered, please retry";
    char buff = '\n';

    gameIntro();

    // ask for a room size
    try
    {
        cout << "Enter number between 10-20 to create a cave:\n>";
        cin >> n;

        if(!cin)
            throw noInt;
        else if(n < 10 || n > 20)
            throw n;
        else
            playGame(n);
    }
    catch(int n)
    {
        cout << n << " is invalid  because it's out of range.\n" << endl;
    }
    catch(string s)
    {
        cout << s << endl;
    }

    return 0;
}
