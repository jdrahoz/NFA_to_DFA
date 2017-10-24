
// --------------------------------------------------- //
// julia drahozal 2441134
// eecs 665
// assignment 1: nfa2dfa
//
// main.cpp
// file to run nfa -> dfa conversion
// --------------------------------------------------- //


// includes
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include "nfa.h"
#include "dfa.h"

using namespace std;

// function declarations
void nfa2dfa (NFA* nfa, DFA* dfa);
vector <int> eclosure (vector <int> states, NFA* nfa);
vector <int> move (vector <int> states, char input_symbol, NFA* nfa);
string formatVector (vector <int> vec);


// --------------------------------------------------- //
// main function
// --------------------------------------------------- //


// run nfa to dfa conversion
int main (int argc, char* argv[])
{
	// initialize nfa
	NFA* nfa = new NFA ();

	// initialize dfa
	vector <char> dfa_input_symbols = nfa -> getInputSymbols ();
	dfa_input_symbols.pop_back ();
	DFA* dfa = new DFA (dfa_input_symbols);

	// run algorithm
	nfa2dfa (nfa, dfa);

	// print result
	dfa -> prettyPrint ();

	// delete
	delete dfa;
	delete nfa;
}


// --------------------------------------------------- //
// algorithm methods
// --------------------------------------------------- //


// convert nfa to dfa
void nfa2dfa (NFA* nfa, DFA* dfa)
{
	// initial state
	vector <int> initial_state;
	initial_state.push_back (nfa -> getInitialState ());
	dfa -> addState (eclosure (initial_state, nfa));
	cout << "E-closure(I0) = " << formatVector (eclosure (initial_state, nfa)) << " = " << dfa -> getNumStates () + 1 << "\n";

	// run through all unmarked states
	while (dfa -> unmarkedStatesLeft ())
	{
		// mark state
		int unmarked_state_index = dfa -> getNextUnmarkedState ();
		vector <int> unmarked_state = dfa -> getStates ()[unmarked_state_index];
		cout << "\nMark " << unmarked_state_index + 1 << "\n";
		dfa -> markState (unmarked_state_index);

		// run through all inputs
		for (unsigned int input_num = 0; input_num < dfa -> getInputSymbols ().size (); input_num++)
		{
			char input_symbol = dfa -> getInputSymbols ()[input_num];

			// calculate move & e-closure
			vector <int> move_states = move (unmarked_state, input_symbol, nfa);
			vector <int> new_state = eclosure (move_states, nfa);

			// no move on input
			if (new_state.size () == 0)
			{
				continue;
			}

			// print move & e-closure
			cout << formatVector (unmarked_state) << " --" << input_symbol << "--> " << formatVector (move_states) << "\n";
			cout << "E-closure" << formatVector (move_states) << " = " << formatVector (new_state);

			// add new dfa state
			int state_num;
			if (!(dfa -> stateAlreadyExists (new_state)))
			{
				dfa -> addState (new_state);
				state_num = dfa -> getStates ().size ();
			}
			else
			{
				state_num = dfa -> getStateNum (new_state);
			}
			cout << " = " << state_num << "\n";

			// add transition
			vector <int> transition;
			transition.push_back (state_num);
			dfa -> addTransition (unmarked_state_index, input_num, transition);
		}
	}
	dfa -> findFinalStates (nfa -> getFinalStates ());
}

// calculate e-closure of set of states
vector <int> eclosure (vector <int> states, NFA* nfa)
{
	// get variables
	vector <vector <vector <int> > > transition_table = nfa -> getTransitionTable ();
	int num_inputs = nfa -> getNumInputSymbols ();

	// initialize
	vector <int> eclosure = states;
	stack <int> stack;
	for (int state : states)
	{
		stack.push (state);
	}

	// run algorithm
	while (!stack.empty ())
	{
		// get top element
		int state = stack.top ();
		stack.pop ();

		// check all edges
		vector <int> transitions = transition_table[state - 1][num_inputs - 1];
		for (int transition : transitions)
		{
			// search e-closure set
			bool in_eclosure = false;
			for (int x : eclosure)
			{
				if (x == transition)
				{
					in_eclosure = true;
				}
			}
			if (!in_eclosure)
			{
				// add new state
				eclosure.push_back (transition);
				stack.push (transition);
			}
		}
	}
	sort (eclosure.begin (), eclosure.end ());
	return eclosure;
}

// calculate move from set of states on input symbol
vector <int> move (vector <int> states, char input_symbol, NFA* nfa)
{
	// get variables
	vector <vector <vector <int> > > transition_table = nfa -> getTransitionTable ();
	vector <char> input_symbols = nfa -> getInputSymbols ();
	int input_symbol_index = 0;
	for (int i = 0; i < nfa -> getNumInputSymbols () - 1; i++)
	{
		if (input_symbols[i] == input_symbol)
		{
			input_symbol_index = i;
		}
	}

	// initialize
	vector <int> move_set;

	// run algorithm
	for (int t : states)
	{
		// check all edges
		vector <int> transitions = transition_table[t-1][input_symbol_index];
		for (int transition : transitions)
		{
			// search e-closure set
			int in_eclosure = false;
			for (int x : move_set)
			{
				if (x == transition)
				{
					in_eclosure = true;
				}
			}
			if (!in_eclosure)
			{
				// add new state
				move_set.push_back (transition);
				vector <int> transition_set;
				transition_set.push_back (transition);
			}
		}
	}
	sort (move_set.begin (), move_set.end ());
	return move_set;
}


// --------------------------------------------------- //
// printing methods
// --------------------------------------------------- //


// return string with vector formatted for printing
string formatVector (vector <int> vec)
{
	string str;
	str += "{";
	unsigned int count = 1;
	for (int x : vec)
	{
		str += to_string (x);
		if (count < vec.size ())
		{
			str += ',';
		}
		count++;
	}
	str += "}";
	return str;
}
