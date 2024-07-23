//Nithisha Sathishkumar 
//Program 3
//Feb 13, 2024
//Professor Kim
//DFS

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct EdgeNode;      // forward reference for the compiler

struct GraphNode {    // structs used for simplicity, use classes if desired
    EdgeNode* edgeHead; // head of the list of edges
    string data;     // data information about each node
    bool visited;               
};

struct EdgeNode {
    int adjGraphNode;  // subscript of the adjacent graph node
    EdgeNode* nextEdge;
};

class GraphL {                           
public:
    GraphL();
    ~GraphL();
    int buildGraph(ifstream& infile);
    void displayGraph();
    void depthFirstSearch();

private:
    int size;
    GraphNode *nodeArray; // array of GraphNodes
    void depthFirstSearchHelper(int node);
    void clearGraph();
};