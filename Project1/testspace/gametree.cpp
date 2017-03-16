#include "gametree.h"

//remove this later
#include <queue>
#include <iostream>
using namespace std;

GameTree::GameTree()
{

}

GameTree::GameTree(Board* board, bool player, int plyDepth)
{
	if (plyDepth > 5) plyDepth = 5;	//limit max plydepth!
	this->root = new State(*board, player);
	this->player = player;
	maxDepth = plyDepth;
}

 GameTree::~GameTree()
{
	destroy(root);
}

 void GameTree::destroy(State * root)
{
	if (!(root == NULL))
	{
		for (int i = 0; i < root->children.size(); i++)
		{
			destroy(root->children[i]);
		}
		delete root;	
	}
}

Move GameTree::makeBestMove(GUIBoard* board)
{
	//get move
	int best = alphaBetaPruning(root, 0);
		//get index
	int i;
	for (i = 0; i < root->children.size(); i++)
	{
		if (best == root->children[i]) break;
	}
	vector<Move* >* moves = getPossibleMoves(root);
	Move* move = moves[i];
	
	//apply move
	bool clockwise;	
        if (player == board->PLAYER1)
        {
            if (move->direction == 1)
                clockwise = state->CLOCKWISE;
            else clockwise = state->ANTICLOCKWISE;
        }
        else
        {
            if (move->direction == 1)
                clockwise = state->ANTICLOCKWISE;
            else clockwise = state->CLOCKWISE;
        }
	
	if (board->isNamua())
	{
		if (board->isTakasa())
		{
			board->enterTakasaSeed(move->row, move->col, clockwise);
		}
		else
		{
			board->enterSeed(move->row, move->col, clockwise);			
		}
	}
	
	//deallocate memory
	for (int i = 0; i < moves->size(); i++)
		delete (*moves)[i];
	delete moves;
	//@todo mtaji moves
	cout << "alphabeta result is " << alphaBetaPruning(root, 0) << endl;
}

vector<Move*>* GameTree::getPossibleMoves(State* state)
{
///////////////////////////////
//cout << "in getPosMoves: start " << endl;	
	vector<Move*>* moves= new vector<Move*>;
	int row, col;
	
	if (state->getPlayer() == state->PLAYER1) row = 2;
	else row = 1;
	
	if (state->isNamua())
	{
///////////////////////////////
//cout << "in getPosMoves: isNamua " << endl;			
		for (col = 0; col < 8; col++)
		{
			if (!state->isEmpty(row, col))
			{

				if (state->isTakasa())					
				{
					Move* move = new Move();
					move->row = row;
					move->col = col;					
					move->direction = 1;//right
					moves->push_back(move);
					Move* move2 = new Move();
					move2->row = row;
					move2->col = col;					
					move2->direction = 0;//left
					moves->push_back(move2);															
				}
				else
				{
					int oppRow;
					if (state->getPlayer() == state->PLAYER1)
						oppRow = 1;
					else oppRow = 2;
					
					if (!state->isEmpty(oppRow, col))
					{
						Move* move = new Move();
						move->row = row;
						move->col = col;
						if (col < 2 && !state->isTakasa())
						{
							move->direction = 1;//right
							moves->push_back(move);
						}
						else if (col > 5 && !state->isTakasa())
						{
							move->direction = 0;//left
							moves->push_back(move);					
						}
						else
						{
							move->direction = 1;//right
							moves->push_back(move);
							Move* move2 = new Move();
							move2->row = row;
							move2->col = col;					
							move2->direction = 0;//left
							moves->push_back(move2);										
						}
					}
				}
			}
		}	
	}
	//@todo mtaji moves
///////////////////////////////
//cout << "in getPosMoves: end " << endl;		
	return moves;
}

State* GameTree::getNextState(State* state, Move* move)
{
	State* newState = new State(static_cast<Board>(*state), !state->getPlayer());
	newState->isMaxNode = !state->isMaxNode;
        bool clockwise;
	
        if (state->getPlayer() == state->PLAYER1)
        {
            if (move->direction == 1)
                clockwise = state->CLOCKWISE;
            else clockwise = state->ANTICLOCKWISE;
        }
        else
        {
            if (move->direction == 1)
                clockwise = state->ANTICLOCKWISE;
            else clockwise = state->CLOCKWISE;
        }
	
	if (state->isNamua())
	{
		if (state->isTakasa())
		{
			newState->enterTakasaSeed(move->row, move->col, clockwise);
		}
		else
		{
			newState->enterSeed(move->row, move->col, clockwise);			
		}
	}
	//@todo mtaji moves
	return newState;
}

