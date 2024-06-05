using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;
using System.Threading;                 // lib for delay

namespace Tractor_0._1
{
    public partial class Form1 : Form
    {
        private SerialPort serialPort;
        // Создаем список названий
        private List<string> namesList = new List<string>();

        public Form1()
        {
            InitializeComponent();
            // Добавляем названия в список
            namesList.Add("CY62128ELL-45SXI");
            namesList.Add("CY7C1019DV33-10ZSXI");
            namesList.Add("CY7C1069G30-10ZSXI");
            namesList.Add("MB85RS512T");
            

            // Привязываем список к ComboBox
            memoryBox.DataSource = namesList;
        }

        private void Button1_Click(object sender, EventArgs e)
        // button REFRESH
        {
            cmbCOMPorts.Items.Clear();
            string[] portNames = SerialPort.GetPortNames();

            if (portNames.Length > 0)
            {
                cmbCOMPorts.Items.AddRange(portNames);
                cmbCOMPorts.SelectedIndex = 0;
            }
            else
            {
                MessageBox.Show("COM-порты не найдены. Подключите устройство и перезапустите приложение.");
            }
        }

        private void cmbCOMPorts_SelectedIndexChanged(object sender, EventArgs e)
        // Menu with selection COMport 
        {
            if (cmbCOMPorts.SelectedItem != null)
            {
                string selectedPortName = cmbCOMPorts.SelectedItem.ToString();
                serialPort = new SerialPort(selectedPortName);
                // Дополнительные настройки COM-порта (например, скорость передачи, биты данных и другие параметры)
                serialPort.BaudRate = 19200; // Пример установки скорости передачи
                serialPort.DataBits = 8;     // Пример установки битов данных
                serialPort.ReadTimeout = 500;
            }
        }

