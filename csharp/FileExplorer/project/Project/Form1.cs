using System;
using System.IO;
using System.Collections;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.ComponentModel;
using System.Globalization;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;


namespace Project
{
    public partial class frmMain : Form
    {
        public frmMain()
        {
            string initFullpath = @"C:\";
        
            InitializeComponent();

            string[] args = System.Environment.GetCommandLineArgs();
            if (args.Length == 2)
            {
                string fullpathRequested = args[1] ;
                if (SetFullpath(fullpathRequested))
                {
                    initFullpath = fullpathRequested;
                }
            }
            
            InitTree(initFullpath);
            
            this.ClientSize = new System.Drawing.Size(800, 1000);
            this.splitContainer2.SplitterDistance = 750 ;
            this.cmbMaxfilesize.SelectedIndex = 0;
        }

        private long GetComboValue(ComboBox cmb)
        {
            string str = cmb.Items[cmb.SelectedIndex].ToString();
            
            int idx ;
            while( ( idx = str.IndexOf(',') ) >= 0 )
            {
                str = str.Remove(idx,1) ;            
            }
            return int.Parse( str );
        }
        

        private void ExitProgram()
        {
            // timtodo OTHER CLEANUP?
            Application.Exit();
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ExitProgram();
        }

        private void InitTree(string dirname)
        {
            Cursor.Current = Cursors.WaitCursor; 

            tvwDir.Nodes.Clear();

            TreeNode node = new TreeNode(dirname);
            tvwDir.Nodes.Add(node);

            AddSubnodes(node);

            tvwDir.Nodes[0].Expand() ;

            Cursor.Current = Cursors.Default; 
        }
        
        private bool IsDirectory( string fullpath )
        {
            if (fullpath == null)
            {
                return false;
            }
            DirectoryInfo dir = new DirectoryInfo(fullpath);

            return dir.Exists;
        }

        private void AddSubnodes(TreeNode node)
        {
            if (node.GetNodeCount(false) != 0)
            {
                return; // already expanded
            }
        
            string fullname = GetFullpath(node);

            if ( !IsDirectory(fullname) )
            {
                return;  // no subnodes if not a directory
            }

            Cursor.Current = Cursors.WaitCursor; 

            // first handle directories
            DirectoryInfo dir = new DirectoryInfo(fullname);
            DirectoryInfo[] dirSubs = dir.GetDirectories();
            ArrayList dirnames = new ArrayList();
            foreach (DirectoryInfo dirSub in dirSubs)
            {
                if ((dirSub.Attributes & FileAttributes.Hidden) != 0)
                {
                    continue;
                }
                dirnames.Add(dirSub.Name);
            }
            dirnames.Sort();
            foreach (string dirname in dirnames)
            {
                TreeNode subNode = new TreeNode(dirname);
                node.Nodes.Add(subNode);
            }

            // next handle files
            FileInfo[] infos = dir.GetFiles();
            ArrayList files = new ArrayList();
            foreach (FileInfo info in infos)
            {
                files.Add(info.Name);
            }
            files.Sort();
            foreach (string file in files)
            {
                TreeNode fileNode = new TreeNode(file);
                node.Nodes.Add(fileNode);
            }
            
            Cursor.Current = Cursors.Default ; 
        }
        
        private string GetFullpath(TreeNode node)
        {
            if (node.Parent == null)
            {
                return node.Text;
            }
            else
            {
                string start = GetFullpath(node.Parent);
                if (!start.EndsWith("\\"))
                {
                    start += "\\";
                }
                return start + node.Text;
            }
        }

