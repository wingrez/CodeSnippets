/*************************************************
Function: LTrim
Description: 删除字符串中的前导字符
Input: 字符串str，前导字符ch
Output: 
Return: 删除前导字符后的字符串
Others:
*************************************************/
string LTrim(const string &str, char ch)
{
    int i = 0;
    while (i < str.size() && str[i] == ch) {
        i++;
    }
    return str.substr(i);
}

/*************************************************
Function: RTrim
Description: 删除字符串中的后导字符
Input: 字符串str，后导字符ch
Output: 
Return: 删除后导字符后的字符串
Others:
*************************************************/
string RTrim(const string &str, char ch)
{
    int i = str.size() - 1;
    while (i >= 0 && str[i] == ch) {
        i--;
    }
    return str.substr(0, i + 1);
}


/*************************************************
Function: Trim
Description: 删除字符串中的前导字符和后导字符
Input: 字符串str，前导字符和后导字符ch
Output: 
Return: 删除前导和后导字符后的字符串
Others:
*************************************************/
string Trim(const string &str, char ch)
{
    return LTrim(RTrim(str, ch), ch);
}