#include <iostream>
#include <vector>
#include <climits>
#include <ctime>

using namespace std;

const int INF = INT_MAX;
int NO_PARENT = -1;
int i = 0;
void printPath(int currentVertex, vector<int>& parents, int start_vertex, vector<vector<vector<int>>>& all_info,int i, vector<int>& path) {
  // Declare i locally
    if (currentVertex == NO_PARENT) {
        return;
    }
    printPath(parents[currentVertex], parents, start_vertex, all_info, i, path);
    path.push_back(currentVertex);
    cout << currentVertex << " ";
}
void printSolution(int startVertex, vector<int>& distances, vector<int>& parents, vector<vector<vector<int>>>& all_info, int i, vector<vector<int>>& distance) {
    int nVertices = distances.size();
    cout << "Vertex\t Distance\tPath";
    for (int vertexIndex = 0; vertexIndex < nVertices; vertexIndex++) {
        vector<int> path;
        if (vertexIndex != startVertex) {
            cout << "\n" << startVertex << " -> ";
            cout << vertexIndex << " \t\t ";
            cout << distances[vertexIndex] << "\t\t";
            distance[startVertex][vertexIndex] = distances[vertexIndex];
            printPath(vertexIndex, parents, startVertex, all_info, i, path);
            for (int j = 0; j < path.size(); j++) {
                all_info[startVertex][vertexIndex][j] = path[j];
            }
        } 
    }
}

void dijkstra(vector<vector<int>>& adjacencyMatrix, int startVertex, vector<vector<vector<int>>>& all_info, vector<vector<int>>& distance) {
    int nVertices = adjacencyMatrix[0].size();

    vector<int> shortestDistances(nVertices, INF);
    vector<bool> added(nVertices, false);

    shortestDistances[startVertex] = 0;
    vector<int> parents(nVertices, NO_PARENT);

    for (int i = 0; i < nVertices; i++) {
        int nearestVertex = -1;
        int shortestDistance = INF;

        for (int vertexIndex = 0; vertexIndex < nVertices; vertexIndex++) {
            if (!added[vertexIndex] && shortestDistances[vertexIndex] < shortestDistance) {
                nearestVertex = vertexIndex;
                shortestDistance = shortestDistances[vertexIndex];
            }
        }

        added[nearestVertex] = true;

        for (int vertexIndex = 0; vertexIndex < nVertices; vertexIndex++) {
            int edgeDistance = adjacencyMatrix[nearestVertex][vertexIndex];

            if (edgeDistance > 0 && (shortestDistance + edgeDistance) < shortestDistances[vertexIndex]) {
                parents[vertexIndex] = nearestVertex;
                shortestDistances[vertexIndex] = shortestDistance + edgeDistance;
            }
        }
    }

    printSolution(startVertex, shortestDistances, parents, all_info, i, distance);
}


int main() {
    srand(time(0));
    int row, col, temp;
    cout << "Enter the rows size:";
    cin >> row;
    cout << "\nEnter the column size:";
    cin >> col;

    vector<vector<vector<int>>> all_info(row, vector<vector<int>>(col, vector<int>(col, NO_PARENT)));
    vector<vector<int>> adjacencyMatrix(row, vector<int>(col, 0));
    vector<vector<int>> distance(row, vector<int>(col, 0));
    for(int i = 0 ; i<distance.size();i++){
        for(int j = 0 ; j<distance.size();j++){
            distance[i][j]=-1;
        }
    }
    cout << "This is the matrix for random values of the distance" << endl;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (i == j) {
                adjacencyMatrix[i][j] = 0;
            } else {
                temp = rand() % 8;
                if (temp == 0) {
                    adjacencyMatrix[i][j] = -1;
                } else {
                    adjacencyMatrix[i][j] = temp;
                }
            }
        }
    }

    // Displaying the random matrix
    cout << "Random Matrix:\n";
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cout << adjacencyMatrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    vector<vector<int>> trafficLight(row, vector<int>(col, 0));
    cout << "This is the matrix for the traffic light at a particular route (2 for red, 1 for yellow, 0 for green)" << endl;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (i == j) {
                trafficLight[i][j] = 0;
            } else {
                trafficLight[i][j] = rand() % 3;
            }
        }
    }

    // Displaying the trafficLight matrix
    cout << "Traffic Light Matrix:\n";
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cout << trafficLight[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    // Adding the time after the traffic light matrix to the distance of the route
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (adjacencyMatrix[i][j] != -1) {
                adjacencyMatrix[i][j] += trafficLight[i][j];
            }
        }
    }

    // Displaying the matrix after the traffic Light matrix is added
    cout << "Matrix After Adding Traffic Light Times:\n";
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cout << adjacencyMatrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    // Enter the number of directions to be printed
    int b;
    cout << "Enter the number of direction to be printed : ";
    cin >> b;

    vector<int> route(b);
    for (int i = 0; i < b; i++) {
        cout << "Enter the direction : ";
        cin >> route[i];
    }

    for (int i = 0; i < b; i++) {
        dijkstra(adjacencyMatrix, route[i], all_info,distance);
        cout << endl;
    }

    // Displaying the paths stored in all_info
    cout << "Paths stored in all_info: " << endl;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            for (int k = 0; k < col ; k++) {
                cout << all_info[i][j][k] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    
    // cout<<"Distance vector diaplay :";
    // for(int i = 0 ; i<distances.size();i++){
    //     cout<<distances[i]<<" ";
    // }
    for(int i = 0 ; i<distance.size();i++){
        for(int j = 0 ; j<distance.size();j++){
            cout<<distance[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}