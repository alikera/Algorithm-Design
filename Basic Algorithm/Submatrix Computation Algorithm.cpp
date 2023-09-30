#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h>
using namespace std;

class Carpet
{
public:
    void get_input();
    void fill_ants();
    void find_minimum();
private:
    vector< vector<long long int> > ants;
    long long int m;
    long long int n;
    long long int masahat;

};

void Carpet::get_input()
{
    long long int m_,n_,k_;
    cin >> n_ >> m_ >> k_;


    m = m_;
    n = n_;
    masahat = k_;
    vector<long long int> temp(m,0);
    vector< vector<long long int> > my_vec(n, temp);

    ants = my_vec;
    fill_ants();
}

void Carpet::fill_ants()
{
    for (long long int i = 0; i < n; ++i)
        for (long long int j = 0; j < m; ++j)        
            cin >> ants[i][j];

}

void Carpet::find_minimum()
{
    long long int tajamoi[n][m];

    tajamoi[0][0] = ants[0][0];

    for (long long int j = 1; j < m; j++)
        tajamoi[0][j] = ants[0][j] + tajamoi[0][j - 1];


    for (long long int i = 1; i < n; i++) 
        tajamoi[i][0] = ants[i][0] + tajamoi[i - 1][0];

    for (long long int i = 1; i < n; i++)
        for (long long int j = 1; j < m; j++)
            tajamoi[i][j] = ants[i][j] + tajamoi[i - 1][j] + tajamoi[i][j - 1] - tajamoi[i - 1][j - 1];
    
    // for (long long int i = 0; i < n; i++)
    // {
    //     for (long long int j = 0; j < m; j++) {
    //         cout << setw(3) << tajamoi[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    vector< pair<long long int, long long int> > measures;

    long long int sth = masahat + 666;
    for (long long int z = masahat; z < sth; z++)
    {
        long long int radikal = (long long int)(sqrt(z));
        for (long long int i = 1; i <= radikal; i++)
            if(!(z % i))
            {
                pair<long long int, long long int> tt = make_pair(i, z / i);
                measures.push_back(tt);
            }
    }

    // for (long long int i = 0; i < measures.size(); ++i)
    // {
    //     cout << measures[i].first << " " << measures[i].second << endl;
    // }

    long long int answer = 10000000010;
    for (long long int i = 0; i < measures.size(); ++i)
    {
        long long int x = measures[i].first;
        long long int y = measures[i].second;

        if(x <= n && y <= m)
            for (long long int z = x - 1; z < n; ++z)
            {
                for (long long int w = y - 1; w < m; ++w)
                {
                    long long int temp = tajamoi[z][w];

                    if (z >= x && w >= y)
                        temp = temp + tajamoi[z - x][w - y];
                    if (w >= y)
                        temp = temp - tajamoi[z][w - y];
                    if (z >= x)
                        temp = temp - tajamoi[z - x][w];
                    if (temp < answer)
                        answer = temp;
                }
            }

        x = measures[i].second;
        y = measures[i].first;
        if(x <= n && y <= m)
            for (long long int z = x - 1; z < n; ++z)
            {
                for (long long int w = y - 1; w < m; ++w)
                {
                    long long int temp = tajamoi[z][w];

                    if (z >= x && w >= y)
                        temp = temp + tajamoi[z - x][w - y];
                    if (w >= y)
                        temp = temp - tajamoi[z][w - y];
                    if (z >= x)
                        temp = temp - tajamoi[z - x][w];
                    if (temp < answer)
                        answer = temp;
                }
            }
    }
    cout << answer << endl;
}
int main()
{
    Carpet carpet;
    carpet.get_input();

    carpet.find_minimum();


    return 0;
}