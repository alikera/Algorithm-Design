#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h>
using namespace std;

typedef vector<int> sequence;
class Travel
{
public:
	void get_input();
	void get_sequences(sequence& seq);
	int find_min_time();

private:
	int fill_t;
	int num_of_cities;
	sequence distances;
	sequence capacities; 
};

void Travel::get_input()
{
	int n, k;
	cin >> n >> k;

	fill_t = k;
	num_of_cities = n;

	get_sequences(distances);
	get_sequences(capacities);
}

void Travel::get_sequences(sequence& seq)
{
	int inp;
	for (int i = 0; i < num_of_cities; ++i)
	{
		cin >> inp;
		seq.push_back(inp);
	}
}

int Travel::find_min_time()
{
	int sum_dist = 0;
	int sum_feul = 0;
	int max_index = 0;
	int reach_time = 0;

	for (int i = 0; i < num_of_cities; ++i)
	{
		sum_dist += distances[i];
		sum_feul += capacities[i];
		reach_time += distances[i];

		while (sum_dist > sum_feul)
		{
			sum_feul += capacities[max_index];
			reach_time += fill_t;
		}

		if(i == num_of_cities - 1)
			break;
		else
		{
			if (capacities[i+1] > capacities[max_index])
				max_index = i+1;
		}
	}

	return reach_time;
}
int main()
{
	Travel machine;

    machine.get_input();
    cout << machine.find_min_time();

    return 0;
}