#ifndef COUNTINGMANAGER_H
#define COUNTINGMANAGER_H
#include <memory>
#include <vector>
#include "doubleimage.h"
#include "tweens/tweenmanager.h"
#include "resourceloader.h"

class CountingManager
{
public:
    CountingManager(ResourceLoaderPtr resource_loader);
    void update(float dt);
    bool finished();
    void set_input(std::vector <std::vector <DoubleImagePtr>> input);
    static const int MIN_LINE_LENGTH = 2;
    void clear_marks();
private:
    void check_line(std::vector <DoubleImagePtr> horizontal_line);
    void count_money_for_line(int index, int length);
    int prize;
    std::vector <TweenManagerPtr> tmanagers;
    ResourceLoaderPtr resource_loader;
    std::vector <DoubleImagePtr> marked_images;
};

typedef std::shared_ptr <CountingManager> CountingManagerPtr;

#endif // COUNTINGMANAGER_H
