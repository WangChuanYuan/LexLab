//
// Created by 王川源 on 2018/11/2.
//
#include "DFA.h"

int DFA::d_stateCount(0);

DFA::DFA(){
    start = State(0);
    ends = States();
    edges = Edges();
}