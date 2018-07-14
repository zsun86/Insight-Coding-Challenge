/*
	Basic Linked List class
*/
template <typename Object>
class List
{
  public:
    List() : head(NULL), tail(NULL), curr(NULL), length(0) {}
	
    int getLength() { return length; }

    void insertBeforeFirst(const Object & v)
    {
        head = new ListNode(v, head);
        if (tail == NULL)
            tail = head;
        length++;
    }

    void insertAfterLast(const Object & v)
    {
        if (tail == NULL)
            head = tail = new ListNode(v);
        else
        {
            tail->next = new ListNode(v);
            tail = tail->next;
        }
        length++;
    }

    void removeFirst()  // will crash if list empty
    {
        ListNode    *p = head;
        head = head->next;
        delete p;
        length--;
        if (head == NULL)
            tail = NULL;
    }

    void restart() { curr = head; }
    bool pastLast() { return curr == NULL; }
    void goNext() { if (curr != NULL) curr = curr->next; }
	void changeCurrentVal(const Object &v) { curr->val = v; }
    Object & getCurrent() { return curr->val; }  // may crash

	~List() {
		while(length > 0) {
			removeFirst();
		}
	}

  private:
    struct ListNode
    {
        ListNode(const Object & v, ListNode *p = NULL)
        : val(v), next(p) {}

        Object     val;
        ListNode   *next;
    };

    ListNode    *head, *tail, *curr;
    int         length;
};

