#pragma once
#include <vector>
using namespace std;
struct Edge {
	std::pair<int, int> edge;
	int weight;
};
class LittleAlgorithm 
{
public:
	vector<pair<int, int>> result;
	LittleAlgorithm(int vertexesNumber, vector<Edge> edges);
	vector<vector<int>> data;
	void findHamiltonCycle();
private:
	enum check { Row, Col };
	void makeAdjacencyMatrix();
	int getMin(vector<vector<int>>, int, check);
	void matrixProcedure(vector<vector<int>>);
	void showMatrix(vector<vector<int>>);
	int getResultSum();
	bool validateData();
	int vertexesNumber = 0;
	vector<Edge> edges;
};