using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ADSFileSystemGUI
{
    public partial class MainPage : Form
    {
        public MainPage()
        {
            ADSIO.formatDisk();
            InitializeComponent();
            MessageBox.Show("Disco Virtual Formatado!");
        }

        private byte[] fileBuffer;
         
        private void btnFileOpen_Click(object sender, EventArgs e)
        {
            if (ofdFilePicker.ShowDialog() == DialogResult.OK)
            {
                try
                {
                    /*
                    lblArquivo.Text = ofdFilePicker.SafeFileName;
                    ADSIO connector = new ADSIO();
                    string fileName = Path.GetFileNameWithoutExtension(ofdFilePicker.SafeFileName);
                    string fileExt = Path.GetExtension(ofdFilePicker.SafeFileName);
                    ADSFile file = connector.OpenFile(fileName, fileExt, "File");

                    byte[] data = File.ReadAllBytes(ofdFilePicker.FileName);
                    int writed = connector.WriteFile(data, 1, data.Length, file);
                    Debug.WriteLine("Bytes escritos: " + writed);
                    connector.CloseFile(file);
                */
                    lblArquivo.Text = ofdFilePicker.SafeFileName;
                    this.fileBuffer = File.ReadAllBytes(ofdFilePicker.FileName);
                }
                catch (Exception)
                {
                    MessageBox.Show("Erro ao abrir arquivo.");
                }
            }
        }

        private void btnTester_Click(object sender, EventArgs e)
        {
            //FileInfo[] array = ADSIO.safeGetFileList();
        }

        

        private void btnSaveInDisk_Click(object sender, EventArgs e)
        {
            if (txbExtension.Text != "" && txbFileName.Text != "")
            {
                ADSIO connector = new ADSIO();
                string fName = txbFileName.Text;
                string fExt = txbExtension.Text;
                ADSFile file = connector.OpenFile(fName, fExt, "File");
                int writed = connector.WriteFile(this.fileBuffer, 1, fileBuffer.Length, file);
                Debug.WriteLine("Bytes escritos: " + writed);
                connector.CloseFile(file);
            }
            

            /*
            if (svfSaveFile.ShowDialog() == DialogResult.OK)
            {
                try
                {
                    ADSIO connector = new ADSIO();
                    string fileName = Path.GetFileNameWithoutExtension(svfSaveFile.FileName);
                    string fileExt = Path.GetExtension(svfSaveFile.FileName);
                    ADSFile file = connector.OpenFile(fileName, fileExt, "File");

                    byte[] bFile = connector.ReadFile(1, file.Info.size, file);
                    connector.CloseFile(file);
                    File.WriteAllBytes(svfSaveFile.FileName, bFile);
                }
                catch (Exception)
                {
                    MessageBox.Show("Erro ao abrir arquivo.");
                }
            }*/
        }

        private void txbExtension_TextChanged(object sender, EventArgs e)
        {

        }
        

        private void btnRecover_Click(object sender, EventArgs e)
        {
            if (svfSaveFile.ShowDialog() == DialogResult.OK)
            {
                try
                {
                    ADSIO connector = new ADSIO();
                    ADSFile file = connector.OpenFile(txbRecover.Text, "", "");
                    byte[] bFile = connector.ReadFile(1, file.Info.size, file);
                    svfSaveFile.FileName = file.Info.name + "." + file.Info.ext;
                    connector.CloseFile(file);
                    File.WriteAllBytes(svfSaveFile.FileName, bFile);
                }
                catch (Exception)
                {
                    MessageBox.Show("Erro ao abrir arquivo.");
                }
            }
        }
    }
}
