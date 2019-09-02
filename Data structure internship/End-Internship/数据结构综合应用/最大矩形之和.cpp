class Solution {
public:
	int maxSumSubmatrix(vector<vector<int>> &matrix, int k) {
		vector<vector<int>>sum(matrix);
		for (int i = 0; i < sum.size(); i++) {
			for (int j = 1; j < sum[i].size(); j++) {
				sum[i][j] += sum[i][j - 1];
			}
		}
		for (int i = 1; i < sum.size(); i++) {
			for (int j = 0; j < sum[i].size(); j++) {
				sum[i][j] += sum[i - 1][j];
			}
		}
		int res = INT_MIN;
		for (int i1 = 0; i1 < sum.size(); i1++) {
			for (int j1 = 0; j1 < sum[i1].size(); j1++) {
				for (int i2 = i1; i2 < sum.size(); i2++) {
					for (int j2 = j1; j2 < sum[i1].size(); j2++) {
						int temp = sum[i2][j2];
						if (j1 - 1 >= 0)temp -= sum[i2][j1 - 1];
						if (i1 - 1 >= 0)temp -= sum[i1 - 1][j2];
						if (i1 - 1 >= 0 && j1 - 1 >= 0)temp += sum[i1 - 1][j1 - 1];
						if (temp <= k)res = res < temp ? temp : res;
					}
				}
			}
		}
		return res;
	}
};
