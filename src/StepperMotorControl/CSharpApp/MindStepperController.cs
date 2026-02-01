/*
 * MindStepperController - Neurosky EEG-Based Stepper Motor Control
 * 
 * This application connects to a Neurosky MindWave headset and controls
 * a stepper motor on an Arduino based on the user's attention level.
 * Attention (0-100) maps to motor position (0-2048 steps / 0-360 degrees).
 * 
 * Author: SMIT
 * Version: 1.0.0
 * Date: 2026
 */

using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.IO;
using System.IO.Ports;
using NeuroSky.ThinkGear;
using NeuroSky.ThinkGear.Algorithms;

namespace MindControlExamples
{
    /// <summary>
    /// Main program class that handles Neurosky headset connection and stepper motor control
    /// </summary>
    class MindStepperController
    {
        // Neurosky ThinkGear connector instance
        static Connector connector;
        
        // Serial port for Arduino communication
        static SerialPort arduinoPort;
        
        // Track last attention for change detection
        static int lastAttention = -1;
        
        // Configuration constants
        const string NEUROSKY_COM_PORT = "COM3";    // Neurosky headset COM port
        const string ARDUINO_COM_PORT = "COM12";     // Arduino COM port
        const int ARDUINO_BAUD_RATE = 115200;        // Arduino serial baud rate
        const int SESSION_DURATION_MS = 450000;      // Session duration (7.5 minutes)
        const int CHANGE_THRESHOLD = 5;              // Minimum attention change to trigger motor

        /// <summary>
        /// Application entry point
        /// </summary>
        public static void Main(string[] args)
        {
            Console.WriteLine("==============================================");
            Console.WriteLine("  Mind Control Stepper - Motor Controller");
            Console.WriteLine("==============================================");
            Console.WriteLine();

            // Initialize the Neurosky ThinkGear connector
            connector = new Connector();
            
            // Register event handlers for device connection events
            connector.DeviceConnected += new EventHandler(OnDeviceConnected);
            connector.DeviceConnectFail += new EventHandler(OnDeviceFail);
            connector.DeviceValidating += new EventHandler(OnDeviceValidating);

            // Scan for Neurosky devices starting from the specified COM port
            Console.WriteLine($"Scanning for Neurosky headset on {NEUROSKY_COM_PORT}...");
            connector.ConnectScan(NEUROSKY_COM_PORT);

            // Enable blink detection feature
            connector.setBlinkDetectionEnabled(true);
            
            // Run the session for the specified duration
            Thread.Sleep(SESSION_DURATION_MS);

            // Cleanup and exit
            Console.WriteLine();
            Console.WriteLine("Session ended. Goodbye!");
            connector.Close();
            Environment.Exit(0);
        }

        /// <summary>
        /// Event handler called when a Neurosky device is successfully connected
        /// </summary>
        static void OnDeviceConnected(object sender, EventArgs e)
        {
            Connector.DeviceEventArgs de = (Connector.DeviceEventArgs)e;

            Console.WriteLine($"[SUCCESS] Neurosky device found on: {de.Device.PortName}");
            Console.WriteLine();
            Console.WriteLine($"Connecting to Arduino on {ARDUINO_COM_PORT}...");

            // Initialize Arduino serial connection
            arduinoPort = new SerialPort(ARDUINO_COM_PORT, ARDUINO_BAUD_RATE, Parity.None, 8, StopBits.One);
            arduinoPort.Open();

            // Wait for Arduino to initialize
            Thread.Sleep(3000);

            Console.WriteLine("[SUCCESS] Connected to Arduino");
            Console.WriteLine();
            Console.WriteLine("==============================================");
            Console.WriteLine("  Monitoring attention level...");
            Console.WriteLine("  Stepper position = Attention × 3.6 degrees");
            Console.WriteLine("  (0% = 0°, 50% = 180°, 100% = 360°)");
            Console.WriteLine("==============================================");
            Console.WriteLine();

            // Register data received event handler
            de.Device.DataReceived += new EventHandler(OnDataReceived);
        }

        /// <summary>
        /// Event handler called when device scanning fails
        /// </summary>
        static void OnDeviceFail(object sender, EventArgs e)
        {
            Console.WriteLine("[ERROR] No Neurosky devices found!");
            Console.WriteLine("Please ensure your headset is turned on and paired.");
        }

        /// <summary>
        /// Event handler called during device validation
        /// </summary>
        static void OnDeviceValidating(object sender, EventArgs e)
        {
            Console.WriteLine("Validating device connection...");
        }

        /// <summary>
        /// Event handler for processing EEG data from the headset
        /// Sends attention level to Arduino for stepper motor position control
        /// </summary>
        static void OnDataReceived(object sender, EventArgs e)
        {
            Device.DataEventArgs de = (Device.DataEventArgs)e;
            DataRow[] tempDataRowArray = de.DataRowArray;

            TGParser tgParser = new TGParser();
            tgParser.Read(de.DataRowArray);

            // Process each data point from the headset
            for (int i = 0; i < tgParser.ParsedData.Length; i++)
            {
                if (tgParser.ParsedData[i].ContainsKey("Attention"))
                {
                    int attentionLevel = (int)tgParser.ParsedData[i]["Attention"];
                    int targetDegrees = (int)(attentionLevel * 3.6); // Map 0-100 to 0-360
                    
                    // Only send command if attention changed significantly
                    if (lastAttention == -1 || Math.Abs(attentionLevel - lastAttention) >= CHANGE_THRESHOLD)
                    {
                        // Create visual dial indicator
                        int dialPos = attentionLevel / 5;
                        string dial = "";
                        for (int d = 0; d < 20; d++)
                        {
                            if (d == dialPos) dial += "●";
                            else dial += "○";
                        }
                        
                        Console.WriteLine($"Attention: {attentionLevel,3}% | Target: [{dial}] {targetDegrees}°");

                        // Send attention level to Arduino
                        arduinoPort.WriteLine($"{attentionLevel};0;");

                        // Wait for motor movement (stepper moves slowly)
                        Thread.Sleep(1000);

                        // Read and display Arduino response
                        string arduinoResponse = arduinoPort.ReadExisting();
                        if (!string.IsNullOrEmpty(arduinoResponse))
                        {
                            string[] lines = arduinoResponse.Split(new[] { '\r', '\n' }, StringSplitOptions.RemoveEmptyEntries);
                            foreach (string line in lines)
                            {
                                Console.WriteLine($"  {line.Trim()}");
                            }
                        }
                        Console.WriteLine();
                        
                        lastAttention = attentionLevel;
                    }
                }
            }
        }
    }
}
