#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Node
{
public:
    Node(long long int key_);
    void add_adj(long long int node);


    long long int get_key() { return key; }
    long long int get_visited() { return visited; }
    long long int get_diameter() { return diameter; }
    long long int get_diameter_2() { return diameter_2; }
    long long int get_parent() { return adj[0]; }
    long long int get_degree() { return degree; }

    void set_values(long long int diam, bool vis);
    void set_diameter_2();
    void travers_adj(vector<long long int>& ghotr, vector<long long int>& que, vector<bool>& visited, long long int& sss);
    bool delete_adj(long long int node);
    void delete_node();
private:
    vector<long long int> adj;
    long long int key;
    long long int degree;
    long long int diameter;
    long long int diameter_2;
    bool visited;
};
Node::Node(long long int key_)
{
    key = key_;
    degree = 0;
}

void Node::set_values(long long int diam, bool vis)
{
    diameter = diam;
    visited = vis;
}

void Node::set_diameter_2()
{
    diameter_2 = diameter;
}
void Node::add_adj(long long int node)
{
    adj.push_back(node);
    degree++;
}

void Node::travers_adj(vector<long long int>& ghotr, vector<long long int>& que, vector<bool>& visited, long long int& sss)
{
    for (long long int i = 0; i < degree; ++i)
    {
        if (!visited[adj[i]])
        {
            ghotr[adj[i]] += ghotr[key];
            visited[adj[i]] = true;
            ghotr[adj[i]]++;
            que.push_back(adj[i]);
            sss++;

        }
    }
}

bool Node::delete_adj(long long int node)
{
    auto it = adj.begin();
    for (long long int i = 0; i < degree; ++i)
        if(adj[i] == node)
            adj.erase(it+i);

    degree--;
    if(degree == 1)
        return true;
    else
        return false;
}

void Node::delete_node()
{
    degree = 0;
    diameter = -1;
    diameter_2 = -1;
    // adj.clear();
}

class Tree
{
public:
    void initialize();
    void get_input();
    long long int bfs_traversal(long long int key);
    pair<long long int, long long int> find_ghotr();
    bool find_leaves(pair<long long int,long long int> exceptions);
    long long int shrink_candy_tree();
    bool is_path();
    void print_out();
private:
    vector<Node> tree;
    vector<long long int> leaves;
    vector<long long int> ghotr;
    vector<long long int> ghotr_2;
    size_t size;

    long long int candy;
};

void Tree::initialize()
{
    long long int n;
    cin >> n;
    size = n;
    for (long long int i = 0; i < n; ++i)
    {
        Node node(i);
        tree.push_back(node);
    }
    candy = 0;
}

void Tree::get_input()
{
    for (long long int i = 0; i < size-1; ++i)
    {
        long long int x, y;
        cin >> x >> y;

        tree[x-1].add_adj(y-1);
        tree[y-1].add_adj(x-1);
    }
}

long long int Tree::bfs_traversal(long long int key)
{
    vector<long long int> que;
    vector<bool> visited(size, false);
    vector<long long int> dd(size, 0);
    ghotr = dd;

    que.push_back(key);
    visited[key] = true;
    long long int sss = 1;
    long long int z = 0;
    while(sss)
    {
        long long int node = que[z];
        z++;
        sss--;
        tree[node].travers_adj(ghotr, que, visited, sss);
    }

    long long int max_idx = 0;
    for (long long int i = 1; i < size; ++i)
        if(ghotr[i] > ghotr[max_idx])
            max_idx = i;

    return max_idx;
}

pair<long long int, long long int> Tree::find_ghotr()
{
    // long long int nominated;
    // for (auto node : tree)
    //     if(node->get_degree() != 0)
    //         nominated = node->get_key();

    long long int start = bfs_traversal(0);
    long long int end = bfs_traversal(start);

    return make_pair(start, end);
}
long long int my_size = 0;

bool Tree::find_leaves(pair<long long int,long long int> exceptions)
{
    for(auto node : tree)
        if (node.get_degree() == 1 && node.get_key() != exceptions.first && node.get_key() != exceptions.second)
        {
            my_size++;
            leaves.push_back(node.get_key());
        }
    
    if(my_size == 2)
        return true;
    else
        return false;
}
long long int Tree::shrink_candy_tree()
{
    long long int max = 0;
    pair<long long int,long long int> diam_found = find_ghotr();
    // cout << diam_found.first << "mm" << diam_found.second << endl;
    
    ghotr_2 = ghotr;

    long long int len_diam = ghotr[diam_found.second];
    
    
    if(len_diam == 2)
    {
        long long int w = (size-2)*2 + 1;
        return w;
    }
    long long int dummy = bfs_traversal(diam_found.second);
    find_leaves(diam_found);

    long long int z = 0;
    while(my_size >= 1)
    {
        long long int l = leaves[z];
        
        max = 0;
        if(ghotr[l] > max)
            max = ghotr[l];

        if(ghotr_2[l] > max)
            max = ghotr_2[l];

        candy += max;

        long long int idx_parent = tree[l].get_parent();

        if(tree[idx_parent].delete_adj(l))
        {
            my_size++;
            leaves.push_back(idx_parent);
        }


        my_size--;
        z++;
    }


        candy += (len_diam+1)*len_diam / 2;
    return candy;
}
void Tree::print_out()
{
    long long int w = size*(size-1)/2;
    cout << w << endl;
}
int main()
{
    Tree candy_tree;
    candy_tree.initialize();
    candy_tree.get_input();

    cout << candy_tree.shrink_candy_tree() << endl;
    return 0;
}
