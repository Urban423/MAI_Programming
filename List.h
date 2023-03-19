#pragma once

class custom_list
{
public:
    custom_list(char elelemen);
    void add(char elelement);
    void SetNext(custom_list* new_link);
    void removeLast(custom_list* previous = nullptr);
    char get();
    custom_list* getNext();
    void deleteList();
    ~custom_list();
private:
    char element;
    custom_list* next;
};