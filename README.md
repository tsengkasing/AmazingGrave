# AmazingGrave
A game power by cocos2d-x 3.5 /using C++ on Win

## how to use

Install the cocos2d-x 3.5
create a new project using python in cmd with the Command
"cocos new AmazingGrave -p 'packageName' -l cpp -d 'file directory'"

put the classes folder and Resourses folder cover the former folder
Open the \proj.win32\AmazingGrave.sln with **Visual Studio 2013**.
Just Run it.


**if you meet an error in "cocos2d\extensions\GUI\CCScrollView\CCScrollView.h"**

***change the line***
` #include "extensions\ExtensionMacros.h"`
`#include "extensions\ExtensionExport.h"`

***into***
` #include "../../ExtensionMacros.h"`
` #include "../../ExtensionExport.h"`

## game intruction

There are 4 game missions.


