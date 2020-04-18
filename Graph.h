#include<database.h>
# define INF 2147483647
#ifndef GRAPH_H
#define GRAPH_H


typedef pair<int, int> iPair;

class Graph
{
	int V;
	map<int,string>departments;
	map<string,int>intdep;
	list< int > *adj;
	vector<int>parent;
	int exit;

public:
	Graph();
	~Graph();
	int n_vertices();
	void addEdge(int u, int v);
	void create();
    void printPath(vector<int> parent, int j,vector<int> &ans);
	vector<int> shortestPath(int s , vector<int> &parent);
	void navigate(set<string> vertices);
    void path_taken(int cur_vertice , map<int,bool> &visited ,vector<int> &ans,vector<int> &cur_path,int cost=INF,int cur_cost=0);
    void display();
    void clearmap();


};
#endif // GRAPH_H


