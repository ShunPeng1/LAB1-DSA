#include <iostream>
#include <assert.h>

using namespace std;

template <class T>
class SLinkedList
{
public:
    class Iterator; //forward declaration
    class Node;     //forward declaration
protected:
    Node *head;
    Node *tail;
    int count;
public:
    SLinkedList() : head(NULL), tail(NULL), count(0){};
    ~SLinkedList();
    void add(const T &e);
    void add(int index, const T &e);
    T removeAt(int index);
    bool removeItem(const T &removeItem);
    bool empty();
    int size();
    void clear();
    T get(int index);
    void set(int index, const T &e);
    int indexOf(const T &item);
    bool contains(const T &item);
    string toString();
    SLinkedList(const SLinkedList &list)
    {
        this->count = 0;
        this->head = NULL;
        this->tail = NULL;
    }
    Iterator begin()
    {
        return Iterator(this, true);
    }
    Iterator end()
    {
        return Iterator(this, false);
    }
public:
    class Node
    {
    private:
        T data;
        Node *next;
        friend class SLinkedList<T>;
    public:
        Node()
        {
            next = 0;
        }
        Node(Node *next)
        {
            this->next = next;
        }
        Node(T data, Node *next = NULL)
        {
            this->data = data;
            this->next = next;
        }
    };
    class Iterator
    {
    private:
        SLinkedList<T> *pList;
        Node *current;
        int index; // corresponding with current node
    public:
    
        Iterator(SLinkedList<T> *pList = nullptr, bool begin = false);
        Iterator &operator=(const Iterator &iterator);
        void set(const T &e);
        T &operator*();
        bool operator!=(const Iterator &iterator);

        //
        void remove();
        
        // Prefix ++ overload
        Iterator &operator++();
        
        // Postfix ++ overload
        Iterator operator++(int);
    };
};

template <class T>
void SLinkedList<T>::add(const T& e) {
    /* Insert an element into the end of the list. */
    
    //cout<<this->toString()<<endl;
    count++;
    Node *nNode = new Node(e, nullptr);
    if(count == 1){
        head = nNode;
        tail = nNode;
        
    }
    else{
        tail->next = nNode;
        tail = tail->next;
    }
    
}

template<class T>
void SLinkedList<T>::add(int index, const T& e) {
    /* Insert an element into the list at given index. */ 
    
    //cout<<this->toString()<<endl;
    
    Node *nNode = new Node(e, nullptr);
    if(count==1){
        head = nNode;
        tail = nNode;
        return;
    }
    
    Node *roam = head;
    
    if(index == 0){
        
        nNode->next = head;
        head = nNode;
        return;
    }
    int i = 1;
    while(roam){
        if(i==index){
            break;
        }
        roam = roam->next;
        i++;
    }
    Node * nextNode = roam->next;
    roam->next = nNode;
    nNode->next = nextNode;
}

template<class T>
int SLinkedList<T>::size() {
    /* Return the length (size) of list */ 
    return count;
}

template <class T>
SLinkedList<T>::Iterator::Iterator(SLinkedList<T>* pList, bool begin)
{
    /*
        Constructor of iterator
        * Set pList to pList
        * begin = true: 
        * * Set current (index = 0) to pList's head if pList is not NULL
        * * Otherwise set to NULL (index = -1)
        * begin = false: 
        * * Always set current to NULL
        * * Set index to pList's size if pList is not NULL, otherwise 0
    */

   this->pList = pList;
   if(begin){
        if(pList->head){
            index = 0;
            current  = pList->head;
        }
        else{
            index = -1;
            current = nullptr;
        }
   }    
   else{
        current = nullptr;
        if(pList->head){
            index = pList->count;
        }
        else{
            index = 0;
        }
   }
}

template <class T>
typename SLinkedList<T>::Iterator& SLinkedList<T>::Iterator::operator=(const Iterator& iterator)
{
    /*
        Assignment operator
        * Set this current, index, pList to iterator corresponding elements.
    */
    this->current = iterator.current;
    this->index = iterator.index;
    this->pList = iterator.pList;
    return *this;
}

