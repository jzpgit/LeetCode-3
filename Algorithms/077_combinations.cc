class Solution {
public:
	vector<vector<int> > combine(int n, int k) {
		vector<vector<int> > ret;
		vector<int> path;
		iterative(1, n, k, path, ret);
		return ret;
	}
	//picking num numbers from beg to end (inclusive)
	void iterative(int beg, int end, int num, vector<int> &path, vector<vector<int> > &ret) {
		if(num == 0) ret.push_back(path);
		else {
			for(int k = beg; k <= end; ++k) {
				vector<int> newpath(path);
				newpath.push_back(k); //pick k
				iterative(k+1, end, num-1, newpath, ret);
			}
		}
	}
};