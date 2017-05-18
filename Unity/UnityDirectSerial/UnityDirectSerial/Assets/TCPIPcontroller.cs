using UnityEngine;
using System.Collections;
using System;
using System.Net;
using System.Net.Sockets;
using System.Text.RegularExpressions;

public class TCPIPcontroller : MonoBehaviour, ICommunicationController
{
    public string ip = "192.168.1.100";
    public int port = 5000;
    public float sendRate = 0.2f;

    public string sendBuffer = "";
    private float responseDisplayTime;
    private String response = "";
    private String lastCommand = "enteredroom";
    private bool commandReceived = false;
    private float lastSent = 0f;
    private Socket _clientSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
    private byte[] _recieveBuffer = new byte[8142];

    // box
    private Texture2D backgroundTexture;
    private GUIStyle textureStyle;

    void Start() 
    {
        try
        {
            _clientSocket.Connect(new IPEndPoint(IPAddress.Parse(ip), port));
        }
        catch (SocketException ex)
        {
            Debug.Log(ex.Message);
        }
        response = "connected";
        _clientSocket.BeginReceive(_recieveBuffer, 0, _recieveBuffer.Length, SocketFlags.None, new AsyncCallback(ReceiveCallback), null);

        backgroundTexture = Texture2D.whiteTexture;
        textureStyle = new GUIStyle { normal = new GUIStyleState { background = backgroundTexture } };
    }

    private void ReceiveCallback(IAsyncResult AR)
    {
        //Check how much bytes are recieved and call EndRecieve to finalize handshake
        int recieved = _clientSocket.EndReceive(AR);

        if (recieved <= 0) {
            _clientSocket.Close();
            this.Start(); // connection broke
            Debug.Log("Connection broke.  Restarting");
            response = "Connection broke.  Restarting";
            return;
        }

        //Copy the recieved data into new buffer , to avoid null bytes
        byte[] recData = new byte[recieved];
        Buffer.BlockCopy(_recieveBuffer, 0, recData, 0, recieved);

        //Process data here the way you want , all your bytes will be stored in recData
        parseResponse(System.Text.Encoding.Default.GetString(recData));

        //Start receiving again
        _clientSocket.BeginReceive(_recieveBuffer, 0, _recieveBuffer.Length, SocketFlags.None, new AsyncCallback(ReceiveCallback), null);
    }

    // remove IP send details and test for reply to commands
    void parseResponse(String s)
    {
        string regex = "(\\<.*\\>)";
        string output = Regex.Replace(s, regex, "");
        if (output.Contains("received: " + lastCommand)) commandReceived = true;
        response = output;
        Debug.Log("response: " + response);
    }

    private void OnDestroy()
    {
        _clientSocket.Close();
    }

    private void SendData(byte[] data)
    {
        SocketAsyncEventArgs socketAsyncData = new SocketAsyncEventArgs();
        socketAsyncData.SetBuffer(data, 0, data.Length);
        _clientSocket.SendAsync(socketAsyncData);
    }

    // Update is called once per frame
    void Update()
    {
        if ((lastSent + sendRate) < Time.time)
        {
            if (sendBuffer.Length > 0)
            {
                SendData(System.Text.Encoding.ASCII.GetBytes(sendBuffer + "\n"));
                sendBuffer = "";
            }
            lastSent = Time.time;
        }
    }

    private void OnGUI()
    {
        if (response.Length > 0)
        {
            GUI.backgroundColor = commandReceived ? Color.green : Color.red;
            GUI.Box(new Rect(20, 20, 500, 20), response, textureStyle);
        }
    }

    public void writeCommand(string s)
    {
        sendBuffer += s;
        commandReceived = false;
        lastCommand = sendBuffer;
    }
}
