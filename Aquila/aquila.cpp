#include <stdlib.h>

#include "aquila.h"

namespace aquila {
	const char* version() {
		return __DRAGO_AQUILA;
	}

	void add_node(int id) {

	}

	void remove_node(int id) {

	}

	void connect_nodes(int a, int b) {

	}

	void disconnect_nodes(int a, int b) {

	}

	void clear_nodes() {

	}

	void navigate() {

	}

	Node::Node(Graph* graph) {
	}

	Node::~Node() {
	}

	std::map<int, Node>* Node::GetConnections() {
		return nullptr;
	}

	void Node::Connect(Node* node) {
	}

	void Node::Disconnect(Node* node) {
	}

	Graph::Graph() {
	}

	Graph::~Graph() {
	}

	int Graph::AddNode() {
		return 0;
	}

	void Graph::RemoveNode(Node* node) {
	}

	void Graph::ConnectNodes(Node* a, Node* b) {
	}

	void Graph::DisconnectNodes(Node* a, Node* b) {
	}

	void Graph::ClearNodes() {
	}

	void Graph::Navigate(Node* source, Node* destination) {
	}
}