int GameTree::alphaBetaPruning(State* cur, int curDepth)
{
///////////////////////////////
//cout << "in abpruning: start: depth " << curDepth << endl;
	for (int i = 0; i < curDepth; i++)
	cout << "\t\t";
	cout << "depth " << curDepth << ": ";
	cur->print();
//////////////////////////////	
	if (curDepth == maxDepth)
	{
		///////////////////////////////
//cout << "in abpruning: (curDepth == maxDepth) " << curDepth << endl;
		cur->evaluation = cur->evaluate(player);
		return cur->evaluate(player);
	}
	
	//initialize alphaBeta value

///////////////////////////////
//cout << "in abpruning: before isMaxNode" << endl;			
	
	if (cur->isMaxNode) cur->evaluation = -101;
	else cur->evaluation = 101;

///////////////////////////////
//cout << "in abpruning: before isMaxNode" << endl;				
	
	//generate list of moves
	vector<Move* >* moves = getPossibleMoves(cur);
	int tmp;
	bool prune;
///////////////////////////////
//cout << "in abpruning: just made all children " << curDepth << endl;	
	
	//for every move
	for (int i = 0; i < moves->size(); i++)
	{
		//add to children = get Next State(curstate, move[i])
		cur->children.push_back(getNextState(cur, (*moves)[i]));
		
		//add current alphaBeta value to stack
		if (cur->isMaxNode) 
		{
			alphaValues.push_back(cur->evaluation);
///////////////////////////////
//cout << "\tin abpruning: push to alpha: " << cur->evaluation<< endl;								
		}
		else 
		{
			betaValues.push_back(cur->evaluation);
///////////////////////////////
//cout << "\tin abpruning: push to alpha: " << cur->evaluation<< endl;											
		}
		
		//tmp = alphaBetPruning(children.at(i));
		tmp = alphaBetaPruning(cur->children[i], curDepth + 1);//////////////////////////////////////////////////////////////////recursive call over here
		
		//cur.alphaBeta value = max or min (tmp, cur.alphaBetaValue)
		if (cur->isMaxNode)
		{
			//find maximum of two values
			if (tmp > cur->evaluation) cur->evaluation = tmp;		
			//compare tmp to previous Beta values
			prune = compareBeta(tmp);
		}
		else
		{
			//find minimum of two values
			if (tmp < cur->evaluation) cur->evaluation = tmp;
			//compare tmp to previous alpha values
			prune = compareAlpha(tmp);
		}	
		
		//remove current alphaBeta value from stack
		if (cur->isMaxNode) 
		{
			alphaValues.pop_back();	
///////////////////////////////
//cout << "\tin abpruning: pop from alpha: " << cur->evaluation<< endl;											
		}
		else 
		{
			betaValues.pop_back();
///////////////////////////////
//cout << "\tin abpruning: pop from alpha: " << cur->evaluation<< endl;											
		}
		
		//if (prune) delete moves and return temp
		if (prune)
		{
			for (int i = 0; i < moves->size(); i++)
				delete (*moves)[i];
			delete moves;
///////////////////////////////
cout << "in abpruning: decidet to prune because of " << tmp << endl;			
			return tmp;
		}
	}
	//delete moves
	for (int i = 0; i < moves->size(); i++)
		delete (*moves)[i];
	delete moves;
	
	//return cur.aplhaBetaValue
///////////////////////////////
//cout << "in abpruning: end depth " << curDepth << endl;	
	return cur->evaluation;
}

bool GameTree::compareAlpha(int x)
{
	//	"Search is discontinued below any Min node
	//	having a Beta value less than or equal to the Alpha
	//	value of any of its Max node ancestors"
	for (int i = 0; i < alphaValues.size(); i++)
		if (x <= alphaValues[i]) return true;
	return false;
}

bool GameTree::compareBeta(int x)
{
	// 	Search is discontinued below any Max node
	// 	having an Alpha value greater than or equal to
	//	the Beta value of any of its Min node ancestors
	for (int i = 0; i < betaValues.size(); i++)
		if (x >= betaValues[i]) return true;
	return false;	
}

void GameTree::print()
{
	State* cur = root;
	queue<State*> q;
	int stop = 1, count = 1;
	if (cur != NULL)
	{
		q.push(cur);
		while (!q.empty())
		{
			cur = q.front();
			q.pop();
			cout << cur->evaluation;
			cur->print();
			for (int i = 0; i < cur->children.size(); i++)
				q.push(cur->children[i]);
			if (stop == count)
			{
				stop = q.size();
				cout << endl << "------------------------------------------"<< endl;
				count = 0;
			}
			count++;
		}
	}
}
