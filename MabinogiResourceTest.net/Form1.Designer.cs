namespace MabinogiResourceTest.net
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.m_Tree = new System.Windows.Forms.TreeView();
            this.button1 = new System.Windows.Forms.Button();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.SuspendLayout();
            // 
            // m_Tree
            // 
            this.m_Tree.Location = new System.Drawing.Point(12, 12);
            this.m_Tree.Name = "m_Tree";
            this.m_Tree.Size = new System.Drawing.Size(421, 520);
            this.m_Tree.TabIndex = 0;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(173, 538);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(98, 35);
            this.button1.TabIndex = 1;
            this.button1.Text = "加载";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.Filter = "Mabinbogi Pack文件(*.pack)|*.pack";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(445, 575);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.m_Tree);
            this.Name = "Form1";
            this.Text = "测试";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TreeView m_Tree;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
    }
}

