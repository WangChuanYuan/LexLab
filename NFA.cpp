//
// Created by 王川源 on 2018/11/1.
//
#include "NFA.h"

Labels getLabels(Edges edges){
    Labels labels = Labels();
    for(int i = 0; i < edges.size(); i++){
        if(edges[i].label != EPSILON && !exists(labels, edges[i].label))
            labels.push_back(edges[i].label);
    }
    return labels;
}

States epsilonClosure(States states, Edges edges) {
    States closure = States();
    closure.insert(closure.end(), states.begin(), states.end());
    int lastSize = -1;
    int size = closure.size();
    while (lastSize != size){
        for (int i = 0; i < edges.size(); i++) {
            State from = edges[i].from;
            State to = edges[i].to;
            if (edges[i].label == EPSILON && exists(closure, from) && !exists(closure, to))
                closure.push_back(to);
        }
        lastSize = size;
        size = closure.size();
    }
    return closure;
}

States subset(States states, Label label, Edges edges){
    States subset = States();
    for (int i = 0; i < edges.size(); i++){
        Edge edge = edges[i];
        if(edge.label == label && exists(states, edge.from) && !exists(subset, edge.to))
            subset.push_back(edge.to);
    }
    return subset;
}
/*--------------------------------------------------
 * 以下为类方法
 * ------------------------------------------------*/
int NFA::n_stateCount(0);

NFA::NFA() {
    start = n_stateCount++;
    end = n_stateCount++;
    edges = Edges();
}

NFA::NFA(Label label) {
    start = n_stateCount++;
    end = n_stateCount++;
    edges = Edges();
    edges.push_back(Edge{start, end, label});
}

DFA NFA::toDFA() {
    DFA dfa = DFA();
    vector<States> dfaStates;
    Labels labels = getLabels(edges);

    States intiState = States();
    intiState.push_back(start);
    States from = epsilonClosure(intiState, edges), to;

    int lastSize = -1;
    int size = dfaStates.size();
    while (lastSize != size) {
        for(int i = 0; i < dfaStates.size(); i++){
            from = dfaStates[i];
            for(int j = 0; j < labels.size(); j++) {
                Label label = labels[j];
                to = epsilonClosure(subset(from, label, edges), edges);
                //是否是新的DFA状态
                if(!to.empty() && !exists(dfaStates, to)) {
                    dfaStates.push_back(to);
                    //增加DFA的边
                    int id = DFA::d_stateCount++;
                    dfa.edges.push_back({i, id, label});
                    //判断是否加入DFA终态
                    if(exists(to, end) && !exists(dfa.ends, id))
                        dfa.ends.push_back(id);
                }
            }
        }
        lastSize = size;
        size = dfaStates.size();
    }
    return dfa;
}

