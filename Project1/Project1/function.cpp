#include <iostream>
#include "windows.h"
#include <vector>
#include <stack>
#include <ctime>
#include <queue>
using namespace std;

struct  edge
{
	int a, b, cost;
};

void DFS(int **arr, int n,int index, int flag = 0) {
	cout <<"DFS"<< endl;
	stack<int> s;
	int *nodes = new int[n];
	for (int i = 0; i < n; i++) {
		nodes[i] = 0;
	}
	s.push(index);
	while (!s.empty()) {
		int node = s.top();
		s.pop();
		if (nodes[node] == 999) continue;
		nodes[node] = 999;
		for (int j = n - 1; j >= 0; j--) {
			if (arr[node][j] != 0 && nodes[j] !=999) {
				s.push(j);
				nodes[j] = 1;
			}
		}
		if (flag == 1) {
			cout << "v" << node << endl;
		}
	}
	cout << "Finish algorithm" << endl;
	delete[] nodes;
}

void BFS(int **arr, int n,int index,int flag=0) {
	cout << "BFS"<< endl;
	queue<int> s;
	int *nodes = new int[n];
	for (int i = 0; i < n; i++) {
		nodes[i] = 0;
	}
	s.push(index);
	while (!s.empty()) {
		int node = s.front();
		s.pop();
		nodes[node] = 999;
		for (int j = 0; j < n; j++) {
			if (arr[node][j] != 0 && nodes[j] == 0) {
				s.push(j);
				nodes[j] = 1;
			}
		}
		if (flag == 1) {
			cout << "v" << node << endl;
		}
	}
	cout << "Finish algorithm" << endl;
	delete[] nodes;
}

void dijkstra(int **arr, int n,int index, int flag=0) {
	int end;
	int *d = new int[n];
	int *v = new int[n];
	int minindex, min,temp;
	for (int i = 0; i < n; i++) {
		d[i] = 10000;
		v[i] = 1;
	}
	d[index] = 0;
	do {
		minindex = 10000;
		min = 10000;
		for (int i = 0; i < n; i++) {
			if ((v[i] == 1) && (d[i] < min)) {
				min = d[i];
				minindex = i;
			}
		}
		if (minindex != 10000) {
			for (int i = 0; i < n; i++) {
				if (arr[minindex][i] > 0) {
					temp = min + arr[minindex][i];
					if (temp < d[i]) {
						d[i] = temp;
					}
				}
			}
			v[minindex] = 0;
		}
	} while (minindex < 10000);

	for (int o = index; o < n; o++) {
		end = o;
		if (d[end] == 10000) {
			//cout << "No path from v" << index << " to v" << end << "." << endl;
			continue;
		}
		int *ver = new int[n];
		int saveEnd = end;
		ver[0] = end + 1;
		int k = 1;
		int weight = d[end];
		while (end > index) {
			for (int i = 0; i < n; i++) {
				if (arr[end][i] != 0) {
					int temp = weight - arr[end][i];
					if (temp == d[i]) {
						weight = temp;
						end = i;
						ver[k] = i + 1;
						k++;
					}
				}
			}
		}
		if (flag == 1) {
			cout << "Найкоротший шлях з v" << index << " до v" << saveEnd << endl;
			for (int i = k - 1; i >= 0; i--) {
				cout << ver[i] - 1 << " ";
			}
			cout << endl;
		}
		delete[] ver;
	}
	delete[] d;
	delete[] v;
}

void floid_uorshal(int **arr, int n, int flag=0) {
	cout << endl;
	time_t start, end1;
	cout << "Floid_uorshall algorithm" << endl;
	time(&start);
	int INF = 9999999;
	int **d = new int*[n];
	int index, end;
	for (int i = 0; i < n; i++) {
		d[i] = new int[n];
		for (int j = 0; j < n; j++) {
			d[i][j] = arr[i][j];
			if (arr[i][j] == 0) d[i][j] = INF;
		}
	}
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {			
			for (int j = 0; j < n; j++) {
				if (d[i][j] > d[i][k] + d[k][j])
					d[i][j] = d[i][k] + d[k][j];
			}
		}
	}

	for (int i = 0; i < n; i++) {
		d[i][i] = 0;
	}
	for (int q = 0; q < n; q++) {
		for (int w = q + 1; w < n; w++) {
			index = q;
			end = w;
			if (d[index][end]== INF ) {
				//cout << "No path from v" << index << " to v" << end << "." << endl;
				continue;
			}
			int *ver = new int[n];
			int saveEnd = end;
			ver[0] = end + 1;
			int k = 1;
			int weight = d[index][end];
			while (end > index+1) {
				for (int i = 0; i < n; i++) {
					if (arr[end][i] != 0) {
						int temp = weight - arr[end][i];
						if (temp == d[index][i]) {
							weight = temp;
							end = i;
							ver[k] = i + 1;
							k++;
						}
					}
				}
			}
			if (flag == 1) {
				cout << "Найкоротший шлях з v" << index << " до v" << saveEnd << endl;
				for (int i = k - 1; i >= 0; i--) {
					cout << ver[i] - 1 << " ";
				}
				cout << endl;
			}
			delete[] ver;
		}
	}
	time(&end1);
	cout << difftime(end1,start) << endl;
	cout << "Finish algorithm" << endl;
	cout << endl;
	for (int i = 0; i < n; i++) {
		delete[] d[i];
	}
	delete[] d;
}

