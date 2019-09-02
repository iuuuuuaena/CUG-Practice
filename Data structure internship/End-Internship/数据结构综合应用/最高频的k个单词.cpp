struct compare
{
	bool operator()(const pair<string, int>& a, const pair<string, int>& b)
	{
		if (a.second < b.second)
			return true;
		else if (a.second == b.second)
			return a.first > b.first;
		return false;
	}
};

class Solution {
public:
    /**
     * @param words: an array of string
     * @param k: An integer
     * @return: an array of string
     */
    
    vector<string> topKFrequentWords(vector<string> &words, int k) {
        // write your code here
		priority_queue<string> q1;
		for (auto w : words) {
			q1.push(w);
		}
		priority_queue<pair<string,int>,vector<pair<string, int>>,compare>q2;
		pair<string, int> temp("",0);
		string tempstr;
		while (!q1.empty()) {
			tempstr = q1.top(); q1.pop();
			if (tempstr != temp.first) {
			    if (temp.second!=0)
				{
					q2.push(temp);
				}
				temp.first = tempstr;
				temp.second = 1;
			}
			else
			{
				temp.second=temp.second+1;
			}
		}
		q2.push(temp);
		vector<string> res;
		for (int i = 0; i < k; ++i)
		{
			res.push_back(q2.top().first);
			q2.pop();
		}
		return res;

    }  
};