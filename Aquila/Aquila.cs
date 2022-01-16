using RGiesecke.DllExport;
using System;
using System.Collections.Generic;

namespace Aquila {
    public class Aquila {
        [DllExport]
        public static string Version() {
            return "0.0.0";
        }
    }
}
