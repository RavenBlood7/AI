#include <iostream>
#include <fstream>

using namespace std;


int main(int argc, char *argv[])
{
	ifstream infile(argv[1]);
	ofstream outfile("out.data");
	string line;
	
	if (infile.is_open())
	{
		while (getline(infile, line))
		{
///////////////////
cout << "line is: " << line << endl;			
			int n = line.find_first_of(",");
			while (n != string::npos)
			{
				line.replace(n, 1, " ");
				n = line.find_first_of(",");
			}
			outfile << line << endl;
		}
	}
	
	infile.close();
	outfile.close();

	return 0;
}
