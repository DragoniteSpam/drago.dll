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
            this.buttonLoad = new System.Windows.Forms.Button();
            this.buttonExport = new System.Windows.Forms.Button();
            this.treeProjectExplorer = new System.Windows.Forms.TreeView();
            this.label1 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // buttonLoad
            // 
            this.buttonLoad.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.buttonLoad.Font = new System.Drawing.Font("Calibri", 16F);
            this.buttonLoad.Location = new System.Drawing.Point(14, 114);
            this.buttonLoad.Name = "buttonLoad";
            this.buttonLoad.Size = new System.Drawing.Size(240, 47);
            this.buttonLoad.TabIndex = 1;
            this.buttonLoad.Text = "Load";
            this.buttonLoad.UseVisualStyleBackColor = true;
            this.buttonLoad.Click += new System.EventHandler(this.buttonLoad_Click);
            // 
            // buttonExport
            // 
            this.buttonExport.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.buttonExport.Font = new System.Drawing.Font("Calibri", 16F);
            this.buttonExport.Location = new System.Drawing.Point(13, 167);
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
            // label1
            // 
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 16F);
            this.label1.Location = new System.Drawing.Point(13, 13);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(240, 85);
            this.label1.TabIndex = 4;
            this.label1.Text = "Load a Unity project and save it for use in GameMaker";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.label1.Click += new System.EventHandler(this.label1_Click);
            // 
            // Program
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.treeProjectExplorer);
            this.Controls.Add(this.buttonExport);
            this.Controls.Add(this.buttonLoad);
            this.Name = "Program";
            this.Text = "Grand Unification GUI";
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.Button buttonLoad;
        private System.Windows.Forms.Button buttonExport;
        private System.Windows.Forms.TreeView treeProjectExplorer;
        private System.Windows.Forms.Label label1;
    }
}