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
    }
	
	// Update is called once per frame
	void Update () {
        foreach (InputMapping mapping in inputs)
        {
            mapping.target.displacement += Input.GetAxis(mapping.inputName) * mapping.sensitivity;
        }

	}
}