        private async void btnTest_Click(object sender, EventArgs e)
        // button Test
        {
            if (serialPort != null && !serialPort.IsOpen)
            {
                serialPort.Open();
                // Получаем выбранную строку из memoryBox
                int selectedIndex = memoryBox.SelectedIndex;
                if (selectedIndex == 0)
                    Test_CY62128ELL45SXI();
                else if (selectedIndex == 1)
                    CY7C1019DV3310ZSXI();
                else if (selectedIndex == 2)
                    CY7C1069G30();
                else if (selectedIndex == 3)
                    MB85RS512T();



                    // Читаем данные из порта
                    string receivedData = await WaitForResponse(serialPort);
                errorBox.Text = receivedData;
                serialPort.Close();
            }
            else
            {
                // COM-порт не был выбран или уже открыт
                MessageBox.Show("Выберите COM-порт и убедитесь, что он закрыт.");
            }

        }

        
        void Test_CY62128ELL45SXI ()
        {
            if (serialPort.IsOpen)
            {
                serialPort.Write("{\"COMMAND\":\"DELETE\"}\r\n");
                // Отправляем сообщение через COM порт
                serialPort.Write("{\"COMMAND\":\"INIT_GPIO\",\"MODE\":\"OUTPUT\",\"PORT\":\"PORTC\",\"PINS\":15,\"TYPE\":\"CONTROL\"}\r\n");
                // Ждем 100 мс перед отправкой следующего сообщения
                Thread.Sleep(100);
                serialPort.Write("{\"COMMAND\":\"INIT_GPIO\",\"MODE\":\"OUTPUT\",\"PORT\":\"PORTF\",\"PINS\":65535,\"TYPE\":\"ADDR1\"}\r\n");
                Thread.Sleep(100);
                serialPort.Write("{\"COMMAND\":\"INFO\",\"MEMORY\":65535,\"STEP\":16}\r\n");
                Thread.Sleep(100);
                serialPort.Write("{\"COMMAND\":\"INIT_GPIO\",\"MODE\":\"OUTPUT\",\"PORT\":\"PORTA\",\"PINS\":255,\"TYPE\":\"DATA\"}\r\n");
                Thread.Sleep(100);
                serialPort.Write("{\"COMMAND\":\"MODIFIC_GPIO\",\"PORT\":\"PORTA\",\"PINS\":170,\"STATUS\":1,\"ACTION\":0}\r\n");
                Thread.Sleep(100);
                serialPort.Write("{\"COMMAND\":\"MODIFIC_GPIO\",\"PORT\":\"PORTC\",\"PINS\":2,\"STATUS\":0,\"ACTION\":0}\r\n");
                Thread.Sleep(100);
                serialPort.Write("{\"COMMAND\":\"MODIFIC_GPIO\",\"PORT\":\"PORTC\",\"PINS\":8,\"STATUS\":0,\"ACTION\":1}\r\n");
                Thread.Sleep(100);
                serialPort.Write("{\"COMMAND\":\"MODIFIC_GPIO\",\"PORT\":\"PORTC\",\"PINS\":4,\"STATUS\":1,\"ACTION\":1}\r\n");
                Thread.Sleep(100);
                serialPort.Write("{\"COMMAND\":\"MODIFIC_GPIO\",\"PORT\":\"PORTC\",\"PINS\":1,\"STATUS\":0,\"ACTION\":1}\r\n");
                Thread.Sleep(100);
                serialPort.Write("{\"COMMAND\":\"DELAY\",\"TIME\":\"10\",\"ACTION\":1}");
                Thread.Sleep(100);
                serialPort.Write("{\"COMMAND\":\"MODIFIC_GPIO\",\"PORT\":\"PORTC\",\"PINS\":1,\"STATUS\":1,\"ACTION\":1}\r\n");
                Thread.Sleep(100);
                serialPort.Write("{\"COMMAND\":\"MODIFIC_GPIO\",\"PORT\":\"PORTC\",\"PINS\":8,\"STATUS\":1,\"ACTION\":1}\r\n");
                Thread.Sleep(100);
                serialPort.Write("{\"COMMAND\":\"MODIFIC_GPIO\",\"PORT\":\"PORTC\",\"PINS\":4,\"STATUS\":0,\"ACTION\":1}\r\n");
                Thread.Sleep(100);
                serialPort.Write("{\"COMMAND\":\"DATA_CHANGE\",\"ACTION\":1}\r\n");
                Thread.Sleep(100);
                serialPort.Write("{\"COMMAND\":\"WRITE\"}\r\n");
                Thread.Sleep(5000);

                serialPort.Write("{\"COMMAND\":\"INIT_GPIO\",\"MODE\":\"INPUT\",\"PORT\":\"PORTA\",\"PINS\":255,\"TYPE\":\"DATA\"}\r\n");
                Thread.Sleep(100);
                serialPort.Write("{\"COMMAND\":\"MODIFIC_GPIO\",\"PORT\":\"PORTC\",\"PINS\":1,\"STATUS\":1,\"ACTION\":0}\r\n");
                Thread.Sleep(100);
                serialPort.Write("{\"COMMAND\":\"MODIFIC_GPIO\",\"PORT\":\"PORTC\",\"PINS\":8,\"STATUS\":0,\"ACTION\":2}\r\n");
                Thread.Sleep(100);
                serialPort.Write("{\"COMMAND\":\"MODIFIC_GPIO\",\"PORT\":\"PORTC\",\"PINS\":4,\"STATUS\":1,\"ACTION\":2}\r\n");
                Thread.Sleep(100);
                serialPort.Write("{\"COMMAND\":\"MODIFIC_GPIO\",\"PORT\":\"PORTC\",\"PINS\":2,\"STATUS\":0,\"ACTION\":2}\r\n");
                Thread.Sleep(100);
                serialPort.Write("{\"COMMAND\":\"DELAY\",\"TIME\":\"20\",\"ACTION\":2}\r\n");
                Thread.Sleep(100);
                serialPort.Write("{\"COMMAND\":\"READ_GPIO\",\"PORT\":\"PORTA\",\"PINS\":255,\"ACTION\":2}\r\n");
                Thread.Sleep(100);
                serialPort.Write("{\"COMMAND\":\"MODIFIC_GPIO\",\"PORT\":\"PORTC\",\"PINS\":2,\"STATUS\":1,\"ACTION\":2}\r\n");
                Thread.Sleep(100);
                serialPort.Write("{\"COMMAND\":\"MODIFIC_GPIO\",\"PORT\":\"PORTC\",\"PINS\":8,\"STATUS\":1,\"ACTION\":2}\r\n");
                Thread.Sleep(100);
                serialPort.Write("{\"COMMAND\":\"MODIFIC_GPIO\",\"PORT\":\"PORTC\",\"PINS\":4,\"STATUS\":0,\"ACTION\":2}\r\n");
                Thread.Sleep(100);
                serialPort.Write("{\"COMMAND\":\"DATA_CHANGE\",\"ACTION\":2}\r\n");
                Thread.Sleep(100);
                serialPort.Write("{\"COMMAND\":\"READ\"}\r\n"); 
            }
            else
            {
                MessageBox.Show("COM порт не открыт");
            }
        }

