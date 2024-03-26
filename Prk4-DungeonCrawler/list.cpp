#include "list.h"

List::List(): list_size(0)
{
}

List::~List()
{
    while(start!=nullptr){
        pop_back();
    }
}

void List::push_back(Level *level)
{
    Element* tmp = new Element{level, nullptr, nullptr};
    if(empty()){
        start = tmp;
        list_size++;
        return;
    }

    auto currElem = start;
    while(currElem->next!=nullptr){
        currElem = currElem->next;
    }
    tmp->prev = currElem;
    currElem->next = tmp;
    list_size++;
}

void List::push_front(Level *level)
{
    Element* tmp = new Element{level, nullptr, nullptr};
    if (empty()){
        start = tmp;
        list_size++;
        return;
    }
    tmp->next = start;
    start->prev = tmp;
    start = tmp;
    list_size++;
}

void List::pop_back()
{
    if (start==nullptr){
        throw std::invalid_argument("List is empty");
        return;
    }

    if (start->next==nullptr){
        delete start;
        start=nullptr;
        list_size--;
        return;
    }
    auto currElem = start;
    while(currElem->next->next != nullptr){
        currElem = currElem->next;
    }
    delete currElem->next;
    currElem->next = nullptr;
    list_size--;
}

void List::pop_front()
{
    if (start==nullptr){
        throw std::invalid_argument("List is empty");
        return;
    }
    auto tmp = start;
    start = start->next;
    start->prev = nullptr;
    delete tmp;
    list_size--;
}

bool List::empty()
{
    return list_size == 0;
}

size_t List::size()
{
    return list_size;
}

void List::remove(Level *level)
{
    if (start==nullptr){
        throw std::invalid_argument("List is empty");
        return;
    }

    auto currElem = start;
    while (currElem->next != nullptr){
        auto tmp = currElem->next;
        if (currElem->currlevel == level){
            currElem->prev->next = currElem->next;
            currElem->next->prev = currElem->prev;
            list_size--;
            delete currElem;
        }
        currElem = tmp;
    }
}

List::iterator List::begin()
{
    if(empty()){
        return iterator(nullptr);
    }
    return iterator(start);
}

List::iterator List::end()
{
    return iterator(new Element{nullptr, nullptr, nullptr});
}

Level *List::getNext(Level * level)
{
    auto currElem = start;
    while (currElem->currlevel != level && currElem->next != nullptr){
        currElem = currElem->next;
    }
    return currElem->next->currlevel;
}

Level *List::getPrev(Level *level)
{
    auto currElem = start;
    while (currElem->currlevel != level && currElem->next != nullptr){
        currElem = currElem->next;
    }
    return currElem->prev->currlevel;
}




