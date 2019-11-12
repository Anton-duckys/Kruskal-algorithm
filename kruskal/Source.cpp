#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<stdlib.h>
#include<fstream>
using namespace std;

int main() {
	ifstream fin;
	ofstream fout;
	fin.open("input.txt");
	fout.open("output.txt");
	int cost = 0;// our shortest path
	int count = 0;// amount of edges in spanning subgraph
	
	int n;
	fin >> n;// amount of verexes
	//vector for defining edges
	vector < pair < int, pair<int, int> > > g; // cost - vertex 1 - vertex 2 
	vector<vector<string>> matr;// adjacency matrix of weighted graph
	//fill adjacency matrix from file
	matr.resize(n);
	for (auto &el : matr) {
		el.reserve(n);		
	}
	for (auto &el : matr) {
		for (int i = 0; i < n; ++i) {
			string s;
			fin >> s;
			
			el.push_back(s); 
			
		}
	

	}
	// put values of adjacency matrix into vector of pairs g
	for (int i = 0; i < n-1; ++i) {
		for (int j = i+1; j < n; ++j) { 
			{if(matr[i][j]!="inf")
				g.push_back(make_pair(atoi((matr[i][j]).c_str()), make_pair(i, j)));
				
			}
		}
	}


	
	// vector for edges in spanning subgraph
	vector < pair<int, int> > res;

	sort(g.begin(), g.end());
	vector<int> tree_id(n);
	for (int i = 0; i < n; ++i)
		tree_id[i] = i;
	for (int i = 0; i<g.size(); ++i)
	{
		int a = g[i].second.first, 
			b = g[i].second.second, 
			lenght = g[i].first;
		if (tree_id[a] != tree_id[b])
		{
			cost += lenght;
			res.push_back(make_pair(a, b));
			int old_id = tree_id[b],
				new_id = tree_id[a];
			for (int j = 0; j < n; ++j)
				if (tree_id[j] == old_id)
					tree_id[j] = new_id;
			
		}
	}
	sort(res.begin(), res.end());
	fout << "ADJACENT PEAKS" << endl;
	// print our edges in spanning subgraph
	for (auto el : res) {
		fout <<"("<< el.first << " , " << el.second<<")" << endl;
	}
	
	fout <<"The shortest path: "<< cost << endl;
	
	
	
	return 0;
}