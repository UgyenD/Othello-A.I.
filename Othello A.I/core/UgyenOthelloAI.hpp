// UgyenOthelloAI.hpp

#ifndef UGYENOTHELLOAI_HPP
#define UGYENOTHELLOAI_HPP

#include "OthelloAI.hpp"

namespace udorji
	{
	class UgyenOthelloAI : public OthelloAI
		{
		public:
			virtual std::pair<int, int> chooseMove (const OthelloGameState& state);
			std::vector<std::pair<int,int>> validMoves(std::unique_ptr<OthelloGameState>& state);
			int eval(std::unique_ptr<OthelloGameState>& state);
			int search(std::unique_ptr<OthelloGameState>& state, int depth, OthelloCell turn);

		};
	}


#endif //UgyenOTHELLOAI_HPP