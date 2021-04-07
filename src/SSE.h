//
// Created by guanqin on 2/12/20.
//

#ifndef SVF_EX_SSE_H
#define SVF_EX_SSE_H
#include <iostream>
#include <vector>
#include <sstream>
#include <functional>
#include "SVF-FE/LLVMUtil.h"
#include "Graphs/SVFG.h"
#include "z3++.h"

#define NODE(x) node##x
using namespace z3;
using namespace SVF;
using namespace std;
using namespace llvm;
// static symbolic execution


class SSE
{
public:
    SSE(PAG* p): pag(p){};
    std::set<const CallBlockNode *> &identify(const std::string& funName,std::set<const CallBlockNode *>& container)
    {
        for (const CallBlockNode *cs : pag->getCallSiteSet())
        {
            const SVFFunction *fun = SVFUtil::getCallee(cs->getCallSite());
            if (fun->getName() == funName)
            {
                container.insert(cs);
            }
        }
        return container;
    }
    void DFS(std::set<const ICFGNode *> &visited, std::vector<const ICFGNode *> &path, std::stack<const Instruction *> &callstack, const ICFGNode *src, const ICFGNode *dst);
    
private:
    
    PAG *pag;

    

};







#endif //SVF_EX_SSE_H
