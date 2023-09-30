/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
long long int answer = 0;
struct Edge
{
    long long int weight;
    long long int start;
    long long int end;
};

class Graph
{
public:
    void get_input();
    void get_edges();
    void get_weights();
    
    long long int find(long long int v);

    void merge(long long int u, long long int v);
    void kruskal();


    void find_shortest_path_between_pairs();
    
private:
    vector<Edge> graph;
    vector<Edge> MST;
    vector<long long int> weights;
    vector<long long int> happiness;
    
    vector<long long int> parents;
    vector<long long int> h;
    vector<long long int> num_vertex;
    long long int V;
    long long int E;
    long long int MST_SIZE;
};

void Graph::get_input()
{
    long long int n, m;
    cin >> n >> m;
    V = n;
    E = m;
    
    vector<long long int> temp(V, 0);
    parents = temp;
    h = temp;
    num_vertex = temp;
    
    for (long long int i = 0; i < V; i++)
        parents[i] = i;
    
    for (long long int i = 0; i < V; i++)
        h[i] = 0;
    
     for (long long int i = 0; i < V; i++)
        num_vertex[i] = 1;
    
    get_weights();
    get_edges();

    // for(long long int i = 0; i < V; i++)
    // {
    //     if(graph[i].size())
    //         cout << " i : "<< i << "   " <<graph[i][0].id << " w " << graph[i][0].weight;
    // }
}
void Graph::get_weights()
{
    long long int w;
    for(long long int i = 0; i < V; i++)
    {
        cin >> w;
        weights.push_back(w);
    }
}
void Graph::get_edges()
{
    long long int src, dest;
    for(long long int i = 0; i < E; i++)
    {
        cin >> src >> dest;
        src--;
        dest--;
        
        long long int w_src = weights[src];
        long long int w_dest = weights[dest];
        
        long long int weight_min = (w_src < w_dest) ? w_src : w_dest;
        
        Edge Edge_t;
        Edge_t.start = src;
        Edge_t.end = dest;
        Edge_t.weight = weight_min;
        graph.push_back(Edge_t);
    }
}

long long int Graph::find(long long int v)
{
    while(parents[v] != v)
    {
        v = parents[v];
    }
    return v;
}

void Graph::merge(long long int u, long long int v)
{
    long long int root = find(u);
    long long int roott = find(v);
    
    if(h[root] == h[roott])
    {
        parents[roott] = root;
        h[root]++;
        num_vertex[root] += num_vertex[roott];
        return;
    }
    
    if(h[root] > h[roott])
    {
        parents[roott] = root;
        num_vertex[root] += num_vertex[roott];
        return;
    }
    
    //cout << parents[roott];
    
    if(h[root] < h[roott])
    {
        parents[root] = roott;
        num_vertex[roott] += num_vertex[root];
        return;
    }
    
    //cout << parents[root];
}
bool my_func(const Edge& a, const Edge& b)
{
    // Edge a1 = (Edge)a;
    // Edge b1 = (Edge)b;
    return a.weight > b.weight;
}

void Graph::kruskal()
{
    sort(graph.begin(), graph.end(), my_func);
    MST_SIZE = 0;
    for(long long int i = 0; i < E; i++)
    {
        long long int arr[3] = {graph[i].start, graph[i].end, graph[i].weight};
        // arr[0] = graph[i].start;
        // arr[1] = graph[i].end;
        // arr[2] = graph[i].weight;
        
        long long int root_u = find(arr[0]);
        long long int root_v = find(arr[1]);
        
        if(root_v != root_u)
        {
            answer += num_vertex[root_v] * num_vertex[root_u] * arr[2];
           //cout << " v:" << num_vertex[root_v] << " u:" << num_vertex[root_u] << " w:" << arr[2] << endl;

            Edge edge_t;
            edge_t.start = arr[0];
            edge_t.end = arr[1];
            edge_t.weight = arr[2];
            
            MST_SIZE++;
            merge(root_u, root_v);
        }
        if(MST_SIZE == V-1)
        {
            cout << answer << endl;
            return;
        }
    }
    //cout << num_
    //cout << num_vertex[root_v] << num_vertex[root_u] << endl << vertex[root_v] << num_vertex[root_u] << endl;
    // for(long long int i = 0; i < V-1; i++)
    // {
    //     cout << "u: " << MST[i].start << "v: " << MST[i].end << "w: " << MST[i].weight << endl; 
    // }
    cout << answer << endl;
}
// void Graph::max_happiness(long long int src)
// {
//     vector<long long int> temp(V, 0);
//     happiness = temp;
//     happiness[src] = 1999999999;
    
//     vector<len> track;
//     Edge Edge_t;
//     Edge_t.weight = 0;
//     Edge_t.id = src;
//     track.push_back(Edge_t);
//     long long int size_track = 1;
    
//     while(size_track)
//     {
//         curr = track[size_track-1];
//         size_track--;
//         long long int size_adj = graph[curr].size();
//         for(long long int i = 0; i < size_adj; i++)
//         {
//             long long int w_t, max_t;
//             max_t = (graph[i].weight < track[curr]) ? graph[i].weight : track[curr];
//         }
//     }
// }
int main()
{
    Graph graph;
    graph.get_input();
    graph.kruskal();

    return 0;
}

