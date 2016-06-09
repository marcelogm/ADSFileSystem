using System;
using System.Diagnostics;
using System.Runtime.InteropServices;

namespace ADSFileSystemGUI
{
    public class ADSFile
    {
        public ADSFile(FileInfo info, byte[] data)
        {
            this.Info = info;
            this.Data = data;
        }
        public FileInfo Info { get; set; }
        public byte[] Data { get; set; }
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct FileInfo
    {
        public FileInfo(string name, string desc, string ext, int size)
        {
            this.name = name;
            this.desc = desc;
            this.ext = ext;
            this.size = size;
        }

        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 21)]
        public string name;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 21)]
        public string desc;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 4)]
        public string ext;
        [MarshalAs(UnmanagedType.I4)]
        public int size;
    }

    public class ADSIO
    {
        #region DLLInteraction
        private const string dllUri = "ADSFileSystem.dll";
        [DllImport(dllUri, CharSet = CharSet.Ansi, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        private extern static unsafe void writeFile(string name, string ext, char* flag, string descr, int size, byte* content);
        [DllImport(dllUri, CharSet = CharSet.Ansi, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        private extern static bool deleteFile(string name);
        [DllImport(dllUri, CharSet = CharSet.Ansi, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        private extern static bool readFile(string name, byte[] dados);
        [DllImport(dllUri, CharSet = CharSet.Ansi, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool existsFile(string name);
        [DllImport(dllUri, CharSet = CharSet.Ansi, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public extern static void formatDisk();
        [DllImport(dllUri, CharSet = CharSet.Ansi, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        private extern static IntPtr getFileInfo(string name);

        private unsafe static bool safeWriteFile(string name, string ext, char flag, string descr, int size, byte[] content)
        {
            try
            {
                byte* pContent;
                fixed (byte* p = content) pContent = p;
                writeFile(name, ext, (char*)&flag, descr, size, pContent);
                return true;
            }
            catch (Exception e)
            {
                Debug.WriteLine("Exception: " + e.ToString());
                return false;
            }
        }
        private static bool safeDeleteFile(string name)
        {
            try
            {
                deleteFile(name);
                return true;
            }
            catch (Exception e)
            {
                Debug.WriteLine("Exception: " + e.ToString());
                return false;
            }
        }
        private static byte[] safeReadFile(string name, int size)
        {
            try
            {
                var target = new byte[size];
                readFile(name, target);
                return target;
            }
            catch (Exception e)
            {
                Debug.WriteLine("Exception: " + e.ToString());
                return null;
            }
        }
        #endregion
      
        public ADSFile OpenFile(string fileName, string extension, string description)
        {
            ADSFile file; FileInfo info;
            if (existsFile(fileName))
            {
                IntPtr ptr = getFileInfo(fileName);
                info = (FileInfo)Marshal.PtrToStructure(ptr, typeof(FileInfo));
                byte[] buffer = new byte[info.size];
                readFile(info.name, buffer);
                file = new ADSFile(info, buffer);
            }
            else
            {
                info = new FileInfo(fileName, description, extension, 0);
                file = new ADSFile(info, null);
            }
            return file;
        }

        public int WriteFile(byte[] data, int size, int count, ADSFile stream)
        {
            if (size == 0 || count == 0) return -1;
            try
            {
                byte[] buffer = new byte[size * count];
                int i = 0;
                for (i = 0; i < count; i++)
                    Array.Copy(data, size * i, buffer, size * i, size);
                stream.Info = new FileInfo(stream.Info.name, stream.Info.desc, stream.Info.ext, size * count);
                stream.Data = buffer;
                return i;
            }
            catch (Exception e)
            {
                Debug.WriteLine("Exception: " + e);
                return -1;
            }
        }

        public byte[] ReadFile(int size, int count, ADSFile stream)
        {
            if (size == 0 || count == 0) return null;
            try {
                if ((size * count) > stream.Info.size) return null;
                byte[] buffer = new byte[size * count];
                int i = 0;
                for (i = 0; i < count; i++)
                    Array.Copy(stream.Data, size * i, buffer, size * i, size);
                return buffer;
            }
            catch (Exception e)
            {
                Debug.WriteLine("Exception: " + e);
                return null;
            }
        }

        public bool CloseFile(ADSFile stream)
        {
            if (!stream.Equals(null))
            {
                try
                {
                    return safeWriteFile(stream.Info.name, 
                        stream.Info.ext, 'f', 
                        stream.Info.desc, 
                        stream.Info.size, 
                        stream.Data); 
                }
                catch (Exception e)
                {
                    Debug.WriteLine("Exception: " + e);
                    return false;
                }
            }
            return false;
        }
    }
}
