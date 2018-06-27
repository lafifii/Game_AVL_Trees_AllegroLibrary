#pragma once

template<typename T>
class AVLTree {
	struct Node;

	Node* root;
	std::function<int(T, T)> compare;

	void rotateLeft(Node*& node);
	void rotateRight(Node*& node);
	void balance(Node*& node);

	void add(Node*& node, T element);
	unsigned int length(Node* node);
	int heightAVL(Node* node);
	void update(Node* node);
	T search(Node* node, T key);
	
public:
	AVLTree();
	AVLTree(int ind);
	~AVLTree();

	unsigned int length();
	int heightAVL();
	void add(T element);
	T search(T key);
};

template <typename T>
AVLTree<T>::AVLTree() : root(nullptr) {
	compare = [](T a, T b) 
	{ return a->getIndex() - b->getIndex(); };
}
template <typename T>
AVLTree<T>::AVLTree(int ind) 
{
	root = nullptr;
	if (ind == 1)
		compare = [](T a, T b) { return a->getNEnemigos() - b->getNEnemigos(); };
	else if(ind == 2)
		compare = [](T a, T b) { return a->getNRecursos() - b->getNRecursos(); };
	else if (ind == 3)
		compare = [](T a, T b) { return a->getDistancia() - b->getDistancia(); };
		
	else if (ind == 4)
		compare = [](T a, T b) {
		if (a->getUbicacion() == b->getUbicacion())return 0;
		if (a->getUbicacion() > b->getUbicacion())return 1;
		if (a->getUbicacion() < b->getUbicacion())return -1;
	};
		
	else 
		compare = [](T a, T b) { return a->getNBloques() - b->getNBloques(); };
}

template <typename T>
AVLTree<T>::~AVLTree() {
	std::stack<Node*> st;
	st.push(root);
	while (!st.empty()) {
		Node* node = st.top();
		st.pop();
		if (node != nullptr) {
			st.push(node->leftChild);
			st.push(node->rightChild);
			delete node;
		}
	}
}
template <typename T>
struct AVLTree<T>::Node {
	T element;
	unsigned int length;
	unsigned int heightAVL;
	Node* leftChild;
	Node* rightChild;

	Node(T element = NONE, unsigned int length = 1, unsigned int heightAVL = 0,
		Node* leftChild = nullptr, Node* rightChild = nullptr)
		: element(element), length(length), heightAVL(heightAVL),
		leftChild(leftChild), rightChild(rightChild) {}
};
template <typename T>
unsigned int AVLTree<T>::length() {
	return length(root);
}

template <typename T>
unsigned int AVLTree<T>::length(Node* node) {
	return node != nullptr ? node->length : 0;
}

template <typename T>
int AVLTree<T>::heightAVL() {
	return heightAVL(root);
}
template <typename T>
int AVLTree<T>::heightAVL(Node* node) {
	return node != nullptr ? node->heightAVL : -1;
}

template <typename T>
void AVLTree<T>::update(Node* node) {
	if (node != nullptr) {
		node->heightAVL = 1 + max(heightAVL(node->leftChild), heightAVL(node->rightChild));
		node->length = 1 + length(node->leftChild) + length(node->rightChild);
	}
}

template <typename T>
void AVLTree<T>::rotateLeft(Node*& node) {
	Node* d = node->rightChild;
	node->rightChild = d->leftChild;
	d->leftChild = node;
	update(d->leftChild);
	update(d);
	node = d;
}
template <typename T>
void AVLTree<T>::rotateRight(Node*& node) {
	Node* b = node->leftChild;
	node->leftChild = b->rightChild;
	b->rightChild = node;
	update(b->rightChild);
	update(b);
	node = b;
}
template <typename T>
void AVLTree<T>::balance(Node*& node) {
	int hl = heightAVL(node->leftChild);
	int hr = heightAVL(node->rightChild);
	if (hl - hr < -1) {
		hl = heightAVL(node->rightChild->leftChild);
		hr = heightAVL(node->rightChild->rightChild);
		if (hl > hr) {
			rotateRight(node->rightChild);
		}
		rotateLeft(node);
	}
	else if (hl - hr > 1) {
		hl = heightAVL(node->leftChild->leftChild);
		hr = heightAVL(node->leftChild->rightChild);
		if (hl < hr) {
			rotateLeft(node->leftChild);
		}
		rotateRight(node);
	}
	else {
		update(node);
	}
}
template <typename T>
void AVLTree<T>::add(T element) {
	add(root, element);
}
template <typename T>
void AVLTree<T>::add(Node*& node, T element) {
	if (node == nullptr) {
		node = new Node(element);
	}
	else {
		if (compare(element, node->element) < 0) {
			add(node->leftChild, element);
		}
		else {
			add(node->rightChild, element);
		}
		balance(node);
	}
}

template <typename T>
T AVLTree<T>::search(T key) {
	return search(root, key);
}
template <typename T>
T AVLTree<T>::search(Node* node, T key) {
	
	if (node != nullptr) {

		if (compare(key, node->element) == 0) {
			return node->element;
		}
		else if (compare(key, node->element) < 0) {
			return search(node->leftChild, key);
		}
		else {
			return search(node->rightChild, key);
		}
	}
	else {
		return NONE;
	}
}
