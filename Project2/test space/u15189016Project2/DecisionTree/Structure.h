/**
*	@file Structure.h
*	@class Structure
*
*	@brief Converts spec file into accessible datastructure
*
*	@section Description
*	Makes the details of the problem easily accessible to other modules
*
*	@section License
*	Copyright belongs to Juan du Preez (15189016)
*
*/

#ifndef STRUCTURE
#define STRUCTURE

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class Structure
{
	private:
		string className;			/**< Overall name for the list of classes*/
		vector<string> classValues;	/**< The list of actual classes*/
		int numClassValues;		/**< The number of actual classes*/
	
		vector<string> attributeList;	/**< List of all possible attributes*/
		vector<vector<string> > attributeValueMatrix; /**< Matrix of attribute values corresponding to attributeList*/
		int numAttributes; 			/**< The number of different attributes*/

	public:
		Structure(string specFile); 	/**< Constructor that disects the file and creates the object*/
		
		string getClassName(); 
		int getNumClassValues(); 
		int getNumAttributes();
		int getNumAttributeValues(string attribute);
	
		vector<string> getClassValues();
		vector<string> getAttributes();
		vector<string> getAttributeValues(string attribute);
		int getIndex(string attribute);
		string getAttribute(int index);
	
		string toString();			/**< For displaying purposes*/
	
};

#endif