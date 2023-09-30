#include <iostream>
#include <vector>
#include <string>

using namespace std;
long long int moves = 0;
long long int idx;

class Towers
{
public:
	void get_input(long long int& count);
	void find_min_height(long long int count);
	long long int find_min_moves(long long int from, long long int current, long long int to);
private:
	vector<long long int> towers;

};
void Towers::get_input(long long int& count)
{
	cin >> count;

	for (long long int i = 0; i < count; ++i)
	{
		long long int temp;
		cin >> temp;

		towers.push_back(temp);
	}
}

void Towers::find_min_height(long long int count)
{
	long long int min = 1000000001;
	for (long long int i = 0; i < count; ++i)
	{
		if (towers[i] < min)
			min = towers[i];
	}
}

long long int Towers::find_min_moves(long long int from, long long int current, long long int to)
{
	if(from >= to)
		return 0;

	long long int min_height_index = from;
	for(long long int k = from; k < to; k++)
	{
		if(towers[k] < towers[min_height_index])
			min_height_index = k;

		else
			idx = k;
	}

	long long int temp = find_min_moves(from, towers[min_height_index], min_height_index) 
				+ find_min_moves(min_height_index + 1, towers[min_height_index], to);

	long long int all_verticals = to - from;
	if (temp + towers[min_height_index] >= all_verticals + current)
		return (to - from);

	else
		return temp + towers[min_height_index] - current;


}

int main()
{
	long long int count;
	Towers tt;
	tt.get_input(count);	

	cout << tt.find_min_moves(0, 0, count);

}
