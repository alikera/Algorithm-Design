/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
struct Edge
{
    long int vertex;
    long int weight;
    
    long int tb;
};
class Matrix
{
public:
    void create_graph(long int n);
    long int find_max_flow();
    bool bfs_traversal(vector<long int>& parents);

    bool travers_adj(vector<long int>& que, vector<bool>& visited, long int& sss, long int node, vector<long int>& parents);

    void set_value_nodes();


private:
    vector<vector<long int> > graph;
    vector<vector<long int> > residual;
    vector<vector<long int> > graph_t;
    long int E;
    long int X;
};
vector<long int> seq;
// vector<vector<long int> > table;
void Matrix::create_graph(long int n)
{
    E = 2*n;
    X=n;
    
    vector<long int> tt(E+2, 0);
    vector<vector<long int> > ttp(E+2, tt);
    graph = ttp;
    graph_t = ttp;
    
    for (long int i = 0; i < n; i++)
    {
        graph[E][i] = 1;
        graph_t[E][i] = 1;
        // for (long int j = 0; j < n; j++)
        // {
        //     long int sth;
        //     cin >> sth;
        //     table[i][j] = sth;
        //     seq.push_back(sth);
        // }
        for(long int j = n; j < E; j++)
        {
            long int sth;
            cin >> sth;
            // table[i][j-n] = sth;
            seq.push_back(sth);
            
            //Edge edge_t;
            //Edge_t.vertex = j;
            //Edge_t.weight = 1;
            //Edge_t.tb = sth;
            
            graph[i][j] = 1;
            graph_t[i][j] = sth;
            
            graph[j][E+1] = 1;
            graph_t[j][E+1] = 1;
        }
    }
    // for (long int j = 0; j < n; j++)
    // {
    //     Edge edge_t;
    //     edge_t.vertex = j;
    //     edge_t.weight = 1;
    //     edge_t.tb = -1;

    //     graph[E][j] = 1;
    //     graph_t[E][j] = 1;
    // }
    // for (long int j = n; j < E; j++)
    // {
    //     Edge edge_t;
    //     edge_t.vertex = E+1;
    //     edge_t.weight = 1;
    //     edge_t.tb = -1;
        
    //     graph[j][E+1] = 1;
    //     graph_t[j][E+1] = 1;
    // }
    // for (long int i = 0; i < n; i++)
    // {
    //     for(long int j = 0; j < n; j++)
    //     {
    //         //cout << graph[i][j].vertex << "w" << graph[i][j].tb << " ";
    //     }
    //     //cout << endl;
    // }
    // for (long int i = n; i < E; i++)
    // {
        
    //     //cout << graph[i][0].vertex << "w" << graph[i][0].tb << " ";
    
    //     //cout << endl;
    // }
    // for (long int i = 0; i < n; i++)
    // {
    //     //cout << graph[E][i].vertex << "w" << graph[E][i].tb << " ";
    // }
    // //cout << graph[E][j].vertex << "w" << graph[E][j].tb << " ";
    //cout << "here" << endl;
}
long int current;

long int get_input()
{
    long int size_table;
    cin >> size_table;
    
    
    // for (long int i = 0; i < size_table; i++)
    // {
    //     for (long int j = 0; j < size_table; j++)
    //     {
    //         long int sth;
    //         cin >> sth;
    //         table[i][j] = sth;
    //         seq.push_back(sth);
    //     }
    // }
     
    return size_table;       
}
bool Matrix::bfs_traversal(vector<long int>& parents)
{
    ////cout << "here" << endl;
    vector<long int> que;
    vector<bool> visited(E+2, false);
    
    que.push_back(E);
    visited[E] = true;
    
    long int sss = 1;
    long int z = 0;
    
    parents[E] = -1;
    while(sss)
    {
        ////cout << "here1" << endl;
        long int node = que[z];
        ////cout << node << endl;
        z++;
        sss--;
        if(travers_adj(que, visited,sss, node, parents))
            return true;
    }
    
    //cout << "nowwwwwww" << endl;
    return false;
}

bool Matrix::travers_adj(vector<long int>& que, vector<bool>& visited, long int& sss, long int node, vector<long int>& parents)
{
    long int i;
    bool flag = false;
    //cout << "LLLLL" << endl;
    for (i = 0; i < E+2; i++)
    {
        if (visited[i] == false && residual[node][i] > 0)
        {
            if(graph_t[node][i] <= current)
            {
                if (i == E+1)
                {
                    //cout << "dest_found" << endl;
                    parents[i] = node;
                    flag = true;
                }
                if(flag == true)
                    return true;
                que.push_back(i);
                sss++;
                parents[i] = node;
                visited[i] = true;
            }
        }
    }
    //cout << "nothing" << endl;
    return false;

}

void Matrix::set_value_nodes()
{
    // for (long int i = 0; i < E; i++)
    // {
    //     if(seq[i] == 0)
    //     {
    //         Edge edge_t;
    //         edge_t.vertex = ZERO;
    //         edge_t.weight = ZERO;
    //         graph[i].push_back(edge_t);
    //     }
    //     else
    //     {
    //         Edge edge_t;
    //         edge_t.vertex = ONE;
    //         edge_t.weight = ONE;
    //         graph[i].push_back(edge_t);
    //     }
    // }
}
long int Matrix::find_max_flow()
{
    //Edge //Edge_t;
    //Edge_t.vertex = -100;
    //Edge_t.weight = -100;
    vector<long int> parents(E+2, -100);

    residual = graph;
    long int answer = 0;
    // for (long int i = 0; i < E+2; i++)
    // {
    //     for(long int j = 0; j < residual[i].size(); j++)
    //     {
    //         //cout << residual[i][j];
    //     }
    //     //cout << endl;
    // }
    bool while_condition = false;
    
    do
    {
        while_condition = bfs_traversal(parents);
        if(!while_condition)
            break;
        long int j;
        //cout << "ffff";
        //cout << "love" << endl;
            
        long int flw = 1999999999;
        ////cout << "ssd" << parents[E+1] << endl;
        for (long int i = E+1; i != E; i = parents[i])
        {
            long int j = parents[i];
            if(residual[j][i] < flw)
                flw = residual[j][i];
        }
        for (long int i = E+1; i != E; i = parents[i])
        {
            long int j = parents[i];
            residual[j][i] -= flw;
            residual[i][j] = residual[i][j] + flw;
        }
        
        answer = answer + flw;
    }
    while(while_condition);

    return answer;
}
int main()
{
    std::ios::sync_with_stdio(false);
    long int n = get_input();
    Matrix mat;
    mat.create_graph(n);
    sort(seq.begin(), seq.end());
    //cout << "now" << endl;
    // srand(time(0));
    // cout << rand()%2;
    for (long int i = 0; i < n*n; i=i+ 1)
    {
        // cout << rand()%2+1;
        current = seq[i];
        long int out = mat.find_max_flow();
        
        // cout << "out" << out << endl;
        if(out == n)
            break;
            
        if(out > n)
        {
            cout << seq[i-1];
            return 0;
        }
    }
    
    cout << current;
}


