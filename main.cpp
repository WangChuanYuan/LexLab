#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include "include/RECompiler.h"

vector<string> split(const string& s, const string& sep) {
    vector<string> res;
    string::size_type pos1, pos2;
    pos2 = s.find(sep);
    pos1 = 0;
    while (string::npos != pos2) {
        res.push_back(s.substr(pos1, pos2-pos1));

        pos1 = pos2 + sep.size();
        pos2 = s.find(sep, pos1);
    }
    if(pos1 != s.length())
        res.push_back(s.substr(pos1));
    return res;
}

int main() {
    ifstream fin(".\\resource\\reg.l", ios::in);
    char line[1024] = {0};
    int state = 0;
    vector<string> splitS;
    map<string, string> preDefine;
    map<string, string> tagAndRE;
    while(fin.getline(line, sizeof(line))) {
        stringstream ss(line);
        string content = ss.str();
        switch(state) {
            case 0:
                if(content == "%%"){
                    state = 1;
                    continue;
                }
                splitS = split(content, " ");
                preDefine[splitS[0]] = splitS[1];
                break;
            case 1:
                splitS = split(content, " ");
                for(map<string, string>::iterator it = preDefine.begin(); it != preDefine.end(); it++) {
                    string pre = it->first;
                    string def = it->second;
                    int pos = splitS[1].find(pre);
                    while (pos != -1) {
                        splitS[1].replace(pos, pre.length(), def);
                        pos = splitS[1].find(pre);
                    }
                }
                tagAndRE[splitS[0]] = splitS[1];
                break;
        }
    }
    fin.close();
    vector<NFA> nfas;
    for(map<string, string>::iterator it = tagAndRE.begin(); it != tagAndRE.end(); it++) {
        Tag tag = it->first;
        RE re = it->second;
        RECompiler reCompiler(re, tag);
        NFA nfa = reCompiler.toNFA();
        nfas.push_back(nfa);
    }
    NFA merged = RECompiler::merge(nfas);
    DFA dfa = merged.toDFA();
    DFA dfao = dfa.minimize();
    //生成代码
    ifstream codeIn(".\\resource\\template.cpp");
    ofstream codeOut(".\\resource\\Lex_out.cpp");
    string code;
    char codeLine[1024] = {0};
    while(codeIn.getline(codeLine, sizeof(codeLine))) {
        stringstream ss(codeLine);
        code += (ss.str() + "\r\n");
    }
    string initialCode;
    Edges edges = dfao.edges;
    map<State, Tags> tagsMap = dfao.tagsMap;
    for (int i = 0; i < edges.size(); i++) {
        stringstream ss;
        ss << "edges.push_back({" << edges[i].from << "," << edges[i].to << ", '" << edges[i].label << "'});" << endl;
        initialCode += ss.str();
    }
    for (map<State, Tags>::iterator it = tagsMap.begin(); it != tagsMap.end(); it++){
        stringstream ss;
        ss << "tagMap[" << it->first << "] = \"" << it->second[0] << "\";" << endl;
        initialCode += ss.str();
    }
    string templateRegion = "/* initialize code */";
    int pos = code.find(templateRegion);
    if(pos != -1)
        code.replace(pos, templateRegion.length(), initialCode);
    codeOut << code;
    codeIn.close();
    codeOut.close();
    return 0;
}