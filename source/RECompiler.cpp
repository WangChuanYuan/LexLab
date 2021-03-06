#include <utility>

//
// Created by 王川源 on 2018/10/30.
//
#include <utility>
#include <stack>
#include "../include/RECompiler.h"
#include "../include/Global.h"

bool isOp(char c) {
    return c == LEFT_BRACKET || c == RIGHT_BRACKET || c == JOIN || c == UNION || c == CLOSURE;
}

bool isLetter(char c) {
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) || (c >= '0' && c <= '9') || c == '.' || c == '_';
}

/**
 * 增加join运算符
 * @param re 原先的中缀正则表达式
 * @return 完整化后的中缀正则表达式
 */
RE integrity(RE re) {
    int len = re.size();
    char first, second;
    string res;
    for (int i = 0; i < len - 1; i++) {
        first = re.at(i);
        second = re.at(i + 1);
        res += first;
        if (first != LEFT_BRACKET && first != UNION && isLetter(second))
            res += JOIN;
        else if (second == LEFT_BRACKET && first != UNION && first != LEFT_BRACKET)
            res += JOIN;
    }
    res += second;
    return res;
}

/*
 *     $ ( * | . )
 * isp 0 1 7 5 3 8
 * icp 0 8 6 4 2 1
 */
// in stack priority
int isp(char c) {
    switch (c) {
        case END:
            return 0;
        case LEFT_BRACKET:
            return 1;
        case CLOSURE:
            return 7;
        case UNION:
            return 5;
        case JOIN:
            return 3;
        case RIGHT_BRACKET:
            return 8;
        default:
            return -1;
    }
}

// in coming priority
int icp(char c) {
    switch (c) {
        case END:
            return 0;
        case LEFT_BRACKET:
            return 8;
        case CLOSURE:
            return 6;
        case UNION:
            return 4;
        case JOIN:
            return 2;
        case RIGHT_BRACKET:
            return 1;
        default:
            return -1;
    }
}

/**
 * 中缀转后缀
 * @param re 完整化后的中缀正则表达式
 * @return 后缀表达式
 */
RE toPostfix(RE re) {
    //添加结束字符
    re += END;

    stack<char> s;
    char c1 = END, c2, op;
    s.push(c1);

    string res;
    int reader = 0;
    c1 = re.at(reader++);
    while (!s.empty()) {
        if (isLetter(c1)) {
            res += c1;
            c1 = re.at(reader++);
        } else {
            //为操作符
            c2 = s.top();
            if (isp(c2) < icp(c1)) {
                s.push(c1);
                c1 = re.at(reader++);
            } else if (isp(c2) > icp(c1)) {
                op = s.top();
                s.pop();
                res += op;
            } else {
                op = s.top();
                s.pop();
                if (op == LEFT_BRACKET)
                    c1 = re.at(reader++);
            }
        }
    }
    return res;
}
/*--------------------------------------------------
 * 以下为类方法
 * ------------------------------------------------*/
RECompiler::RECompiler() : regex(""), tag(""){}

RECompiler::RECompiler(RE re, Tag t) : regex(std::move(re)), tag(std::move(t)) {}

/**
 * 检查正则表达式是否合法
 * 包括是否含有非字母表字符以及括号是否匹配
 * @param re
 * @return
 */
bool RECompiler::isLegal() {
    int len = regex.size();
    char c;
    stack<char> s;
    for (int i = 0; i < len; i++) {
        c = regex.at(i);
        if (isLetter(c))
            continue;
        else if (isOp(c)) {
            if (c == LEFT_BRACKET)
                s.push(c);
            else if (c == RIGHT_BRACKET) {
                if (s.empty())
                    return false;
                else s.pop();
            }
            continue;
        } else return false;
    }
    if (!s.empty())
        return false;
    return true;
}

NFA RECompiler::NFA_join(NFA left, NFA right){
    Edge trans{left.ends[0], right.start, EPSILON};
    left.edges.insert(left.edges.end(), right.edges.begin(), right.edges.end());
    left.ends[0] = right.ends[0];
    left.edges.push_back(trans);
    left.tagsMap.clear();
    Tags tags;
    tags.push_back(tag);
    left.tagsMap.insert(pair<State, Tags>(left.ends[0], tags));
    return left;
}

NFA RECompiler::NFA_union(NFA left, NFA right){
    NFA fa = NFA();
    Edge trans1{fa.start, left.start, EPSILON};
    Edge trans2{fa.start, right.start, EPSILON};
    Edge trans3{left.ends[0], fa.ends[0], EPSILON};
    Edge trans4{right.ends[0], fa.ends[0], EPSILON};
    fa.edges.insert(fa.edges.end(), left.edges.begin(), left.edges.end());
    fa.edges.insert(fa.edges.end(), right.edges.begin(), right.edges.end());
    fa.edges.push_back(trans1);
    fa.edges.push_back(trans2);
    fa.edges.push_back(trans3);
    fa.edges.push_back(trans4);
    Tags tags;
    tags.push_back(tag);
    fa.tagsMap.insert(pair<State, Tags>(fa.ends[0], tags));
    return fa;
}

NFA RECompiler::NFA_closure(NFA fa){
    NFA res = NFA();
    Edge trans1{res.start, fa.start, EPSILON};
    Edge trans2{res.start, res.ends[0], EPSILON};
    Edge trans3{fa.ends[0], fa.start, EPSILON};
    Edge trans4{fa.ends[0], res.ends[0], EPSILON};
    res.edges.insert(res.edges.end(), fa.edges.begin(), fa.edges.end());
    res.edges.push_back(trans1);
    res.edges.push_back(trans2);
    res.edges.push_back(trans3);
    res.edges.push_back(trans4);
    Tags tags;
    tags.push_back(tag);
    res.tagsMap.insert(pair<State, Tags>(res.ends[0], tags));
    return res;
}

/**
 * 使用Thompson算法将正则表达式转为NFA
 * @return
 */
NFA RECompiler::toNFA() {
    regex = integrity(regex);
    regex = toPostfix(regex);

    int len = regex.size();
    char c;
    stack<NFA> s;
    NFA fa, left, right;
    NFA::n_stateCount = NFA::n_stateCount - 6;
    for(int i = 0; i < len; i++){
        c = regex.at(i);
        switch(c){
            case JOIN:
                right = s.top();
                s.pop();
                left = s.top();
                s.pop();
                fa = NFA_join(left, right);
                s.push(fa);
                break;
            case UNION:
                right = s.top();
                s.pop();
                left = s.top();
                s.pop();
                fa = NFA_union(left, right);
                s.push(fa);
                break;
            case CLOSURE:
                left = s.top();
                s.pop();
                fa = NFA_closure(left);
                s.push(fa);
                break;
            default:
                fa = NFA(c);
                s.push(fa);
        }
    }
    fa = s.top();
    s.pop();
    return fa;
}

NFA RECompiler::merge(vector<NFA> nfas) {
    if(nfas.size() == 1)
        return nfas[0];
    else {
        NFA merged = NFA();
        NFA::n_stateCount--;
        States ends = States();
        for(int i = 0; i < nfas.size(); i++) {
            merged.edges.insert(merged.edges.end(), nfas[i].edges.begin(), nfas[i].edges.end());
            ends.insert(ends.end(), nfas[i].ends.begin(), nfas[i].ends.end());
            Edge edge{merged.start, nfas[i].start, EPSILON};
            merged.edges.push_back(edge);
            merged.tagsMap.insert(nfas[i].tagsMap.begin(), nfas[i].tagsMap.end());
        }
        merged.ends = ends;
        return merged;
    }
}