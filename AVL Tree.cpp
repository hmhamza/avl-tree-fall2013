#include <iostream>
using namespace std;

struct Node_Tree{
	int data;
	Node_Tree *left;
	Node_Tree *right;
	int balanceFactor;
};

struct Node_Queue{
	Node_Tree *data_Node;
	Node_Queue *next;
};

class Queue{

	Node_Queue dummyHead;			//dummy head Node_Queue
	Node_Queue *tail;
	int no_of_elements;

public:
	Queue(){
		dummyHead.next = nullptr;
		tail = &dummyHead;
		no_of_elements = 0;
	}

	bool isEmpty(){
		return (dummyHead.next == nullptr);
	}

	bool enqueue(Node_Tree *obj){
		Node_Queue *temp = new Node_Queue;
		temp->data_Node = obj;
		temp->next = nullptr;
		tail->next = temp;
		tail = temp;
		no_of_elements++;
		return true;
	}

	bool dequeue(Node_Tree *&n){
		if (isEmpty())
			return false;
		else{
			Node_Queue *temp = dummyHead.next;
			if (temp == tail)
				tail = &dummyHead;
			n = temp->data_Node;
			dummyHead.next = temp->next;
			delete temp;
			return true;
		}
	}

	~Queue(){
		Node_Tree *n;
		while (!isEmpty())
			dequeue(n);
		tail = nullptr;
	}
};

class BinarySearchTree{
	Node_Tree *root;

public:

	BinarySearchTree(){
		root = nullptr;
	}

	BinarySearchTree(int x){
		Node_Tree *newNode = new Node_Tree;
		newNode->data = x;
		newNode->left = nullptr;
		newNode->right = nullptr;
		newNode->balanceFactor = 0;
		root = newNode;
	}

	BinarySearchTree(BinarySearchTree &obj){
		root = copyTree(obj.root);
	}

	Node_Tree* copyTree(Node_Tree *n){
		if (n == nullptr)
			return nullptr;
		Node_Tree *left = copyTree(n->left);
		Node_Tree *right = copyTree(n->right);
		Node_Tree *newNode = new Node_Tree;
		newNode->data = n->data;
		newNode->balanceFactor = n->balanceFactor;
		newNode->left = left;
		newNode->right = right;
		return newNode;
	}

	Node_Tree* search(int key){
		Node_Tree *curr = root;
		while (curr != nullptr){
			if (curr->data == key)
				return curr;
			else if (key<curr->data)
				curr = curr->left;
			else
				curr = curr->right;
		}
		return nullptr;
	}

