/*
 * This project gives a class for making an arbitrary tree and a main
 * method for creating and displaying information on a tree. SDG
 *
 *		 author: David Gilstad
 *		created: April 2, 2019
 */
#include <iostream>
using namespace std;

/*
 * This class is an arbitrary tree using parent array representation. In this
 * representation the tree's nodes are labeled using ints, and for a tree of size
 * n the ints used are 0 to n-1 (e.g. size = 5, then the nodes are 0, 1, 2, 3, 4).
 * These labels are used as indexes in an array, and the parents of each node are
 * held at that index (e.g. 3 has parent 5, so array[3] = 5).
 */
class Tree {
protected:
	int size, // # of nodes in the tree
		root, // the root of the tree
		*parent; // array holding parents of each node
public:
	/* Default constructor. Initializes the parent array to a size of 0. */
	Tree() { parent = new int[size = 0]; }

	/* Non-default constructor. Initializes the parent array to the given size. */
	Tree(int numNodes) { parent = new int[size = numNodes]; }

	/* Copy constructor. */
	Tree(const Tree &obj) {
		parent = new int[size = obj.size];
		for (int i = 0; i < obj.size; i++) parent[i] = obj.parent[i];
	}

	/* Destructor. */
	~Tree() { delete[] parent; }

	/* Returns the root of the tree. */
	int Root() { return root; }

	/* Returns the parent of the given node. */
	int Parent(int node) { return parent[node]; }

	/*
	 * Returns the level of the given node. The root is at the 1st level, its
	 * children are at the 2nd, their children are at the 3rd, and so on.
	 */
	int Level(int node) {
		int level; // start at level 1, add 1 for every level above it
		for (level = 1; node != Root(); level++) node = Parent(node);
		return level;
	}

	/* Returns the height of the tree (i.e. how many levels the tree has). */
	int height() {
		int max = 0; // find the highest level in the tree.
		for (int i = 0; i < size; i++) if (Level(i) > max) max = Level(i);
		return max; // the highest level is the number of levels in the tree
	}

	/* Returns the least common or "youngest" ancestor of the given two nodes. */
	int LCA(int n1, int n2) {
		if (n1 == n2) return n1; // when n1 = n2, their ancestor matches
		// an ancestor is always older, so always move the younger node up
		else if (Level(n1) > Level(n2)) return LCA(Parent(n1), n2); // move n1 up
		else return LCA(n1, Parent(n2)); // move n2 up
	}

	/* Sets the root of the tree to the given node. */
	void setRoot(int node) { root = node; }

	/* Sets the given node in the parent array to the given parent node. */
	void setParent(int node, int nodeParent) { parent[node] = nodeParent; }

	/* Prints out all the children of the given node. */
	void Children(int node) {
		for (int i = 0; i < size; i++) if (node == Parent(i)) cout << i << " ";
		cout << endl;
	}

	/* Prints out all the siblings of the given node. */
	void Siblings(int node) {
		for (int i = 0, index = 0; i < size; i++)
			// make sure they share the same parent and i isn't the node itself
			if (Parent(node) == Parent(i) && i != node) cout << i << " ";
		cout << endl;
	}

	/* Prints out all the nodes at the given level. */
	void nodesAtLevel(int level) {
		for (int i = 0; i < size; i++) if (level == Level(i)) cout << i << " ";
		cout << endl;
	}

	/* Prints out the preorder of the tree with the given node as the root. */
	void preorder(int node) {
		cout << node << " "; // print the root, then preorder each of its children
		for (int i = 0; i < size; i++) if (node == Parent(i)) preorder(i);
	}

	/* Overloaded <<. Prints the tree in the form: 0:parent(0)  1:parent(1), etc. */
	friend ostream& operator<< (ostream &s, Tree &T) {
		for (int i = 0; i < T.size; i++) s << i << ":" << T.Parent(i) << "  ";
		return s;
	}
};

/* Main method. Reads in a tree, then displays information about it. */
int main() {
	int numNodes, node, parent;

	cin >> numNodes; // read in numNodes and make a tree of that size
	Tree *myTree = new Tree(numNodes);

	// read in every node and its parent, then put them in myTree
	for (int i = 0; i < numNodes; i++) {
		cin >> node >> parent; // read in the node and parent
		myTree->setParent(node, parent); // set them in the parent array
		if (parent == -1) myTree->setRoot(node); // the root has parent -1
	}

	// create a copy of myTree
	Tree *newTree = new Tree(*myTree);

	// perform operations to show all the methods function properly
	cout << "The tree read in is: " << endl << *myTree << endl;
	cout << "The copied tree is: " << endl << *newTree << endl;
	cout << "The root of the tree is: " << myTree->Root() << endl;
	cout << "The LCA of nodes 3 and 8 is: " << newTree->LCA(3, 8) << endl;
	cout << "The children of node 10 are: " << endl; myTree->Children(10);
	cout << "The siblings of node 2 are: " << endl; myTree->Siblings(2);
	cout << "The nodes at level 3 are: " << endl; myTree->nodesAtLevel(3);
	cout << "The height of the tree is: " << myTree->height() << endl;
	cout << "The level of node 5 in the tree is: " << myTree->Level(5) << endl;
	cout << "The preorder of the tree is: " << endl;
	myTree->preorder(myTree->Root()); cout << endl;

	delete myTree; delete newTree;
	system("pause"); return 0;
}