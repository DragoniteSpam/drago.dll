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
}
