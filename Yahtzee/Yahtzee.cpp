
#include <iostream>
#include <algorithm>
#include <vector>
#include "player.h"
#include <time.h>
#include <list>
#include <fstream>
#include "scorecard.h"
#include "Yahtzee.h"
#include "game.h"

using namespace std;


string encrypt(string unencrypted) {
    /*Simple encryption by changing the value based on position in the string, making
    sure it can't be a comma as it is stored in a csv.*/

    int index = 0;
    char delim = *(",");
    for (char s : unencrypted) {
        unencrypted[index] -= 5 * (index + 1);
        if (unencrypted[index]==delim) {
            unencrypted[index] += 1;
        }
        index++;
    }
    return unencrypted;

}


void displayPlayer(const player* player) {
    player->display();
}
bool sortByName(const player* lhs, const player* rhs) {
    return (*(lhs)).isSmaller(rhs,true);
}
bool sortByScore(const player* lhs, const player* rhs) {
    
    return (*(lhs)).isSmaller(rhs, false);
}
vector<player*> readFile() {
    //reading all of the data from the players file, IE Name,Password,Highscore
    vector<player*> playersVector;
    ifstream file("players.csv");
    string line;
    int index = 0;
    string data[3];
    while (getline(file, line))
    {
        istringstream iss(line);
        string result;
        //Seperating out the commas from the data.
        while (getline(iss, result, ','))
        {
            data[index] = result;
            index++;
        }
        playersVector.push_back(new player(data[0], data[1], stoi(data[2])));
        index = 0;
    }
    //We pass through the vector and return it once we've updated it
    return playersVector;
}

void playerMenu(player* player) {
    //Seperate instance of a menu, where we already have the pointer to the specific player using it
    //Used for playing the game or looking at scores
    
    int option, optionTwo;
    int gameShown = 0;


    bool menu = true;
    bool menuTwo = true;
    while (menu) {
        //Making sure they have scorecards
        if (!player->scorecardsNullMem()) {
            player->readFile();
        }
        player->averageScoreCalc();
        player->displayAll();
        bool firstPass = true;
        cout <<
            "\n1: Play Game" <<
            "\n2: View Scoreboards" <<
            "\n9: Return\n";
        cin >> option;
        switch (option) {

        case 1:
            player->startGame();

            break;
        case 2:
            while (menuTwo) {

                if (firstPass) {
                    player->displayScorecard(gameShown);

                }

                cout <<
                    "\n1: Next Game" <<
                    "\n2: Previous Game" <<
                    "\n9: Return\n";
                cin >> optionTwo;

                switch (optionTwo) {

                case 1:

                    if (player->endOfScores(gameShown + 1)) {
                        cout << "\nError. No previous game";
                    }
                    else {
                        gameShown += 1;
                        player->displayScorecard(gameShown);
                    }
                    firstPass = false;
                    break;

                case 2:

                    if (gameShown - 1 < 0) {
                        cout << "\nError. No next game";
                    }
                    else {
                        gameShown -= 1;
                        player->displayScorecard(gameShown);
                    }
                    firstPass = false;
                    break;


                case 9:
                    menuTwo = false;
                    break;
                }
            }
            break;

        case 9:
            menu = false;
            break;
        }
    }
}

vector<player*>  login(vector<player*> playersVector,bool removing) {
    //A function that does both login and removing a player, the boolean parameter defining which it does
    string username, password;
    cout << "\nPlease enter a username: ";
    cin >> username;
    cout << "\nPlease enter a password: ";
    cin >> password;
    password = encrypt(password);
    bool success;
    for (vector<player*>::iterator it = playersVector.begin(); it != playersVector.end(); ++it) {
        success = (*it)->checkData(username, true);
        if (success) {

            if ((*it)->checkData(password, false)) {
                cout << "Login Success\n";
                if (!removing) {
                    playerMenu(*it);
                }
                else {
                    string filename = username + ".csv";
                    const char* file= filename.c_str();
                    if (remove(file) != 0)
                        cout << "Error deleting file";
                    else
                        cout << "File successfully deleted";
                    delete* it;
                    playersVector.erase(it);
                    return playersVector;

                }

            }
            else {
                cout << "Login Failed\n";
                break;
            }
        }        
    }
    if (!success) {
        cout << "No such user \n";
    }
    return playersVector;
}





void writeFile(vector<player*> playersVector)
{   //Writing Name,Password,Highscore back to the players file
    ofstream myfile;
    myfile.open("players.csv");
    vector<string> data;
    for (vector<player*>::iterator it = playersVector.begin(); it != playersVector.end(); ++it) {
        data = ((*it)->writeFile());
        myfile << data[0]<<"," <<data[1]<<"," <<data[2]<<"\n";
    }
    
    myfile.close();
    
}






int main()
{
#ifdef _DEBUG
    _onexit(_CrtDumpMemoryLeaks);
#endif
    //Starting the first menu loop
    int option;
    bool menu = true;
    string username, password;
    vector<player*> playersVector = readFile();
    //Reading all the players in the storage
    while (menu) {
        cout << "\nName      Highscore\n";
        for_each(playersVector.cbegin(), playersVector.cend(), displayPlayer);
        cout << "\nMenu"
            << "\n1: Select a player"
            << "\n2: Add player"
            << "\n3: Remove player"
            << "\n4: Sort players alpha"
            << "\n5: Sort by score"
            << "\n9: Exit\n";
        cin >> option;
        switch (option) {
        case 1:
            login(playersVector, false);
            break;
        case 2:
            cout << "\nPlease enter player name: ";
            cin >> username;
            cout << "\nPlease enter password: ";
            cin >> password;
            password = encrypt(password);
            playersVector.push_back(new player(username, password, 0));
            break;
        case 3:

            playersVector=login(playersVector, true);
            break;
        case 4:
            sort(playersVector.begin(), playersVector.end(), sortByName);
            break;
        case 5:
            sort(playersVector.begin(), playersVector.end(), sortByScore);
            break;
        case 9:
            writeFile(playersVector);
            for (vector<player*>::iterator it = playersVector.begin(); it != playersVector.end(); ++it) {
                
                
                if ((*it)->scorecardsNullMem()) {

                    ((*it)->writeIndivFile());
                    
                }
                
                delete* (it);
            }
            menu = false;
            break;
        }

        

    }
    return 0;
}

