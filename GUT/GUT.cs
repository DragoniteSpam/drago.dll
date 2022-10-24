using System;
using System.Collections.Generic;
using System.Windows.Forms;
using System.IO;

namespace GUT {
    public class GUT {
        public void Reset() {

        }

        public void Open() {
            using (OpenFileDialog finder = new OpenFileDialog()) {
                finder.Filter = "Unity scenes (*.unity)|*.unity";

                if (finder.ShowDialog() == DialogResult.OK) {
                    Reset();
                    Extract(finder.FileName);
                }
            }
        }

        public void Export() {
            using (SaveFileDialog finder = new SaveFileDialog()) {
                finder.Filter = /* come up with a file extension and format later */"";

                if (finder.ShowDialog() == DialogResult.OK) {

                }
            }
        }

        private void Extract(string filename) {
            DirectoryInfo projectRootFolder = new DirectoryInfo(Path.GetDirectoryName(filename));
            while (projectRootFolder != null && projectRootFolder.Name != "Assets") {
                projectRootFolder = projectRootFolder.Parent;
            }
        }
    }
}
