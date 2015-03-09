using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using MabinogiResource;

namespace MabinogiResourceTest.net
{
    public partial class Form1 : Form
    {
        private TreeNode m_Root;
        private PackResourceSet m_Pack;

        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog(this) == DialogResult.OK)
            {
                m_Pack = PackResourceSet.CreateFromFile(openFileDialog1.FileName);
                if (m_Pack != null)
                {
                    m_Tree.BeginUpdate();
                    m_Tree.Nodes.Clear();
                    m_Root = m_Tree.Nodes.Add("data");
                    for (uint i = 0; i < m_Pack.GetFileCount(); ++i)
                    {
                        PackResource pr = m_Pack.GetFileByIndex(i);
                        if (pr != null)
                        {
                            InsertFileNode(pr.GetName());
                        }
                    }
                    m_Root.Expand();
                    m_Tree.EndUpdate();
                }
            }
        }

        private void InsertFileNode(string filename)
        {
            string[] paths = filename.Split('\\');
            TreeNode node = m_Root;
            for (uint i = 0; i < paths.Length; ++i)
            {
                int index = node.Nodes.IndexOfKey(paths[i]);
                if (index < 0)
                {
                    node = node.Nodes.Add(paths[i], paths[i]);
                }
                else
                {
                    node = node.Nodes[index];
                }
            }
        }
    }
}
