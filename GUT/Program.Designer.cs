namespace GUT {
    partial class Program {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing) {
            if (disposing && (components != null)) {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent() {
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.buttonLoad = new System.Windows.Forms.Button();
            this.buttonExport = new System.Windows.Forms.Button();
            this.treeProjectExplorer = new System.Windows.Forms.TreeView();
            this.SuspendLayout();
            // 
            // textBox1
            // 
            this.textBox1.Font = new System.Drawing.Font("Calibri", 16F);
            this.textBox1.Location = new System.Drawing.Point(13, 13);
            this.textBox1.Multiline = true;
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(240, 65);
            this.textBox1.TabIndex = 0;
            this.textBox1.Text = "Click to open and convert a Unity project";
            this.textBox1.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // buttonLoad
            // 
            this.buttonLoad.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.buttonLoad.Font = new System.Drawing.Font("Calibri", 16F);
            this.buttonLoad.Location = new System.Drawing.Point(13, 85);
            this.buttonLoad.Name = "buttonLoad";
            this.buttonLoad.Size = new System.Drawing.Size(240, 47);
            this.buttonLoad.TabIndex = 1;
            this.buttonLoad.Text = "Load";
            this.buttonLoad.UseVisualStyleBackColor = true;
            // 
            // buttonExport
            // 
            this.buttonExport.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.buttonExport.Font = new System.Drawing.Font("Calibri", 16F);
            this.buttonExport.Location = new System.Drawing.Point(13, 138);
            this.buttonExport.Name = "buttonExport";
            this.buttonExport.Size = new System.Drawing.Size(240, 47);
            this.buttonExport.TabIndex = 2;
            this.buttonExport.TabStop = false;
            this.buttonExport.Text = "Export";
            this.buttonExport.UseVisualStyleBackColor = true;
            this.buttonExport.Click += new System.EventHandler(this.button2_Click);
            // 
            // treeProjectExplorer
            // 
            this.treeProjectExplorer.Location = new System.Drawing.Point(260, 13);
            this.treeProjectExplorer.Name = "treeProjectExplorer";
            this.treeProjectExplorer.Size = new System.Drawing.Size(528, 425);
            this.treeProjectExplorer.TabIndex = 3;
            // 
            // Program
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.ControlBox = false;
            this.Controls.Add(this.treeProjectExplorer);
            this.Controls.Add(this.buttonExport);
            this.Controls.Add(this.buttonLoad);
            this.Controls.Add(this.textBox1);
            this.Name = "Program";
            this.Text = "Program";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Button buttonLoad;
        private System.Windows.Forms.Button buttonExport;
        private System.Windows.Forms.TreeView treeProjectExplorer;
    }
}