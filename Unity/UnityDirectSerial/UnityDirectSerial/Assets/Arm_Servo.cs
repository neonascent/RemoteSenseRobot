using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Arm_Servo : MonoBehaviour {
    public Type type = Arm_Servo.Type.Claw;
    public int currentPulse = 400;
    public int minPulse = 100;
    public int maxPulse = 900;
    public float minDisplacement = 0f;
    public float maxDisplacement = -90f;
    public float displacement = 90f;
    public float offset = 0f;
    public GameObject pivotPoint;
    public GameObject[] servoChildren;
    public string commandString = "C";

    public bool dirty = true;

    public enum Type { Claw, RotationY, RotationX, RotationZ};

    private ICommunicationController sp;

    // Use this for initialization
    void Start () {
        sp = (ICommunicationController)FindObjectOfType<SerialPortController>();
        if (sp == null) sp = (ICommunicationController)FindObjectOfType<TCPIPcontroller>();
        if (sp == null) throw new UnityException("no controller");
    }
	
	// Update is called once per frame
	void Update () {
        displacement = Mathf.Clamp(displacement, minDisplacement, maxDisplacement);
        int newPulse = Map(displacement, minDisplacement, maxDisplacement, minPulse, maxPulse);
        if (newPulse != currentPulse)
        {
            dirty = true;
            currentPulse = newPulse;
        }       
        if (dirty)
        {
            doDisplacement();
            updateSerial();
            dirty = false;
        }
    }

    void doDisplacement()
    {
        Vector3 rotation = Vector3.zero;
        switch (type)
        {
            case Type.Claw:
                servoChildren[0].transform.localPosition = new Vector3(-offset - (displacement / 2), 0, 0);
                servoChildren[1].transform.localPosition = new Vector3(offset + (displacement / 2), 0, 0);
                return;
            case Type.RotationX:
                rotation.x = displacement + offset;
                break;
            case Type.RotationY:
                rotation.y = displacement + offset;
                break;
            case Type.RotationZ:
                rotation.z = displacement + offset;
                break;
            default:
                break;
        }
        servoChildren[0].transform.localEulerAngles = rotation;
    }

    void updateSerial()
    {
        string s = "$" + commandString + currentPulse.ToString() + ".";
        Debug.Log("Sending Command: " + s);
        sp.writeCommand(s);
    }

    public int Map(float value, float fromSource, float toSource, float fromTarget, float toTarget)
    {
        return int.Parse(((value - fromSource) / (toSource - fromSource) * (toTarget - fromTarget) + fromTarget).ToString("0"));
    }
}