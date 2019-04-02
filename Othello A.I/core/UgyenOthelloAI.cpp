//UgyenOthelloAI.cpp

#ifndef UGYENOTHELLOAI_CPP
#define UGYENOTHELLOAI_CPP

#include <ics46/factory/DynamicFactory.hpp>
#include "UgyenOthelloAI.hpp"
#include "OthelloGameState.hpp"
#include "OthelloCell.hpp"
#include <vector>
#include <iostream>

ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI, udorji::UgyenOthelloAI, "Ugyen's Othello AI (Required)");



//Returns a pair containing the most optimal postion for Ugyen's Othello AI. The most optimal move is chosen through  
//depth-first recursion in which the pseudo game tree is traversed 3 layers deep. 
std::pair<int, int> udorji::UgyenOthelloAI::chooseMove(const OthelloGameState& state)
   {
   		std::cout<< "chooseMove was called!" <<std::endl;
   		int depth = 3;
   		int moveIndex = 0;
   		int bestScore = -999;
   		int chosenScore;
   		OthelloCell turn = OthelloCell::white;
   		std::unique_ptr<OthelloGameState> cpy = state.clone();
   		std::vector<std::pair<int,int>> paths = validMoves(cpy);
   		int size = paths.size();
   		
   		for(int i = 0; i < size; i++)
   		{
   			std::unique_ptr<OthelloGameState> cpySecond = state.clone();
   			cpySecond->makeMove(paths[i].first, paths[i].second);

   			if (cpySecond->isBlackTurn())
   			{
   				turn = OthelloCell::black;
   			}
   			
   			chosenScore = search(cpySecond, depth, turn);
   			std::cout << "size: " << size << std::endl;
   			std::cout << "chosenScore: "<< chosenScore <<" bestScore: "<< bestScore << std::endl;
   			
   			if(chosenScore > bestScore)
   			{
   				moveIndex = i;
   				std::cout << moveIndex << std::endl;
   				bestScore = chosenScore;
   			}
   		}

   		std::cout<< "Move picked: "<< moveIndex << " Paths size: "<< size<<std::endl;
   		return paths[moveIndex];
   }



//Returns a vector conataining pairs which are considered valid moves for the current player whoose turn it is. 
//It is used to determine the max and mins of slected moves. 
std::vector<std::pair<int,int>> udorji::UgyenOthelloAI::validMoves(std::unique_ptr<OthelloGameState>& state)
{
	int w = state->board().width()-1;
	int h = state->board().height()-1;


	std::vector<std::pair<int,int>> moves;
	for(int x = w; x >= 0; x--)
	{
		for(int y = h; y >= 0; y--)
		{
			if(state->isValidMove(x,y))
			{
				moves.push_back(std::pair<int,int>(x,y));
				std::cout<< "(" << x << "," << y << ")" <<std::endl;
			}
		}
	} 	 
	
	return moves;
}



//Returns an evaluation of the current game state.
int udorji::UgyenOthelloAI::eval(std::unique_ptr<OthelloGameState>& state)
{	
	if (state->isBlackTurn())
	{
		return state->blackScore() - state->whiteScore();
	}

	else
	{
		return state->whiteScore() - state->blackScore();
	}
}



//Performs depth-first recursion to traverse a pseudo game tree for the most optimal game evaluation and ulitmately 
//move.
int udorji::UgyenOthelloAI::search(std::unique_ptr<OthelloGameState>& state, int depth, OthelloCell turn)
{
	int myScore = -100;
	int otherScore = 100;
	int currentScore;
	std::vector<std::pair<int,int>> paths = validMoves(state);
	int size = paths.size();
	
	if (size == 0 || depth == 0)
	{
		return eval(state);

	}

	else
	{
		if ((state->isBlackTurn() && OthelloCell::black == turn) || (state->isWhiteTurn() && OthelloCell::white == turn))
		{
			for (int i = 0; i < size; i++)
			{
				std::unique_ptr<OthelloGameState> cpy = state->clone();
				cpy->makeMove(paths[i].first, paths[i].second);
				currentScore = search(cpy, depth-1, turn);

				if(currentScore > myScore)
				{
					myScore = currentScore;
				}

			}
			return myScore;
		}
		
		else
		{
			for (int i = 0; i < size; i++)
			{
				std::unique_ptr<OthelloGameState> cpy = state->clone();
				cpy->makeMove(paths[i].first, paths[i].second);
				currentScore = search(cpy, depth-1, turn);
				if(currentScore < otherScore)
				{
					otherScore = currentScore;
				}

			return otherScore;

			}
		}	
	}			
}





#endif //UGYENOTHELLOAI_CPP