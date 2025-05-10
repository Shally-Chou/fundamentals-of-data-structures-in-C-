#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <queue>
#include <set>

using namespace std;

// 產生graph
void generateRandomGraph(int n, int e, vector<vector<int>>& adjMatrix, vector<vector<int>>& adjList) {    //
    srand(time(0));    //
    set<pair<int, int>> edgeSet;    //

    while ((int)edgeSet.size() < e) {
        int u = rand() % n;    //設vertex
        int v = rand() % n;
        if (u != v) {    //確保不是自己走到自己
            int a = min(u, v), b = max(u, v);    //
            if (edgeSet.count({a, b}) == 0) {    //如果這條路還沒被記錄到
                edgeSet.insert({a, b});    //加進去
                adjMatrix[a][b] = adjMatrix[b][a] = 1;    //設矩陣 a,b=b,a 無向圖 長度一律設為1
                adjList[a].push_back(b);    //
                adjList[b].push_back(a);    //
            }
        }
    }
}

// 匯出CSV file
void exportEdgeList(const vector<vector<int>>& graph, const string& filename) {    //
    ofstream file(filename);
    file << "Vertex 1,Vertex 2\n";    //寫入file的第一行
    int n = graph.size();    //
    for (int u = 0; u < n; ++u) {    //歷遍串列
        for (int v : graph[u]) {    //
            if (u < v) file << u << "," << v << "\n";    //避免邊出現重複
        }
    }
    file.close();
}

// DFS 遍歷
void dfs(int u, vector<bool>& visited, const vector<vector<int>>& graph, vector<vector<int>>& tree) {    //
    visited[u] = true;    //標記為走過 grey
    for (int v : graph[u]) {    //
        if (!visited[v]) {    //如果連到的點有沒走過的 white
            tree[u].push_back(v);    //
            tree[v].push_back(u);    //
            dfs(v, visited, graph, tree);    //重跑dfs u變成v
        }
    }
}

// BFS 遍歷
void bfs(int start, vector<bool>& visited, const vector<vector<int>>& graph, vector<vector<int>>& tree) {    //
    queue<int> q;    //建一個列 放等等要尋訪的東西 像是看1把2,3放進去 看2序列變成3,4,5
    q.push(start);    //把起始點放到列裡面 top是1就把1放進去
    visited[start] = true;    //標記為走過 grey

    while (!q.empty()) {    //當列不為空時就一直跑
        int u = q.front(); q.pop();    //最前面的值給u 然後把他從列中刪掉
        for (int v : graph[u]) {
            if (!visited[v]) {    //如果連到的點有沒走過的 white
                visited[v] = true;    //過去 標為走過 grey
                tree[u].push_back(v);    //
                tree[v].push_back(u);    //
                q.push(v);    //
            }
        }
    }
}

// 印出鄰接矩陣
void printAdjMatrix(const vector<vector<int>>& matrix) {    //
    int n = matrix.size();
    cout << "    ";
    for (int i = 0; i < n; ++i) cout << i << "  ";    //有幾個數字就印到多少 阿從0開始
    cout << endl;
    for (int i = 0; i < n; ++i) {
        cout << " " << i << " ";
        for (int j = 0; j < n; ++j) {
            cout << " " << matrix[i][j] << " ";    //
        }
        cout << endl;
    }
}

// 印出鄰接串列
void printAdjList(const vector<vector<int>>& adjList) {    //
    for (int i = 0; i < adjList.size(); ++i) {    //
        cout << i << ": ";
        for (int j : adjList[i]) cout << j << " ";    //
        cout << endl;    //
    }
}

int main() {
    int n, e;
    cout << "請輸入節點數 n：";
    cin >> n;
    int maxEdge = n * (n - 1) / 2;
    cout << "請輸入邊數 e（最大為 C(n,2) = " << maxEdge << "）：";
    cin >> e;

    if (e > maxEdge) {
        cout << "邊數超過最大可能值，請重新輸入。" << endl;
        return 0;    //
    }

    vector<vector<int>> adjMatrix(n, vector<int>(n, 0));    //
    vector<vector<int>> adjList(n);    //
    generateRandomGraph(n, e, adjMatrix, adjList);    //

    cout << "\n鄰接矩陣 :" << endl;
    printAdjMatrix(adjMatrix);    //

    cout << "\n鄰接串列 :" << endl;
    printAdjList(adjList);    //

    // 匯出graph
    exportEdgeList(adjList, "graph_edges.csv");    //

    // DFS Tree
    vector<vector<int>> dfs_tree(n);    //
    vector<bool> visited(n, false);    //
    for (int i = 0; i < n; ++i)
        if (!visited[i]) dfs(i, visited, adjList, dfs_tree);    //
    exportEdgeList(dfs_tree, "dfs_tree_edges.csv");    //

    // BFS Tree
    vector<vector<int>> bfs_tree(n);
    fill(visited.begin(), visited.end(), false);    //
    for (int i = 0; i < n; ++i)
        if (!visited[i]) bfs(i, visited, adjList, bfs_tree);    //
    exportEdgeList(bfs_tree, "bfs_tree_edges.csv");    //

    // 印出 DFS/BFS Tree 的鄰接串列
    cout << "\nDFS Tree 的鄰接串列:" << endl;
    printAdjList(dfs_tree);

    cout << "\nBFS Tree 的鄰接串列:" << endl;
    printAdjList(bfs_tree);

    cout << "\n圖與 DFS/BFS Tree 已輸出成 CSV！" << endl;

    return 0;
}
