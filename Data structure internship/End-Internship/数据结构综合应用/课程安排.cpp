class Solution {
public:
	vector<int> findOrder(int numCourses, vector<pair<int, int>> &prerequisites) {
		vector<int> res;
		vector<vector<int>> graph(numCourses, vector<int>(0));
		int count[numCourses];//入度数组
		vector<int> result;
		for (int i = 0; i < numCourses; i++) {
			count[i] = 0;
		}
		for (auto item : prerequisites) {
			graph[item.second].push_back(item.first);
			count[item.first]++;
		}
		stack<int> q;
		for (int i = 0; i < numCourses; i++) {
			if (count[i] == 0) q.push(i);
		}
		while (!q.empty()) {
			int temp = q.top();
			q.pop();
			res.push_back(temp);
			for (int i = 0; i < graph[temp].size(); i++) {
				count[graph[temp][i]]--;
				if (count[graph[temp][i]] == 0) q.push(graph[temp][i]);
			}
		}
		if (res.size() != numCourses) res.clear();
		return res;
	}
};
