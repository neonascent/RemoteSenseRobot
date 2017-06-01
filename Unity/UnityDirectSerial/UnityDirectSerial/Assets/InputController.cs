using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class InputController : MonoBehaviour {

    public InputMapping[] inputs;

    // structure for mapping inputs to servos
    [System.Serializable]
    public struct InputMapping
    {
        public string inputName;
        public Arm_Servo target;
        public float sensitivity;
        public int triggerState;
    }

    void Start()
    {
        // initialise trigger states 
        for (int i = 0; i < inputs.Length; i++)
        {
            inputs[i].triggerState = 0;
        }
    }

    public void triggerInput(int i)
    {
        int sign = Math.Sign(i);
        i = Math.Abs(i) - 1;
        inputs[i].triggerState = sign;
    }

    public void clearInput(int i)
    {
        i = Math.Abs(i)-1;
        inputs[i].triggerState = 0;

    }

	
	// Update is called once per frame
	void Update () {
        foreach (InputMapping mapping in inputs)
        {
            mapping.target.displacement += Input.GetAxis(mapping.inputName) * mapping.sensitivity;
            mapping.target.displacement += mapping.triggerState * mapping.sensitivity;
        }

	}
}