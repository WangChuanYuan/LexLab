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
    State end;
    Edges edges;

    NFA();
    NFA(Label label);
    DFA toDFA();
};

#endif //LEXLAB_FA_H
