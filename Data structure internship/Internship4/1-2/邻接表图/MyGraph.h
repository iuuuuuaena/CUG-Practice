#pragma once
#include"Graphlnk.h"
#include"MinHeap.h"
#include"MST.h"
template<class T,class E>
class MyGraph:public Graphlnk<T,E>
{
public:
	MyGraph(int sz = DefaultVertices) :Graphlnk<T, E>(sz) {}
	~MyGraph() {};
	void input();
	void output();
	void dfs(const T& v);
	void bfs(const T& v);

	bool CreatByFile(ifstream &in);
	void Prim(MinSpanTree<T, E>& MST);

private:

};

template<class T, class E>
void MyGraph<T, E>::Prim(MinSpanTree<T, E>& MST)
{
	MSTEdgeNode<T, E> ed; //边结点辅助单元
	int i, u, v, count;
	int n = this->NumberOfVertices();	  //顶点数	
	int m = this->NumberOfEdges();	  //边数
//	int u = getVertexPos(u0);		  //起始顶点号
	u = 0;
	MinHeap <E, MSTEdgeNode<T, E> > H(m);  //最小堆
	bool *Vmst = new bool[n];   //最小生成树顶点集合
	for (i = 0; i < n; i++) Vmst[i] = false;
	Vmst[u] = true;		        //u 加入生成树
	count = 1;
	do {			        //迭代	
		v = this->getFirstNeighbor(u);
		while (v != -1) {	 //检测u所有邻接顶点		
			if (!Vmst[v]) {	        //v不在mst中			
				ed.tail = u;  ed.head = v;
				ed.key = this->getWeight(u, v);
				H.Insert(ed);	        //(u,v)加入堆
			}     //堆中存所有u在mst中, v不在mst中的边
			v = this->getNextNeighbor(u, v);
		}
		while (!H.IsEmpty() && count < n) {
			H.RemoveMin(ed);	         //选堆中具最小权的边
			if (!Vmst[ed.head]) {
				MST.Insert(ed);       //加入最小生成树
				u = ed.head;
				Vmst[u] = true;//u加入生成树顶点集合
				count++;
				break;
			}
		}
	} while (count < n);
}

template<typename T, typename E>
bool MyGraph<T, E>::CreatByFile(ifstream & in)
{
	int i, j, k, n, m;
	T e1, e2;
	E weight=0;
	in >> n >> m;				//输入顶点数与边数
	for (i = 0; i < n; i++) {	//依次输入顶点值
		in >> e1;
		this->insertVertex(e1);
	}
	i = 0;
	while (i < m) {
		assert(in >> e1 >> e2 >> weight);	//依次输入边的两顶点值及其权值
		j = this->getVertexPos(e1);				//取对应顶点下标
		k = this->getVertexPos(e2);
		if (j == -1 || k == -1) {			//取对应顶点不存在
			cout << "Input error!\n"; return false;
		}
		else {
			this->insertEdge(j, k, weight);		//由顶点下标和权值插入边
			i++;
		}
	}
	return true;
}

template<class T, class E>
void MyGraph<T, E>::input() {
	int i, j, k, n, m;
	T e1, e2;
	E weight;
	cin >> n >> m;				//输入顶点数与边数
	for (i = 0; i < n; i++) {	//依次输入顶点值
		cin >> e1;
		this->insertVertex(e1);
	}
	i = 0;
	while (i < m) {
		assert(cin >> e1 >> e2 >> weight);	//依次输入边的两顶点值及其权值
		j = getVertexPos(e1);				//取对应顶点下标
		k = getVertexPos(e2);
		if (j == -1 || k == -1) {			//取对应顶点不存在
			cout << "Input error!\n";
		}
		else {
			insertEdge(j, k, weight);		//由顶点下标和权值插入边
			i++;
		}
	}
}

template<class T, class E>
void MyGraph<T, E>::output() {
	int i, j, n, m;
	T e1, e2;
	E weight;
	n = this->NumberOfVertices();		//顶点数与边数
	m = this->NumberOfEdges();
	cout << "Number of Vertices: " << n << endl;
	cout << "Number of Edges: " << m << endl;
	cout << "The edges in the graph are:\n";
	for (i = 0; i < n; i++) {
		for (j = i + 1; j < n; j++) {
			weight = this->getWeight(i, j);
			if (weight > 0 && weight < this->maxWeight) {
				e1 = this->getValue(i);	//由下标取得顶点值
				e2 = this->getValue(j);
				cout << "(" << e1 << "," << e2 << "," << weight << ")" << endl;
			}
		}
	}
}

template<class T, class E>
void MyGraph<T, E>::dfs(const T&v) {//深度优先遍历
	bool *visited = new bool[this->numVertices];
	for (int i = 0; i < this->numVertices; i++) {
		visited[i] = false;
	}
	int loc = this->getVertexPos(v);
	cout << this->getValue(loc) << ' ';
	visited[loc] = true;
	stack<int> S; S.push(loc);
	bool sign;
	int w;
	while (!S.empty())
	{
		loc = S.top();
		w = this->getFirstNeighbor(loc);
		sign = false;
		while (w != -1 && sign == false) {
			if (visited[w] == false) {
				cout << this->getValue(w) << " ";
				visited[w] = true;
				sign = true;
				S.push(w);
			}
			w = this->getNextNeighbor(loc, w);
		}
		if (!sign)S.pop();
	}
	delete[] visited;
}

template<class T, class E>
void MyGraph<T, E>::bfs(const T&v) {
	int w;
	bool *visited = new bool[this->numVertices];
	for (int i = 0; i < this->numVertices; i++) {
		visited[i] = false;
	}
	int loc = this->getVertexPos(v);
	cout << this->getValue(loc) << " ";
	visited[loc] = true;
	queue<int> Q; Q.push(loc);
	while (!Q.empty())
	{
		loc = Q.front(); Q.pop();
		w = this->getFirstNeighbor(loc);
		while (w != -1)
		{
			if (visited[w] == false) {
				cout << this->getValue(w) << ' ';
				visited[w] = true;
				Q.push(w);
			}
			w = this->getNextNeighbor(loc, w);
		}
	}
	delete[] visited;
}