using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
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
        }

        private void btnFileOpen_Click(object sender, EventArgs e)
        {
            ofdFilePicker.ShowDialog();
            string fileName = ofdFilePicker.SafeFileName;
            string fullyFileName = ofdFilePicker.FileName;
            byte[] content = File.ReadAllBytes(fullyFileName);

            ADSIO.safeWriteFile(fileName, "png", 'r', "Um arquivo", content.Length, content);
        }

        private void btnSaveFile_Click(object sender, EventArgs e)
        {
            svfSaveFile.ShowDialog();
            string fileName = ofdFilePicker.SafeFileName;
            string fullyFileName = ofdFilePicker.FileName;
            byte[] content = File.ReadAllBytes(fullyFileName);
            byte[] newByteContent = ADSIO.safeReadFile(fileName, content.Length);
            File.WriteAllBytes(svfSaveFile.FileName, newByteContent);
        }
    }
}
