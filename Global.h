//
// Created by 王川源 on 2018/11/2.
//
#ifndef LEXLAB_GLOBAL_H
#define LEXLAB_GLOBAL_H

#include <vector>
#include <algorithm>

using namespace std;

typedef int State;
typedef vector<State> States;
typedef char Label;
typedef vector<Label> Labels;
typedef struct {
    State from;
    State to;
    Label label;
} Edge;
typedef vector<Edge> Edges;
class DFAState {
public:
    int id;
    States states;
    DFAState(int i, States s) {
        id = i;
        states = s;
        //排序方便比较是否相等
        sort(states.begin(), states.end());
    }
    bool operator == (DFAState ds) {
        return states == ds.states;
    }
};

const char JOIN = '.';
const char UNION = '|';
const char CLOSURE = '*';
const char LEFT_BRACKET = '(';
const char RIGHT_BRACKET = ')';

const char EPSILON = '#';
const char END = '$';

template<class T>
bool exists(vector<T> array, T element) {
    if (array.end() != find(array.begin(), array.end(), element))
        return true;
    else return false;
}

#endif //LEXLAB_GLOBAL_H
