#include <iostream>
#include <queue>
#include <vector>
#include <string.h>
#include <cmath>
using namespace std;
#define MAX_N 10000
int n;
int graph[MAX_N][MAX_N];
bool check[MAX_N][MAX_N];
vector<int> result;

struct node {
	int level;
	vector<int> path;
	int bound;
};

class mycomparison
{
	bool reverse;
public:
	mycomparison(const bool& revparam = false)
	{
		reverse = revparam;
	}
	bool operator() (const node& lhs, const node&rhs) const
	{
		if (reverse) return (lhs.bound > rhs.bound);
		else return (lhs.bound<rhs.bound);
	}
};


int TSP_Bound(const std::vector<int>& v) {
	int res = 0;
	memset(check, 0, sizeof(check));
	for (int i = 0; i < v.size() - 1; i++) {
		for (int j = 0; j < n; j++) {
			check[v[i]][j] = true;
		}
		check[v[i + 1]][v[i]] = true;
		for (int j = 0; j < n; j++) {
			check[j][v[i + 1]] = true;
		}
		res += graph[v[i]][v[i+1]];
	}
	for (int i = 0; i < n; i++) {
		int _min = 1e9;
		bool flag = false;
		for (int j = 0; j < n; j++) {
			if (j != i && check[i][j] == false) {
				flag = true;
				_min = min(graph[i][j],_min);
			}
		}
		if (!flag) {
			_min = 0;
		}
		res += _min;
	}
	return res;
}

bool isIn(int j, const vector<int> &x) {
	for (int i = 0; i < x.size(); i++) {
		if (j == x[i])
			return true;
	}
	return false;
}


int Length(const vector<int> &x) {
	int res = 0;
	for (int i = 0; i < x.size() - 1; i++) {
		res += graph[x[i]][x[i + 1]];
	}
	return res;
}

int TSM(int src) {
	int best = 1e9;

	vector<int> path(1, 0);
	node u{src, path, TSP_Bound(path)};
	node v;
	typedef priority_queue <node, vector<node>, mycomparison> mypq_type;
	mypq_type pq(true);

	pq.push(u);

	while (pq.size()) {
		u = pq.top();
		pq.pop();
		if (u.bound < best) {
			v.level = u.level + 1;
			for (int i = 1; i < n; i++) {
				bool flag = false; // biến cờ để xét xem i có nằm trong path hay không 
				for (int j = 0; j < u.path.size(); j++) {
					if (u.path[j] == i) {
						flag = true;
						break;
					}
				}
				if (!flag) {
					v.path = u.path;
					v.path.push_back(i);

					if (v.level == n - 2) {
						int j;
						for (j = 1; j < n; j++) {
							if (!isIn(j, v.path))
								break;
						}
						v.path.push_back(j);
						v.path.push_back(0);
						int LenghtV = Length(v.path);
						if (LenghtV < best) {
							best = LenghtV;
							result = v.path;
						}
					}
					else {
						v.bound = TSP_Bound(v.path);
						if (v.bound < best)
							pq.push(v);
					}
				}
			}
		}
	}

	return best;
}

int main() {




	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n;
	int temp;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> graph[i][j];
		}
	}

	int ret = TSM(0);
	cout << ret << endl;
	for (int i = 0; i < result.size(); i++) {
		cout << result[i] << " ";
	}
	

	return 0;
}