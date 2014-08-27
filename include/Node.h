#ifndef PCG_NODE_H
#define PCG_NODE_H



#include <unordered_set>

template<typename T>
class Node {
    public:
        Node(Node<T>* parent, T data);
        ~Node();
    private:
        T mData;
        Node* mpParent;
        Node* mpLeft;
        Node* mpRight;
    public: // Public Methods
        T GetData(void) const;
        Node* GetParent(void) const;
        
        void MakeLeftChild(T space);
        Node* GetLeftChild(void) const;
        
        void MakeRightChild(T space);
        Node* GetRightChild(void) const;
    public: // Public inner types
        class NodeIterator {
            public:
                NodeIterator(Node* parent);
            private:
                std::unordered_set<Node*> mVisited;
                Node* mpRoot;
                Node* mpCurrent;
            public:
                bool Next();
                T GetData() const;
                Node* GetNode() const;
                bool IsLeaf() const;
                void Reset();
        };
};



#endif
