#include "fopt.h"

#include <iostream>
#include <fstream>
#include <string.h>

void F::init()
{
    std::ifstream file;
    std::string str;

    file.open(getFileName());
    if (file.is_open()){
        while (!file.eof()){
            std::getline(file, str);
            readFileEvent(str);
        }
    }
    file.close();
}

void F::flush()
{
    std::fstream file(getFileName(), std::ios::out | std::ios::trunc);
    std::string str;
    writeFileEvent(str);
    file << str;
    file.close();
}

std::string F::getFileName()
{
    return "";
}

void F::readFileEvent(std::string &)
{

}

bool F::writeFileEvent(std::string &)
{
    return false;
}

fTime F::getDate(std::string &str)
{
    fTime t;
    ::memset(&t, 0, sizeof(fTime));
    std::string tmpStr;
    typedef std::string::size_type ss;
    ss i = 0;
    int m = 0;
    while (str[i]){

        if (str[i] == '/'){
            if (m == 0){
                t.year = ::atoi(tmpStr.c_str());
                tmpStr.clear();
            } else {
                t.month = ::atoi(tmpStr.c_str());
                tmpStr.clear();
            }
            m++;
            i++;
            continue;
        }
        if (str[i] == ':'){
            if (m == 3){
                t.hour = ::atoi(tmpStr.c_str());
                tmpStr.clear();
            } else if (m == 4){
                t.min = ::atoi(tmpStr.c_str());
                tmpStr.clear();
            }
            m++;
            i++;
            continue;
        }
        if (str[i] < 48){
            if (m == 2){
                t.day = ::atoi(tmpStr.c_str());
                tmpStr.clear();
            } else if (m == 4){
                t.min = ::atoi(tmpStr.c_str());
                tmpStr.clear();
                str = str.substr(i, str.length());
                break;
            } else if (m == 5){
                t.sec = ::atoi(tmpStr.c_str());
                tmpStr.clear();
                str = str.substr(i, str.length());
                break;
            }
            i++;
            m++;
            continue;
        }
        tmpStr.push_back(str[i]);
        i++;
    }

    //printf("%ld, %d, %d, %d, %d\n", t.year, t.month, t.day, t.hour, t.min);
    return t;
}

double F::getDouble(std::string &str)
{
    std::string tmpStr;
    typedef std::string::size_type ss;
    ss i = 0;
    int m = 0;
    while (str[i]){
        if (str[i] == '\n'){
            return 0;
        }

        if (str[i] >= 45){
            tmpStr.push_back(str[i]);
            m = 1;
        } else {
            if (m == 1) break;
        }
        i++;
    }
    str = str.substr(i, str.length());
    return atof(tmpStr.c_str());
}

int F::getInt(std::string &str)
{
    std::string tmpStr;
    typedef std::string::size_type ss;
    ss i = 0;
    int m = 0;
    while (str[i]){
        if (str[i] > 45){
            tmpStr.push_back(str[i]);
            m = 1;
        } else {
            if (m == 1) break;
        }
        i++;
    }
    str = str.substr(i, str.length());
    return atoi(tmpStr.c_str());
}

std::string F::getStr(std::string &str)
{
    std::string tmpStr;
    typedef std::string::size_type ss;
    ss i = 0;
    int m = 0;
    while (str[i]){
        if (str[i] > 65){
            tmpStr.push_back(str[i]);
            m = 1;
        } else {
            if (m == 1) break;
        }
        i++;
    }
    return tmpStr;
}

void FOpt::pushBack(TT node)
{
    typename TMap::iterator iter = data.find(node.id);
    if (iter == data.end()){
        std::list<TT> l;
        l.emplace_back(node);
        data.insert(std::pair<int, std::list<TT>>(node.id, l));
    } else {
        iter->second.emplace_back(node);
    }
}

bool FOpt::getNodeIter(int Id, TList::iterator &iter)
{
    TMap::iterator iterMap;
    if ((iterMap = data.find(Id)) == data.end()){
        return false;
    }

    iter = iterMap->second.begin();
    return true;
}

bool FOpt::setNodeIter(int Id, int set, TList::iterator &iter)
{
    TMap::iterator iterMap;
    if ((iterMap = data.find(Id)) == data.end()){
        return false;
    }

    if (set){
        if (iter != iterMap->second.end()){
            iter++;
        } else {
            return false;
        }
    } else {
        if (iter != iterMap->second.begin()){
            iter--;
        } else {
            return false;
        }
    }

    return true;
}

