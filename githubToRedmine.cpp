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
    {"    - ", "*** "},
    {"# ", "h1. "},
    {"## ", "h2. "},
    {"### ", "h3. "}
};

std::unordered_map<std::string, std::string>::iterator iter = g2rMap.begin();

/*
 * @author: Kyle Kwanghyun Jung
 * @notes: 
 * (1) \033[ starts the ANSI color code. 
 * (2) Put numbers separated by ;, which represents color or effects.
 * (3) Finish with m. 
 */

// 1 means bold, 31 means red
std::string log_red_bold_begin = "\033[1;31m";
// 0 means reset.
std::string log_end = "\033[0m";

/*
 * @returns : returns a boolean value representing that there has been at least 
 * one find-and-replace operation.
 */
bool findAndReplaceStr(std::string& rInput, 
        const std::string& from, 
        const std::string& to)
{
    std::string::size_type pos = 0;
    std::string::size_type offset = 0;
    bool bResult(false);

    while((pos = rInput.find(from, offset)) != std::string::npos) 
    {
        std::cout << "Found a github grammar : " << from << "\n" 
            << "Replacing it with the corresponding redmine grammar : " 
            << to << "\n" << std::endl;

        rInput.replace(rInput.begin() + pos, 
                rInput.begin() + pos + from.size(), 
                to);

        offset = pos + to.size();

        bResult = true;
    }

    return bResult;
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Argument Error. " 
            << "Example : ./g2r.out fileName.txt"
            << std::endl;

        return 0;
    }

    std::string file_in = argv[1];
    std::string::size_type commaPos = file_in.find_last_of(".");
    std::string file_in_noExt = file_in.substr(0, commaPos);
    std::string ext = file_in.substr(commaPos + 1);
    std::string file_out = file_in_noExt + "_out." + ext;

    std::filebuf fb_out;

    std::string readLine;

    int lineNo = 0;

    std::cout << "\n\n\n";

    std::cout << log_red_bold_begin << "===== Opening File : " << file_in << 
        " =====\n" << std::endl << log_end;

    std::ifstream inStream(file_in, std::ios::in);
    if (inStream.is_open())
    {
        std::ofstream outStream(file_out);

        while (getline(inStream, readLine))
        {
            std::cout << "Reading line : " << lineNo << "\n" <<
                readLine << "\n" << std::endl;

            for ( ; iter != g2rMap.end() ; ++iter)
            {
                if (findAndReplaceStr(readLine, iter->first, iter->second))
                {
                    // Writing to Out File
                    outStream << readLine;
                }
            }

            // Reading a single line done. Reset converter map iterator
            ++lineNo;
            iter = g2rMap.begin();
        }

        inStream.close();
        outStream.close();
    }
    else
    {
        std::cout << "Error occurred while opening the file : "
            << file_in
            << ". Check the path and try running again."
            << std::endl;
    }
}  
