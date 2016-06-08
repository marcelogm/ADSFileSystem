using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
/*
typedef struct  {

    int coisa;
} ADS_FILE;

ADS_FILE* ADS_open( const char* filename);

size_t ADS_write( const void* ptr, size_t size, size_t count, ADS_FILE* stream);

size_t ADS_read(void* ptr, size_t size, size_t count, ADS_FILE* stream);

int ADS_close(ADS_FILE* stream);

ADS_FILE* ADS_open(const char * filename){
	ADS_FILE* f = malloc(sizeof(ADS_FILE));
	return f;
}

size_t ADS_write(const void * ptr, size_t size, size_t count, ADS_FILE * stream){
	return 0;
}

size_t ADS_read(void * ptr, size_t size, size_t count, ADS_FILE * stream){
	return 0;
}

int ADS_close(ADS_FILE * stream){
	return 0;
}

*/

namespace ADSFileSystemGUI
{
    public class ADSFile {
        public ADSFile()
        {
        }
        public string name { get; internal set; }
        public string desc { get; internal set; }
        public int size { get; internal set; }
        public byte content { get; internal set; }
        public IntPtr filePointer { get; internal set; }
    };

    class ADSIO
    {
        private const string dllUri = "C:\\Users\\marce\\documents\\visual studio 2015\\Projects\\ADSFileSystem\\ADSFileSystemGUI\\ADSFileSystem.dll";
        [DllImport(dllUri, CharSet = CharSet.Ansi, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        private extern static unsafe void writeFile(string name, string ext, char* flag, string descr, int size, byte* content);
        [DllImport(dllUri, CharSet = CharSet.Ansi, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        private extern static unsafe bool deleteFile(string name);
        [DllImport(dllUri, CharSet = CharSet.Ansi, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        private extern static unsafe void readFile(string name, byte[] dados);
        [DllImport(dllUri, CharSet = CharSet.Ansi, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        private extern static unsafe bool existsFile(string name);
        [DllImport(dllUri, CharSet = CharSet.Ansi, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public extern static void formatDisk();

        public unsafe static bool safeWriteFile(string name, string ext, char flag, string descr, int size, byte[] content) {
           try {
                byte* pContent;
                fixed (byte* p = content) pContent = p;
                writeFile(name, ext, (char*)&flag, descr, size, pContent);
                return true;
            } catch (Exception e) {
                Debug.WriteLine("Exception: " + e.ToString());
                return false;
            }
        }

        private unsafe static bool safeDeleteFile(string name) {
            return true;
        }

        public unsafe static byte[] safeReadFile(string name, int size) {
            var target = new byte[size];
            readFile(name, target);
            return target;
        }

        private unsafe static bool safeExistsFile(string name) {

            return existsFile(null);
        }
    }
}
