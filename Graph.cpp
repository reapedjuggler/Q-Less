#include "Graph.h"

int Graph :: n_vertices()
{
    return V;
}

Graph::Graph()
{

     int i=1;
     ifstream fin;
        fin.open("files/skulist/skulist_department_backup.txt");
        if(!fin)
        {   cout<<"Error"<<endl;

        }
        departments.insert(make_pair(0,"Entrance"));
        while(!fin.eof())
        {
            string str,sku;
            fin>>sku>>str;
            intdep.insert(make_pair(str,i));
            departments.insert(make_pair(i++,str));
        }
        exit=i;
        departments.insert(make_pair(i,"EXIT"));
        fin.close();


    vector<int> temp(departments.size(),-1);
	parent = temp;
	this->V = departments.size();
	adj = new list<int> [V];
    remove("files/graph/map_backup.txt");
	fin.open("files/graph/map.txt");
	if(!fin)
	{
        ofstream fout;
        fout.open("files/graph/map.txt");
        cout<<"NEW MAP\n";
        fout.close();
        fin.open("files/graph/map.txt");

	}
	else
	{   fin>>i;
        while(i!=-2)
        {
            int temp1;
            fin>>temp1;
            while(temp1!=-1)
            {
                adj[i].push_back(temp1);

                fin>>temp1;
            }
            fin>>i;
        }
	}
    fin.close();
    rename("files/graph/map.txt","files/graph/map_backup.txt");

}
Graph::~Graph()
{
    ofstream  fout;
    fout.open("files/graph/map.txt");
    for(int i=0;i<V-2;i++)
    {
        fout<<i<<endl;
        for(auto it=adj[i].begin();it!=adj[i].end();it++)
            fout<<*it<<endl;
        fout<<-1<<endl;
    }
    fout<<-2;
    fout.close();
}

void Graph::addEdge(int u, int v)
{
	adj[u].push_back(v);
	adj[v].push_back(u);

}

void Graph :: create()
{
    auto tempit1=departments.end();
    tempit1--;
    tempit1--;
    cout<<"Department List:\n";
    for(auto it=departments.begin();it!=departments.end();it++)
        if( it!=tempit1)
            cout<<it->first<<"      "<<it->second<<endl;
    cout<<"Press -1 when done telling connections\n";
    cout<<"Entrance is Connected to Departments:";
    int x;
    bool flag=1;

    cin>>x;
    do
    {
        if(x==-1 && flag)
        {
            cout<<"Entrance must be connect to atleast one department\n";
            cin>>x;
            continue;
        }
        flag=0;
        addEdge(0,x);
        cin>>x;

    }
    while(x!=-1);

    for(int i=1;i<V-2;i++)
    {
        cout<<departments[i]<<" is Connected to Departments:";
        cin>>x;
        while(x!=-1)
        {
            addEdge(i,x);
            cin>>x;
        }

    }



}
vector<int> Graph::shortestPath(int src, vector<int> &parent)
{

	priority_queue< iPair, vector <iPair> , greater<iPair> > pq;

	vector<int> dist(V, INF);

	pq.push(make_pair(0, src));
	dist[src] = 0;

	vector<bool> f(V, false);

	while (!pq.empty())
	{

		int u = pq.top().second;
		pq.pop();
		f[u] = true;


		for (auto i = adj[u].begin(); i != adj[u].end(); ++i)
		{
			int v = *i;
			int weight = 1;

			if (f[v] == false && dist[v] > dist[u] + weight)
			{
                parent[v]=u;
				dist[v] = dist[u] + weight;
				pq.push(make_pair(dist[v], v));
			}
		}
	}
	return dist;


}
void Graph :: printPath(const vector<int> parent, int j,vector<int> &ans)
{
    if (parent[j]==-1)
        return;

    printPath(parent, parent[j],ans);
    ans.push_back(j);
}



void Graph :: path_taken(int cur_vertice , map<int,bool> &visited ,vector<int> &ans,vector<int> &cur_path,int cost,int cur_cost)
{
    vector<int>temp;
    vector<int>parent(n_vertices(),-1);
    temp=shortestPath(cur_vertice,parent);
    visited[cur_vertice]=true;

    bool flag=1;
    for(auto it=visited.begin();it!=visited.end();it++)
    {
        if(it->second==false)
        {
            auto tempit=cur_path.end();
            vector<int>b;
            printPath(parent,it->first,b);
            cur_path.insert(cur_path.end(), b.begin(), b.end());
            flag=0;
            path_taken(it->first,visited,ans,cur_path,cost,cur_cost+temp[it->first]);
            for(int i=0;i<b.size();i++)
            cur_path.pop_back();
        }
    }

    if(flag)
        if (cost>cur_cost+temp[exit])
            cost=cur_cost,ans=cur_path;
    visited[cur_vertice]=false;
    return;

}

void Graph :: navigate(set<string> vertices)
{
   map<int,bool> visited;
    for(auto it=vertices.begin();it!=vertices.end();it++)
    {

        visited.insert(make_pair(intdep[*it],false));
    }
    vector<int>ans,cur;

    path_taken(0,visited,ans,cur);

    cout<<"From Starting ";
    for(int i=0;i<ans.size();i++)
    {
        if(vertices.find(departments[ans[i]])!=vertices.end())
            cout<<"visit ";
        else
            cout<<"go through ";
        cout<<departments[ans[i]]<<" then\n";

    }
    cout<<"Go to Exit\n";

}
void Graph:: display()
{
    for(int i=0;i<V-2;i++)
    {
        cout<<i<<" :";
        for(auto it=adj[i].begin();it!=adj[i].end();it++)
            cout<<*it<<" ";
        cout<<endl;
    }
    cout<<endl;
}
void Graph :: clearmap()
{
    for(int i=0;i<V;i++)
        adj[i].clear();
}
/*

*/

