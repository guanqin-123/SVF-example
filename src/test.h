// "/Users/charles/UTS/SVF-all/temp/SVF-Teaching-Solutions/Assignment-4/testcase/bc/test1.ll"
#ifndef TEST_H_
#define TEST_H_
#include "Assignment-1.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "SVF-FE/LLVMUtil.h"
#include "Graphs/SVFG.h"
#include "WPA/Andersen.h"
#include "SABER/LeakChecker.h"
#include "SVF-FE/PAGBuilder.h"
#include "SSE.h"

using namespace SVF;
using namespace llvm;
using namespace std;
TEST(SSE, test1)
{
    SVFModule* svfModule = LLVMModuleSet::getLLVMModuleSet()->buildSVFModule("./testcase/bc/test1.ll");

/// Build Program Assignment Graph (PAG)
    PAGBuilder builder;
    PAG *pag = builder.build(svfModule);
    pag->dump("pag");

    /// Create Andersen's pointer analysis
    Andersen *ander = AndersenWaveDiff::createAndersenWaveDiff(pag);


    /// Call Graph
    PTACallGraph *callgraph = ander->getPTACallGraph();
    callgraph->dump("callgraph");

    /// ICFG
    ICFG *icfg = pag->getICFG();
    icfg->dump("icfg");

    /// Value-Flow Graph (VFG)
    VFG *vfg = new VFG(callgraph);
    vfg->dump("vfg");

    /// Sparse value-flow graph (SVFG)
    SVFGBuilder svfBuilder;
    SVFG *svfg = svfBuilder.buildFullSVFGWithoutOPT(ander);
    svfg->dump("svfg");

    LeakChecker *saber = new LeakChecker(); // if no checker is specified, we use leak checker as the default one.
    saber->runOnModule(svfModule);
}







#endif