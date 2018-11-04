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
edges.push_back({0,1, '0'});
edges.push_back({0,2, '1'});
edges.push_back({0,2, '2'});
edges.push_back({0,2, '3'});
edges.push_back({0,2, '4'});
edges.push_back({0,2, '5'});
edges.push_back({0,2, '6'});
edges.push_back({0,2, '7'});
edges.push_back({0,2, '8'});
edges.push_back({0,2, '9'});
edges.push_back({0,11, 'a'});
edges.push_back({0,11, 'o'});
edges.push_back({0,11, 'e'});
edges.push_back({0,11, 'i'});
edges.push_back({0,11, 'u'});
edges.push_back({0,11, '_'});
edges.push_back({1,2, '0'});
edges.push_back({1,2, '1'});
edges.push_back({1,2, '2'});
edges.push_back({1,2, '3'});
edges.push_back({1,2, '4'});
edges.push_back({1,2, '5'});
edges.push_back({1,2, '6'});
edges.push_back({1,2, '7'});
edges.push_back({1,2, '8'});
edges.push_back({1,2, '9'});
edges.push_back({1,27, '.'});
edges.push_back({2,2, '0'});
edges.push_back({2,2, '1'});
edges.push_back({2,2, '2'});
edges.push_back({2,2, '3'});
edges.push_back({2,2, '4'});
edges.push_back({2,2, '5'});
edges.push_back({2,2, '6'});
edges.push_back({2,2, '7'});
edges.push_back({2,2, '8'});
edges.push_back({2,2, '9'});
edges.push_back({2,27, '.'});
edges.push_back({11,11, '0'});
edges.push_back({11,11, '1'});
edges.push_back({11,11, '2'});
edges.push_back({11,11, '3'});
edges.push_back({11,11, '4'});
edges.push_back({11,11, '5'});
edges.push_back({11,11, '6'});
edges.push_back({11,11, '7'});
edges.push_back({11,11, '8'});
edges.push_back({11,11, '9'});
edges.push_back({11,11, 'a'});
edges.push_back({11,11, 'o'});
edges.push_back({11,11, 'e'});
edges.push_back({11,11, 'i'});
edges.push_back({11,11, 'u'});
edges.push_back({11,11, '_'});
edges.push_back({27,44, '0'});
edges.push_back({27,44, '1'});
edges.push_back({27,44, '2'});
edges.push_back({27,44, '3'});
edges.push_back({27,44, '4'});
edges.push_back({27,44, '5'});
edges.push_back({27,44, '6'});
edges.push_back({27,44, '7'});
edges.push_back({27,44, '8'});
edges.push_back({27,44, '9'});
edges.push_back({44,44, '0'});
edges.push_back({44,44, '1'});
edges.push_back({44,44, '2'});
edges.push_back({44,44, '3'});
edges.push_back({44,44, '4'});
edges.push_back({44,44, '5'});
edges.push_back({44,44, '6'});
edges.push_back({44,44, '7'});
edges.push_back({44,44, '8'});
edges.push_back({44,44, '9'});
tagMap[1] = "num";
tagMap[2] = "num";
tagMap[11] = "id";
tagMap[44] = "decimal";

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
                fout << word << " is illegal." << endl;
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
