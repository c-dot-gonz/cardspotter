#include "CardDatabase.h"
#include "QueryThread.h"
#include <unistd.h>
#include <emscripten.h>
#include <emscripten/bind.h>

using namespace emscripten;
using namespace std;

class CardSpotter
{
private:
    CardDatabase gDatabase;
    Query query;

public:
    CardSpotter() : query(gDatabase)
    {
    }

    int SetSetting(std::string key, std::string value)
    {
        const int dbResult = gDatabase.SetSetting(key, value);
        const int queryResult = query.SetSetting(key, value);
        const int result = std::max(dbResult, queryResult);
        return result;
    }

    int LoadDatabase(std::string data)
    {
        gDatabase.LoadString(data.c_str());
        return 1;
    }

    val AddScreen(const int &addr, int length, const size_t width, const size_t height)
    {
        uint8_t *data = reinterpret_cast<uint8_t *>(addr);
        Result r;
        const bool success = query.AddScreenAndPrint(data, length, width, height, r);
        // This is the JS object value returned to JS
        val rv(val::object());
        // This vector will hold the points of recognized image
        std::vector<cv::Point2f> rectpoints;
        rectpoints.resize(4);
        if (success)
        {
            const Match &match = r.myMatch.myList[0];
            match.myInput.myRect.points(&rectpoints[0]);
            // I don't know why we need this...
            rv.set("name", val(match.myDatabaseCard->myCardName));
            rv.set("id", val(match.myDatabaseCard->myCardId));
            rv.set("score", val((int)match.myScore[0]));
            rv.set("set", val(match.myDatabaseCard->mySetCode));
            rv.set("url", val(match.myDatabaseCard->myImgCoreUrl));
            // The rectangle in the image where the card was found
            rv.set("x1", val((int)rectpoints[0].x));
            rv.set("x2", val((int)rectpoints[1].x));
            rv.set("x3", val((int)rectpoints[2].x));
            rv.set("x4", val((int)rectpoints[3].x));
            rv.set("y1", val((int)rectpoints[0].y));
            rv.set("y2", val((int)rectpoints[1].y));
            rv.set("y3", val((int)rectpoints[2].y));
            rv.set("y4", val((int)rectpoints[3].y));
        }
        return rv;
    }

    val FindCardInImage(const int &addr, int length, const size_t width, const size_t height)
    {
        uint8_t *data = reinterpret_cast<uint8_t *>(addr);
        Result r;
        const bool success = query.FindCardInRoiAndPrint(data, length, width, height, r);
        // This is the JS object value returned to JS
        val rv(val::object());
        // This vector will hold the points of recognized image
        std::vector<cv::Point2f> rectpoints;
        rectpoints.resize(4);
        if (success)
        {
            const Match &match = r.myMatch.myList[0];
            match.myInput.myRect.points(&rectpoints[0]);
            // I don't know why we need this...
            rv.set("name", val(match.myDatabaseCard->myCardName));
            rv.set("id", val(match.myDatabaseCard->myCardId));
            rv.set("score", val((int)match.myScore[0]));
            rv.set("set", val(match.myDatabaseCard->mySetCode));
            rv.set("url", val(match.myDatabaseCard->myImgCoreUrl));
            // The rectangle in the image where the card was found
            rv.set("x1", val((int)rectpoints[0].x));
            rv.set("x2", val((int)rectpoints[1].x));
            rv.set("x3", val((int)rectpoints[2].x));
            rv.set("x4", val((int)rectpoints[3].x));
            rv.set("y1", val((int)rectpoints[0].y));
            rv.set("y2", val((int)rectpoints[1].y));
            rv.set("y3", val((int)rectpoints[2].y));
            rv.set("y4", val((int)rectpoints[3].y));
        }
        return rv;
    }
};

EMSCRIPTEN_BINDINGS(my_module)
{
    class_<CardSpotter>("CardSpotter")
        .constructor()
        .function("LoadDatabase", &CardSpotter::LoadDatabase)
        .function("SetSetting", &CardSpotter::SetSetting)
        .function("AddScreen", &CardSpotter::AddScreen, allow_raw_pointers())
        .function("FindCardInImage", &CardSpotter::FindCardInImage, allow_raw_pointers());
}