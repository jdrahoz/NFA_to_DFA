
// --------------------------------------------------- //
// julia drahozal 2441134
// eecs 665
// assignment 1: nfa2dfa
//
// dfa.h
// header file for dfa class
// --------------------------------------------------- //


// includes
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#ifndef DFA_H
#define DFA_H


// --------------------------------------------------- //
// nfa class declaration
// --------------------------------------------------- //


class DFA
{
	public:

		// member variables
		vector <vector <int> > m_states;
		int m_initial_state;
		vector <int> m_final_states;
		int m_num_states;
		vector <char> m_input_symbols;
		int m_num_input_symbols;
		vector <int> m_marked_states;
		vector <vector < vector <int> > > m_transition_table;	// tt[state][input][transition]

		// -------------------------------- //
		// constructor & destructor
		// -------------------------------- //

		DFA (vector <char> input_symbols);
		~DFA ();

		// -------------------------------- //
		// getters & setters
		// -------------------------------- //

		// return set of states
		vector <vector <int> > getStates ();

		// return number of states
		int getNumStates ();

		// return set of all inputs symbols
		vector <char> getInputSymbols ();

		// return number of input symbols
		int getNumInputSymbols ();

		// -------------------------------- //
		// algorithm methods
		// -------------------------------- //

		// update all member variables to include new state
		void addState (vector <int> nfa_states);

		// update transition table to include new transition
		void addTransition (int state, int input_symbol_num, vector <int> states);

		// update marked array
		void markState (int state);

		// update set of final states
		void findFinalStates (vector <int> nfa_final_states);

		// -------------------------------- //
		// helper methods
		// -------------------------------- //

		// return if there are unmarked states or not
		bool unmarkedStatesLeft ();

		// return index of next unmarked state
		int getNextUnmarkedState ();

		// return if state already exists
		bool stateAlreadyExists (vector <int> state);

		// return index of state
		int getStateNum (vector <int> state);

		// -------------------------------- //
		// printing methods
		// -------------------------------- //

		// print info and transition table
		void prettyPrint ();

	private:

		// return string with vector formatted for printing
		string formatVector (vector <int> vec);
};

#endif
