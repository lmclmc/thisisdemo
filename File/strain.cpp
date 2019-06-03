#include "strain.h"
#include <string>
#include <string.h>
#include <memory>
#include <map>
#include <list>
#include <iostream>

strain::strain()
{

}

std::string strain::getFileName()
{
    return "D://yingbian.txt";
}

void strain::readFileEvent(std::string &str)
{
    TT a;
    ::memset(&a, 0, sizeof(TT));
    fTime t = getDate(str);
    ::memcpy(&a.t, &t, sizeof(fTime));

    int tmp = 0;
    while (a.value = getDouble(str)){
        a.id = tmp;
        tmp ++;
        pushBack(a);
    }
}

bool strain::writeFileEvent(std::string &str)
{
    TMap::iterator iterMap;
    TList::iterator iterList;
    char tmp[512];
    str.clear();
    std::map<int, std::shared_ptr<std::list<TT>>> tmpMapT;
//tmpList.t.sec+tmpList.t.min*60+tmpList.t.sec*3600+tmpList.t.day*86400, std::make_shared<std::list<TT>>(l)
    std::list<TT> l;
    int tmpTime;
    for (auto tmpMap : getData()){
        for (auto tmpList : tmpMap.second){
            tmpTime = tmpList.t.sec+tmpList.t.min*60+tmpList.t.sec*3600+tmpList.t.day*86400;
            if (tmpMapT.find(tmpTime) == tmpMapT.end()){
                tmpMapT.insert(std::pair<int, std::shared_ptr<std::list<TT>>>(tmpTime, std::make_shared<std::list<TT>>(l)));
                tmpMapT.find(tmpTime)->second.get()->emplace_back(tmpList);
            } else {
                tmpMapT.find(tmpTime)->second.get()->emplace_back(tmpList);
            }
        }
    }
    ::memset(tmp, 0, sizeof(tmp));
    std::list<TT>::iterator iter;
    for (auto tmpMap : tmpMapT){
        ::sprintf(tmp, "%d/%d/%d %d:%d:%d  ", tmpMap.second.get()->begin()->t.year, tmpMap.second.get()->begin()->t.month,
                  tmpMap.second.get()->begin()->t.day, tmpMap.second.get()->begin()->t.hour, tmpMap.second.get()->begin()->t.min, tmpMap.second.get()->begin()->t.sec);
        str.insert(str.size(), tmp);
        for (iter = tmpMap.second.get()->begin(); iter != tmpMap.second.get()->end(); iter++){
            ::memset(tmp, 0, sizeof(tmp));
            ::sprintf(tmp, "%lf  ", iter->value);
            str.insert(str.size(), tmp);
        }
        ::memset(tmp, 0, sizeof(tmp));
        tmp[0] = '\n';
        str.insert(str.size(), tmp);
    }
}
