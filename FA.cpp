//
// Created by 王川源 on 2018/11/1.
//
#include "FA.h"

int FA::stateCount(0);

FA::FA() {
    start = stateCount++;
    end = stateCount++;
    edges = Edges();
}

FA::FA(Label label) {
    start = stateCount++;
    end = stateCount++;
    edges = Edges();
    edges.push_back(Edge{start, end, label});
}

