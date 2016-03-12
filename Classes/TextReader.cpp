#include "TextReader.h"
#include "json\document.h"
#include "json\rapidjson.h"

using namespace rapidjson;
USING_NS_CC;

static TextReader* textReader = NULL;

TextReader* TextReader::getInstance()
{
    if (!textReader)
    {
        textReader = new TextReader;
    }

    return textReader;
}

void TextReader::readFromJson()
{
    ssize_t size;
    unsigned char* ch = FileUtils::getInstance()->getFileData("Dialogue.json", "r", &size);
    std::string data = std::string((const char*)ch, size);

    Document doc;
    doc.Parse<0>(data.c_str());

    if (doc.HasParseError())
    {
        log("GetParseError%s\n", doc.GetParseError());
    }

    char name[10] = { '\0' };
    for (int i = 0; i < 25; i++)
    {
        sprintf(name, "Tag%d", i + 1);

        rapidjson::Value& valArr = doc[name];

        if (!valArr.IsArray())
            return;

        rapidjson::Value& p = valArr[(unsigned)0];
        ConfigDialogue* confDialogue = new ConfigDialogue;
        confDialogue->name = p.GetString();

        p = valArr[(unsigned)1];
        confDialogue->context = p.GetString();

        dialogue[i] = confDialogue;
    }

}

const char* TextReader::getContent(int tag) const
{
    return dialogue.at(tag - 1)->context.c_str();
}

const char* TextReader::getName(int tag) const
{
    return dialogue.at(tag - 1)->name.c_str();
}
