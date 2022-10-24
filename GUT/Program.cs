using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace GUT {
    public partial class Program : Form {
        private GUT data = new GUT();
        public Program() {
            InitializeComponent();
        }

        private void button2_Click(object sender, EventArgs e) {

        }

        private void buttonLoad_Click(object sender, EventArgs e) {
            using (OpenFileDialog finder = new OpenFileDialog()) {
                finder.Filter = "Unity scenes (*.unity)|*.unity";

                if (finder.ShowDialog() == DialogResult.OK) {
                    data.Open(finder.FileName);
                }
            }
        }

        private void label1_Click(object sender, EventArgs e) {
            using (SaveFileDialog finder = new SaveFileDialog()) {
                finder.Filter = /* come up with a file extension and format later */"";

                if (finder.ShowDialog() == DialogResult.OK) {
                    data.Export(finder.FileName);
                }
            }
        }
    }
}
