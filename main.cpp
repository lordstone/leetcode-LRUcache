class mylist{
public:
    int value;
    int key;
    mylist* prev;
    mylist* next;
    mylist(){}
};


class LRUCache{
public:
    
    mylist anchor;
    unordered_map<int, mylist*> mymap;
    int mycap;
    
    void unlink(mylist* thelist){
        mylist* prev = thelist->prev;
        mylist* next = thelist->next;
        prev->next = next;
        next->prev = prev;
    }
    
    void insertEnd(mylist* thelist){
        mylist* prev = anchor.prev;
        prev->next = thelist;
        anchor.prev = thelist;
        thelist->prev = prev;
        thelist->next = &anchor;
    }
    
    void removeHead(){
        if(anchor.next != &anchor){
            mylist* tmp = anchor.next;
            mylist* tmp2 = tmp -> next;
            mymap.erase(tmp->key);
            tmp2->prev= &anchor;
            anchor.next = tmp2;
            delete tmp;
        }
    }
    
    mylist* addEnd(int value, int key){
        mylist* tmp;
        tmp = new mylist();
        mylist* prev = anchor.prev;
        tmp->value = value;
        tmp->key = key;
        tmp->next = &anchor;
        tmp->prev = prev;
        prev->next = tmp;
        anchor.prev = tmp;
        return tmp;
    }
    
    LRUCache(int capacity) {
        mycap = capacity;
        anchor.next = &anchor;
        anchor.prev = &anchor;
    }
    
    int get(int key) {
        
        int retval = -1;
        if( ( mymap.find(key)) == mymap.end()){
            return retval;
        }else{
            mylist* tmp = mymap[key];
            retval = tmp->value;
            unlink(tmp);
            insertEnd(tmp);
            return retval;
        }
        
        //return -1;
    }
    
    void set(int key, int value) {
        if((mymap.find(key)) != mymap.end()){
            mylist* tmp = mymap[key];
            tmp->value = value;
            unlink(tmp);
            insertEnd(tmp);
        }else{
            if(mymap.size() >=  mycap){
                removeHead();
            }
            mymap[key] = addEnd(value, key);
        }
    }
};
