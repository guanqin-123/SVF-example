//
// Created by guanqin on 2/12/20.
//

#include "SSE.h"
#include <ostream>
#include "test.h"
#define NODE(x) node##x
using namespace SVF;
using namespace SVFUtil;
using namespace llvm;
using namespace std;
using namespace z3;




void SSE::DFS(std::set<const ICFGNode *> &visited, std::vector<const ICFGNode *> &path, std::stack<const Instruction*> &callstack, const ICFGNode *src, const ICFGNode *dst)
{
    visited.insert(src);
    path.push_back(src);
    if (src == dst)
    {
        //current path reached, start verifying reasoning symbolic execution
        for(const ICFGNode * iNode:path)
        {
            SVFUtil::outs()<<"{ " << iNode->toString() << " } -> ";
        }
        SVFUtil::outs()<< "End \n";
    }   
    for (const ICFGEdge *edge : src->getOutEdges())
    {
        if (visited.find(edge->getDstNode()) == visited.end())
        {
            if(edge->isIntraCFGEdge()){
                DFS(visited, path, callstack, edge->getDstNode(), dst);
            }else if(const CallCFGEdge* callEdge = SVFUtil::dyn_cast<CallCFGEdge>(edge)){   // edge->isCFGEdge()
                callstack.push(callEdge->getCallSite());
                DFS(visited, path, callstack,  edge->getDstNode(), dst);
            }else if(const RetCFGEdge* retEdge = SVFUtil::dyn_cast<RetCFGEdge>(edge)){ //edge->isRetCFGEdge()
                if(callstack.top() == retEdge->getCallSite())
                {
                    callstack.pop();
                    DFS(visited, path, callstack, edge->getDstNode(), dst);
                }
            } 
        }
    }
    visited.erase(src);
    path.pop_back();
}

// void SSE::SSEsolve(std::vector<const ICFGNode *>& path)
// {
//     for(const ICFGNode* iNode: path)
//     {
        
//     }
// }










int main(){
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}