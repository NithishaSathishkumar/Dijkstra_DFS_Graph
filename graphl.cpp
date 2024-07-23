//Nithisha Sathishkumar 
//Program 3
//Feb 13, 2024
//Professor Kim

#include "graphl.h"

//Constructor
GraphL::GraphL(){
    this->size = 0;
    this->nodeArray = nullptr;
}

//Deconstructor
GraphL::~GraphL(){
    clearGraph();
}

int GraphL::buildGraph(ifstream& infile){
    //reading size from the file 
    infile >> this->size;

    //check if the size is valid
    if(this->size <= 0 || this->size > 100){
        return -1;
    }

    // Allocate memory for the array of GraphNodes
    this->nodeArray = new GraphNode[this->size + 1];

    // Read the data for each node from 1 to size
    for(int i = 1; i <= size; i++){
        // Using getline to handle possible spaces in the name
        getline(infile >> ws, nodeArray[i].data);
    }

    // Read edges from the file until encountering (0, 0)
    int source, destination; 
    while(infile >> source >> destination && (source != 0 && destination != 0)){
        
        // Create a new EdgeNode for the current edge
        EdgeNode *newNode = new EdgeNode;
        newNode->adjGraphNode = destination;

        // Insert the new edge at the beginning of the adjacency list for the source node
        newNode->nextEdge = nodeArray[source].edgeHead;
        nodeArray[source].edgeHead = newNode;
    }

    // Return 1 on successful graph construction
    return 1;
}

void GraphL::displayGraph(){
    // Display the graph information
    cout << endl << "Graph:" << endl;

    // Loop through each node in the graph
    for (int i = 1; i <= size; i++) {

        // Display node information
        cout << "Node " << i << "\t" << nodeArray[i].data << endl;

        // Display edges for the temp node
        EdgeNode* temp = nodeArray[i].edgeHead;

        while (temp != nullptr) {
            // Display each edge in the adjacency list for the current node
            cout << "  edge " << i << " " << temp->adjGraphNode << endl;

            // Move to the next edge in the adjacency list
            temp = temp->nextEdge;
        }
    }

    //Print newLine
    cout << endl;
}

void GraphL::depthFirstSearch(){
    // Output a header indicating the following information is the depth-first ordering
    cout << "Depth-first ordering: ";

    // Iterate through each node in the graph
    for (int i = 1; i <= size; ++i) {

        // If the current node has not been visited, perform depth-first search starting from it
        if (!nodeArray[i].visited) {
            depthFirstSearchHelper(i);
        }
    }

    //Print newLine
    cout << endl;
}

void GraphL::depthFirstSearchHelper(int node){
    // Output the current node in the depth-first ordering
    cout << node << " ";

    // Mark the current node as visited
    nodeArray[node].visited = true;

    // Iterate through the adjacency list of the current node
    EdgeNode* temp = nodeArray[node].edgeHead;

    while (temp != nullptr) {

        // Get the adjacent node from the current edge
        int adjNode = temp->adjGraphNode;

        // If the adjacent node has not been visited, perform depth-first search starting from it
        if (!nodeArray[adjNode].visited) {
            depthFirstSearchHelper(adjNode);
        }

        // Move to the next edge in the adjacency list
        temp = temp->nextEdge;
    }
}

void GraphL::clearGraph(){
  for(int i = 1; i <= size; i++){
    EdgeNode *temp = nodeArray[i].edgeHead;
    while(temp != nullptr){
        EdgeNode *next = temp->nextEdge;
        delete temp;
        temp = next; 
    }
  }
  delete[] nodeArray;
  size = 0;
}
