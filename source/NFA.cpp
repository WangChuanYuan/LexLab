//
// Created by 王川源 on 2018/11/1.
//
#include "../include/NFA.h"
#include "../include/Global.h"

States epsilonClosure(States states, Edges edges) {
    States closure = States();
    closure.insert(closure.end(), states.begin(), states.end());
    int lastSize = -1;
    int size = closure.size();
    while (lastSize != size) {
        for (int i = 0; i < edges.size(); i++) {
            State from = edges[i].from;
            State to = edges[i].to;
            if (edges[i].label == EPSILON && exists(closure, from) && !exists(closure, to))
                closure.push_back(to);
        }
        lastSize = size;
        size = closure.size();
    }
    //排序方便比较是否相等
    sort(closure.begin(), closure.end());
    return closure;
}

States subset(States states, Label label, Edges edges) {
    States subset = States();
    for (int i = 0; i < edges.size(); i++) {
        Edge edge = edges[i];
        if (edge.label == label && exists(states, edge.from) && !exists(subset, edge.to))
            subset.push_back(edge.to);
    }
    //排序方便比较是否相等
    sort(subset.begin(), subset.end());
    return subset;
}

/*--------------------------------------------------
 * 以下为类方法
 * ------------------------------------------------*/
int NFA::n_stateCount(0);

NFA::NFA() {
    start = n_stateCount++;
    ends = States();
    ends.push_back(n_stateCount++);
    edges = Edges();
    tagsMap = map<State, Tags>();
}

NFA::NFA(Label label) {
    start = n_stateCount++;
    ends = States();
    ends.push_back(n_stateCount++);
    edges = Edges();
    edges.push_back(Edge{start, ends[0], label});
    tagsMap = map<State, Tags>();
}

Labels NFA::getLabels() {
    Labels labels = Labels();
    for (int i = 0; i < edges.size(); i++) {
        if (edges[i].label != EPSILON && !exists(labels, edges[i].label))
            labels.push_back(edges[i].label);
    }
    return labels;
}

DFA NFA::toDFA() {
    DFA dfa = DFA();
    vector<States> dfaStates;
    Labels labels = getLabels();

    States intiState = States();
    intiState.push_back(start);
    States from = epsilonClosure(intiState, edges), to;
    dfaStates.push_back(from);

    int lastSize = -1;
    int size = dfaStates.size();
    while (lastSize != size) {
        for (int i = 0; i < size; i++) {
            from = dfaStates[i];
            for (int j = 0; j < labels.size(); j++) {
                Label label = labels[j];
                to = epsilonClosure(subset(from, label, edges), edges);
                //是否是新的DFA状态
                if (!to.empty()) {
                    if (!exists(dfaStates, to)) {
                        dfaStates.push_back(to);
                        //增加DFA的边
                        int id = DFA::d_stateCount++;
                        dfa.edges.push_back({i, id, label});
                        //判断是否加入DFA终态
                        for(int i = 0; i < ends.size(); i++){
                            bool flag = false;
                            if(exists(to, ends[i])){
                                flag = true;
                            }
                            if(flag) {
                                if(!exists(dfa.ends, id))
                                    dfa.ends.push_back(id);
                                for(int j = 0; j < tagsMap[ends[i]].size(); j++) {
                                    if(dfa.tagsMap.find(id) == dfa.tagsMap.end()){
                                        dfa.tagsMap[id] = Tags();
                                    }
                                    if(!exists(dfa.tagsMap[id], tagsMap[ends[i]][j]))
                                        dfa.tagsMap[id].push_back(tagsMap[ends[i]][j]);
                                }
                            }
                        }
                    } else {
                        //增加DFA的边
                        int id = distance(dfaStates.begin(), find(dfaStates.begin(), dfaStates.end(), to));
                        Edge edge{i, id, label};
                        if (!exists(dfa.edges, edge))
                            dfa.edges.push_back(edge);
                    }
                }
            }
        }
        lastSize = size;
        size = dfaStates.size();
    }
    return dfa;
}

