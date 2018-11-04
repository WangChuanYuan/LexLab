#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

typedef struct {
    int from;
    int to;
    char label;
} Edge;
typedef vector<Edge> Edges;

map<int, string> tagMap;
Edges edges;

int transTo(int state, char label, Edges edges) {
    for (int i = 0; i < edges.size(); i++) {
        if (edges[i].from == state && edges[i].label == label)
            return edges[i].to;
    }
    return -1;
}

int main() {
/* initialize code */
    ifstream fin(".\\input.txt", ios::in);
    ofstream fout(".\\output.txt", ios::out);
    char line[1024] = {0};
    while(fin.getline(line, sizeof(line))) {
        stringstream ss(line);
        string word = ss.str();
        int state = 0;
        for (char c : word) {
            state = transTo(state, c, edges);
            if(state == -1){
                break;
            }
        }
        if (tagMap.find(state) == tagMap.end()) {
            fout << word << " is illegal." << endl;
        } else {
            fout << word << " is " << tagMap[state] << "." << endl;
        }
    }
}
