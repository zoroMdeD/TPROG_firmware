using System.IO.Ports;

namespace Tprog_0._1
{
    public partial class Form1 : Form
    {
        private SerialPort serialPort;
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }



        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        // Menu with selection COMport 
        {
            if (cmbCOMPorts.SelectedItem != null)
            {
                string selectedPortName = cmbCOMPorts.SelectedItem.ToString();
                serialPort = new SerialPort(selectedPortName);
                // ƒополнительные настройки COM-порта (например, скорость передачи, биты данных и другие параметры)
                serialPort.BaudRate = 19200; // ѕример установки скорости передачи
                serialPort.DataBits = 8;     // ѕример установки битов данных
                serialPort.ReadTimeout = 500;
            }
        }

        private void btnTest_Click(object sender, EventArgs e)
        {

        }

        private void btnRefresh_Click(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void label3_Click(object sender, EventArgs e)
        {

        }
    }
}