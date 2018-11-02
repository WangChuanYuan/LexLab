//
// Created by 王川源 on 2018/10/30.
//
#ifndef LEXLAB_RECOMPILER_H
#define LEXLAB_RECOMPILER_H

#include <string>
#include "FA.h"

using namespace std;
typedef string RE;

class RECompiler {
private:
    RE regex;
public:
    RECompiler();
    RECompiler(RE regex);
    ~RECompiler();

    bool isLegal();
    FA toNFA();
};

#endif //LEXLAB_RECOMPILER_H
