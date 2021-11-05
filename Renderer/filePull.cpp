#include "filePull.h"
namespace aie
{

	shader loadShader(const char* vertPath, const char* fragPath)
	{
		return makeShader(readShader(vertPath).c_str(), readShader(fragPath).c_str());
	}

	string readShader(const char* path)
	{
		string currentLine;
		string fileString;
		ifstream myFile(path);
		if (myFile.is_open())
		{
			while (getline(myFile, currentLine))
			{
				fileString.append(currentLine + '\n');
			}
			myFile.close();
		}
		else
		{
			cout << "you done goofed can't open the file!";
		}
		return fileString;

	}
}
