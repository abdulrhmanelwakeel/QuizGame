#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

struct User // User Inforamtions
{
    int score = 0;
    string name;
};
User user;

void startGame();

int gameQuestion(ifstream& file);

map<string, int> mp;
void showScore(string userName, int userScore);

int main()
{
    cout << "*** Welcome to the Quiz Game ***" << endl;
    startGame();

    return 0;
}

void startGame()
{
    while (true) // Game loop
    {



        cout << "Enter User Name:  "; // User login
        cin >> user.name;

        string feild;
        ifstream file1;

        bool flag = false;
        do // Chossing the filed
        {
            if (flag)
            {
                cout << "Invaild Answer!!" << endl;
            }
            cout << "Choose a Feild: \nPress 'sp' for Sports, Press 't' for Tech, Press 'm' for Movies, Press 'sc' for scince" << endl;
            cin >> feild;
            flag = true;
        } while (feild != "sp" && feild != "sc" && feild != "m" && feild != "t");

        if (feild == "sp") // Sport Filed
        {
            file1.open("Sport.txt");
            user.score = gameQuestion(file1);
        }
        else if (feild == "t") // Technology Filed
        {
            ifstream file1("Tech.txt");
            user.score = gameQuestion(file1);
        }
        else if (feild == "m") // Movies Filed
        {
            ifstream file1("Movies.txt");
            user.score = gameQuestion(file1);
        }
        else if (feild == "sc") // Scince Filed
        {
            ifstream file1("Science.txt");
            user.score = gameQuestion(file1);
        }

        showScore(user.name, user.score); // Score seaction

        char key;
        cout << "Press 'p' to play again , 'x' to Quit" << endl;
        cin >> key;

        if (key == 'p')
        {
            continue;
        }
        if (key == 'x')// Closing game
        {
            break;
        }


    }

}

int gameQuestion(ifstream& file)
{
    string question[10], c1[10], c2[10], c3[10], c4[10];
    char rightAns[10];
    int correct = 0, award = 250, k = 0;

    while (file >> question[k] >> c1[k] >> c2[k] >> c3[k] >> c4[k] >> rightAns[k]) // Read from the File
    {
        for (int i = 0; i < question[k].size(); i++) // Remove underscore from file
        {
            if (question[k][i] == '_')
            {
                cout << ' ';
            }
            else
            {
                cout << question[k][i];
            }
        }
        cout << endl;

        cout << c1[k] << ' ' << c2[k] << ' ' << c3[k] << ' ' << c4[k] << endl; //Showing Choices
        cout << "Enter the Answer: A or B or C or D" << endl;

        char ans; // Get user Choice
        cin >> ans;

        if (ans == rightAns[k] || ans == rightAns[k] + 32)
        {
            cout << "Correct Answer!! You Won " << award << " L.E" << endl;
            award *= 2; // Award increasment
            correct++;  // Count correct answers

            if (correct == 5) // 1st Round
            {
                cout << "Congratulations!! You reached Level 2" << endl;
            }
            if (correct == 10) // 2nd Round
            {
                cout << "Congratulations!! You won the Quiz Game" << endl;
            }
        }
        else // Wrong answer
        {
            cout << "Sorry, Wrong Answer" << endl;
            cout << endl;
            cout << "****************" << endl;
            break;
        }
        cout << endl;
        cout << "********" << endl;

        k++;
    }

    file.close(); // Closing file

    return correct;
}

void showScore(string userName, int userScore)
{
    ifstream readScore("Score.txt"); // Read old scores from the Score File
    string name;
    int score, rank;
    while (readScore >> rank >> name >> score)
    {
        mp[name] = score;
    }

    mp[userName] = userScore; // Add new Scores

    ofstream scoreFile("Score.txt"); // Open the File to Write on it
    int j = 1;
    bool full = false;

    for (int i = 10; i >= 0; i--)
    {
        for (auto it : mp) // Searching in the Map for all the users with score i
        {
            if (j <= 10 && it.second == i)
            {
                scoreFile << j << " " << it.first << " " << it.second << endl; // Save the score in external File
                j++;                                                           // Count the number of users saved
            }
            else if (j > 10) // Stop Ranking after the 10th user
            {
                full = true;
                break;
            }
        }
        if (full) // Flag to break the loop
        {
            break;
        }
    }
}