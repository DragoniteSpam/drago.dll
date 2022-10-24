using System;
using System.Collections.Generic;
using System.Windows.Forms;
using System.IO;

namespace GUT {
    public class GUT {
        public void Reset() {

        }

        public void Open(string filename) {
            Reset();
            DirectoryInfo projectRootFolder = new DirectoryInfo(Path.GetDirectoryName(filename));
            while (projectRootFolder != null && projectRootFolder.Name != "Assets") {
                projectRootFolder = projectRootFolder.Parent;
            }
        }

        public void Export(string filename) {
        }
    }
}
