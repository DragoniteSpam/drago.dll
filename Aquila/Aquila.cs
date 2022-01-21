using System;
using System.Collections.Generic;

namespace Aquila {
    public class Aquila {
        static int id_record = 0;

        public int ID { get; private set; }

        private Dictionary<int, Node> nodes = new Dictionary<int, Node>();

        public Aquila() {
            ID = id_record++;
        }

        public int AddNode(double data) {
            Node addition = new Node(data);
            nodes[addition.ID] = addition;
            return addition.ID;
        }

        public void RemoveNode(int id) {
            if (nodes.ContainsKey(id)) {
                nodes.Remove(id);
            }
        }
    }

    public class Node {
        static int id_record = 0;

        public int ID { get; private set; }
        public double Data { get; set; }

        private HashSet<Node> connections = new HashSet<Node>();

        public Node(double data) {
            ID = id_record++;
            Data = data;
        }

        public void Connect(Node other) {
            if (!connections.Contains(other)) {
                connections.Add(other);
                other.connections.Add(this);
            }
        }

        public void Disconnect(Node other) {
            connections.Remove(other);
            other.connections.Remove(this);
        }
    }
}
