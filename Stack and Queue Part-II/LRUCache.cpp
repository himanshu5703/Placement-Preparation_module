class LRUCache {
public:

    class node{
        public:
        int key;
        int val;
        node* next;
        node* prev;
        node(int _key, int _val){
            key = _key;
            val = _val;
        }
    };

    node* head = new node(-1, -1);
    node* tail = new node(-1, -1);

    int cap;
    unordered_map<int , node*> mp;

    LRUCache(int capacity) {

        cap = capacity;
        head->next = tail;
        tail->prev = head;
    }

    void addNode(node* newnode){

        node* temp = head->next;
        newnode->next = temp;
        newnode->prev = head;
        head->next = newnode;
        temp->prev = newnode;
    }
    

    void deletenode(node* deletenode){
        node* deleteprev = deletenode->prev;
        node* deletenext = deletenode->next;
        deleteprev->next = deletenext;
        deletenext->prev = deleteprev;
    }
    int get(int key) {
        
        if(mp.find(key) != mp.end()){
            node* tempnode = mp[key];
            int ans = tempnode->val;
            mp.erase(key);
            deletenode(tempnode);
            addNode(tempnode);
            mp[key] = head->next;
            return ans;
        }

        return -1;
    }
    
    void put(int key, int value) {

        if(mp.find(key) != mp.end()){
            node* tempnode = mp[key];
            mp.erase(key);
            deletenode(tempnode);

        }

        if(mp.size() == cap){
            mp.erase(tail->prev->key);
            deletenode(tail->prev);
        }

        addNode(new node(key, value));
        mp[key] = head->next;
        
    }
};

