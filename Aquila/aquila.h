#ifndef __DRAGO_AQUILA
#define __DRAGO_AQUILA "0.0.1"

#include <map>
#include "main/core.h"

namespace aquila {
	const char* version();

	void add_node(int);
	void remove_node(int);
	void connect_nodes(int, int);
	void disconnect_nodes(int, int);
	void clear_nodes();
	void navigate();

	class Graph {
	private:
		std::map<int, Node> nodes;
		int id;
	public:
		Graph();
		int AddNode();
		void RemoveNode(Node* node);
		void ConnectNodes(Node* a, Node* b);
		void DisconnectNodes(Node* a, Node* b);
		void ClearNodes();
		void Navigate(Node* source, Node* destination);
	};

	class Node {
	private:
		int id;
	public:
		Node(Graph* graph);
		std::map<int, Node>* GetConnections();
		void Connect(Node* node);
		void Disconnect(Node* node);
	};
}

#endif