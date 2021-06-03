#include <iostream>
#include<list>
#include<unordered_map>
using namespace std;

//Node to store the data
class Node{
public:
    string key;
    int value;
    Node(string key,int value){
        this->key=key;
        this->value=value;
    }
};

//LRU Cache Data Structure
class LRUCache{
public:
    int maxSize;
    list<Node>l;
    unordered_map<string,list<Node>::iterator>m;

    LRUCache(int maxSize){
        this->maxSize=maxSize>1?maxSize:1;
    }
    void insertKeyValue(string key,int value){
         //2 cases
         if(m.count(key)!=0){
             //replace the old value with the new value
             auto it=m[key];
             it->value=value;
         }
         else{
             //check cache is full or not
             //remove least recently used item from cache
             if(l.size()==maxSize){
                 Node last=l.back();
                 m.erase(last.key);//remove from hashmap
                 l.pop_back();//remove from list
             }
             Node n(key,value);
             l.push_front(n);
             m[key]=l.begin();
         }
    }
    int* getValue(string key){
        if(m.count(key)!=0){
            auto it=m[key];
            int value=it->value;
            //insert it at head as it becomes most Recently used
            l.push_front(*it);
            l.erase(it);
            m[key]=l.begin();
            return &l.begin()->value;
        }
        return NULL;
    }
    string mostRecentKey(){
        return l.front().key;
    }
};

int main() {
    LRUCache lru(3);
    lru.insertKeyValue("mango",10);
    lru.insertKeyValue("apple",20);
    lru.insertKeyValue("guava",30);
    cout << lru.mostRecentKey() <<endl;

    lru.insertKeyValue("mango",40);
    cout << lru.mostRecentKey() <<endl;

    int *orders = lru.getValue("mango");
    if(orders!=NULL){
        cout<<"Order of Mango "<<*orders <<endl;
    }


    lru.insertKeyValue("banana",20);

    if(lru.getValue("apple")==NULL){
        cout<<"apple doesn't exist";
    }

    if(lru.getValue("guava")==NULL){
        cout<<"guava doesn't exist";
    }

    if(lru.getValue("banana")==NULL){
        cout<<"banana doesn't exist";
    }
    if(lru.getValue("mango")==NULL){
        cout<<"mango doesn't exist";
    }




    return 0;
}
