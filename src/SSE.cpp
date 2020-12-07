//
// Created by guanqin on 2/12/20.
//

#include "SSE.h"
#include <ostream>
#define NODE(x) node##x
using namespace SVF;
using namespace SVFUtil;
using namespace llvm;
using namespace std;
using namespace z3;

void SSE::pathTrack(vector<icfgPath> &paths, icfgPath &seq, set<ICFGNode *> &visited, ICFGNode *src, ICFGNode *dst) {
    visited.insert(src);
    seq.push_back(src);
    if (src->getId()==dst->getId())
    {
        //store one reached seq
        paths.push_back(seq);
    }
    for ( auto it = src->OutEdgeBegin(); it != src->OutEdgeEnd(); it ++) {
        ICFGNode *cur = (*it)->getDstNode();
        if (visited.find(cur) == visited.end()) {
            pathTrack(paths, seq, visited, cur, dst);
        }
    }
    visited.erase(src);
    seq.pop_back();
}

void SSE::sse_gether_expr()
{
    for (const vector<ICFGNode*>& single_p : this->icP)
    {
        for (int index = 0; index < single_p.size(); index++)
        {
            ICFGNode* iNode = single_p[index];
            if (auto* ibNode = SVFUtil::dyn_cast<IntraBlockNode>(iNode))
            {
                NodeID flag_expr; // init icfgedge condition
                for (auto& cedges:ibNode->getOutEdges())
                {
                    if (cedges->getDstNode()==single_p[index+1])
                        flag_expr = SVFUtil::dyn_cast<IntraCFGEdge>(cedges)->getBranchCondtion().second;
                }
                for (auto& edge:ibNode->getPAGEdges())
                {
                    int pek = edge->getEdgeKind();
                    if (als.find(pek) == als.end())
                        assert(false && pek && "  edge kind is not included please contact SVF team");
                    als[pek](flag_expr,edge);
                }
            }
        }
        //one path expression all gathered pushed to eVs then clear eV
        eVs.push_back(eV);
        eV.clear();
    }
    sse_solutions(this->eVs);
}

pair<expr,expr>SSE::getExprFromEdge(const PAGEdge* edge) {
    PAGNode* src = edge->getSrcNode();
    PAGNode* dst = edge->getDstNode();
    string srcId = id_to_str(src->getId());
    string dstId = id_to_str(dst->getId());
    expr NODE(srcId) = this->Ctx.int_const(("node"+srcId).c_str());
    expr NODE(dstId) = this->Ctx.int_const(("node"+dstId).c_str());
    return make_pair(NODE(srcId),NODE(dstId));
}
vector<solver> SSE::sse_solutions(vector<EXPR_V> &exprPaths) {
    vector<solver> res;
    for(auto& exprP:exprPaths)
    {
        solver s(Ctx);
        for (auto& ex:exprP)
        {
            s.add(ex);
        }
        res.push_back(s);
        std::cout << "---------finish analysis --------- " << "\n";
        std::cout << s.check() << "\n";
        std::cout << s.assertions()<< "\n";
    }
}