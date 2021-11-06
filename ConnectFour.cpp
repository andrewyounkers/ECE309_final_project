#include <iostream>
using namespace std;

// implementation for list object to be used
class List 
{
private:
// implementation of ListNode class
class ListNode 
  {
  public:
    char val; 
    ListNode *next;	
    ListNode(char v, ListNode *n=nullptr) 
    {
      val = v;
      next = n;
    }
  };
  ListNode *head;
  ListNode *tail;
public:
    // iterator class
    class iterator 
    {
    private:
        ListNode *node; 
    public: 
        iterator(ListNode *n=nullptr) { node = n; }
        // return val of iterator
        char& getVal() { return node->val; }
        void next() { node = node->next; }
    
        bool operator==(const iterator &other) 
        {
            return node == other.node;
        }   
    
        bool operator != (const iterator &other) 
        {
            return node != other.node;
        }

        //code allowing to increment iterator by overloading ++
        iterator& operator++() 
        {
            next();
            return *this;
        }
    };
    
    // get begining and end of a list
    iterator begin() { return iterator(head); }
    iterator end() { return iterator(); }
    
    // code to append to the list
    // all that is needed in managing the connect 4 board
    void append(char a) 
    {
        ListNode *node = new ListNode(a);
        if (head==nullptr) 
        { 
            head = node;
            tail = node;
        } 
        else 
        {
            tail->next = node;
            tail = node;         
        }
    }
};

// classs for Board using row and coloumn
// to define how big the board is
class Board 
{
protected:
    int row;
    int coloumn;
public:
    // set default rows to 7 and coloumns to 6
    Board(int r = 7,int c = 6) 
    {
        row = r;
        coloumn = c;
    }
};

// derive BoardHT from Board
class BoardHT : public Board 
{
protected:
    // dist will be amount of coloums and be max length of lists in each bucket
    int dist;
    // one bucket per row, buckets will hold lists
    struct bucket 
    {
        List list;
        bucket() { list; } 
    };
    // hash function, will be updated more when insert is implemented, somewhat a placeholder for now
    int hash(int key) const 
    {
        int val = key - 1;
        return std::abs(val);
    }
public:
    // made public to be able to test locally in main(), will be protected when fully implemented
    bucket *table;
    // constructor for board using HT
    BoardHT() 
    {
        dist = coloumn;
        table = new bucket [row];
    }
};

// used for local testing, not important to actual project design
// creates and prints a table of 7 rows and 6 coloumns all holding 'R'
int main()
{
    BoardHT F;
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 6; j++) 
        {
            F.table[i].list.append('R');
        }
    }
    List::iterator it;
    for (int j = 0; j < 6; j++)
    {
        for (int i = 0; i < 7; i++)
        {
            if (j == 0) it = F.table[i].list.begin();
            else 
            {
                for (int k = 0; k < j; k++) 
                {
                    it = F.table[i].list.begin();
                    ++it;   
                }
            }
            cout << it.getVal() << " ";   
        }    
        cout << endl;
    }
}