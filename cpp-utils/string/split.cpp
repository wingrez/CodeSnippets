/*************************************************
Function: Split
Description: 分割字符串
Input: 字符串str，分割符delim
Output: 分割后的字符串数组tokens
Return: 无
Others:
*************************************************/
void Split(const string &s, vector<string> &tokens, const string &delim = " ") {
    string::size_type lastPos = s.find_first_not_of(delim, 0);
    string::size_type pos = s.find_first_of(delim, lastPos);
    while (string::npos != pos || string::npos != lastPos) {
        tokens.push_back(s.substr(lastPos, pos - lastPos));
        lastPos = s.find_first_not_of(delim, pos);
        pos = s.find_first_of(delim, lastPos);
    }
}