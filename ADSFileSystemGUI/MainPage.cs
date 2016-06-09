using System;
using System.Diagnostics;
using System.IO;
using System.Windows.Forms;

namespace ADSFileSystemGUI
{
    public partial class MainPage : Form
    {
        public MainPage()
        {
            InitializeComponent();
            DialogResult response = MessageBox.Show("Deseja formatar o Disco Virtual?", 
                "Disco Virtual", 
                MessageBoxButtons.YesNo, 
                MessageBoxIcon.Asterisk);
            if (response == DialogResult.Yes)
                ADSIO.formatDisk();
        }
        
        private byte[] fileBuffer;
         
        private void btnFileOpen_Click(object sender, EventArgs e)
        {
            if (ofdFilePicker.ShowDialog() == DialogResult.OK)
            {
                txbExtension.Enabled = true;
                txbFileName.Enabled = true;
                btnSaveInDisk.Enabled = true;
                try
                {
                    lblArquivo.Text = ofdFilePicker.SafeFileName;
                    this.fileBuffer = File.ReadAllBytes(ofdFilePicker.FileName);
                }
                catch (Exception)
                {
                    MessageBox.Show("Erro ao abrir arquivo.");
                }
            }
        }

        private void btnSaveInDisk_Click(object sender, EventArgs e)
        {
            if (txbExtension.Text != "" && txbFileName.Text != "")
            {
                try
                {
                    ADSIO connector = new ADSIO();
                    string fName = txbFileName.Text;
                    string fExt = txbExtension.Text;
                    ADSFile file = connector.OpenFile(fName, fExt, "File");
                    int writed = connector.WriteFile(this.fileBuffer, 1, fileBuffer.Length, file);
                    Debug.WriteLine("Bytes escritos: " + writed);
                    connector.CloseFile(file);
                    tslFeedBack.Text = "Arquivo enviado.";
                }
                catch (Exception ex)
                {
                    Debug.WriteLine("Exception: " + ex.ToString());
                    tslFeedBack.Text = "Erro ao enviar arquivo.";
                }
            }
            else tslFeedBack.Text = "Digite valores válidos.";
        }

        private void btnRecover_Click(object sender, EventArgs e)
        {
            ADSIO connector = new ADSIO();
            ADSFile file = connector.OpenFile(txbRecover.Text, "", "");
            svfSaveFile.FileName = file.Info.name + "." + file.Info.ext;
            if (file.Data == null)
            {
                tslFeedBack.Text = "O arquivo não existe.";
                return;
            }
            if (svfSaveFile.ShowDialog() == DialogResult.OK)
            {
                try
                { 
                    byte[] bFile = connector.ReadFile(1, file.Info.size, file);
                    File.WriteAllBytes(svfSaveFile.FileName, bFile);
                }
                catch (Exception ex)
                {
                    Debug.WriteLine("Exception: " + ex.ToString());
                    tslFeedBack.Text = "Não foi recuperar o arquivo.";
                }
                finally
                {
                    connector.CloseFile(file);
                }
            }
        }

        private void tsiSobre_Click(object sender, EventArgs e)
        {
            About abt = new About();
            abt.Show();
        }

        private void tsiSair_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
