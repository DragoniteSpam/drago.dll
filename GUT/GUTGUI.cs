using System;
using System.Windows.Forms;


namespace GUT {
    internal class GUTGUI {
        [STAThread]
        static void Main() {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Program());
        }
    }
}
