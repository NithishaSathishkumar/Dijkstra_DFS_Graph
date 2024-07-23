//Nithisha Sathishkumar 
//Program 3
//Feb 13, 2024
//Professor Kim
//Dijkstra's shortest path algorithm

#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
#include"limits.h"
using namespace std;

const int MAXNODES = 100;
struct TableType {
    bool visited;          // whether node has been visited
    int dist;              // shortest distance from source known so far
    int path;              // previous node in path of min dist
};

class GraphM {                           
public:
    GraphM();
    int buildGraph(ifstream& infile);
    int insertEdge(int source, int destination, int weight);
    int removeEdge(int source, int destination);
    int checkEdge(int source, int destination, int weight);
    void findShortestPath();
    void displayAll();
    void display(int source, int destination);
    void printPath(int source, int destination); 
    void printData(int source, int destination);
    void displayAdjacencyMatrix(); 
    void displayLocations();

private:
    string data[MAXNODES];              // data for graph nodes
    int C[MAXNODES][MAXNODES];            // Cost array, the adjacency matrix
    int size;                             // number of nodes in the graph
    TableType T[MAXNODES][MAXNODES];      // stores visited, distance, path
    int path[MAXNODES];

};