void bellman(int **arr,vector<edge> e, int n, int index, int flag=0) {
	int INF = 9999;
	int *d = new int[n];
	for (int i = 0; i < n; i++) {
		d[i] = INF;
	}
	d[index] = 0;
	int end;
	int from, to;
	for (; ;) {
		bool any = false;
		for (int j = 0; j < e.size(); ++j) {
			from = e[j].a;
			to = e[j].b;
			if (d[to] > d[from] + e[j].cost) {
				d[to] = d[from] + e[j].cost;
				any = true;
			}
		}
		if (!any) break;
	}
	
	for (int o = index; o < n; o++) {
		end = o;
		if (d[end] == INF) {
			//cout << "No path from v" << index << " to v" << end << "." << endl;
			continue;
		}
		int *ver = new int[n];
		int saveEnd = end;
		ver[0] = end + 1;
		int k = 1;
		int weight = d[end];
		while (end > index) {
			for (int i = 0; i < n; i++) {
				if (arr[end][i] != 0) {
					int temp = weight - arr[end][i];
					if (temp == d[i]) {
						weight = temp;
						end = i;
						ver[k] = i + 1;
						k++;
					}
				}
			}
		}
		if (flag == 1) {
			cout << "Найкоротший шлях з v" << index << " до v" << saveEnd << endl;
			for (int i = k - 1; i >= 0; i--) {
				cout << ver[i] - 1 << " ";
			}
			cout << endl;
		}
		delete[] ver;
	}
	delete[] d;
}


void dijkstra_ready(int **arr, int n,int flag=0) {
	time_t start, end;
	cout << "Dijkstra algorithm" << endl;
	time(&start);
	for (int i = 0; i < n; i++) {
		dijkstra(arr, n, i, flag);
	}
	time(&end);
	cout << difftime(end, start)<<endl;
	cout << "Finish algorithm" << endl;
}

void bellman_ready(int **arr, vector<edge> e, int n,int flag=0) {
	time_t start, end;
	cout << "Bellman-Ford algorithm" << endl;
	time(&start);
	for (int i = 0; i < n; i++) {
		bellman(arr, e, n, i, flag);
	}
	time(&end);
	cout<<difftime(end,start)<<endl;
	cout << "Finish algorithm" << endl;
}

void my_variant() {
	int n = 17;
	int **arr = new int*[n];
	for (int i = 0; i < n; i++) {
		arr[i] = new int[n];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			arr[i][j] = 0;
		}
	}
	arr[0][1] = 4;  arr[0][2] = 3;   arr[0][3] = 2;   arr[1][3] = 1;  arr[1][4] = 5;
	arr[2][4] = 1;  arr[2][11] = 7;  arr[3][10] = 5;  arr[4][6] = 4;  arr[4][8] = 15;
	arr[4][10] = 4;  arr[4][15] = 8;  arr[5][9] = 2;  arr[5][12] = 8;  arr[5][7] = 7;
	arr[5][13] = 8;  arr[6][8] = 4;  arr[6][10] = 7;  arr[7][9] = 12;  arr[7][11] = 8;
	arr[8][9] = 9;  arr[8][12] = 8;   arr[8][15] = 5;   arr[8][16] = 20;  arr[9][12] = 8;
	arr[9][14] = 2; arr[10][11] = 4;   arr[12][16] = 9;   arr[13][15] = 5;  arr[14][16] = 1;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (arr[i][j] != 0) arr[j][i] = arr[i][j];
		}
	}
	/*for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}*/

	vector<edge> e;
	edge temp;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (arr[i][j] != 0) {
				temp.a = i;
				temp.b = j;
				temp.cost = arr[i][j];
				e.push_back(temp);
			}
		}
	}
	for (int i = 0; i < n; i++) {
		DFS(arr, n, i,1);
	}
	cout << endl;
	for (int i = 0; i < n; i++) {
		BFS(arr, n,i, 1);
	}
	cout << endl;
	dijkstra_ready(arr, n,1);
	floid_uorshal(arr, n,1);
	bellman_ready(arr, e, n,1);

}

int  **create_graph(vector<edge> &E, int i) {
	edge temp;
	int a, b, cost;
	int k = rand() % (2 * i) + i * 3;
	int **arr = new int*[i];
	for (int j = 0; j < i; j++) {
		arr[j] = new int[i];
		for (int u = 0; u < i; u++) {
			arr[j][u] = 0;
		}
	}
	for (int j = 0; j < k; j++) {
		a = rand() % i;
		b = rand() % i;
		cost = rand() % 200;
		arr[a][b] = cost;
		arr[b][a] = cost;
	}
	for (int u = 0; u < i; u++) {
		for (int j = 0; j < i; j++) {
			if (arr[u][j] != 0) {
				temp.a = u;
				temp.b = j;
				temp.cost = arr[u][j];
				E.push_back(temp);
			}
		}
	}
	return arr;
}

void last_task() {
	for (int i = 1000; i < 3000; i += 100) {
		vector<edge> E;
		int **arr = create_graph(E, i);
		/*for (int u= 0; u < i; u++) {
			for (int k = 0; k < i; k++) {
				cout<<arr[u][k]<<" ";
			}
			cout << endl;
		}
		for (int j = 0; j < i; j++) {
			DFS(arr, i, j);
		}
		cout << endl;
		for (int j = 0; j < i; j++) {
			BFS(arr, i, j);
		}*/
		dijkstra_ready(arr, i);
		floid_uorshal(arr, i);
		bellman_ready(arr, E, i);
		for (int j = 0; j < i; j++) {
			delete[] arr[j];
		}
		delete[] arr;
		vector<edge>().swap(E);
	}
}

int main() {
	srand(time(NULL));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	//my_variant();
	last_task();
	cout << endl;
	system("pause");

 
}