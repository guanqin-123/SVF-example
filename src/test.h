
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
TEST(SSE, test0)
{
    SVF::SVFModule *svfModule = SVF::LLVMModuleSet::getLLVMModuleSet()->buildSVFModule({"./testcase/bc/power3B.c.ll"});

/// Build Program Assignment Graph (PAG)
    PAGBuilder builder;
    PAG *pag = builder.build(svfModule);
    /// Create Andersen's pointer analysis
    Andersen* ander = new Andersen(pag);
    ander->analyze();
    ander->getConstraintGraph()->dump(svfModule->getModuleIdentifier() + ".consG");
    /// ICFG
    ICFG *icfg = pag->getICFG();
    icfg->dump(svfModule->getModuleIdentifier() + ".icfg");
    SSE* sse = new SSE(pag,icfg);
    std::vector<const ICFGNode *> path;
    std::stack<const Instruction *>callstack;
    std::set<const ICFGNode *> visited;
    std::set<const ICFGNode *> start;
    std::set<const ICFGNode *> end;
    for (const ICFGNode *src : sse->identifyStart(start))
    {
        for (const ICFGNode *dst : sse->identifyEnd(end))
        {
            sse->DFS(visited, path, callstack, src, dst);
        }
    }
    // sse->testZ3();
    SVF::LLVMModuleSet::releaseLLVMModuleSet();
    SVF::PAG::releasePAG();
    delete sse;
}
// TEST(SSE, test1)
// {
//     SVF::SVFModule *svfModule = SVF::LLVMModuleSet::getLLVMModuleSet()->buildSVFModule({"./testcase/bc/test0_1.c.ll"});

// /// Build Program Assignment Graph (PAG)
//     PAGBuilder builder;
//     PAG *pag = builder.build(svfModule);
//     pag->dump(svfModule->getModuleIdentifier() + ".pag");

//     /// Create Andersen's pointer analysis
//     Andersen* ander = new Andersen(pag);
//     ander->analyze();
//     ander->getConstraintGraph()->dump(svfModule->getModuleIdentifier() + ".consG");
//     /// ICFG
//     ICFG *icfg = pag->getICFG();
//     icfg->dump(svfModule->getModuleIdentifier() + ".icfg");
//     SSE* sse = new SSE(pag);
//     std::vector<const ICFGNode *> path;
//     std::stack<const Instruction *>callstack;
//     std::set<const ICFGNode *> visited;
//     std::set<const CallBlockNode *> sources;
//     std::set<const CallBlockNode *> sinks;
//     for (const CallBlockNode *src : sse->identify("source",sources))
//     {
//         for (const CallBlockNode *snk : sse->identify("sink",sinks))
//         {
//             sse->DFS(visited, path, callstack, src, snk);
//         }
//     }
//     SVF::LLVMModuleSet::releaseLLVMModuleSet();
//     SVF::PAG::releasePAG();
//     delete sse;
// }
// TEST(SSE, test2)
// {
//     SVF::SVFModule *svfModule = SVF::LLVMModuleSet::getLLVMModuleSet()->buildSVFModule({"./testcase/bc/test1.c.ll"});

//     PAGBuilder builder;
//     PAG *pag = builder.build(svfModule);
//     pag->dump(svfModule->getModuleIdentifier() + ".pag");

//     ICFG *icfg = pag->getICFG();
//     icfg->dump(svfModule->getModuleIdentifier() + ".icfg");
//     SSE* sse = new SSE(pag);
//     std::vector<const ICFGNode *> path;
//     std::stack<const Instruction *>callstack;
//     std::set<const ICFGNode *> visited;
//     std::set<const CallBlockNode *> sources;
//     std::set<const CallBlockNode *> sinks;
//     for (const CallBlockNode *src : sse->identify("source",sources))
//     {
//         for (const CallBlockNode *snk : sse->identify("sink",sinks))
//         {
//             sse->DFS(visited, path, callstack, src, snk);
//         }
//     }
//     SVF::LLVMModuleSet::releaseLLVMModuleSet();
//     SVF::PAG::releasePAG();
//     delete sse;
// }
/**
TEST(SSE, test2)
{
    SVF::SVFModule *svfModule = SVF::LLVMModuleSet::getLLVMModuleSet()->buildSVFModule({"./testcase/bc/test2.c.ll"});

/// Build Program Assignment Graph (PAG)
    PAGBuilder builder;
    PAG *pag = builder.build(svfModule);
    pag->dump(svfModule->getModuleIdentifier() + ".pag");
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
    SVF::LLVMModuleSet::releaseLLVMModuleSet();
    SVF::PAG::releasePAG();
    delete sse;
}

TEST(SSE, test3)
{
    SVF::SVFModule *svfModule = SVF::LLVMModuleSet::getLLVMModuleSet()->buildSVFModule({"./testcase/bc/test3.c.ll"});

/// Build Program Assignment Graph (PAG)
    PAGBuilder builder;
    PAG *pag = builder.build(svfModule);
    pag->dump(svfModule->getModuleIdentifier() + ".pag");
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
    SVF::LLVMModuleSet::releaseLLVMModuleSet();
    SVF::PAG::releasePAG();
    delete sse;
}
**/

#endif