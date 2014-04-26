/*Taken from
 *http://www.instructables.com/id/3D-Snake-on-Charlieplexed-4x4x4-LED-Cube/
*/

#ifndef NODE_H
#define NODE_H

template <typename T>
class List;

template <typename T>
class Node
{
    friend class List<T>;
    public:
        Node(Node * next = 0, Node * previous = 0): next(next), previous(previous){}
        Node(T data, Node<T> * next = 0, Node * previous = 0): data(data), next(next), previous(previous){}
    private:
        T data;
        Node * next;
        Node * previous;
};

#endif // NODE_H