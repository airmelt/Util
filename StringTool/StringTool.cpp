#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace Util
{
// Returns a copy of the string, with leading and trailing whitespace omitted. 
string trim(const string& str)
{
    string::size_type left = str.find_first_not_of(' ');
    if (left == string::npos)
    {
        return str;
    }
    string::size_type right = str.find_last_not_of(' ');
    if (right != string::npos)
    {
        return str.substr(left, right - left + 1);
    }
    return str.substr(left);
}

// Splits this string around matches of the given separator
int split(const string& str, vector<string>& result, string separator = ",")
{
    if (str.empty())
    {
        return 0;
    }

    string temp;
    string::size_type pos_begin = str.find_first_not_of(separator);
    string::size_type comma_pos = 0;

    while (pos_begin != string::npos)
    {
        comma_pos = str.find(separator, pos_begin);
        if (comma_pos != string::npos)
        {
            temp = str.substr(pos_begin, comma_pos - pos_begin);
            pos_begin = comma_pos + separator.length();
        }
        else
        {
            temp = str.substr(pos_begin);
            pos_begin = comma_pos;
        }

        if (!temp.empty())
        {
            result.push_back(temp);
            /* string.clear()
               作用: 将字符串的内容清空，让源字符串成为一个空字符串（长度为0个字符）*/
            temp.clear();
        }
    }
    return 0;
}

}
