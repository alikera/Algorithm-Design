#include <bits/stdtr1c++.h>

using namespace std;

struct Edge
{
    int start;
    int end;
    int weight;
};

vector<Edge> differ, edges;
vector<vector<int> > graph_1;
vector<vector<int> > graph_2;

vector<int> visited_1;
vector<int> visited_2;
int n, m;
vector<int> distances;

vector<int> q;
int size_q = 0;
int differ_size = 0;

void get_input()
{
    cin >> n >> m;
    vector<int> tt;
    vector<vector<int> > ttp(1001, tt);
    graph_1 = ttp;
    graph_2 = ttp;
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        
        graph_1[a].push_back(b);
        graph_2[b].push_back(a);
        
        Edge edge_t;
        edge_t.start = a;
        edge_t.end = b;
        edge_t.weight = 0;
        edges.push_back(edge_t);
    }
}
void visit_queue(vector<int>& visited, vector<vector<int> >& graph, int sth)
{
    visited[sth] = 1;
    q.insert(q.begin(), sth);
    size_q++;
    
    while(size_q)
    {
        int u = q[size_q-1];
        size_q--;
        for (auto v : graph[u])
        {
            if (visited[v] == 0)
            {
                visited[v] = 1;
                q.insert(q.begin(), v);
                size_q++;
            }
        }
    }
}
int main()
{
    get_input();
    vector<int> temp(1001, 0); 
    visited_1 = temp;
    visited_2 = temp;
    
    visit_queue(visited_1, graph_1, 1);
    
    visit_queue(visited_2, graph_2, n);
    
    for (int i = 1; i <= n; i++)
    {
        if(visited_2[i] == 0)
            continue;
            
        if (visited_1[i] == 0)
            continue;
            
        for (auto j : graph_1[i])
        {
            if(visited_2[j] == 0)
                continue;
                
            if (visited_1[j] == 0)
                continue;
            
            Edge edge_t;
            edge_t.start = i;
            edge_t.end = j;
            edge_t.weight = 2;
            differ.push_back(edge_t);
            differ_size++;
            
            Edge edge_tt;
            edge_tt.start = j;
            edge_tt.end = i;
            edge_tt.weight = -1;
            differ.push_back(edge_tt);
            differ_size++;
        }
    }
    
    vector<int> tempp(1001, 1999999999);
    distances = tempp;
    distances[1] = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < differ_size; j++)
            if(distances[differ[j].end] - differ[j].weight > distances[differ[j].start])
                distances[differ[j].end] = distances[differ[j].start] + differ[j].weight;
    
    int flag = 0;
    for (int j = 0; j < differ_size; j++)
        if (distances[differ[j].end] - differ[j].weight > distances[differ[j].start])
            flag = 1;
    
    if (flag)
        cout << "No" << endl;
        
    else 
    {
        cout << "Yes" << endl;
        for (int i = 0; i < m; i++)
        {
            if (distances[edges[i].end] == 1999999999)
                cout << 1 << endl;
                
            else if(distances[edges[i].start] == 1999999999)
                cout << 1 << endl;
                
            else
                cout << distances[edges[i].end] - distances[edges[i].start] << endl;
        }
    }
    return 0;
}
