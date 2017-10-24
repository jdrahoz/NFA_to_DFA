
// --------------------------------------------------- //
// julia drahozal 2441134
// eecs 665
// assignment 1: nfa2dfa
//
// nfa.h
// header file for nfa class
// --------------------------------------------------- //


// includes
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#ifndef NFA_H
#define NFA_H


// --------------------------------------------------- //
// nfa class declaration
// --------------------------------------------------- //


class NFA
{
	public:

		// member variables
		int m_initial_state;
		vector <int> m_final_states;
		int m_num_states;
		vector <char> m_input_symbols;
		int m_num_input_symbols;
		vector <vector < vector <int> > > m_transition_table;	// tt[state][input][transition]

		// -------------------------------- //
		// constructor & destructor
		// -------------------------------- //

		NFA ();
		~NFA ();

		// -------------------------------- //
		// getters & setters
		// -------------------------------- //

		// return initial state
		int getInitialState ();

		// return set of final states
		vector <int> getFinalStates ();

		// return set of all inputs symbols
		vector <char> getInputSymbols ();

		// return number of input symbols
		int getNumInputSymbols ();

		// return transition table
		vector <vector <vector <int> > > getTransitionTable ();

	private:

		// -------------------------------- //
		// parsing methods
		// -------------------------------- //

		// parse initial state from input
		int parseInitialState ();

		// parse set of final states from input
		vector <int> parseFinalStates ();

		// parse number of states from input
		int parseNumStates ();

		// parse set of all input symbols
		vector <char>  parseInputSymbols ();

		// parse transition table from input
		vector <vector <vector <int> > > parseTransitionTable ();
};

#endif
