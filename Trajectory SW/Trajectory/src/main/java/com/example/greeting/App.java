package com.example.greeting;

import com.fazecast.jSerialComm.SerialPort;

import java.awt.*;
import java.io.File;


import java.util.ArrayList;
import java.util.List;

public class App {
    // here check for tiva is connected or not
    private static SerialPort chosenPort;
    private static String receivedData;

    public static void main(String[] args) {
        SerialPort[] serialPorts = SerialPort.getCommPorts();

        for (SerialPort port : serialPorts) {
            System.out.println("Available port: " + port.getSystemPortName());
        }
        String portName = "COM3";                                                        // Replace with the name of the serial port you want to connect to

        chosenPort = SerialPort.getCommPort(portName);
        if (chosenPort.openPort()) {
            System.out.println("Connected to " + portName);
        } else {
            System.err.println("Failed to open " + portName);
            System.exit(1);
            return;
        }
        StringBuilder str;
        // now we checked then after that we can receive  data
        while (true) {
            str = new StringBuilder();
            try {
                while (true) {
                    byte[] readBuffer = new byte[1024];                                      //  allocate area to store data
                    int numBytesRead = chosenPort.readBytes(readBuffer, readBuffer.length);   // trim string to the size of data received
                    receivedData = new String(readBuffer, 0, numBytesRead);             // now data stored
                    if (!receivedData.isEmpty()) {                                             // check for receive data is empty or not
                        if (receivedData.contains("@")) {
                            str.append("\n");
                        } else if (receivedData.contains("^")) {
                            break;                                                             // when sent "^" stop adding point
                        } else {
                            str.append(receivedData);
                            System.out.println(receivedData);
                        }
                    }
                }
                // prepare point to draw
                String[] n2;
                String[] n1;
                String[] n3;
                String[] n4;
                String[] n8;
                String[] n5;
                String[] n6;
                String[] n7;
                String[] y;
                String s = String.valueOf(str);
                y = s.split("\n");
                n1 = y[0].split(",");
                n2 = y[1].split(",");
                n3 = y[2].split(",");
                n4 = y[3].split(",");
                n5 = y[4].split(",");
                n6 = y[5].split(",");
                n7 = y[6].split(",");
                n8 = y[7].split(",");
                List<Point> pointList = new ArrayList<>();
                pointList.add(new Point(Double.parseDouble(n1[0].trim()), Double.parseDouble(n1[1].trim())));
                pointList.add(new Point(Double.parseDouble(n2[0].trim()), Double.parseDouble(n2[1].trim())));
                pointList.add(new Point(Double.parseDouble(n3[0].trim()), Double.parseDouble(n3[1].trim())));
                pointList.add(new Point(Double.parseDouble(n4[0].trim()), Double.parseDouble(n4[1].trim())));
                pointList.add(new Point(Double.parseDouble(n5[0].trim()), Double.parseDouble(n5[1].trim())));
                pointList.add(new Point(Double.parseDouble(n6[0].trim()), Double.parseDouble(n6[1].trim())));
                pointList.add(new Point(Double.parseDouble(n7[0].trim()), Double.parseDouble(n7[1].trim())));
                pointList.add(new Point(Double.parseDouble(n8[0].trim()), Double.parseDouble(n8[1].trim())));
                // sent point to draw
                OpenStreetMapViewer.writePointList(pointList);
                File htmlFile = new File("index.html");
                System.out.println(htmlFile.toURI());
                // open browser to put point on them and connected it
                Desktop.getDesktop().browse(htmlFile.toURI());
            } catch (Exception e) {
                // Ignore exception
            }

        }


    }
}