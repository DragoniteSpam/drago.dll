using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace GUT {
    public class GUT {
        public void Reset() {

        }

        public void Open() {
            using (OpenFileDialog finder = new OpenFileDialog()) {
                finder.Filter = "Unity scenes (*.unity)|*.unity";

                if (finder.ShowDialog() == DialogResult.OK) {
                    Reset();
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
    }
}