        void CY7C1019DV3310ZSXI ()
        {
            serialPort.Write("{\"COMMAND\":\"DELETE\"}\r\n");
            Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"INIT_GPIO\",\"MODE\":\"OUTPUT\",\"PORT\":\"PORTC\",\"PINS\":7,\"TYPE\":\"CONTROL\"}\r\n");
            Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"INIT_GPIO\",\"MODE\":\"OUTPUT\",\"PORT\":\"PORTF\",\"PINS\":65535,\"TYPE\":\"ADDR1\"}\r\n");
            Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"INFO\",\"MEMORY\":65535,\"STEP\":16}\r\n");
            Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"MODIFIC_GPIO\",\"PORT\":\"PORTC\",\"PINS\":7,\"STATUS\":1,\"ACTION\":0}\r\n");
            Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"INIT_GPIO\",\"MODE\":\"OUTPUT\",\"PORT\":\"PORTA\",\"PINS\":255,\"TYPE\":\"DATA\"}\r\n");
            Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"DATA_CHANGE\",\"ACTION\":1}\r\n");
            Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"MODIFIC_GPIO\",\"PORT\":\"PORTC\",\"PINS\":3,\"STATUS\":0,\"ACTION\":1}\r\n");
            Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"MODIFIC_GPIO\",\"PORT\":\"PORTC\",\"PINS\":3,\"STATUS\":1,\"ACTION\":1}\r\n");
            Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"WRITE\"}\r\n");
            Thread.Sleep(1000);
            serialPort.Write("{\"COMMAND\":\"INIT_GPIO\",\"MODE\":\"INPUT\",\"PORT\":\"PORTA\",\"PINS\":255,\"TYPE\":\"DATA\"}\r\n");
            Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"MODIFIC_GPIO\",\"PORT\":\"PORTC\",\"PINS\":2,\"STATUS\":1,\"ACTION\":0}\r\n");
            Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"DATA_CHANGE\",\"ACTION\":2}\r\n");
            Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"MODIFIC_GPIO\",\"PORT\":\"PORTC\",\"PINS\":5,\"STATUS\":0,\"ACTION\":2}\r\n");
            Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"READ_GPIO\",\"PORT\":\"PORTA\",\"PINS\":255,\"ACTION\":2}\r\n");
            Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"MODIFIC_GPIO\",\"PORT\":\"PORTC\",\"PINS\":5,\"STATUS\":1,\"ACTION\":2}\r\n");
            Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"READ\"}\r\n");
        }

        void CY7C1069G30()
        {
            serialPort.Write("{\"COMMAND\":\"DELETE\"}\r\n"); Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"INIT_GPIO\",\"MODE\":\"OUTPUT\",\"PORT\":\"PORTC\",\"PINS\":15,\"TYPE\":\"CONTROL\"}\r\n"); Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"INIT_GPIO\",\"MODE\":\"OUTPUT\",\"PORT\":\"PORTF\",\"PINS\":65535,\"TYPE\":\"ADDR1\"}\r\n"); Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"INFO\",\"MEMORY\":65535,\"STEP\":255}\r\n"); Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"MODIFIC_GPIO\",\"PORT\":\"PORTC\",\"PINS\":13,\"STATUS\":1,\"ACTION\":0}\r\n"); Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"INIT_GPIO\",\"MODE\":\"OUTPUT\",\"PORT\":\"PORTA\",\"PINS\":255,\"TYPE\":\"DATA\"}\r\n"); Thread.Sleep(100);

            serialPort.Write("{\"COMMAND\":\"DATA_CHANGE\",\"ACTION\":1}\r\n"); Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"MODIFIC_GPIO\",\"PORT\":\"PORTC\",\"PINS\":5,\"STATUS\":0,\"ACTION\":1}\r\n"); Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"MODIFIC_GPIO\",\"PORT\":\"PORTC\",\"PINS\":10,\"STATUS\":1,\"ACTION\":1}\r\n"); Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"DELAY\",\"TIME\":\"50\",\"ACTION\":1}\r\n"); Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"MODIFIC_GPIO\",\"PORT\":\"PORTC\",\"PINS\":2,\"STATUS\":0,\"ACTION\":1}\r\n"); Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"MODIFIC_GPIO\",\"PORT\":\"PORTC\",\"PINS\":13,\"STATUS\":1,\"ACTION\":1}\r\n"); Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"WRITE\"}\r\n"); Thread.Sleep(1000);

            serialPort.Write("{\"COMMAND\":\"INIT_GPIO\",\"MODE\":\"INPUT\",\"PORT\":\"PORTA\",\"PINS\":255,\"TYPE\":\"DATA\"}\r\n"); Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"MODIFIC_GPIO\",\"PORT\":\"PORTC\",\"PINS\":2,\"STATUS\":0,\"ACTION\":0}\r\n"); Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"MODIFIC_GPIO\",\"PORT\":\"PORTC\",\"PINS\":13,\"STATUS\":1,\"ACTION\":0}\r\n"); Thread.Sleep(100);

            serialPort.Write("{\"COMMAND\":\"DATA_CHANGE\",\"ACTION\":2}\r\n"); Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"MODIFIC_GPIO\",\"PORT\":\"PORTC\",\"PINS\":9,\"STATUS\":0,\"ACTION\":2}\r\n"); Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"MODIFIC_GPIO\",\"PORT\":\"PORTC\",\"PINS\":6,\"STATUS\":1,\"ACTION\":2}\r\n"); Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"DELAY\",\"TIME\":\"50\",\"ACTION\":2}\r\n"); Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"READ_GPIO\",\"PORT\":\"PORTA\",\"PINS\":255,\"ACTION\":2}\r\n"); Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"MODIFIC_GPIO\",\"PORT\":\"PORTC\",\"PINS\":2,\"STATUS\":0,\"ACTION\":2}\r\n"); Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"MODIFIC_GPIO\",\"PORT\":\"PORTC\",\"PINS\":13,\"STATUS\":1,\"ACTION\":2}\r\n"); Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"READ\"}\r\n"); Thread.Sleep(100);
        }

        void MB85RS512T ()
        {
            serialPort.Write("{\"COMMAND\":\"DELETE\"}\r\n");
            Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"INIT_GPIO\",\"MODE\":\"OUTPUT\",\"PORT\":\"PORTC\",\"PINS\":7,\"TYPE\":\"CONTROL\"}\r\n");
            Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"INIT_SPI\",\"NUMBER\":1}\r\n");
            Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"DELAY\",\"TIME\":\"10\",\"ACTION\":0}\r\n");
            Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"INFO\",\"MEMORY\":65535,\"STEP\":8}\r\n");
            Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"MODIFIC_GPIO\",\"PORT\":\"PORTC\",\"PINS\":4,\"STATUS\":1,\"ACTION\":0}\r\n");
            Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"SPI_TRANSMIT\",\"NUMBER\":1,\"DATA\":6,\"ACTION\":0}\r\n");
            Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"DELAY\",\"TIME\":\"10\",\"ACTION\":0}\r\n");
            Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"MODIFIC_GPIO\",\"PORT\":\"PORTC\",\"PINS\":1,\"STATUS\":1,\"ACTION\":0}\r\n");
            Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"DELAY\",\"TIME\":\"10\",\"ACTION\":0}\r\n");
            Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"MODIFIC_GPIO\",\"PORT\":\"PORTC\",\"PINS\":1,\"STATUS\":0,\"ACTION\":0}\r\n");
            Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"SPI_TRANSMIT\",\"NUMBER\":1,\"DATA\":2,\"ACTION\":0}\r\n");
            Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"SPI_TRANSMIT\",\"NUMBER\":1,\"DATA\":0,\"ACTION\":0}\r\n");
            Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"SPI_TRANSMIT\",\"NUMBER\":1,\"DATA\":0,\"ACTION\":0}\r\n");
            Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"SPI_TRANSMIT\",\"NUMBER\":1,\"DATA\":85,\"ACTION\":1}\r\n");
            Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"WRITE\"}\r\n");
            Thread.Sleep(1000);
            serialPort.Write("{\"COMMAND\":\"MODIFIC_GPIO\",\"PORT\":\"PORTC\",\"PINS\":1,\"STATUS\":1,\"ACTION\":0}\r\n");
            Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"DELAY\",\"TIME\":\"10\",\"ACTION\":0}\r\n");
            Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"MODIFIC_GPIO\",\"PORT\":\"PORTC\",\"PINS\":1,\"STATUS\":0,\"ACTION\":0}\r\n");
            Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"SPI_TRANSMIT\",\"NUMBER\":1,\"DATA\":3,\"ACTION\":0}\r\n");
            Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"SPI_TRANSMIT\",\"NUMBER\":1,\"DATA\":0,\"ACTION\":0}\r\n");
            Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"SPI_TRANSMIT\",\"NUMBER\":1,\"DATA\":0,\"ACTION\":0}\r\n");
            Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"SPI_RECEIVE\",\"NUMBER\":1,\"ACTION\":2}\r\n");
            Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"READ\"}\r\n");
            Thread.Sleep(1000);
            serialPort.Write("{\"COMMAND\":\"MODIFIC_GPIO\",\"PORT\":\"PORTC\",\"PINS\":1,\"STATUS\":1,\"ACTION\":0}\r\n");
            Thread.Sleep(100);
            serialPort.Write("{\"COMMAND\":\"DELAY\",\"TIME\":\"10\",\"ACTION\":0}\r\n");
        }
            private async Task<string> WaitForResponse(SerialPort serialPort)
        {
            string response = "";
            DateTime startTime = DateTime.Now;

            while ((DateTime.Now - startTime).TotalSeconds < 30) // Максимальное время ожидания (в данном случае 30 секунд)
            {
                if (serialPort.BytesToRead > 0)
                {
                    response = serialPort.ReadExisting();
                    break;
                }

                await Task.Delay(100); // Подождем 100 мс перед следующей попыткой
            }

            return response;
        }


        private void memoryBox_SelectedIndexChanged(object sender, EventArgs e)
        // Menu with selection memory
        {

        }

        private void errorBox_TextChanged(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void label3_Click(object sender, EventArgs e)
        {

        }
    }
}
