#include<iostream>
#include<vector>
using namespace std;

vector<int> MergeSortedVectors(vector<int>& v1, vector<int>& v2) {

	// v3 is the output vector
	// it will store the merged vector obtained by merging v1 and v2
	vector<int> v3;

	int i, j, n, m;
	i = j = 0;
	n = v1.size();
	m = v2.size();


	// traverse each elemenst of v1 and v2
	while (i < n && j < m) {

		// comparing v1[i] and v2[j]
		// if v1[i] is smaller than v2[j]
		// push v1[i] to v3 and increment i
		// if v[i] is less than v2[j]
		// push v2[j] to v3 and increment j
		if (v1[i] <= v2[j]) {
			v3.push_back(v1[i]);
			++i;
		}
		else {
			v3.push_back(v2[j]);
			++j;
		}

	}

	// push the elements left in v1 to v3
	while (i < n) {
		v3.push_back(v1[i]);
		++i;
	}

	// push the elements left in v2 to v3
	while (j < m) {
		v3.push_back(v2[j]);
		++j;
	}

	return v3;

}

int main() {

	int n, m;
	vector<int> v1, v2, v3;

	// input vector 1
	cout << "Enter Size of Vector 1: ";
	cin >> n;
	v1 = vector<int>(n);
	cout << "Enter Elements of Vector 1 ( In Ascending Order ): ";
	for (int i = 0; i < n; ++i) {
		cin >> v1[i];
	}

	// input vector 2
	cout << "\nEnter Size of Vector 2: ";
	cin >> m;
	v2 = vector<int>(m);
	cout << "Enter Elements of Vector 2 ( In Ascending Order ): ";
	for (int i = 0; i < m; ++i) {
		cin >> v2[i];
	}

	// v3 stores the vector obtained by merging v1 and v2
	// the size of v3 is equal to n + m
	v3 = MergeSortedVectors(v1, v2);

	cout << "\nVector Obtained by Merging Vector 1 and Vector 2: ";
	for (int i = 0; i < v3.size(); ++i) {
		cout << v3[i] << ' ';
	}

}
