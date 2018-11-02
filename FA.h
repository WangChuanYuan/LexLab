//
// Created by 王川源 on 2018/10/30.
//
#ifndef LEXLAB_FA_H
#define LEXLAB_FA_H

#include <vector>

using namespace std;

typedef int State;
typedef vector<State> States;
typedef char Label;
typedef struct {
    State from;
    State to;
    Label label;
} Edge;
typedef vector<Edge> Edges;

class FA {
public:
    static int stateCount;
    State start;
    State end;
    Edges edges;

    FA();
    FA(Label label);
};

#endif //LEXLAB_FA_H
