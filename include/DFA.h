//
// Created by 王川源 on 2018/11/2.
//

#ifndef LEXLAB_DFA_H
#define LEXLAB_DFA_H

#include "Global.h"

class DFA {
public:
    static int d_stateCount;
    State start;
    States ends;
    Edges edges;
    map<State, Tags> tagsMap;

    DFA();
    Labels getLabels();
    States getNoEndStates();
    DFA minimize();
};


#endif //LEXLAB_DFA_H
