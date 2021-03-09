#include "Algorithm1.h"
#include "TreePair.h"
#include <algorithm>

void Algorithm1::compute(Tree* srcTree, Tree* dstTree, int minHeight, HIPList& L1, HIPList& L2, 
    std::vector<std::pair<Tree*, Tree*>>& candidateMappings, std::vector<std::pair<Tree*, Tree*>>& resultMappings)
{
    L1.push(srcTree->height(srcTree), srcTree);
    L2.push(dstTree->height(dstTree), dstTree);
    while (Util::min(L1.peekMax(), L2.peekMax()) > minHeight)
    {
        if (L1.peekMax() != L2.peekMax())
        {
            if (L1.peekMax() > L2.peekMax())
            {
                std::vector<Tree*> trees = L1.pop();
                for (Tree* element : trees)
                {
                    L1.open(element);
                }
            }
            else
            {
                std::vector<Tree*> trees = L2.pop();
                for (Tree* element : trees)
                {
                    L2.open(element);
                }
            }
        }
        else
        {
            std::vector<Tree*> H1 = L1.pop();
            std::vector<Tree*> H2 = L2.pop();
            for (Tree* t1 : H1)
            {
                for (Tree* t2 : H2)
                {
                     if (t1->isomorphic(t2))
                    {
                        if (dstTree->existsIsomorphic(t1, t2) || srcTree->existsIsomorphic(t2, t1))
                        {
                            candidateMappings.push_back(std::pair<Tree*, Tree*>(t1, t2));
                        }
                        else
                        {
                            std::vector<Tree*> t1Descendants = t1->getDescendants();
                            std::vector<Tree*> t2Descendants = t2->getDescendants();
                            for (Tree* e1 : t1Descendants)
                            {
                                for (Tree* e2 : t2Descendants)
                                {
                                    if (e1->isomorphic(e2))
                                    {
                                        resultMappings.push_back(std::pair<Tree*, Tree*>(e1, e2));
                                    }
                                }
                            }
                        }
                    }
                }
            }
            std::vector<std::pair<Tree*, Tree*>> AUnionM;
            if (!candidateMappings.empty() && !resultMappings.empty())
            {
                AUnionM.insert(candidateMappings.end(), resultMappings.begin(), resultMappings.end());
            }
            if (candidateMappings.empty())
            {
                AUnionM = resultMappings;
            }
            if (resultMappings.empty())
            {
                AUnionM = candidateMappings;
            }
            //Q
            std::vector<Tree*> srcTreeNodes = srcTree->postorder(srcTree);
            std::vector<Tree*> dstTreeNodes = dstTree->postorder(dstTree);
            for (Tree* t1 : H1)
            {
                for (Tree* tx : dstTreeNodes)
                {
                    if (!TreePair::findPair(t1, tx, AUnionM))
                    {
                        L1.open(t1);
                    }
                }
            }
            for (Tree* tx : srcTreeNodes)
            {
                for (Tree* t2 : H2)
                {
                    if (!TreePair::findPair(tx, t2, AUnionM)) 
                    {
                        L2.open(t2);
                    }
                }
            }
        }
    }
    
    sort(candidateMappings.begin(), candidateMappings.end(), [resultMappings](const std::pair<Tree*, Tree*> pair1, const std::pair<Tree*, Tree*> pair2)
        {
            return pair1.first->dice(pair1.first, pair1.second, resultMappings) > pair2.first->dice(pair2.first, pair2.second, resultMappings);
        });
    while (!candidateMappings.empty())
    {
        std::pair<Tree*, Tree*> firstElem = candidateMappings.at(0);
        candidateMappings.erase(resultMappings.begin());
        std::vector<Tree*> t1Desc = firstElem.first->getDescendants();
        std::vector<Tree*> t2Desc = firstElem.second->getDescendants();
        for (Tree* st1 : t1Desc)
        {
            for (Tree* st2 : t2Desc)
            {
                if (st1->isomorphic(st2))
                {
                    resultMappings.push_back(std::pair<Tree*, Tree*>(st1, st2));
                }
            }
        }
        std::vector<std::pair<Tree*, Tree*>>::iterator resultMIt;
        for (resultMIt = candidateMappings.begin(); resultMIt != candidateMappings.end(); ++resultMIt)
        {
            if ((*resultMIt).first == firstElem.first || (*resultMIt).second == firstElem.second)
            {
                resultMIt = candidateMappings.erase(resultMIt);
            }
        }
    }
}
