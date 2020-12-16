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
    typedef vector<expr> EXPR_V;
    typedef vector<ICFGNode*> icfgPath;


    static SSE& getInstance()
    {
        static SSE sse;
        return sse;
    }
    void pathTrack(vector<icfgPath> &paths, icfgPath &seq, set<ICFGNode*> &visited, ICFGNode* src, ICFGNode* dst);

    //check two nodes reachebility stored paths in icP or raise assertions and force to stop
    void check_reachability(ICFGNode* icfgPN1, ICFGNode* icfgPN2)
    {
        set<ICFGNode *> visited;
        icfgPath seq;
        //get the paths to icP
        pathTrack(this->icP, seq, visited, icfgPN1, icfgPN2);
        if (this->isEmpty())
            assert(false && "no reachebility between two nodes");
        SSE::sse_gether_expr();
    }
    vector<icfgPath> getAllPaths()
    {
        return this->icP;
    }

    inline string id_to_str(u32_t num)
    {
        std::stringstream ss;
        string str;
        ss << num;
        ss >> str;
        return str;
    }

    void sse_gether_expr();

    pair<expr,expr>getExprFromEdge(const PAGEdge* edge);

    vector<solver> sse_solutions(vector<EXPR_V>& exprPaths);


    // edge cases allocators
    unordered_map<int,std::function<void(NodeID, const PAGEdge*)>> als = {
            {0, [this](NodeID flag, const PAGEdge* pagEdge){this->processACS(flag, pagEdge);}},
            {1, [this](NodeID flag, const PAGEdge* pagEdge){this->processACS(flag, pagEdge);}},
            {2, [this](NodeID flag, const PAGEdge* pagEdge){this->processACS(flag, pagEdge);}},
            {3, [this](NodeID flag, const PAGEdge* pagEdge){this->processACS(flag, pagEdge);}},
            {4, [this](NodeID flag, const PAGEdge* pagEdge){this->processCall(flag, pagEdge);}},
            {5, [this](NodeID flag, const PAGEdge* pagEdge){this->processRet(flag, pagEdge);}},
            {6, [this](NodeID flag, const PAGEdge* pagEdge){this->processNGep(flag, pagEdge);}},
            {7, [this](NodeID flag, const PAGEdge* pagEdge){this->processVGep(flag, pagEdge);}},
            {8, [this](NodeID flag, const PAGEdge* pagEdge){this->processTF(flag, pagEdge);}},
            {9, [this](NodeID flag, const PAGEdge* pagEdge){this->processTJ(flag, pagEdge);}},
            {10, [this](NodeID flag, const PAGEdge* pagEdge){this->processCMP(flag, pagEdge);}},
            {11, [this](NodeID flag, const PAGEdge* pagEdge){this->processBOP(flag, pagEdge);}},
            {12, [this](NodeID flag, const PAGEdge* pagEdge){this->processUOP(flag, pagEdge);}}

            // more ?
    };

    // compare(CMPEdge) types process allocator
    unordered_map<int, std::function<void(NodeID, const PAGEdge*)>> als_cmp = {
            {0, [this](NodeID flag, const PAGEdge* pagEdge){this->processF_F(flag, pagEdge);}},
            {1, [this](NodeID flag, const PAGEdge* pagEdge){this->processF_O(flag, pagEdge);}},
            {33, [this](NodeID flag, const PAGEdge* pagEdge){this->processI_NE(flag, pagEdge);}},
            {34, [this](NodeID flag, const PAGEdge* pagEdge){this->processI_UGT(flag, pagEdge);}},
            {35, [this](NodeID flag, const PAGEdge* pagEdge){this->processI_UGE(flag, pagEdge);}},
            {36, [this](NodeID flag, const PAGEdge* pagEdge){this->processI_ULT(flag, pagEdge);}},
            {37, [this](NodeID flag, const PAGEdge* pagEdge){this->processI_ULE(flag, pagEdge);}},
            {38, [this](NodeID flag, const PAGEdge* pagEdge){this->processI_SGT(flag, pagEdge);}},
            {39, [this](NodeID flag, const PAGEdge* pagEdge){this->processI_SGE(flag, pagEdge);}},
            {40, [this](NodeID flag, const PAGEdge* pagEdge){this->processI_SLT(flag, pagEdge);}},
            {41, [this](NodeID flag, const PAGEdge* pagEdge){this->processI_SLE(flag, pagEdge);}}
    };
    //process Addr, Copy, Store}
    void processACS(const NodeID& flag, const PAGEdge* pagEdge)
    {
        pair<expr, expr> expr_pair = getExprFromEdge(pagEdge);
        cout << "acs"  << "\n";
        eV.push_back(expr_pair.first == expr_pair.second);
    }

    void processCall(const NodeID& flag, const PAGEdge* pagEdge)
    {
        cout << "call";
    }

    void processRet(const NodeID& flag, const PAGEdge* pagEdge)
    {
        cout << "ret";
    }

    void processNGep(const NodeID& flag, const PAGEdge* pagEdge)
    {
        cout << "NGep";
    }

    void processVGep(const NodeID& flag, const PAGEdge* pagEdge)
    {
        cout << "VGep";
    }

    void processTF(const NodeID& flag, const PAGEdge* pagEdge)
    {
        cout << "TF";
    }

    void processTJ(const NodeID& flag, const PAGEdge* pagEdge)
    {
        cout << "TJ";
    }

    //process compare :  ICMP  /  FCMP
    inline void processCMP(const NodeID& flag, const PAGEdge* pagEdge)
    {
        cout << "cmp"<< "\n";
        // icmp / fcmp
        // cmpK will be added in svf project in the future.
        // then just use cmpEdge.get_cmpK() to get the predicate
        SVF::Instruction const *inst = pagEdge->getInst();
        int cmpK = SVFUtil::dyn_cast<llvm::ICmpInst>(inst)->getSignedPredicate();
        als_cmp[cmpK](flag, pagEdge);
    }

    void processBOP(NodeID flag, const PAGEdge* pagEdge)
    {
        cout << "BOP";
    }

    inline void processUOP(NodeID& flag, const PAGEdge* pagEdge)
    {
        pair<expr, expr> expr_pair = getExprFromEdge(pagEdge);
        cout << "UOP" << "\n";
        SVFUtil::outs() << "cmpsrc : " <<  *pagEdge->getSrcNode() <<"\n";
        SVFUtil::outs() << "cmpdst : " <<  *pagEdge->getDstNode() << "\n";
        //when test the concrete number, keep on eye with the compare instructions implies
        eV.push_back(implies((bool)flag,expr_pair.first == expr_pair.second));
    }


    //FCMP_FALSE =  0,  ///< 0 0 0 0    Always false (always folded)
    inline void processF_F(NodeID expr_flag, const PAGEdge* pagEdge){
        assert(false && "no comparison, always returns false");
    }
