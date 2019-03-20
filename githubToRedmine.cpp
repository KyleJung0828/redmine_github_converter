#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

// key = "from" string, which is github grammar.
// value = "to" string, which is redmine grammar.
std::unordered_map<std::string, std::string> g2rMap =
{
    {"- ", "* "},
    {"  - ", "** "},
    {"## ", "h2. "}
};

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Argument Error. " 
            << "Example : ./g2r.out fileName.txt"
            << std::endl;

        return 0;
    }

    std::string filePath = argv[1];
    std::filebuf fb;
    std::string readout;
    std::unordered_map<std::string, std::string>::iterator iter = g2rMap.begin();

    int lineNo = 0;

    if (fb.open (filePath,std::ios::in))
    {
        std::istream readFile(&fb);

        while (getline (readFile, readout))
        {
            std::cout << "Reading line : " << lineNo << "\n" <<
                readout << std::endl;

            for ( ; iter != g2rMap.end() ; ++iter)
            {
                if(readout.find(iter->first))
                {
                    std::cout << "Found string : " << iter->first << 
                        ". Replacing with : " << iter->second << std::endl;
                }
            }
            ++lineNo;
        }

        fb.close();

    }
    else
    {
        std::cout << "Error occurred while opening the file : "
            << filePath
            << ". Check the path and try running again."
            << std::endl;
    }
}  
