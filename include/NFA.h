//
// Created by 王川源 on 2018/10/30.
//
#ifndef LEXLAB_FA_H
#define LEXLAB_FA_H

#include "Global.h"
#include "DFA.h"

class NFA {
public:
    static int n_stateCount;
    State start;
    States ends;
    Edges edges;
    map<State, Tags> tagsMap;

    NFA();
    NFA(Label label);
    Labels getLabels();
    DFA toDFA();
};

#endif //LEXLAB_FA_H
