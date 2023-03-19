#include "List.h"

custom_list::custom_list(char elelemen)
{
    element = elelemen;
    next = nullptr;
}

void custom_list::add(char elelement)
{
    if (next == nullptr)
    {
        next = new custom_list(elelement);
        return;
    }
    next->add(elelement);
}

void custom_list::SetNext(custom_list* new_link)
{
    next = new_link;
}

void custom_list::removeLast(custom_list* previous)
{
    if (next == nullptr)
    {
        if (previous != nullptr)
        {
            previous->SetNext(nullptr);
        }
        delete this;
        return;
    }
    next->removeLast(this);
}

char custom_list::get()
{
    return element;
}

custom_list* custom_list::getNext()
{
    return next;
}

void custom_list::deleteList()
{
    if (next)
    {
        next->deleteList();
    }
    delete this;
}

custom_list::~custom_list() { };