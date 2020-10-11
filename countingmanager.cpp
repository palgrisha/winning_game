#include "countingmanager.h"
#include "tweens/tweencurves.h"
#include "math.h"
#include <algorithm>

CountingManager::CountingManager(ResourceLoaderPtr resource_loader):
    resource_loader(resource_loader)
{
}

void CountingManager::update(float dt)
{
    if (tmanagers.empty())
    {
        return;
    }

    tmanagers.front()->update(dt);
    tmanagers.front()->remove_empty_queues();
    if (tmanagers.front()->size() == 0)
    {
        tmanagers.erase(tmanagers.begin());
    }
}

bool CountingManager::finished()
{
    return tmanagers.size() == 0;
}

void CountingManager::check_line(std::vector <DoubleImagePtr> horizontal_line)
{
    size_t line_size = horizontal_line.size();

    int first = 0;
    int second = first + 1;

    while (second < line_size &&
           horizontal_line.at(first)->get_index() == horizontal_line.at(second)->get_index())
    {
        second++;
    }

    if (second - first < MIN_LINE_LENGTH)
    {
        return;
    }

    auto tween_manager = std::make_shared <TweenManager>();

    for (int i = first; i < second; i++)
    {
        auto image = horizontal_line.at(i);
        auto start_x = image->get_scale_x();
        auto start_y = image->get_scale_y();
        auto final_x = start_x * 3 / 4;
        auto final_y = start_y * 3 / 4;

        auto queue = std::make_shared<TweenQueue>();
        queue->add_tween(std::make_shared <ActionTween> (image, final_x, final_y, 0.5, linear,
                                                         [horizontal_line, i](){horizontal_line.at(i)->swap_textures();}));
        queue->add_tween(std::make_shared <TweenScale> (image, final_x, final_y, start_x, start_y, 0.5, linear));
        tween_manager->add_tween_queue(queue);

        marked_images.push_back(image);
    }

    count_money_for_line(horizontal_line.at(first)->get_index(), second - first);
    tmanagers.push_back(tween_manager);
}

void CountingManager::clear_marks()
{
    for (auto image : marked_images)
    {
        image->swap_textures();
    }

    marked_images.clear();
}

void CountingManager::set_input(std::vector<std::vector<DoubleImagePtr>> input)
{
    prize = 0;
    std::vector <DoubleImagePtr> horizontal_line;

    for (auto j = 0; j < 3; j++)
    {
        for (auto k = 0; k < input.size(); k++)
        {
            horizontal_line.push_back(input.at(k).at(j));
        }
        check_line(horizontal_line);
        horizontal_line.clear();
    }

    std::reverse(tmanagers.begin(), tmanagers.end());

    std::cout << "Your win is " << prize << "\n\n";
}

void CountingManager::count_money_for_line(int index, int length)
{
    int figure_base = 0;

    if (index == resource_loader->get("star")->index)
    {
        figure_base = 150;
    }

    else if (index == resource_loader->get("circle")->index)
    {
        figure_base = 100;
    }

    else if (index == resource_loader->get("square")->index)
    {
        figure_base = 50;
    }

    else if (index == resource_loader->get("triangle")->index)
    {
        figure_base = 50;
    }

    prize += pow(2, (length - MIN_LINE_LENGTH)) * figure_base;

}
