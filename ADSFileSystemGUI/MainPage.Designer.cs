namespace ADSFileSystemGUI
{
    partial class MainPage
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.ofdFilePicker = new System.Windows.Forms.OpenFileDialog();
            this.btnFileOpen = new System.Windows.Forms.Button();
            this.svfSaveFile = new System.Windows.Forms.SaveFileDialog();
            this.btnSaveFile = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // ofdFilePicker
            // 
            this.ofdFilePicker.FileName = "arquivo.txt";
            // 
            // btnFileOpen
            // 
            this.btnFileOpen.Location = new System.Drawing.Point(545, 385);
            this.btnFileOpen.Name = "btnFileOpen";
            this.btnFileOpen.Size = new System.Drawing.Size(75, 23);
            this.btnFileOpen.TabIndex = 0;
            this.btnFileOpen.Text = "Abrir arquivo";
            this.btnFileOpen.UseVisualStyleBackColor = true;
            this.btnFileOpen.Click += new System.EventHandler(this.btnFileOpen_Click);
            // 
            // btnSaveFile
            // 
            this.btnSaveFile.Location = new System.Drawing.Point(626, 385);
            this.btnSaveFile.Name = "btnSaveFile";
            this.btnSaveFile.Size = new System.Drawing.Size(75, 23);
            this.btnSaveFile.TabIndex = 1;
            this.btnSaveFile.Text = "Salvar";
            this.btnSaveFile.UseVisualStyleBackColor = true;
            this.btnSaveFile.Click += new System.EventHandler(this.btnSaveFile_Click);
            // 
            // MainPage
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(713, 420);
            this.Controls.Add(this.btnSaveFile);
            this.Controls.Add(this.btnFileOpen);
            this.Name = "MainPage";
            this.Text = "Form1";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.OpenFileDialog ofdFilePicker;
        private System.Windows.Forms.Button btnFileOpen;
        private System.Windows.Forms.SaveFileDialog svfSaveFile;
        private System.Windows.Forms.Button btnSaveFile;
    }
}

