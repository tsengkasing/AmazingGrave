#pragma once

#include "cocos2d.h"
#include <map>
#include <string>

using std::map;
using std::string;

class TextReader
{
public:
    static TextReader* getInstance();

    void readFromJson();

    const char* getName(int tag) const;

    const char* getContent(int tag) const;
private:
    struct ConfigDialogue
    {
        string name; 
        string context; 
    };

    map<int, ConfigDialogue*> dialogue;
};