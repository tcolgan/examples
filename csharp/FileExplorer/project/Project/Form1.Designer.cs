namespace Project
{
    partial class frmMain
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(frmMain));
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.changedirMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.helpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.aboutToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.statusStrip = new System.Windows.Forms.StatusStrip();
            this.statusLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripDropDownButton1 = new System.Windows.Forms.ToolStripDropDownButton();
            this.copyPathToClipboardToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.tvwDir = new System.Windows.Forms.TreeView();
            this.splitContainer2 = new System.Windows.Forms.SplitContainer();
            this.txtboxFile = new System.Windows.Forms.RichTextBox();
            this.tabcntl = new System.Windows.Forms.TabControl();
            this.tabpageProperties = new System.Windows.Forms.TabPage();
            this.label8 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.chkboxArchive = new System.Windows.Forms.CheckBox();
            this.chkboxSystem = new System.Windows.Forms.CheckBox();
            this.chkboxHidden = new System.Windows.Forms.CheckBox();
            this.chkboxReadonly = new System.Windows.Forms.CheckBox();
            this.txtboxDatetime = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.txtboxFilesize = new System.Windows.Forms.TextBox();
            this.tabpageConfig = new System.Windows.Forms.TabPage();
            this.chkAutodetect = new System.Windows.Forms.CheckBox();
            this.label4 = new System.Windows.Forms.Label();
            this.cmbMaxfilesize = new System.Windows.Forms.ComboBox();
            this.txtboxFullpath = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.chkBinary = new System.Windows.Forms.CheckBox();
            this.menuStrip1.SuspendLayout();
            this.statusStrip.SuspendLayout();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.splitContainer2.Panel1.SuspendLayout();
            this.splitContainer2.Panel2.SuspendLayout();
            this.splitContainer2.SuspendLayout();
            this.tabcntl.SuspendLayout();
            this.tabpageProperties.SuspendLayout();
            this.tabpageConfig.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.helpToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(544, 24);
            this.menuStrip1.TabIndex = 2;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.changedirMenuItem,
            this.exitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(35, 20);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // changedirMenuItem
            // 
            this.changedirMenuItem.Name = "changedirMenuItem";
            this.changedirMenuItem.Size = new System.Drawing.Size(184, 22);
            this.changedirMenuItem.Text = "Change Directory ...";
            this.changedirMenuItem.Click += new System.EventHandler(this.changedirMenuItem_Click);
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(184, 22);
            this.exitToolStripMenuItem.Text = "Exit";
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
            // 
            // helpToolStripMenuItem
            // 
            this.helpToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.aboutToolStripMenuItem});
            this.helpToolStripMenuItem.Name = "helpToolStripMenuItem";
            this.helpToolStripMenuItem.Size = new System.Drawing.Size(40, 20);
            this.helpToolStripMenuItem.Text = "Help";
            // 
            // aboutToolStripMenuItem
            // 
            this.aboutToolStripMenuItem.Name = "aboutToolStripMenuItem";
            this.aboutToolStripMenuItem.Size = new System.Drawing.Size(114, 22);
            this.aboutToolStripMenuItem.Text = "About";
            this.aboutToolStripMenuItem.Click += new System.EventHandler(this.aboutToolStripMenuItem_Click);
            // 
            // statusStrip
            // 
            this.statusStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.statusLabel,
            this.toolStripDropDownButton1});
            this.statusStrip.Location = new System.Drawing.Point(0, 410);
            this.statusStrip.Name = "statusStrip";
            this.statusStrip.Size = new System.Drawing.Size(544, 22);
            this.statusStrip.TabIndex = 3;
            this.statusStrip.Text = "statusStrip1";
            // 
            // statusLabel
            // 
            this.statusLabel.Name = "statusLabel";
            this.statusLabel.Size = new System.Drawing.Size(62, 17);
            this.statusLabel.Text = "statusLabel";
            // 
            // toolStripDropDownButton1
            // 
            this.toolStripDropDownButton1.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripDropDownButton1.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.copyPathToClipboardToolStripMenuItem});
            this.toolStripDropDownButton1.Image = ((System.Drawing.Image)(resources.GetObject("toolStripDropDownButton1.Image")));
            this.toolStripDropDownButton1.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripDropDownButton1.Name = "toolStripDropDownButton1";
            this.toolStripDropDownButton1.Size = new System.Drawing.Size(29, 20);
            this.toolStripDropDownButton1.Text = "toolStripDropDownButton1";
            // 
            // copyPathToClipboardToolStripMenuItem
            // 
            this.copyPathToClipboardToolStripMenuItem.Name = "copyPathToClipboardToolStripMenuItem";
            this.copyPathToClipboardToolStripMenuItem.Size = new System.Drawing.Size(196, 22);
            this.copyPathToClipboardToolStripMenuItem.Text = "Copy Path to Clipboard";
            this.copyPathToClipboardToolStripMenuItem.Click += new System.EventHandler(this.copyPathToClipboardToolStripMenuItem_Click);
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.Location = new System.Drawing.Point(0, 24);
            this.splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.splitContainer1.Panel1.Controls.Add(this.tvwDir);
            this.splitContainer1.Panel1.Margin = new System.Windows.Forms.Padding(5);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.splitContainer2);
            this.splitContainer1.Size = new System.Drawing.Size(544, 386);
            this.splitContainer1.SplitterDistance = 158;
            this.splitContainer1.TabIndex = 4;
            // 
            // tvwDir
            // 
            this.tvwDir.AllowDrop = true;
            this.tvwDir.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tvwDir.Location = new System.Drawing.Point(0, 0);
            this.tvwDir.Name = "tvwDir";
            this.tvwDir.Size = new System.Drawing.Size(158, 386);
            this.tvwDir.TabIndex = 0;
            this.tvwDir.DragDrop += new System.Windows.Forms.DragEventHandler(this.tvwDir_DragDrop);
            this.tvwDir.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.tvwDir_AfterSelect);
            this.tvwDir.DragEnter += new System.Windows.Forms.DragEventHandler(this.tvwDir_DragEnter);
            this.tvwDir.AfterExpand += new System.Windows.Forms.TreeViewEventHandler(this.tvwDir_AfterExpand);
            this.tvwDir.ItemDrag += new System.Windows.Forms.ItemDragEventHandler(this.tvwDir_ItemDrag);
            // 
            // splitContainer2
            // 
            this.splitContainer2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer2.Location = new System.Drawing.Point(0, 0);
            this.splitContainer2.Name = "splitContainer2";
            this.splitContainer2.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer2.Panel1
            // 
            this.splitContainer2.Panel1.BackColor = System.Drawing.SystemColors.ControlDark;
            this.splitContainer2.Panel1.Controls.Add(this.txtboxFile);
            this.splitContainer2.Panel1.Margin = new System.Windows.Forms.Padding(5);
            // 
            // splitContainer2.Panel2
            // 
            this.splitContainer2.Panel2.Controls.Add(this.tabcntl);
            this.splitContainer2.Panel2.Margin = new System.Windows.Forms.Padding(5);
            this.splitContainer2.Size = new System.Drawing.Size(382, 386);
            this.splitContainer2.SplitterDistance = 183;
            this.splitContainer2.TabIndex = 0;
            // 
            // txtboxFile
            // 
            this.txtboxFile.BackColor = System.Drawing.SystemColors.InactiveCaption;
            this.txtboxFile.Cursor = System.Windows.Forms.Cursors.Arrow;
            this.txtboxFile.DetectUrls = false;
            this.txtboxFile.Dock = System.Windows.Forms.DockStyle.Fill;
            this.txtboxFile.Font = new System.Drawing.Font("Courier New", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.txtboxFile.Location = new System.Drawing.Point(0, 0);
            this.txtboxFile.Name = "txtboxFile";
            this.txtboxFile.Size = new System.Drawing.Size(382, 183);
            this.txtboxFile.TabIndex = 0;
            this.txtboxFile.Text = "";
            this.txtboxFile.WordWrap = false;
            // 
            // tabcntl
            // 
            this.tabcntl.Controls.Add(this.tabpageProperties);
            this.tabcntl.Controls.Add(this.tabpageConfig);
            this.tabcntl.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tabcntl.Location = new System.Drawing.Point(0, 0);
            this.tabcntl.Name = "tabcntl";
            this.tabcntl.SelectedIndex = 0;
            this.tabcntl.Size = new System.Drawing.Size(382, 199);
            this.tabcntl.TabIndex = 0;
            // 
            // tabpageProperties
            // 
            this.tabpageProperties.AutoScroll = true;
            this.tabpageProperties.Controls.Add(this.label8);
            this.tabpageProperties.Controls.Add(this.label7);
            this.tabpageProperties.Controls.Add(this.label6);
            this.tabpageProperties.Controls.Add(this.label5);
            this.tabpageProperties.Controls.Add(this.chkboxArchive);
            this.tabpageProperties.Controls.Add(this.chkboxSystem);
            this.tabpageProperties.Controls.Add(this.chkboxHidden);
            this.tabpageProperties.Controls.Add(this.chkboxReadonly);
            this.tabpageProperties.Controls.Add(this.txtboxDatetime);
            this.tabpageProperties.Controls.Add(this.label2);
            this.tabpageProperties.Controls.Add(this.label1);
            this.tabpageProperties.Controls.Add(this.txtboxFilesize);
            this.tabpageProperties.Location = new System.Drawing.Point(4, 22);
            this.tabpageProperties.Name = "tabpageProperties";
            this.tabpageProperties.Padding = new System.Windows.Forms.Padding(3);
            this.tabpageProperties.Size = new System.Drawing.Size(374, 173);
            this.tabpageProperties.TabIndex = 0;
            this.tabpageProperties.Text = "Properties";
            this.tabpageProperties.UseVisualStyleBackColor = true;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(32, 117);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(43, 13);
            this.label8.TabIndex = 11;
            this.label8.Text = "Archive";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(32, 100);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(41, 13);
            this.label7.TabIndex = 10;
            this.label7.Text = "System";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(32, 83);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(41, 13);
            this.label6.TabIndex = 9;
            this.label6.Text = "Hidden";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(32, 66);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(55, 13);
            this.label5.TabIndex = 8;
            this.label5.Text = "Read only";
            // 
            // chkboxArchive
            // 
            this.chkboxArchive.AutoSize = true;
            this.chkboxArchive.Enabled = false;
            this.chkboxArchive.Location = new System.Drawing.Point(11, 117);
            this.chkboxArchive.Name = "chkboxArchive";
            this.chkboxArchive.Size = new System.Drawing.Size(15, 14);
            this.chkboxArchive.TabIndex = 7;
            this.chkboxArchive.UseVisualStyleBackColor = true;
            // 
            // chkboxSystem
            // 
            this.chkboxSystem.AutoSize = true;
            this.chkboxSystem.Enabled = false;
            this.chkboxSystem.Location = new System.Drawing.Point(11, 100);
            this.chkboxSystem.Name = "chkboxSystem";
            this.chkboxSystem.Size = new System.Drawing.Size(15, 14);
            this.chkboxSystem.TabIndex = 6;
            this.chkboxSystem.UseVisualStyleBackColor = true;
            // 
            // chkboxHidden
            // 
            this.chkboxHidden.AutoSize = true;
            this.chkboxHidden.Enabled = false;
            this.chkboxHidden.Location = new System.Drawing.Point(11, 83);
            this.chkboxHidden.Name = "chkboxHidden";
            this.chkboxHidden.Size = new System.Drawing.Size(15, 14);
            this.chkboxHidden.TabIndex = 5;
            this.chkboxHidden.UseVisualStyleBackColor = true;
            // 
            // chkboxReadonly
            // 
            this.chkboxReadonly.AutoSize = true;
            this.chkboxReadonly.Enabled = false;
            this.chkboxReadonly.Location = new System.Drawing.Point(11, 66);
            this.chkboxReadonly.Name = "chkboxReadonly";
            this.chkboxReadonly.Size = new System.Drawing.Size(15, 14);
            this.chkboxReadonly.TabIndex = 4;
            this.chkboxReadonly.UseVisualStyleBackColor = true;
            // 
            // txtboxDatetime
            // 
            this.txtboxDatetime.Location = new System.Drawing.Point(108, 34);
            this.txtboxDatetime.Name = "txtboxDatetime";
            this.txtboxDatetime.ReadOnly = true;
            this.txtboxDatetime.Size = new System.Drawing.Size(198, 20);
            this.txtboxDatetime.TabIndex = 3;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(3, 34);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(100, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "Creation Date/Time";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(3, 8);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(46, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "File Size";
            // 
            // txtboxFilesize
            // 
            this.txtboxFilesize.Location = new System.Drawing.Point(108, 5);
            this.txtboxFilesize.Name = "txtboxFilesize";
            this.txtboxFilesize.ReadOnly = true;
            this.txtboxFilesize.Size = new System.Drawing.Size(198, 20);
            this.txtboxFilesize.TabIndex = 0;
            // 
            // tabpageConfig
            // 
            this.tabpageConfig.Controls.Add(this.chkAutodetect);
            this.tabpageConfig.Controls.Add(this.label4);
            this.tabpageConfig.Controls.Add(this.cmbMaxfilesize);
            this.tabpageConfig.Controls.Add(this.txtboxFullpath);
            this.tabpageConfig.Controls.Add(this.label3);
            this.tabpageConfig.Controls.Add(this.chkBinary);
            this.tabpageConfig.Location = new System.Drawing.Point(4, 22);
            this.tabpageConfig.Name = "tabpageConfig";
            this.tabpageConfig.Padding = new System.Windows.Forms.Padding(3);
            this.tabpageConfig.Size = new System.Drawing.Size(374, 173);
            this.tabpageConfig.TabIndex = 1;
            this.tabpageConfig.Text = "Config";
            this.tabpageConfig.UseVisualStyleBackColor = true;
            // 
            // chkAutodetect
            // 
            this.chkAutodetect.AutoSize = true;
            this.chkAutodetect.Checked = true;
            this.chkAutodetect.CheckState = System.Windows.Forms.CheckState.Checked;
            this.chkAutodetect.Location = new System.Drawing.Point(67, 6);
            this.chkAutodetect.Name = "chkAutodetect";
            this.chkAutodetect.Size = new System.Drawing.Size(104, 17);
            this.chkAutodetect.TabIndex = 6;
            this.chkAutodetect.Text = "Auto detect type";
            this.chkAutodetect.UseVisualStyleBackColor = true;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(9, 59);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(69, 13);
            this.label4.TabIndex = 5;
            this.label4.Text = "Max File Size";
            // 
            // cmbMaxfilesize
            // 
            this.cmbMaxfilesize.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbMaxfilesize.FormattingEnabled = true;
            this.cmbMaxfilesize.Items.AddRange(new object[] {
            "1,000",
            "10,000",
            "100,000",
            "1,000,000",
            "10,000,000",
            "100,000,000"});
            this.cmbMaxfilesize.Location = new System.Drawing.Point(84, 53);
            this.cmbMaxfilesize.Name = "cmbMaxfilesize";
            this.cmbMaxfilesize.Size = new System.Drawing.Size(121, 21);
            this.cmbMaxfilesize.TabIndex = 4;
            this.cmbMaxfilesize.SelectedIndexChanged += new System.EventHandler(this.cmbMaxfilesize_SelectedIndexChanged);
            // 
            // txtboxFullpath
            // 
            this.txtboxFullpath.Location = new System.Drawing.Point(62, 27);
            this.txtboxFullpath.Name = "txtboxFullpath";
            this.txtboxFullpath.Size = new System.Drawing.Size(309, 20);
            this.txtboxFullpath.TabIndex = 3;
            this.txtboxFullpath.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.txtboxFullpath_KeyPress);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(7, 31);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(48, 13);
            this.label3.TabIndex = 2;
            this.label3.Text = "Full Path";
            // 
            // chkBinary
            // 
            this.chkBinary.AutoSize = true;
            this.chkBinary.Location = new System.Drawing.Point(6, 6);
            this.chkBinary.Name = "chkBinary";
            this.chkBinary.Size = new System.Drawing.Size(55, 17);
            this.chkBinary.TabIndex = 1;
            this.chkBinary.Text = "Binary";
            this.chkBinary.UseVisualStyleBackColor = true;
            this.chkBinary.CheckedChanged += new System.EventHandler(this.chkBinary_CheckedChanged);
            // 
            // frmMain
            // 
            this.ClientSize = new System.Drawing.Size(544, 432);
            this.Controls.Add(this.splitContainer1);
            this.Controls.Add(this.statusStrip);
            this.Controls.Add(this.menuStrip1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "frmMain";
            this.Text = "File Explorer";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.statusStrip.ResumeLayout(false);
            this.statusStrip.PerformLayout();
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            this.splitContainer1.ResumeLayout(false);
            this.splitContainer2.Panel1.ResumeLayout(false);
            this.splitContainer2.Panel2.ResumeLayout(false);
            this.splitContainer2.ResumeLayout(false);
            this.tabcntl.ResumeLayout(false);
            this.tabpageProperties.ResumeLayout(false);
            this.tabpageProperties.PerformLayout();
            this.tabpageConfig.ResumeLayout(false);
            this.tabpageConfig.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem changedirMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.StatusStrip statusStrip;
        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.SplitContainer splitContainer2;
        private System.Windows.Forms.TreeView tvwDir;
        private System.Windows.Forms.RichTextBox txtboxFile;
        private System.Windows.Forms.CheckBox chkBinary;
        private System.Windows.Forms.ToolStripStatusLabel statusLabel;
        private System.Windows.Forms.ToolStripDropDownButton toolStripDropDownButton1;
        private System.Windows.Forms.ToolStripMenuItem copyPathToClipboardToolStripMenuItem;
        private string strFullpath;
        private System.Windows.Forms.TabControl tabcntl;
        private System.Windows.Forms.TabPage tabpageProperties;
        private System.Windows.Forms.TabPage tabpageConfig;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox txtboxFilesize;
        private System.Windows.Forms.TextBox txtboxDatetime;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.CheckBox chkboxReadonly;
        private System.Windows.Forms.CheckBox chkboxHidden;
        private System.Windows.Forms.CheckBox chkboxSystem;
        private System.Windows.Forms.CheckBox chkboxArchive;
        private System.Windows.Forms.TextBox txtboxFullpath;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ToolStripMenuItem helpToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem aboutToolStripMenuItem;
        private System.Windows.Forms.ComboBox cmbMaxfilesize;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.CheckBox chkAutodetect;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label5;
    }
}