        private string BinaryFileToString(string fullpath)
        {
            int totalmax = (int)GetComboValue(cmbMaxfilesize);
            char[] data = new char[totalmax];
            string strReturn = "";
            string strLine = "";
            int linecount = 0;
            int charcount = 0;
            int totalcount = 0;
            const int maxcount = 16;
            string strAscii = "";

            StreamReader streamreader = new StreamReader(fullpath);
            streamreader.Read(data, 0, totalmax);
            
            foreach (byte databyte in data)
            {
                if (charcount == 0)
                {
                    strReturn += String.Format("{0:X8}", totalcount);
                    strReturn += "  ";
                    linecount++;
                    strAscii = "";
                }

                strLine += databyte.ToString("X2") + " ";
                if (databyte >= 0x20 && databyte <= 0x7e)
                {
                    strAscii += (char)databyte;
                }
                else
                {
                    strAscii += '.';
                }
                
                charcount++;
                totalcount++;
                if (charcount >= maxcount)
                {
                    strReturn += strLine;
                    strReturn += "  ";
                    strReturn += strAscii;
                    strReturn += "\n";
                    strLine = "";
                    charcount = 0;
                }

                if (totalcount >= totalmax)
                {
                    strReturn += "\n\nMAX SIZE EXCEEDED\n";
                    break;
                }
            }
            streamreader.Dispose();
            return strReturn;
        }

        private bool IsTextFile(string fullpath)
        {
            const int totalmax = 0x1000;
            char[] data = new char[totalmax];
            bool textfile = true;

            StreamReader streamreader = new StreamReader(fullpath);
            streamreader.Read(data, 0, totalmax);

            foreach (byte databyte in data)
            {
                if ((databyte & 0x80) == 0x80)
                {
                    textfile = false;
                    break;
                }
            }
            streamreader.Dispose();

            return textfile ;
        }

        private string TextFileToString(string fullpath)
        {
            long maxText = GetComboValue(cmbMaxfilesize);
            string filetext = "";
            int count = 0;

            if (!IsTextFile(fullpath))
            {
                return "\n\nBINARY FILE\n";
            }

            StreamReader streamreader = new StreamReader(fullpath);
            string line;

            while ((line = streamreader.ReadLine()) != null)
            {
                filetext += line;
                filetext += "\n";
                count += line.Length;
                if (count > maxText)
                {
                    filetext += "\n\nMAX FILE SIZE EXCEEDED\n";
                    break;
                }
            }
            streamreader.Dispose();
            return filetext;
        }

        public bool IsFileUsedbyAnotherProcess(string filename)
        {
            try
            {
                FileStream fs = 
                File.Open(filename, FileMode.Open, FileAccess.Read, FileShare.None);
                fs.Dispose();
            }

            catch
            {
                return true;
            }
            
            return false;
        }

        private long FileSize(string fullpath)
        {
            FileInfo fileinfo = new FileInfo( strFullpath );
            return fileinfo.Length;
        }

        private string GetFilestring()
        {
            if (chkAutodetect.Checked)
            {
                if( IsTextFile(strFullpath) )
                {
                    chkBinary.Checked = false ;
                }
                else
                {
                    chkBinary.Checked = true ;
                }
            }
        
            if (chkBinary.Checked)
            {
                return BinaryFileToString(strFullpath);
            }
            else
            {
                return TextFileToString(strFullpath);
            }
        }


        private void PopulateFileTxtbox()
        {
            Cursor.Current = Cursors.WaitCursor; 
        
            string str = "";
            
            txtboxFile.Clear();
            if( IsDirectory( strFullpath ) )
            {
                str = "\n\nDIRECTORY.";
            }
            else if (File.Exists(strFullpath) )
            {
                if (IsFileUsedbyAnotherProcess(strFullpath))
                {
                    str = "\n\nFILE IS BEING USED BY ANOTHER PROCESS.";
                }
                else if (FileSize(strFullpath) == 0)
                {
                    str = "\n\nFILE SIZE = 0.";
                }
                else
                {
                    str = GetFilestring() ;
                }
            }
            else
            {
                str = "\n\nUNKNOWN TYPE.";
            }
            txtboxFile.AppendText(str);
            
            Cursor.Current = Cursors.Default;
        }

        private bool DisplayFullpath(string fullpath)
        {
            bool success = SetFullpath(fullpath);
            PopulateFileTxtbox();
            statusLabel.Text = strFullpath;
            SetPropertiesPage();
            txtboxFullpath.Text = strFullpath;

            Application.DoEvents();

            return success;
        }

