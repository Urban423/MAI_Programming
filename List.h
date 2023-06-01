#pragma once

class custom_list
{
public:
    custom_list(int elelemen);
    void add(int elelement);
    void SetNext(custom_list* new_link);
    void removeLast(custom_list* previous = nullptr);
    int get();
    custom_list* getNext();
    void deleteList();
    ~custom_list();
private:
    int element;
    custom_list* next;
};