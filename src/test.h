// "/Users/charles/UTS/SVF-all/temp/SVF-Teaching-Solutions/Assignment-4/testcase/bc/test1.ll"
#ifndef TEST_H_
#define TEST_H_
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
// TEST(SSE, test1)
void test1()
{
    SVF::SVFModule *svfModule = SVF::LLVMModuleSet::getLLVMModuleSet()->buildSVFModule({"./testcase/bc/test1.c.ll"});

/// Build Program Assignment Graph (PAG)
    PAGBuilder builder;
    PAG *pag = builder.build(svfModule);
    pag->dump(svfModule->getModuleIdentifier() + ".pag");

    /// Create Andersen's pointer analysis
    // Andersen *ander = AndersenWaveDiff::createAndersenWaveDiff(pag);
    // ander->analyze();
    // ander->dump(svfModule->getModuleIdentifier() + ".consG")
    /// ICFG
    ICFG *icfg = pag->getICFG();
    icfg->dump(svfModule->getModuleIdentifier() + ".icfg");
    SSE* sse = new SSE(pag);
    std::vector<const ICFGNode *> path;
    std::stack<const Instruction *>callstack;
    std::set<const ICFGNode *> visited;
    std::set<const CallBlockNode *> sources;
    std::set<const CallBlockNode *> sinks;
    for (const CallBlockNode *src : sse->identify("source",sources))
    {
        for (const CallBlockNode *snk : sse->identify("sink",sinks))
        {
            sse->DFS(visited, path, callstack, src, snk);
        }
    }

}

// int Test()
// {
//     // ::testing::InitGoogleTest();
//     // return RUN_ALL_TESTS();
    
//     return 0;
// }





#endif