template <class T>
void SLinkedList<T>::Iterator::remove()
{
    /*
        Remove a node which is pointed by current
        * After remove current points to the previous node of this position (or node with index - 1)
        * If remove at front, current points to previous "node" of head (current = NULL, index = -1)
        * Exception: throw std::out_of_range("Segmentation fault!") if remove when current is NULL
    */
   
   if(!current) {
        throw std::out_of_range("Segmentation fault!");
        return ;
    }
    if(current != head){
        delete current;
        current = nullptr;
        index = -1;
        return;
    }

    Node *temp = head;
    while(temp->next != current){
        temp = temp->next;
    }
    delete current;
    current = temp;
    index--;
    
}

template <class T>
void SLinkedList<T>::Iterator::set(const T& e)
{
    /*
        Set the new value for current node
        * Exception: throw std::out_of_range("Segmentation fault!") if current is NULL
    */
   if(current){
        current->data = e;
   }
   else {
        throw std::out_of_range("Segmentation fault!");
   }
}

template <class T>
T& SLinkedList<T>::Iterator::operator*()
{
    /*
        Get data stored in current node
        * Exception: throw std::out_of_range("Segmentation fault!") if current is NULL
    */
   if(!current) {
        throw std::out_of_range("Segmentation fault!");
   }
   return current->data;
}

template <class T>
bool SLinkedList<T>::Iterator::operator!=(const Iterator& iterator)
{
    /*
        Operator not equals
        * Returns false if two iterators points the same node and index
    */
   return( this->current != iterator.current);
}
// Prefix ++ overload
template <class T>
typename SLinkedList<T>::Iterator& SLinkedList<T>::Iterator::operator++()
{
    /*
        Prefix ++ overload
        * Set current to the next node
        * If iterator corresponds to the previous "node" of head, set it to head
        * Exception: throw std::out_of_range("Segmentation fault!") if iterator corresponds to the end
    */
   
   if(!(current != pList->tail)) {
        throw std::out_of_range("Segmentation fault!");
   }
   if(index == -1){
        current = pList->head;
   }
   else {
        current = current->next;
   }
   index++;
   return *this;

}
// Postfix ++ overload
template <class T>
typename SLinkedList<T>::Iterator SLinkedList<T>::Iterator::operator++(int)
{
    /*
        Postfix ++ overload
        * Set current to the next node
        * If iterator corresponds to the previous "node" of head, set it to head
        * Exception: throw std::out_of_range("Segmentation fault!") if iterator corresponds to the end
    */
   
   if(!(current != pList->tail)) {
        throw std::out_of_range("Segmentation fault!");
   }
   if(index == -1){
        current = pList->head;
   }
   else {
        current = current->next;
   }
   index++;
   return *this;
}

// class Polynomial;
// class Term {
// private:
//     double coeff;   
//     int exp;
//     friend class Polynomial;
// public:
//     Term(double coeff = 0.0, int exp = 0) {
//         this->coeff = coeff;
//         this->exp = exp;
//     }
//     bool operator==(const Term& rhs) const {
//         return this->coeff == rhs.coeff && this->exp == rhs.exp;
//     }
//     friend ostream & operator<<(ostream &os, const Term& term) {
//         cout << endl;
//         cout << "Term: " << "(" << term.coeff << " " << term.exp << ")";
//         return os;
//     }
// };
// class Polynomial {
// private:
//     SLinkedList<Term>* terms;
// public:
//     Polynomial() {
//         this->terms = new SLinkedList<Term>();
//     }
//     ~Polynomial() {
//         this->terms->clear();
//     }
//     void insertTerm(const Term& term);
//     void insertTerm(double coeff, int exp);
//     void print() {
//         SLinkedList<Term>::Iterator it;
//         cout << "[";
//         for (it = this->terms->begin(); it != this->terms->end(); it++) {
//             cout << (*it);
//         }
//         cout << endl << "]";
//     }
// };



int main(){
    	
SLinkedList<int> list;
int size = 10;

for (int index = 0; index < size; index++) {
    list.add(list.size(), index);
}

cout << list.toString();
    return 0;
}