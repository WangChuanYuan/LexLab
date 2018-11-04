//
// Created by 王川源 on 2018/11/2.
//
#ifndef LEXLAB_GLOBAL_H
#define LEXLAB_GLOBAL_H

#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

typedef string RE;
typedef string Tag;
typedef vector<Tag> Tags;
typedef int State;
typedef vector<State> States;
typedef char Label;
typedef vector<Label> Labels;
typedef struct Edge{
    State from;
    State to;
    Label label;

    bool operator == (Edge edge){
        return from == edge.from && to == edge.to && label == edge.label;
    }
} Edge;
typedef vector<Edge> Edges;

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
