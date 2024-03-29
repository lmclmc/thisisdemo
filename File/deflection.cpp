#include "deflection.h"
#include <string>
#include <string.h>

Deflection::Deflection()
{

}

std::string Deflection::getFileName()
{
    return "D://naodu.txt";
}

void Deflection::readFileEvent(std::string &str)
{
    TT a;
    ::memset(&a, 0, sizeof(TT));
    fTime t = getDate(str);
    ::memcpy(&a.t, &t, sizeof(fTime));
    a.id = getInt(str);
    a.value = getDouble(str);
    if (a.value < 0.01) return;
    std::string s= getStr(str);
    ::memcpy(a.unit, s.c_str(), strlen(s.c_str()));

    printf("%d\n", a.id);
    pushBack(a);
}

bool Deflection::writeFileEvent(std::string &str)
{
    TMap::iterator iterMap;
    TList::iterator iterList;
    char tmp[128];
    str.clear();
    for (auto tmpMap : getData()){
        for (auto tmpList : tmpMap.second){
            ::memset(tmp, 0, sizeof(tmp));
            ::sprintf(tmp, "%lld/%lld/%lld %lld:%lld %d %lf %s\n", tmpList.t.year, tmpList.t.month,
                      tmpList.t.day, tmpList.t.hour, tmpList.t.min, tmpList.id, tmpList.value, tmpList.unit);
            str.insert(str.size(), tmp);
        }
    }
    return false;
}

