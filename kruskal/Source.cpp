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
	int cost = 0;// наш кратчайший путь
	int count = 0;// количество ребер в полученном остовном подграфе
	
	int n;
	fin >> n;// количество вершин
	vector < pair < int, pair<int, int> > > g; // вес - вершина 1 - вершина 2 
	vector<vector<string>> matr;// матрица смежности (из строк для того, чтобы можно было написать inf если вершины не соединены, потом буду инвертировать строку в число)
	matr.resize(n);
	for (auto &el : matr) {
		el.reserve(n);		
	}
	for (auto &el : matr) {
		for (int i = 0; i < n; ++i) {
			string s;
			fin >> s;
			
			el.push_back(s);// заполняем матрицу смежности 
			
		}
	

	}
	
	for (int i = 0; i < n-1; ++i) {
		for (int j = i+1; j < n; ++j) {// пробегаю по матрицы смежности 
			{if(matr[i][j]!="inf")// пропускаю все ячейки, где записан inf
				g.push_back(make_pair(atoi((matr[i][j]).c_str()), make_pair(i, j)));// кладу значение матрицы в вектор g
				
			}
		}
	}


	
	
	vector < pair<int, int> > res;//  колиечество пар смежных вершин для остовного подграфа(дерева)

	sort(g.begin(), g.end());
	vector<int> tree_id(n);// вектор в котором будем проверять объединены ли вершины или нет
	for (int i = 0; i < n; ++i)//n- количество вершин
		tree_id[i] = i;// помещаем каждую вершину в свое дерево
	for (int i = 0; i<g.size(); ++i)// пока есть ребра в данном графе  
	{
		int a = g[i].second.first, //определяем первую вершину
			b = g[i].second.second, // определяем втору вершину
			lenght = g[i].first;// определяем вес
		if (tree_id[a] != tree_id[b])// проверяем не объеденены ли вершины
		{
			cost += lenght;// суммируем веса для короткого пути
			res.push_back(make_pair(a, b));// закидываем пару вершин нашего дерева в  вектор
			int old_id = tree_id[b],
				new_id = tree_id[a];
			for (int j = 0; j < n; ++j)
				if (tree_id[j] == old_id)//проверяем на образование циклов
					tree_id[j] = new_id;//объединяем вершины
			
		}
	}
	sort(res.begin(), res.end());
	fout << "ADJACENT PEAKS" << endl;
	for (auto el : res) {
		fout <<"("<< el.first << " , " << el.second<<")" << endl;// вывод смежных вершин каркаса
	}
	
	fout <<"The shortest path: "<< cost << endl;// вывод кратчайшего пути
	
	
	
	return 0;
}