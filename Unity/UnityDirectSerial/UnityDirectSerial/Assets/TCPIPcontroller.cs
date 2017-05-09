using UnityEngine;
using System.Collections;
using System;
using System.Net;
using System.Net.Sockets;


public class TCPIPcontroller : MonoBehaviour, ICommunicationController
{
    public string ip = "192.168.1.100";
    public int port = 5000;

    public string sendBuffer = "";

    private Socket _clientSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
    private byte[] _recieveBuffer = new byte[8142];

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

        _clientSocket.BeginReceive(_recieveBuffer, 0, _recieveBuffer.Length, SocketFlags.None, new AsyncCallback(ReceiveCallback), null);

    }

    private void ReceiveCallback(IAsyncResult AR)
    {
        //Check how much bytes are recieved and call EndRecieve to finalize handshake
        int recieved = _clientSocket.EndReceive(AR);

        if (recieved <= 0)
            return;

        //Copy the recieved data into new buffer , to avoid null bytes
        byte[] recData = new byte[recieved];
        Buffer.BlockCopy(_recieveBuffer, 0, recData, 0, recieved);

        //Process data here the way you want , all your bytes will be stored in recData

        //Start receiving again
        _clientSocket.BeginReceive(_recieveBuffer, 0, _recieveBuffer.Length, SocketFlags.None, new AsyncCallback(ReceiveCallback), null);
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
       SendData(System.Text.Encoding.ASCII.GetBytes(sendBuffer));
       sendBuffer = "";
    }


    public void writeCommand(string s)
    {
        sendBuffer += s;
    }
}
