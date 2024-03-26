#ifndef LIST_H
#define LIST_H

#include "level.h"
class List
{
private:
    struct Element{
        //Element(Level* lvl, Element* Prev, Element* Next): currlevel(lvl), prev(Prev), next(Next){};
        Level* currlevel=nullptr;
        Element* prev=nullptr;
        Element* next=nullptr;
    };
    Element* start=nullptr;
    std::size_t list_size;
public:
    class iterator;
    List();
    ~List();
    void push_back(Level* level);
    void push_front(Level*level);
    void pop_back();
    void pop_front();
    bool empty();
    size_t size();
    void remove(Level* level);

    iterator begin();
    iterator end();

    Level* getNext(Level*);
    Level* getPrev(Level*);
    class iterator{
    public:
        iterator(Element* Ptr): ptr(Ptr){}
        iterator& operator++(){
            if(ptr->next == nullptr){
                throw std::invalid_argument("Error!");
            }
            else{
                ptr=ptr->next;
            }
            return *this;
        }
        iterator& operator--(){
            if(ptr->prev == nullptr){
                throw std::invalid_argument("Error!");
            }
            else{
                ptr=ptr->prev;
            }
            return *this;
        }
        Level* getNextLevel(){
            if(ptr->next == nullptr){
                return nullptr;
            }
            return ptr->next->currlevel;
        }
        Level*& operator*(){
            if(ptr->currlevel == nullptr){
                throw std::invalid_argument("Error!");
            }
            return ptr->currlevel;
        }
        bool operator==(const iterator& itr){
            return ptr->currlevel == itr.ptr->currlevel;
        }
        bool operator!=(const iterator& itr){
            return ptr->currlevel != itr.ptr->currlevel;
        }
    private:
        Element* ptr = nullptr;
    };
};

#endif // LIST_H
