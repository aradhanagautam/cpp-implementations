#include <iostream>
#include<unordered_map>
using namespace std;
class LRUCache{
    class Node{
        public:
        int key, val;
        Node* prev;
        Node* next;

        Node(int k, int v)
        {
            key = k;
            val = v;
            prev = nullptr;
            next = nullptr;
        }
    };

    int capacity;
    Node* head;
    Node* tail;
    unordered_map <int,Node*> mp;
    void addNode(Node* node)
    {
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }
    void deleteNode(Node* node)
    {
        Node* prevNode = node->prev;
        Node* nextNode = node->next;
        nextNode->prev = prevNode;
        prevNode->next = nextNode;
    }
public:
    LRUCache(int cap)
    {
        capacity = cap;

        head = new Node(-1,-1);
        tail = new Node(-1,-1);

        head->next = tail;
        tail->prev = head;
    }
    int get(int key)
    {
        if(mp.count(key))
        {
            Node* temp = mp[key];
            int v = temp->val;

            deleteNode(temp);
            addNode(temp);

            return v;
        }
        return -1;
    }
    void put(int key, int value)
    {
         if (capacity == 0) return;
        //case 1: if key already exists
        if(mp.count(key))
        {
            Node* temp = mp[key];
            temp->val = value;

            deleteNode(temp);
            addNode(temp);
        }
        else //case 2: Key is not present
        {
            if(mp.size() == capacity)
            {
                Node* node = tail->prev;
                deleteNode(node);
                mp.erase(node->key);
                delete(node);
            }

            Node* temp = new Node(key,value);
            addNode(temp);
            mp[key] = temp;
        }
    }
    ~LRUCache()
    {
        Node* curr = head;
        while(curr!=nullptr)
        {
            Node* temp = curr->next;
            delete(curr);
            curr = temp;
        }
    }
};
int main() {
    LRUCache cache(2);

    cache.put(1, 10);
    cache.put(2, 20);

    cout << cache.get(1) << endl; // 10

    cache.put(3, 30); // removes key 2

    cout << cache.get(2) << endl; // -1
    cout << cache.get(3) << endl; // 30

    return 0;
}
