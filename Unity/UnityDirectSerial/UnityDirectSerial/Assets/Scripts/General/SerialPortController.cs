using UnityEngine;
using System.Collections;
using System.IO.Ports;
 
public class SerialPortController : MonoBehaviour {

    public string port = "COM4";
    public int speed = 115200;

    public string sendBuffer = "";

    private SerialPort _serialPort;
    private string messageString = "";
    void Start () {
        _serialPort = new SerialPort(port, speed);
        // Set the read/write timeouts
        _serialPort.ReadTimeout = 10;
        _serialPort.WriteTimeout = 10;
        _serialPort.Open(); //Open the Serial Stream.
    }
   
    public void writeCommand(string s)
    {
        sendBuffer += s;
    }

    // Update is called once per frame
    void Update () {
        try
        {
            _serialPort.WriteLine(sendBuffer);
            sendBuffer = "";
            messageString = _serialPort.ReadLine(); //Read the information
            _serialPort.BaseStream.Flush(); //Clear the serial information so we assure we get new information.
        } catch (System.TimeoutException ex)
        {

        }
    }
   
    void OnGUI()
    {
        GUI.Label(new Rect(10,10,300,100), messageString); //Display new values
        // Though, it seems that it outputs the value in percentage O-o I don't know why.
    }
}