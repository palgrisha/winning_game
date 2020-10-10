#ifndef COUNTINGMANAGER_H
#define COUNTINGMANAGER_H
#include <memory>
#include <vector>
#include "doubleimage.h"
#include "tweens/tweenmanager.h"

class CountingManager
{
public:
    CountingManager() = default;
    void update(float dt);
    bool finished();
    void set_input(std::vector <std::vector <DoubleImagePtr>> input);
    static const int MIN_LINE_LENGTH = 2;
private:
    void count_money_for_line(std::vector <DoubleImagePtr> horizontal_line);
    std::vector <TweenManagerPtr> tmanagers;
};

typedef std::shared_ptr <CountingManager> CountingManagerPtr;

#endif // COUNTINGMANAGER_H