	void insert(int n){
		Node_Tree *newNode = new Node_Tree;
		newNode->data = n;
		newNode->left = nullptr;
		newNode->right = nullptr;
		newNode->balanceFactor = 0;

		if (root == nullptr)
			root = newNode;
		else{
			Node_Tree *curr = root,*imbNode=root, *parent_imbNode=nullptr,*temp;
			while (1){
				if (n < curr->data)
				if (curr->left == nullptr){
					curr->left = newNode;
					break;
				}
				else{
					temp = curr;
					curr = curr->left;
					if (curr->balanceFactor != 0){
						imbNode = curr;
						parent_imbNode = temp;
					}
				}

				else
				if (curr->right == nullptr){
					curr->right = newNode;
					break;
				}
				else{
					temp = curr;
					curr = curr->right;
					if (curr->balanceFactor != 0){
						imbNode = curr;
						parent_imbNode = temp;
					}
				}
			}

			temp = imbNode;
			while (imbNode->data != n){
				if (n < imbNode->data){
					imbNode->balanceFactor++;
					imbNode = imbNode->left;
				}
				else
				{
					imbNode->balanceFactor--;
					imbNode = imbNode->right;

				}
			}

			imbNode = temp;
			
			//******************  Left-Left **************
		   	if (imbNode->balanceFactor==2 && n < imbNode->left->data){		
				cout << "\tLeft-Left Imbalance Detected, Doing Left-Left Rotation\n\n";

				if (parent_imbNode == nullptr){					//This step sets B in place of A and afterwards, parent_imbNode is set to B
					root = imbNode->left;
					parent_imbNode = root;
				}
				else if (n < parent_imbNode->data){			
						parent_imbNode->left = imbNode->left;
						parent_imbNode = parent_imbNode->left;
					}
					else{
						parent_imbNode->right = imbNode->left;
						parent_imbNode = parent_imbNode->right;
					}

				imbNode->left = parent_imbNode->right;		//A-Left=B-Right
				if (imbNode->left == nullptr && imbNode->right != nullptr)
					imbNode->balanceFactor = -1;
				else
					imbNode->balanceFactor = 0;

				parent_imbNode->right = imbNode;			//B-Right=A
				parent_imbNode->balanceFactor = 0;
			}					

			//******************  Right-Right **************
			if (imbNode->balanceFactor==-2 && n > imbNode->right->data){		
				cout << "\tRight-Right Imbalance Detected, Doing Right-Right Rotation\n\n";

				if (parent_imbNode == nullptr){				//This step sets B in place of A and afterwards, parent_imbNode is set to B
					root = imbNode->right;
					parent_imbNode = root;
				}
				else if (n < parent_imbNode->data){			
					parent_imbNode->left = imbNode->right;
					parent_imbNode = parent_imbNode->left;
				}
				else{
					parent_imbNode->right = imbNode->right;
					parent_imbNode = parent_imbNode->right;
				}

				imbNode->right = parent_imbNode->left;		//A-Right=B-Left
				if (imbNode->right == nullptr && imbNode->left != nullptr)
					imbNode->balanceFactor = 1;
				else
					imbNode->balanceFactor = 0;

				parent_imbNode->left = imbNode;			//B-Left=A
				parent_imbNode->balanceFactor = 0;

			}

			//******************  Left-Right **************
			if (imbNode->balanceFactor==2 && n > imbNode->left->data){		
				cout << "\tLeft-Right Imbalance Detected, Doing Left-Right Rotation\n\n";

				if (parent_imbNode == nullptr){				//This step sets C in place of A and afterwards, parent_imbNode is set to C
					root = imbNode->left->right;
					parent_imbNode = root;
				}
				else if (n < parent_imbNode->data){			
					parent_imbNode->left = imbNode->left->right;
					parent_imbNode = parent_imbNode->left;
				}
				else{
					parent_imbNode->right = imbNode->left->right;	
					parent_imbNode = parent_imbNode->right;
				}

				imbNode->left->right = parent_imbNode->left;	//B-Right=C-Left
				parent_imbNode->left = imbNode->left;			//C-Left=B

				imbNode->left = parent_imbNode->right;			//A-Left=C-Right
				parent_imbNode->right = imbNode;				//C-Right=A

				parent_imbNode->balanceFactor = 0;

				if (n < parent_imbNode->data){
					parent_imbNode->left->balanceFactor = 0;
					parent_imbNode->right->balanceFactor = -1;
				}
				else if(n > parent_imbNode->data){
					parent_imbNode->right->balanceFactor = 0;
					parent_imbNode->left->balanceFactor = 1;
				}
				else{
					parent_imbNode->right->balanceFactor = 0;
					parent_imbNode->left->balanceFactor = 0;
				}
			}

			//******************  Right-Left **************
			if (imbNode->balanceFactor == -2 && n < imbNode->right->data){
				cout << "\tRight-Left Imbalance Detected, Doing Right-Left Rotation\n\n";

				if (parent_imbNode == nullptr){				//This step sets C in place of A and afterwards, parent_imbNode is set to C
					root = imbNode->right->left;
					parent_imbNode = root;
				}
				else if (n < parent_imbNode->data){			
					parent_imbNode->left = imbNode->right->left;
					parent_imbNode = parent_imbNode->left;
				}
				else{
					parent_imbNode->right = imbNode->right->left;
					parent_imbNode = parent_imbNode->right;
				}

				imbNode->right->left = parent_imbNode->right;	//B-Left=C-Right
				parent_imbNode->right = imbNode->right;			//C-Right=B

				imbNode->right = parent_imbNode->left;			//A-Right=C-Left
				parent_imbNode->left = imbNode;					//C-Left=A

				parent_imbNode->balanceFactor = 0;

				if (n < parent_imbNode->data){
					parent_imbNode->left->balanceFactor = 0;
					parent_imbNode->right->balanceFactor = -1;
				}
				else if (n > parent_imbNode->data){
					parent_imbNode->right->balanceFactor = 0;
					parent_imbNode->left->balanceFactor = 1;
				}
				else{
					parent_imbNode->right->balanceFactor = 0;
					parent_imbNode->left->balanceFactor = 0;
				}
			}
			
		}
	}

	bool deleteNode(int x){
		Node_Tree *del = search(x);
		if (del == nullptr)
			return false;
		Node_Tree *curr = del;
		if (curr->right->left != nullptr){
			curr = curr->right;
			while (curr->left->left != nullptr)
				curr = curr->left;
			del->data = curr->left->data;
			delete curr->left;
			curr->left = nullptr;
		}
		else{
			del->data = curr->right->data;
			delete curr->right;
			curr->right = nullptr;
		}
		return true;
	}

	void print_LevelOrder(){
		cout << "\t\t\tLevel-Order Printing\n\n";
		Queue obj;
		obj.enqueue(root);
		Node_Tree *curr;
		while (!obj.isEmpty()){
			obj.dequeue(curr);
			cout << curr->data << "\tBF: " << curr->balanceFactor << endl;
			if (curr->left != nullptr)
				obj.enqueue(curr->left);
			if (curr->right != nullptr)
				obj.enqueue(curr->right);
		}
	}

	~BinarySearchTree(){
		recursion_Destructor(root);
	}

	void recursion_Destructor(Node_Tree *n){
		if (n->left == nullptr && n->right == nullptr){
			delete n;
			n = nullptr;
			return;
		}
		if (n->left != nullptr)
			recursion_Destructor(n->left);
		if (n->right != nullptr)
			recursion_Destructor(n->right);
		delete n;
		n = nullptr;
	}

};
int main()
{
	BinarySearchTree obj;
	int x;
	while (1){
		system("cls");
		cout << "Enter intger to insert: ";
		cin >> x;
		cout << "\n\n\n";
		if (x == -1)
			break;
		obj.insert(x);
		obj.print_LevelOrder();
		cout << "\n\n\n";
		system("pause");
	}
	return 0;
}