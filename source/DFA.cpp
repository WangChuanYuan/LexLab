//
// Created by 王川源 on 2018/11/2.
//
#include "../include/DFA.h"

States move(States states, Label label, Edges edges) {
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

State transTo(State state, Label label, Edges edges) {
    for (int i = 0; i < edges.size(); i++) {
        if (edges[i].from == state && edges[i].label == label)
            return edges[i].to;
    }
    return -1;
}

bool isDividable(States states, Label label, Edges edges){
    bool hasEnd = false;
    bool noEnd = false;
    for(int i = 0; i < states.size(); i++) {
        if(transTo(states[i], label, edges) != -1)
            hasEnd = true;
        else noEnd = true;
    }
    if(hasEnd == true && noEnd == true)
        return true;
    else return false;
}

States difference(States s1, States s2) {
    States res = States();
    for (int i = 0; i < s1.size(); i++) {
        if (find(s2.begin(), s2.end(), s1[i]) == s2.end())
            res.push_back(s1[i]);
    }
    return res;
}

/*--------------------------------------------------
 * 以下为类方法
 * ------------------------------------------------*/
int DFA::d_stateCount(0);

DFA::DFA() {
    start = d_stateCount++;
    ends = States();
    edges = Edges();
    tagsMap = map<State, Tags>();
}

Labels DFA::getLabels() {
    Labels labels = Labels();
    for (int i = 0; i < edges.size(); i++) {
        if (edges[i].label != EPSILON && !exists(labels, edges[i].label))
            labels.push_back(edges[i].label);
    }
    return labels;
}

States DFA::getNoEndStates() {
    States states = States();
    for (int i = 0; i < edges.size(); i++) {
        if (!exists(ends, edges[i].from) && !exists(states, edges[i].from))
            states.push_back(edges[i].from);
    }
    return states;
}

DFA DFA::minimize() {
    DFA minDFA = DFA();
    d_stateCount--;
    vector<States> minStates;
    Labels labels = getLabels();
    States endStates = ends;
    States noEndStates = getNoEndStates();
    minStates.push_back(endStates);
    minStates.push_back(noEndStates);

    while (minStates.size() != (endStates.size() + noEndStates.size())) {
        int subCount = 0;
        for (int i = 0; i < minStates.size(); i++) {
            States currStates = minStates[i];
            int glag = 0;
            Label label;
            States sub;
            for (int j = 0; j < labels.size(); j++) {
                label = labels[j];
                sub = move(currStates, label, edges);
                int flag = 0;
                for (int k = 0; k < minStates.size(); k++) {
                    //存在一个没有转换，一个有转换的情况
                    if (isDividable(currStates, label, edges))
                        flag++;
                    //存在都有转换，但转换分布在不同节点中 或 都没有转换
                    else if (difference(sub, minStates[k]).size() > 0 && difference(sub, minStates[k]).size() < sub.size())
                        flag++;
                }
                // == minStates.size()
                if (flag) {
                    glag++;
                    break;
                }
            }
            if (glag == 1) {
                States next_one = States();
                next_one.push_back(currStates[0]);
                sub = move(next_one, label, edges);
                int pos;
                for (int m = 0; m < minStates.size(); m++) {
                    if (difference(sub, minStates[m]).size() == 0) {
                        pos = m;
                        break;
                    }
                }
                States next_two = States();
                for (int n = 1; n < currStates.size(); n++) {
                    States temp = States();
                    temp.push_back(currStates[n]);
                    sub = move(temp, label, edges);
                    if (!sub.empty() && difference(sub, minStates[pos]).size() == 0)
                        next_one.push_back(currStates[n]);
                    else next_two.push_back(currStates[n]);
                }
                minStates.erase(minStates.begin() + i);
                if (!next_one.empty())
                    minStates.push_back(next_one);
                if (!next_two.empty())
                    minStates.push_back(next_two);
            } else subCount++;
        }
        if (subCount == minStates.size())
            break;
    }

    States represent = States();
    map<State, State> representMap;
    //选取代表
    for (int i = 0; i < minStates.size(); i++) {
        State rep;
        if (exists(minStates[i], start)) {
            rep = start;
            minDFA.start = start;
        } else {
            sort(minStates[i].begin(), minStates[i].end());
            rep = minStates[i][0];
        }
        represent.push_back(rep);
        if (exists(ends, rep)) {
            minDFA.ends.push_back(rep);
            for (int j = 0; j < minStates[i].size(); j++) {
                if (minDFA.tagsMap.find(rep) == minDFA.tagsMap.end()) {
                    minDFA.tagsMap[rep] = Tags();
                }
                for (int k = 0; k < tagsMap[minStates[i][j]].size(); k++) {
                    if (!exists(minDFA.tagsMap[rep], tagsMap[minStates[i][j]][k]))
                        minDFA.tagsMap[rep].push_back(tagsMap[minStates[i][j]][k]);
                }
            }
        }
        for (int j = 0; j < minStates[i].size(); j++) {
            representMap.insert(pair<State, State>(minStates[i][j], rep));
        }
    }
    //确定边
    for (int i = 0; i < edges.size(); i++) {
        Edge edge{representMap[edges[i].from], representMap[edges[i].to], edges[i].label};
        if (!exists(minDFA.edges, edge))
            minDFA.edges.push_back(edge);
    }
    return minDFA;
}