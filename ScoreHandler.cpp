#include <bits/stdc++.h>
using namespace std;
// helper function for sorting
bool sortbysec(const pair<string, long> &a,
               const pair<string, long> &b)
{
    return (a.second < b.second);
}
class ScoreHandler
{
    long stime = 0, etime = 0, ttime; //  start time , end time , total time
    vector<pair<string, long>> data;  // to store file data
public:
    fstream db;
    ScoreHandler()
    {
        ifstream infile("highscore.dat"); // open file
        string name;
        long score;
        string line;
        while (getline(infile, line)) // iterate through each line
        {
            istringstream iss(line);     // creating  string stream object
            if (!(iss >> name >> score)) // checking for errors
            {
                break;
            }
            data.push_back({name, score}); // storing in data
        }
    }
    void display()
    {
        cout << "HIGHSCORE:\n\n\n";
        int i = 1;
        cout << "-------------------------------------------------------------------------\n";
        cout << " POSITION |\t\tNAME\t\t|\tTIME(in seconds) \n";
        cout << "-------------------------------------------------------------------------\n";

        for (auto ele : data)
        {
            cout << "    " << i << "\t\t\t";
            cout << ele.first;
            for (int j = 0; j < 30 - (ele.first).length(); j++)
                cout << " ";
            cout << "" << ele.second << "\n";
            i++;
        }
    }
    void startime()
    {
        stime = time(NULL);
    }
    void endtime()
    {
        etime = time(NULL);
    }
    // function to set high score
    void setHighScore(string name)
    {
        ttime = etime - stime;
        data.push_back({name, ttime});
        sort(data.begin(), data.end(), sortbysec); // sort vector
        ofstream db("highscore.dat");
        for (auto ele : data)
        {
            db << ele.first << " " << ele.second << endl; // write to database
        }
        db.close();
    }
};
