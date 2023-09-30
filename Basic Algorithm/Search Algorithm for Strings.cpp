#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <math.h>

using namespace std;
class Strings
{
public:
	void get_input();
	long long int create(long long int idx_1, long long int idx_2);
private:
	long long int base[301][301];
	string s;
	long long int s_size, t_size;
	string t;
};

void Strings::get_input()
{
	cin >> s_size >> t_size;
	cin >> s >> t;
 for (long long i = 0; i < 301; i++)
		for (long long j = 0; j < 301; j++)
  {
   if (i == 0)
				base[i][j] = 0;
   if (i != 0)
    base[i][j] = -11;
  }
}
int counter = 0;
long long int Strings::create(long long idx_1, long long idx_2)
{
	counter++;
	if(idx_2 - t_size >= 0)
  return 0;
 long long int size_similars = 0;
 vector<long long int> similars;
 for (long long int i = 0; i < s_size; i++)
 {
  if (s[i] == t[idx_2])
  	if (idx_1 != i || idx_2 == 0)
  	{
   	if ((i > 0 && s[i-1] == s[idx_1]) || (i < s_size-1 && s[i+1] == s[idx_1]))
   	{
    	similars.push_back(i);
    	size_similars++;
   	}
   	else if (idx_2 == 0 || abs(i-idx_1) <= 1)
   	{
   		similars.push_back(i);
    	size_similars++;
   	}
   }
 }
 // cout << size_similars << endl;
 if (size_similars == 0)
 {
  base[idx_2][idx_1] = -1; 
  return -1;
 }
 long long minimum = 99999999999;
 for (long long i = 0; i < size_similars; i++)
 {
 	long long int count;
 	if(idx_2 == 0)
 		count = 0;
 	else
 		count = 1;
  // cout << count << endl;
  if (idx_2 != 0 && abs(idx_1 - similars[i]) > 1)
   count = count-2 + abs(idx_1 - similars[i]) + 1;

  if (base[idx_2+1][similars[i]] == -11)
   base[idx_2+1][similars[i]] = create(similars[i], idx_2 + 1);

  // cout << count << endl;
  if (base[idx_2 + 1][similars[i]] != -1)
  {
	  if (base[idx_2 + 1][similars[i]] <= minimum - count)
	   minimum = base[idx_2 + 1][similars[i]] + count;
 	}
 }
 if (minimum == 99999999999)
 	return -1;
 else
 	return minimum;
}

int main()
{
	Strings top_level;
	top_level.get_input();
 cout << top_level.create(0, 0) << endl;
 // cout << counter;
 return 0;
}
