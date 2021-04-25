//
// Created by guanqin on 2/12/20.
//

#include "SSE.h"
#include <ostream>
#include "test.h"
#include <iostream>
#include <typeinfo>
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

        SVFUtil::outs()<< "start:  \n";
        //current path reached, start verifying reasoning symbolic execution
        for(const ICFGNode * iNode:path)
        {
            SVFUtil::outs()<<"{ " << iNode->getId() << " } -> ";
        }
        SVFUtil::outs()<< "  End \n";
        SSEsolve(path);
        
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

void SSE::SSEsolve(std::vector<const ICFGNode *>& path)
{

    context ctx;
    solver s(ctx);
    
    for(const ICFGNode* iNode: path)
    {
        // to fetch the pagEdges from IntraBlockNode
        if(const IntraBlockNode* ibNode = SVFUtil::dyn_cast<IntraBlockNode>(iNode))
        {
            SVFUtil::outs() << "\n SSE IntraBlockNode content:  " << ibNode->toString() << "\n";
            
            for(const PAGEdge* pagE : ibNode->getPAGEdges())
            {
                //  SVFUtil::outs() << " SSE pag content:" << pagE->toString()  <<"\t src node value name : " <<  pagE->getSrcNode()->getValueName() << "\n";  
                SVFUtil::outs() << "\n---------------------unprocessed----------------------\n" ;
                SVFUtil::outs() <<   pagE->getSrcNode()->toString() << "\n"; 
                SVFUtil::outs() <<   pagE->getDstNode()->toString() << "\n"; 
                
                
                if (const BinaryOPPE* oppe = SVFUtil::dyn_cast<BinaryOPPE>(pagE))
                {
                    // pagE->getDstNode()->isAddressTakenPtr();
                    SVFUtil::outs()<< "binaryOPPE " << oppe->getEdgeID() << "\n" ;
                    
                    // SVFUtil::outs()<< "binaryOPPE  " << oppe->getSrcNode()->toString() ;

                } else if (const CallPE* callpe = SVFUtil::dyn_cast<CallPE>(pagE))
                {

                } else if (const CopyPE* copype = SVFUtil::dyn_cast<CopyPE>(pagE))
                {
                    
                } else if(const GepPE* geppe = SVFUtil::dyn_cast<GepPE>(pagE))
                {

                } else if(const LoadPE* loadpe = SVFUtil::dyn_cast<LoadPE>(pagE))
                {

                }else if(const RetPE* retpe = SVFUtil::dyn_cast<RetPE>(pagE))
                {

                } else if(const StorePE* storepe = SVFUtil::dyn_cast<StorePE>(pagE))
                {

                } else if(const UnaryOPPE* unaryoppe = SVFUtil::dyn_cast<UnaryOPPE>(pagE))
                {
                    
                } else {
                    throw("other edges ? ");
                }
            }
        }
    }

    // std::cout << s.check() << "\n";
    // model m = s.get_model();
    // std::cout << "Model:\n" << s.to_smt2() << "\n";
}
void SSE::Node2Expr(const PAGNode* node)
{
    if(const ValPN* valueNode = SVFUtil::dyn_cast<ValPN>(node))
    {
        SVFUtil::outs() <<" ValPN node value: " <<  *valueNode->getValue() << "\n";
    }
}


void SSE::testZ3()
{
    std::cout << "tactic example 5\n";
    context c;
    expr x = c.real_const("x");
    expr y = c.real_const("y");
    solver s = tactic(c, "smt").mk_solver();
    s.add(x > y + 1);
    s.add(x == 3 || x== 4 );// mock like pts to two address-taken varible in PAG addr edges
    s.add(x == 4); //update map 
    std::cout << s.check() << "\n";
    std::cout << s.get_model() << "\n";
}




int main(){
    ::testing::InitGoogleTest();
    // return 
    return RUN_ALL_TESTS();
}