//    FCMP_OEQ   =  1,  ///< 0 0 0 1    True if ordered and equal
    void processF_O(NodeID expr_flag, const PAGEdge* pagEdge)
    {
        pair<expr, expr> expr_pair = getExprFromEdge(pagEdge);
        cout << "OEQ"  << "\n";
        eV.push_back(expr_pair.first == expr_pair.second);
    }
    /* should be finished as needed in the future...
    FCMP_OGT   =  2,  ///< 0 0 1 0    True if ordered and greater than
    FCMP_OGE   =  3,  ///< 0 0 1 1    True if ordered and greater than or equal
    FCMP_OLT   =  4,  ///< 0 1 0 0    True if ordered and less than
    FCMP_OLE   =  5,  ///< 0 1 0 1    True if ordered and less than or equal
    FCMP_ONE   =  6,  ///< 0 1 1 0    True if ordered and operands are unequal
    FCMP_ORD   =  7,  ///< 0 1 1 1    True if ordered (no nans)
    FCMP_UNO   =  8,  ///< 1 0 0 0    True if unordered: isnan(X) | isnan(Y)
    FCMP_UEQ   =  9,  ///< 1 0 0 1    True if unordered or equal
    FCMP_UGT   = 10,  ///< 1 0 1 0    True if unordered or greater than
    FCMP_UGE   = 11,  ///< 1 0 1 1    True if unordered, greater than, or equal
    FCMP_ULT   = 12,  ///< 1 1 0 0    True if unordered or less than
    FCMP_ULE   = 13,  ///< 1 1 0 1    True if unordered, less than, or equal
    FCMP_UNE   = 14,  ///< 1 1 1 0    True if unordered or not equal
    FCMP_TRUE  = 15,  ///< 1 1 1 1    Always true (always folded)
    FIRST_FCMP_PREDICATE = FCMP_FALSE,
    LAST_FCMP_PREDICATE = FCMP_TRUE,
    BAD_FCMP_PREDICATE = FCMP_TRUE + 1,
    ICMP_EQ    = 32,  ///< equal
    */
    //ICMP_NE    = 33,  ///< not equal
    void processI_NE(NodeID flag, const PAGEdge* pagEdge)
    {
        pair<expr, expr> expr_pair = getExprFromEdge(pagEdge);
        cout << "NE"  << "\n";
        eV.push_back(expr_pair.first != expr_pair.second);
    }

