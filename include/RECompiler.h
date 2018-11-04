//
// Created by 王川源 on 2018/10/30.
//
#ifndef LEXLAB_RECOMPILER_H
#define LEXLAB_RECOMPILER_H

#include "NFA.h"

class RECompiler {
private:
    RE regex;
    Tag tag;
public:
    RECompiler();
    RECompiler(RE regex, Tag tag);

    bool isLegal();
    NFA NFA_join(NFA left, NFA right);
    NFA NFA_union(NFA left, NFA right);
    NFA NFA_closure(NFA fa);
    NFA toNFA();
    static NFA merge(vector<NFA> nfas);
};

#endif //LEXLAB_RECOMPILER_H
