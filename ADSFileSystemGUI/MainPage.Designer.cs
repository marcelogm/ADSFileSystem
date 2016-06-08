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
            this.lblArquivo = new System.Windows.Forms.Label();
            this.txbFileName = new System.Windows.Forms.TextBox();
            this.gbxSaveFile = new System.Windows.Forms.GroupBox();
            this.label1 = new System.Windows.Forms.Label();
            this.llblSFName = new System.Windows.Forms.Label();
            this.txbExtension = new System.Windows.Forms.TextBox();
            this.btnSaveInDisk = new System.Windows.Forms.Button();
            this.gpbRecuperar = new System.Windows.Forms.GroupBox();
            this.btnRecover = new System.Windows.Forms.Button();
            this.txbRecover = new System.Windows.Forms.TextBox();
            this.gbxSaveFile.SuspendLayout();
            this.gpbRecuperar.SuspendLayout();
            this.SuspendLayout();
            // 
            // ofdFilePicker
            // 
            this.ofdFilePicker.FileName = "arquivo.txt";
            // 
            // btnFileOpen
            // 
            this.btnFileOpen.Location = new System.Drawing.Point(6, 19);
            this.btnFileOpen.Name = "btnFileOpen";
            this.btnFileOpen.Size = new System.Drawing.Size(116, 23);
            this.btnFileOpen.TabIndex = 0;
            this.btnFileOpen.Text = "Enviar Arquivo";
            this.btnFileOpen.UseVisualStyleBackColor = true;
            this.btnFileOpen.Click += new System.EventHandler(this.btnFileOpen_Click);
            // 
            // lblArquivo
            // 
            this.lblArquivo.AutoSize = true;
            this.lblArquivo.Location = new System.Drawing.Point(128, 24);
            this.lblArquivo.Name = "lblArquivo";
            this.lblArquivo.Size = new System.Drawing.Size(112, 13);
            this.lblArquivo.TabIndex = 6;
            this.lblArquivo.Text = "Selecione um arquivo.";
            // 
            // txbFileName
            // 
            this.txbFileName.Location = new System.Drawing.Point(5, 61);
            this.txbFileName.MaxLength = 20;
            this.txbFileName.Name = "txbFileName";
            this.txbFileName.Size = new System.Drawing.Size(146, 20);
            this.txbFileName.TabIndex = 7;
            // 
            // gbxSaveFile
            // 
            this.gbxSaveFile.Controls.Add(this.label1);
            this.gbxSaveFile.Controls.Add(this.llblSFName);
            this.gbxSaveFile.Controls.Add(this.txbExtension);
            this.gbxSaveFile.Controls.Add(this.btnSaveInDisk);
            this.gbxSaveFile.Controls.Add(this.btnFileOpen);
            this.gbxSaveFile.Controls.Add(this.lblArquivo);
            this.gbxSaveFile.Controls.Add(this.txbFileName);
            this.gbxSaveFile.Location = new System.Drawing.Point(12, 12);
            this.gbxSaveFile.Name = "gbxSaveFile";
            this.gbxSaveFile.Size = new System.Drawing.Size(337, 96);
            this.gbxSaveFile.TabIndex = 8;
            this.gbxSaveFile.TabStop = false;
            this.gbxSaveFile.Text = "Salvar no Disco Virtual";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(153, 45);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(51, 13);
            this.label1.TabIndex = 11;
            this.label1.Text = "Extensão";
            // 
            // llblSFName
            // 
            this.llblSFName.AutoSize = true;
            this.llblSFName.Location = new System.Drawing.Point(6, 45);
            this.llblSFName.Name = "llblSFName";
            this.llblSFName.Size = new System.Drawing.Size(89, 13);
            this.llblSFName.TabIndex = 10;
            this.llblSFName.Text = "Nome do Arquivo";
            // 
            // txbExtension
            // 
            this.txbExtension.Location = new System.Drawing.Point(153, 61);
            this.txbExtension.MaxLength = 3;
            this.txbExtension.Name = "txbExtension";
            this.txbExtension.Size = new System.Drawing.Size(51, 20);
            this.txbExtension.TabIndex = 9;
            this.txbExtension.TextChanged += new System.EventHandler(this.txbExtension_TextChanged);
            // 
            // btnSaveInDisk
            // 
            this.btnSaveInDisk.Location = new System.Drawing.Point(214, 59);
            this.btnSaveInDisk.Name = "btnSaveInDisk";
            this.btnSaveInDisk.Size = new System.Drawing.Size(116, 23);
            this.btnSaveInDisk.TabIndex = 8;
            this.btnSaveInDisk.Text = "Enviar Arquivo";
            this.btnSaveInDisk.UseVisualStyleBackColor = true;
            this.btnSaveInDisk.Click += new System.EventHandler(this.btnSaveInDisk_Click);
            // 
            // gpbRecuperar
            // 
            this.gpbRecuperar.Controls.Add(this.btnRecover);
            this.gpbRecuperar.Controls.Add(this.txbRecover);
            this.gpbRecuperar.Location = new System.Drawing.Point(12, 114);
            this.gpbRecuperar.Name = "gpbRecuperar";
            this.gpbRecuperar.Size = new System.Drawing.Size(337, 50);
            this.gpbRecuperar.TabIndex = 9;
            this.gpbRecuperar.TabStop = false;
            this.gpbRecuperar.Text = "Recuperar Arquivo";
            // 
            // btnRecover
            // 
            this.btnRecover.Location = new System.Drawing.Point(214, 17);
            this.btnRecover.Name = "btnRecover";
            this.btnRecover.Size = new System.Drawing.Size(116, 23);
            this.btnRecover.TabIndex = 8;
            this.btnRecover.Text = "Recuperar Arquivo";
            this.btnRecover.UseVisualStyleBackColor = true;
            this.btnRecover.Click += new System.EventHandler(this.btnRecover_Click);
            // 
            // txbRecover
            // 
            this.txbRecover.Location = new System.Drawing.Point(6, 19);
            this.txbRecover.MaxLength = 20;
            this.txbRecover.Name = "txbRecover";
            this.txbRecover.Size = new System.Drawing.Size(202, 20);
            this.txbRecover.TabIndex = 7;
            // 
            // MainPage
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(359, 223);
            this.Controls.Add(this.gpbRecuperar);
            this.Controls.Add(this.gbxSaveFile);
            this.Name = "MainPage";
            this.Text = "Form1";
            this.gbxSaveFile.ResumeLayout(false);
            this.gbxSaveFile.PerformLayout();
            this.gpbRecuperar.ResumeLayout(false);
            this.gpbRecuperar.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.OpenFileDialog ofdFilePicker;
        private System.Windows.Forms.Button btnFileOpen;
        private System.Windows.Forms.SaveFileDialog svfSaveFile;
        private System.Windows.Forms.Label lblArquivo;
        private System.Windows.Forms.TextBox txbFileName;
        private System.Windows.Forms.GroupBox gbxSaveFile;
        private System.Windows.Forms.Button btnSaveInDisk;
        private System.Windows.Forms.GroupBox gpbRecuperar;
        private System.Windows.Forms.Button btnRecover;
        private System.Windows.Forms.TextBox txbRecover;
        private System.Windows.Forms.TextBox txbExtension;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label llblSFName;
    }
}