//    ICMP_UGT   = 34,  ///< unsigned greater than
    void processI_UGT(NodeID flag, const PAGEdge* pagEdge)
    {
        pair<expr, expr> expr_pair = getExprFromEdge(pagEdge);
        cout << "UGT"  << "\n";
        eV.push_back(expr_pair.first > expr_pair.second);
    }

//    ICMP_UGE   = 35,  ///< unsigned greater or equal
    void processI_UGE(NodeID flag, const PAGEdge* pagEdge)
    {
        pair<expr, expr> expr_pair = getExprFromEdge(pagEdge);
        cout << "UGE"  << "\n";
        eV.push_back(expr_pair.first >= expr_pair.second);
    }
//    ICMP_ULT   = 36,  ///< unsigned less than
    void processI_ULT(NodeID flag, const PAGEdge* pagEdge)
    {
        pair<expr, expr> expr_pair = getExprFromEdge(pagEdge);
        cout << "ULT"  << "\n";
        eV.push_back(expr_pair.first < expr_pair.second);
    }
//    ICMP_ULE   = 37,  ///< unsigned less or equal
    inline void processI_ULE(NodeID flag, const PAGEdge* pagEdge)
    {
        pair<expr, expr> expr_pair = getExprFromEdge(pagEdge);
        cout << "ULE"  << "\n";
        eV.push_back(expr_pair.first <= expr_pair.second);
    }
//    ICMP_SGT   = 38,  ///< signed greater than
    inline void processI_SGT(NodeID flag, const PAGEdge* pagEdge)
    {
        pair<expr, expr> expr_pair = getExprFromEdge(pagEdge);
        cout << "SGT"  << "\n";
        eV.push_back(expr_pair.first > expr_pair.second);
    }
//    ICMP_SGE   = 39,  ///< signed greater or equal
    void processI_SGE(NodeID flag, const PAGEdge* pagEdge)
    {
        pair<expr, expr> expr_pair = getExprFromEdge(pagEdge);
        cout << "SGE"  << "\n";
        eV.push_back(expr_pair.first >= expr_pair.second);
    }
//    ICMP_SLT   = 40,  ///< signed less than
    void processI_SLT(NodeID flag, const PAGEdge* pagEdge)
    {
        pair<expr, expr> expr_pair = getExprFromEdge(pagEdge);
        cout << "SLT"  << "\n";
        eV.push_back(expr_pair.first < expr_pair.second);
    }
//    ICMP_SLE   = 41,  ///< signed less or equal
    void processI_SLE(NodeID flag, const PAGEdge* pagEdge)
    {
        pair<expr, expr> expr_pair = getExprFromEdge(pagEdge);
        cout << "SLE"  << "\n";
        eV.push_back(expr_pair.first <= expr_pair.second);
    }
//    FIRST_ICMP_PREDICATE = ICMP_EQ,
//    LAST_ICMP_PREDICATE = ICMP_SLE,
//    BAD_ICMP_PREDICATE = ICMP_SLE + 1

private:
    SSE(){};
    inline bool isEmpty()
    {
        return this->icP.empty();
    }
protected:
    //ifcg one path expressions stored in eV
    EXPR_V eV;
    // all expressions
    vector<EXPR_V>eVs;
    vector<icfgPath> icP;
    context Ctx;

};

















#endif //SVF_EX_SSE_H
