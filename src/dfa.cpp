
// --------------------------------------------------- //
// julia drahozal 2441134
// eecs 665
// assignment 1: nfa2dfa
//
// dfa.cpp
// implementation file for dfa class
// --------------------------------------------------- //


// includes
#include "dfa.h"


// --------------------------------------------------- //
// constructor & destructor
// --------------------------------------------------- //


DFA :: DFA (vector <char> input_symbols)
{
	m_input_symbols = input_symbols;
	m_num_input_symbols = m_input_symbols.size ();
}

DFA :: ~DFA () {}


// --------------------------------------------------- //
// getters & setters
// --------------------------------------------------- //


vector <vector <int> > DFA :: getStates ()
{
	return m_states;
}

int DFA :: getNumStates ()
{
	return m_num_states;
}

vector <char> DFA :: getInputSymbols ()
{
	return m_input_symbols;
}

int DFA :: getNumInputSymbols ()
{
	return m_num_input_symbols;
}


// --------------------------------------------------- //
// algorithm methods
// --------------------------------------------------- //


void DFA :: addState (vector <int> nfa_states)
{
	// set up initial state
	if (m_states.size () == 0)
	{
			m_initial_state = 1;
	}

	// add new state
	m_states.push_back (nfa_states);

	// add unmarked state
	m_marked_states.push_back (0);

	// add empty row to transition table
	vector <vector <int> > state;
	for (int i = 0; i < m_num_input_symbols; i++)
	{
		vector <int> trans;
		state.push_back (trans);
	}
	m_transition_table.push_back (state);
}

void DFA :: addTransition (int state, int input_symbol_num, vector <int> states)
{
	m_transition_table[state][input_symbol_num] = states;
}

void DFA :: markState (int state)
{
	m_marked_states[state] = 1;
}

void DFA :: findFinalStates (vector <int> nfa_final_states)
{
	// loop through all states
	int state_num = 1;
	for (vector <int> state : m_states)
	{
		for (int s : state)
		{
			for (int n : nfa_final_states)
			{
				// add to final states
				if (s == n)
				{
					m_final_states.push_back (state_num);
				}
			}
		}
		state_num++;
	}
	sort (m_final_states.begin (), m_final_states.end ());
	m_final_states.erase (unique (m_final_states.begin (), m_final_states.end ()), m_final_states.end ());
}


// --------------------------------------------------- //
// helper methods
// --------------------------------------------------- //


bool DFA :: unmarkedStatesLeft ()
{
	for (int m : m_marked_states)
	{
		if (m == 0)
		{
			return true;
		}
	}
	return false;
}

int DFA :: getNextUnmarkedState ()
{
	int index = 0;
	for (int m : m_marked_states)
	{
		if (m == 0)
		{
			return index;
		}
		index++;
	}
	return -1;
}

bool DFA :: stateAlreadyExists (vector <int> new_state)
{
	bool state_exists = false;

	// loop through all states
	for (vector <int> state : m_states)
	{
		bool in_state = true;
		int size = min (new_state.size (), state.size ());
		if (state.size () != new_state.size ())
		{
			in_state = false;
		}
		for (int i = 0; i < size; i++)
		{
			if (state[i] != new_state[i])
			{
				in_state = false;
			}
		}

		// state found
		if (in_state)
		{
			state_exists = true;
		}
	}
	return state_exists;
}

int DFA :: getStateNum (vector <int> searching_state)
{
	int state_num = 1;

	// loop through all states
	for (vector <int> state : m_states)
	{
		bool in_state = true;
		int size = min (searching_state.size (), state.size ());
		if (state.size () != searching_state.size ())
		{
			in_state = false;
		}
		for (int i = 0; i < size; i++)
		{
			if (state[i] != searching_state[i])
			{
				in_state = false;
			}
		}

		// state found
		if (in_state)
		{
			return state_num;
		}
		state_num++;
	}
	return -1;
}


// --------------------------------------------------- //
// printing methods
// --------------------------------------------------- //


void DFA :: prettyPrint ()
{
	// print general info
	cout << "\nInitial State: " << "{" << m_initial_state << "}\n";
	cout << "Final States: " << formatVector (m_final_states) << "\n";
	cout << "State\t";
	for (char s : m_input_symbols)
	{
		cout << s << "\t";
	}
	cout << "\n";

	// print transition table
	int state_num = 1;
	for (vector <vector <int> > state : m_transition_table)
	{
		cout << state_num << "\t";
		for (vector <int>  transitions : state)
		{
			cout << formatVector (transitions) << "\t" ;
		}
		cout << "\n";
		state_num++;
	}
}

string DFA :: formatVector (vector <int> vec)
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
