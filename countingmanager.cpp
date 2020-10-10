#include "countingmanager.h"
#include "tweens/tweencurves.h"

void CountingManager::update(float dt)
{
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

//функция предполагает, что в одной линии не может быть двух выигрышных комбинаций, из которых нужно выбирать лучшую,
// т.к. невозможно с текущими настройками

void CountingManager::count_money_for_line(std::vector <DoubleImagePtr> horizontal_line)
{
    size_t line_size = horizontal_line.size();

    for (int first = 0; first <= line_size - MIN_LINE_LENGTH; first++)
    {
        int second = first + 1;

        while (second < line_size &&
               horizontal_line.at(first)->get_index() == horizontal_line.at(second)->get_index())
        {
            second++;
        }

        if (second - first < MIN_LINE_LENGTH)
        {
            continue;
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
            queue->add_tween(std::make_shared <ActionTween> (image, final_x, final_y, 0.5, linear, [horizontal_line, i](){horizontal_line.at(i)->swap_textures();}));
            queue->add_tween(std::make_shared <TweenScale> (image, final_x, final_y, start_x, start_y, 0.5, sin_in_out));
            tween_manager->add_tween_queue(queue);

        }

        std::cout << tmanagers.size() << '\n';
        tmanagers.push_back(tween_manager);
        return;
    }


    std::cout << "Nothing \n";

}


void CountingManager::set_input(std::vector<std::vector<DoubleImagePtr>> input)
{
    std::vector <DoubleImagePtr> horizontal_line;
    for (auto j = 0; j < 3; j++)
    {
        for (auto k = 0; k < input.size(); k++)
        {
            horizontal_line.push_back(input.at(k).at(j));
        }
        count_money_for_line(horizontal_line);
        horizontal_line.clear();

    }
    std::cout << '\n';
}
