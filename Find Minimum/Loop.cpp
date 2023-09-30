#include <iostream> 

using namespace std;

class Lake
{
public:
	void get_input();
	int find_min_rocks();
	~Lake();
private:
	int* lake;
	size_t lake_size;
	int frog_range;
	int min;
};
Lake::~Lake()
{
	if(lake != nullptr)
		delete lake;
}
void Lake::get_input()
{
	int w, l;
	cin >> w >> l;
	frog_range = l;

	lake = new int[w-1];
	int counter = 0;
	for (int i = 0; i < w-1; ++i)
	{
		cin >> lake[i];
		if(i < l)
			counter += lake[i];
	}
	min = counter;
	lake_size = w-1;
}
int Lake::find_min_rocks()
{
	int sum = min;
	// cout << min << endl;
	for(int k = 1; k <= lake_size - frog_range; k++)
	{
		sum -= lake[k-1];
		// cout << " llll  " << lake[k+frog_range-1] << endl;
		sum += lake[k+frog_range-1];

		if (sum < min)
			min = sum;

		// cout << "sum "<< sum << endl;
	}
	return min;
}
int main()
{
	Lake base;
	base.get_input();
	cout << base.find_min_rocks() << endl; 

}