#include <bits/stdc++.h>
using namespace std;
bool sortbysec(const pair<string, long> &a,
               const pair<string, long> &b)
{
    return (a.second < b.second);
}
class ScoreHandler
{
    long stime = 0, etime = 0, ttime;
    vector<pair<string, long>> data;

public:
    fstream db;
    ScoreHandler()
    {
        ifstream infile("highscore.dat");
        string name;
        long score;
        string line;
        while (getline(infile, line))
        {
            istringstream iss(line);
            if (!(iss >> name >> score))
            {
                break;
            }
            data.push_back({name, score});
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
    void setHighScore(string name)
    {
        ttime = etime - stime;
        data.push_back({name, ttime});
        sort(data.begin(), data.end(), sortbysec);
        ofstream db("highscore.dat");
        for (auto ele : data)
        {
            db << ele.first << " " << ele.second << endl;
        }
        db.close();
    }
};

int main()
{
    ScoreHandler s;

    s.display();
    return 0;
}