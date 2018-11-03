//
// Created by 王川源 on 2018/11/2.
//
#include "../include/DFA.h"

/*--------------------------------------------------
 * 以下为类方法
 * ------------------------------------------------*/
int DFA::d_stateCount(0);

DFA::DFA(){
    start = d_stateCount++;
    ends = States();
    edges = Edges();
}

Labels DFA::getLabels() {
    Labels labels = Labels();
    for(int i = 0; i < edges.size(); i++){
        if(edges[i].label != EPSILON && !exists(labels, edges[i].label))
            labels.push_back(edges[i].label);
    }
    return labels;
}

States DFA::getNoEndStates() {
    States states = States();
    for(int i = 0; i < edges.size(); i++){
        if(!exists(ends, edges[i].from) && !exists(states, edges[i].from))
            states.push_back(edges[i].from);
    }
    return states;
}

DFA DFA::minimize() {
    int flag = 1; //是否有分组需要划分
    DFA minDFA = DFA();
    vector<States> minStates;
    Labels labels = getLabels();
    States endStates = ends;
    States noEndStates = getNoEndStates();
    minStates.push_back(endStates);
    minStates.push_back(noEndStates);
    while(flag){
        flag = 0;
        vector<States> goal(minStates.size());
        for (int i = 0; i < minStates.size(); i++){
            States currStates = minStates[i];
            for(int j = 0; j < labels.size(); j++){
                Label label = labels[j];
            }
        }
    }
    return minDFA;
}