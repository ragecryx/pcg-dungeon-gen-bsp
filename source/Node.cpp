#include "Node.h"
#include "AABB.h"

// Constructors
template<typename T>
Node<T>::Node(Node<T>* parent, T data) {
    mpParent = parent;
    mpLeft = nullptr;
    mpRight = nullptr;
    mData = data;
}

template<typename T>
Node<T>::~Node() {
	if(mpLeft != nullptr)
		delete mpLeft;
	if(mpRight != nullptr)
		delete mpRight;
}



// Methods
template<typename T>
T Node<T>::GetData() const {
    return mData;
}


template<typename T>
Node<T>* Node<T>::GetParent(void) const {
    return mpParent;
}


template<typename T>
Node<T>* Node<T>::GetLeftChild(void) const {
    return mpLeft;
}

template<typename T>
void Node<T>::MakeLeftChild(T data) {
    mpLeft = new Node(this, data);
}


template<typename T>
Node<T>* Node<T>::GetRightChild(void) const {
    return mpRight;
}

template<typename T>
void Node<T>::MakeRightChild(T data) {
    mpRight = new Node(this, data);
}



// NodeIterator -- Public inner class
template<typename T>
Node<T>::NodeIterator::NodeIterator(Node* parent) {
    mpRoot = parent;
    mpCurrent = parent;
}


template<typename T>
bool Node<T>::NodeIterator::Next() {
    if( mpCurrent->GetLeftChild() != 0 && mVisited.find(mpCurrent->GetLeftChild()) == mVisited.end() ) {
        //mpCurrent->SetLeftVisited();
        mVisited.insert(mpCurrent->GetLeftChild());
        mpCurrent = mpCurrent->GetLeftChild();
        return true;
    }
    
    if( mpCurrent->GetRightChild() != 0 && mVisited.find(mpCurrent->GetRightChild()) == mVisited.end() ) {
        //mpCurrent->SetRightVisited();
        mVisited.insert( mpCurrent->GetRightChild() );
        mpCurrent = mpCurrent->GetRightChild();
        return true;
    }
    
    if( mpCurrent->GetParent() != 0 ) {
        mpCurrent = mpCurrent->GetParent();
        return true;
    } else {
        return false;
    }
}


template<typename T>
T Node<T>::NodeIterator::GetData() const {
    return mpCurrent->mData;
}


template<typename T>
Node<T>* Node<T>::NodeIterator::GetNode() const {
    return mpCurrent;
}


template<typename T>
bool Node<T>::NodeIterator::IsLeaf() const {
    if( mpCurrent->GetLeftChild() == 0 && mpCurrent->GetRightChild() == 0 )
        return true;
    else
        return false;
}


template<typename T>
void Node<T>::NodeIterator::Reset() {
    mVisited.clear();
    mpCurrent = mpRoot;
}


// explicit template instantiation
template class Node<AABB>;


