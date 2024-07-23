//Nithisha Sathishkumar 
//Program 3
//Feb 13, 2024
//Professor Kim

#include "graphm.h"

// Constructor
GraphM::GraphM(){
    this->size = 0;
    
    // Initialize the cost matrix, distance matrix, and visited matrix
    for(int i = 0; i < MAXNODES; i++){
        for(int j = 0; j < MAXNODES; j++){
            C[i][j] = INT_MAX;
            T[i][j].dist = INT_MAX;
            T[i][j].visited = false;
            T[i][j].path = 0;
        }
    }
}

// Method to build the graph from input file, setting size, locations, and edges
int GraphM::buildGraph(ifstream& infile) {
    int src, dest, weight;
    
    // Read the size of the graph
    infile >> this->size;

    // Read locations and store them in the 'data' array
    for (int i = 0; i < size; ++i) {
        getline(infile >> ws, data[i]);
    }

    // Read edges and weights
    while (infile >> src >> dest >> weight) {
        // Check for the end of the edge input (0 0 0)
        if (src == 0 && dest == 0 && weight == 0) {
            break;
        }
        
        // Insert edge into the graph
        insertEdge(src, dest, weight);
    }

    return 1; // or any success code that suits your needs
}

// Method to insert an edge into the graph with a given source, destination, and weight.
int GraphM::insertEdge(int source, int destination, int weight){
    
    // Invalid source or destination
    if(source < 0 && source > size && destination < 0 && destination >= size){
        return -1;
    }

    // Update the cost matrix with the weight
    C[source][destination] = weight;
    
    return checkEdge(source, destination, weight);
}

// Method to remove an edge from the graph with a given source and destination.
int GraphM::removeEdge(int source, int destination){

    // Invalid source or destination
    if(source < 0 && source > size && destination < 0 && destination >= size){
        return -1;
    }

    // Set the weight to INT_MAX to represent no edge
    C[source][destination] = INT_MAX;
    return checkEdge(source, destination, INT_MAX);
}

// Method to check if an edge exists between source and destination with a given weight
int GraphM::checkEdge(int source, int destination, int weight){
    // Edge successfully checked
    if(C[source][destination] == weight){
        return 1;
    }
    
    // Edge check failed
    return -1;
}

// Method to find the shortest paths from each node to every other node in the graph
void GraphM::findShortestPath(){
    int from, to;

    // Initialize distance, visited, and path matrices for each source node
    for(int i = 1; i <= size; i++){
        for(int j = 1; j <= size; j++){
            T[i][j].dist = INT_MAX;
            T[i][j].visited = false;
            T[i][j].path = 0;
        }
    }

    // Calculate shortest paths for each source node
    for(int source = 1; source <= size; source++){
        int num = 0;

        T[source][source].dist = 0;
        
        while(num < size){
            from = 0;

            // Find the unvisited node with the shortest distance
            for(int i = 1; i <= size; i++){
                if(!T[source][i].visited){
                    if(T[source][i].dist < T[source][from].dist){
                        from = i;
                    }
                }
            }
            T[source][from].visited = true;
            num++;

            // Update distances for adjacent nodes
            for(to = 1; to <= size; to++){
                if(!T[source][to].visited && C[from][to] < INT_MAX && T[source][from].dist < INT_MAX){
                    if(T[source][to].dist > T[source][from].dist + C[from][to]){
                        T[source][to].dist = T[source][from].dist + C[from][to];
                        T[source][to].path = from;
                    } 
                }
            }
       }
    }
}

// Display all the shortest paths
void GraphM::displayAll() {
    cout << "Description" <<  setw(20) << "From_node" << setw(10) << "To_node" << setw(14) << "Distance" << setw(10) << "Path" << endl;
    for(int i = 1; i <= size; i++){
        cout << data[i - 1] << endl << endl;

        for(int j = 1; j <= size; j++){
            if(T[i][j].dist != 0){
                cout << setw(27) << i;
                cout << setw(10) << j;

                if(T[i][j].dist == INT_MAX){
                    cout << setw(12) << "---" << endl;
                }else{
                    cout << setw(12) << T[i][j].dist;
                    cout << setw(12);

                    printPath(i, j);
                    cout << endl;


                }
            }
        }
    }

    cout << endl;

}

// Display the shortest path between a source and destination
void GraphM::display(int source, int destination){
    if (source < 0 || source > size || destination < 0 || destination > size) {
        cout << setw(7) << source << setw(7) << destination << setw(15) << "---" << endl;
        return;
    }

    cout << setw(7) << source << setw(7) << destination;

    if(T[source][destination].dist != INT_MAX){
        cout << setw(12) << T[source][destination].dist << setw(15);

        printPath(source, destination); 
        cout << endl;

        printData(source, destination);
    }else{
        cout << setw(15) << "---" << endl;
    }

    cout << endl;
}

// Recursively print the data along the shortest path
void GraphM::printData(int source, int destination) {
    if (T[source][destination].dist != INT_MAX) {
        int index = destination;
        printData(source, destination = T[source][destination].path);
        cout << data[index - 1] << endl;
    }
}

// Recursively print the shortest path
void GraphM::printPath(int source, int destination) {
   if(T[source][destination].dist == INT_MAX){
        return;
   }

   if(source == destination){
        cout << destination << " ";
        return;
   }

   int pathData = destination;
   printPath(source, destination = T[source][destination].path);
   cout << pathData << " ";

}

// Display the adjacency matrix
void GraphM::displayAdjacencyMatrix(){
    for(int i = 0; i < size; i++){
        for(int j = 0;  j < size; j++){
            cout << C[i][j] << " ";
        }
        cout << endl;
    }
}

// Display the locations
void GraphM::displayLocations(){
    for(int i = 0; i < size; i++){
        cout << data[i] << endl;
    }
}

