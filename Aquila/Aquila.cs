using RGiesecke.DllExport;
using System;
using System.Collections.Generic;

namespace Aquila {
    public class GML {
        [DllExport]
        public static string Version() {
            return "0.0.0";
        }
        [DllExport]
        public static double CreateGraph() {
            return 1;
        }
        [DllExport]
        public static double DestroyGraph() {
            return 1;
        }
        [DllExport]
        public static double AddNode(double graph, double data) {
            return 1;
        }
        [DllExport]
        public static double RemoveNode(double graph, double data) {
            return 1;
        }
        [DllExport]
        public static double ConnectNode(double graph, double a, double b) {
            return 1;
        }
        [DllExport]
        public static double DisconnectNodes(double graph, double a, double b) {
            return 1;
        }
        [DllExport]
        public static double ClearNodes(double graph) {
            return 1;
        }
        [DllExport]
        public static double Size(double graph) {
            return 1;
        }
        [DllExport]
        public static double Navigate(double source, double destination) {
            return 1;
        }
    }

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
