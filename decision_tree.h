#ifndef DECISION_TREE_H__
#define DECISION_TREE_H__ 1

#include "board.h"
#include <vector>
#include <cmath>

namespace tictactoe
{
	namespace engine
	{
		class decision_tree
		{
		public:
        //data
			board m_board;
			std::vector<decision_tree*> childs;
			int m_priority;
        //func
		// initialize the decision tree
			decision_tree(board b) : m_board(b),m_priority(0) {}

			int initialise(MARK turn, int depth)
			{
				if (m_board.check() != EMPTY_SPACE)
				{
					m_priority = int(((turn == COMPUTER) ? -1 : 1) * std::pow(depth, POWER));
					return m_priority;
				}
				if (depth == 0 || !m_board.has_empty())
					return 0;

				for (int i = 0; i < TOTAL_CELLS; i++)
				{
					if (m_board[i] == EMPTY_SPACE)
					{
						m_board[i] = turn;
						childs.push_back(new decision_tree(m_board));
						m_priority += childs[childs.size() - 1]->initialise((turn == COMPUTER) ? PLAYER_1 : COMPUTER, depth - 1);
						m_board[i] = EMPTY_SPACE;
					}
				}

				return m_priority;
			}

		// delete the decision tree
			~decision_tree()
			{
				for (auto ptr : childs)
					delete ptr;
			}
		};
	}
}


#endif // DECISION_TREE_H__