        private void tvwDir_AfterExpand(object sender, TreeViewEventArgs e)
        {
            TreeNode node = e.Node;

            foreach (TreeNode child in node.Nodes)
            {
                AddSubnodes(child);
            }
        }

        private void tvwDir_AfterSelect(object sender, TreeViewEventArgs e)
        {
            DisplayFullpath(GetFullpath(e.Node));
        }

        private void tvwDir_DragDrop(object sender, System.Windows.Forms.DragEventArgs e)
        {
            string[] files = (string[])e.Data.GetData(DataFormats.FileDrop);
            string fullpath = files[0];

            InitTree(fullpath);
            DisplayFullpath(fullpath) ;            
        }

        private void tvwDir_ItemDrag(object sender, System.Windows.Forms.ItemDragEventArgs e)
        {
            DoDragDrop(e.Item, DragDropEffects.Move);
        }

        private void tvwDir_DragEnter(object sender, System.Windows.Forms.DragEventArgs e)
        {
            e.Effect = DragDropEffects.Move;
        }        

        private void chkBinary_CheckedChanged(object sender, EventArgs e)
        {
            PopulateFileTxtbox();
        }

        private void copyPathToClipboardToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Clipboard.SetDataObject(strFullpath);
        }

        private void changedirMenuItem_Click(object sender, EventArgs e)
        {
            FolderBrowserDialog dlg = new FolderBrowserDialog();

            dlg.ShowNewFolderButton = false;
            dlg.SelectedPath = Path.GetDirectoryName( strFullpath );
            
            DialogResult result=dlg.ShowDialog();
            
            if (result == DialogResult.OK)
            {
                SetFullpath( dlg.SelectedPath );
                InitTree(strFullpath);
            }
        }

        private void SetPropertiesPage()
        {
            FileInfo fileinfo = new FileInfo( strFullpath );
            string strFilesize = "";
            string strDatetime = "";
            bool boolReadonly = false;
            bool boolHidden = false;
            bool boolSystem = false;
            bool boolArchive = false;

            if (fileinfo.Exists)
            {
                long size = fileinfo.Length;
                DateTime datetime = fileinfo.CreationTime ;
                FileAttributes attr = fileinfo.Attributes;

                strFilesize = String.Format("{0:0,0}", size);
                strDatetime = datetime.ToString("ddd dd mm yyyy HH:mm:ss", CultureInfo.InvariantCulture);

                boolReadonly = (attr & FileAttributes.ReadOnly) == FileAttributes.ReadOnly;
                boolHidden = (attr & FileAttributes.Hidden) == FileAttributes.Hidden;
                boolSystem = (attr & FileAttributes.System) == FileAttributes.System;
                boolArchive = (attr & FileAttributes.Archive) == FileAttributes.Archive;
            }

            txtboxFilesize.Text = strFilesize;
            txtboxDatetime.Text = strDatetime;
            
            chkboxReadonly.Checked = boolReadonly;
            chkboxHidden.Checked = boolHidden;
            chkboxSystem.Checked = boolSystem;
            chkboxArchive.Checked = boolArchive;
        }

        private bool SetFullpath(string fullpath)
        {
            bool success = false;
            DirectoryInfo dirinfo = new DirectoryInfo(fullpath);

            if (dirinfo.Exists || File.Exists(fullpath))
            {
                strFullpath = fullpath;
                success = true;
            }
            return success;
        }

        private void HandleInputPathchange()
        {
            string pathname;
            pathname = txtboxFullpath.Text;

            if (SetFullpath(pathname))
            {
                InitTree(pathname);
                DisplayFullpath(pathname);
            }
            else
            {
                MessageBox.Show("Modify path.", "Path doesn't exist!",
                                 MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }          
        }

        private void txtboxFullpath_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == (char)Keys.Return)
            {
                HandleInputPathchange();   
                e.Handled = true;
            }
        }

        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FormAbout frmAbout = new FormAbout();

            frmAbout.ShowDialog();
        }


        private void cmbMaxfilesize_SelectedIndexChanged(object sender, EventArgs e)
        {
            long val = GetComboValue(cmbMaxfilesize);
            PopulateFileTxtbox();
        }
    }
}
