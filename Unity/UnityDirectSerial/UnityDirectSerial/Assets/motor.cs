using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class motor : MonoBehaviour
{
    
    public Renderer leftTrack;
    public Renderer rightTrack;
    public GameObject ground;
    public string ForwardCommand = "F";
    public string BackwardCommand = "B";
    public string LeftCommand = "L";
    public string RightCommand = "R";

    public float speed = 100f;
    public float time = 0.2f;

    public bool forward = false;
    public bool backward = false;
    public bool left = false;
    public bool right = false;

    public bool dirty = true;

    private bool goforward = false;
    private bool gobackward = false;
    private bool goleft = false;
    private bool goright = false;

    private float activationTime;
    private Material groundMaterial;
    private ICommunicationController sp;

    // Use this for initialization
    void Start()
    {
        sp = (ICommunicationController)FindObjectOfType<SerialPortController>();
        if (sp == null) sp = (ICommunicationController)FindObjectOfType<TCPIPcontroller>();
        if (sp == null) throw new UnityException("no controller");
    }

    // Update is called once per frame
    void Update()
    {
        // keypad
        if (Input.GetKey("w"))
        {
            forward = true;
        }
        if (Input.GetKey("s"))
        {
            backward= true;
        }
        if (Input.GetKey("a"))
        {
            left = true;
        }
        if (Input.GetKey("d"))
        {
            right = true;
        }

        Debug.Log("left " + Input.GetAxis("LeftBumper") + "  " + Input.GetAxis("RightBumper"));
        // xbox input
        if (Input.GetAxis("B") > 0)
        {
            forward = true;
        } else if (Input.GetAxis("A") > 0)
        {
            backward = true;
        } else if (Input.GetAxis("LeftBumper") > 0)
        {
            if (Input.GetAxis("RightBumper") > 0)
            {
                forward = true;
            } else
            {
                right = true;
            }
        } else if (Input.GetAxis("RightBumper") > 0)
        {
            left = true;
        }


            if (left || right || forward || backward)
        {
            goleft = left;
            goright = right;
            goforward = forward;
            gobackward = backward;
            activationTime = Time.time;
            // send serial
            if (left)
            {
                updateSerial(LeftCommand);
            } else if (right) {
                updateSerial(RightCommand);
            } else if (forward)
            {
                updateSerial(ForwardCommand);
            } else if (backward)
            {
                updateSerial(BackwardCommand);
            }
            left = right = forward = backward = false;

        }

        if (goleft || goright || goforward || gobackward)
        {
            if (goleft)
            {
                moveTracks(-1, 1);
            }
            if (goright)
            {
                moveTracks(1, -1);
            }
            if (goforward)
            {
                moveTracks(1, 1);
            }
            if (gobackward)
            {
                moveTracks(-1, -1);
            }



            if ((activationTime + time) < Time.time)
            {
                goleft = goright = goforward = gobackward = false;
                Debug.Log("end");
            }
        }
        /*displacement = Mathf.Clamp(displacement, minDisplacement, maxDisplacement);
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
        }*/
    }

    void moveTracks (int l,int r)
    {
        float trackSpeed = 0.0001f * speed;
        float groundSpeed = 0.0004f * speed;
        float angleSpeed = 0.025f * speed;
        leftTrack.material.SetTextureOffset("_MainTex", new Vector2(0, leftTrack.material.GetTextureOffset("_MainTex").y + (l * trackSpeed)));
        rightTrack.material.SetTextureOffset("_MainTex", new Vector2(0, rightTrack.material.GetTextureOffset("_MainTex").y + (r * trackSpeed)));
        if (l == r)
        {
            ground.transform.position = ground.transform.position - new Vector3(0, 0, (l * groundSpeed));
        } else
        {
            ground.transform.RotateAround(Vector3.zero, Vector3.up, -l * angleSpeed);
        }
        

    }

    void doDisplacement()
    {
        /*Vector3 rotation = Vector3.zero;
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
        servoChildren[0].transform.localEulerAngles = rotation;*/
    }

    void updateSerial(string c)
    {
        string s = "$" + c +  "1.";
        Debug.Log("Sending Command: " + s);
        sp.writeCommand(s);
    }

    public int Map(float value, float fromSource, float toSource, float fromTarget, float toTarget)
    {
        return int.Parse(((value - fromSource) / (toSource - fromSource) * (toTarget - fromTarget) + fromTarget).ToString("0"));
    }





}