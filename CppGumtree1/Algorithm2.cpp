#include "Algorithm2.h"
#include "TreePair.h"

void Algorithm2::compute(Tree* T1, Tree* T2, std::vector<std::pair<Tree*, Tree*>>& resultMapping, float minDice, int maxSize)
{
	int minDescMatch = 3;
	std::vector<Tree*> T1Nodes = T1->postorder(T1);
	for (Tree* t1 : T1Nodes)
	{
		if (!TreePair::isMatched(t1, resultMapping) || TreePair::hasMatchedChild(t1, resultMapping))
		{
			std::vector<Tree*> t2Nodes = T2->candidate(t1, resultMapping, minDescMatch);
			for (Tree* t2 : t2Nodes)
			{
				if (t1->dice(t1, t2, resultMapping) > minDice)
				{
					resultMapping.push_back(std::pair<Tree*, Tree*>(t1, t2));
					std::vector<Tree*> t1Descs = t1->getDescendants();
					std::vector<Tree*> t2Descs = t2->getDescendants();
					if (Util::max(t1Descs.size(), t2Descs.size()) < maxSize)
					{

					}
				}
			}
		}
	}
}
