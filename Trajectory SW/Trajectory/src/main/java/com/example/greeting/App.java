package com.example.greeting;
import  java.io.PrintWriter;
import com.fazecast.jSerialComm.SerialPort;

import java.awt.*;
import java.io.File;

import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

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

        }

        StringBuilder str;
        // now we checked then after that we can receive  data
        while (true) {
            str = new StringBuilder();
            chosenPort.setComPortParameters(9600,8,1,0);
            chosenPort.setComPortTimeouts(chosenPort.TIMEOUT_NONBLOCKING,0,0);
            chosenPort.openPort(20);
            PrintWriter OUT=new PrintWriter(chosenPort.getOutputStream(),true);
            Scanner in=new Scanner(System.in);
            String t=in.next();
            OUT.print(t);
            OUT.flush();
            if(t.compareTo("U") ==0){
            try {
                while (true) {
                    byte[] readBuffer = new byte[1024];                                      //  allocate area to store data
                    int numBytesRead = chosenPort.readBytes(readBuffer, readBuffer.length);   // trim string to the size of data received
                    receivedData = new String(readBuffer, 0, numBytesRead);             // now data stored

                    if (!receivedData.isEmpty()) {                                             // check for receive data is empty or not
                        if (receivedData.contains("@")) {
                            System.out.print("\n");

                            str.append("\n");
                        } else if (receivedData.contains("^")) {
                            System.out.println(receivedData);
                            break;                                                             // when sent "^" stop adding point
                        } else {
                            str.append(receivedData);
                            System.out.print(receivedData);
                        }
                    }
                }
                // prepare point to draw
                String[] n2=null;
                String[] n1=null;
                String[] n3=null;
                String[] n4=null;
                String[] n8=null;
                String[] n5=null;
                String[] n6=null;
                String[] n7=null;
                String[] y=null;
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
                if (Point.isDouble(n1[0]) && Point.isDouble(n1[1]))
                    pointList.add(new Point(Double.parseDouble(n1[0].trim()), Double.parseDouble(n1[1].trim())));
                if (Point.isDouble(n2[0]) && Point.isDouble(n2[1]))
                    pointList.add(new Point(Double.parseDouble(n2[0].trim()), Double.parseDouble(n2[1].trim())));
                if (Point.isDouble(n3[0]) && Point.isDouble(n3[1]))
                    pointList.add(new Point(Double.parseDouble(n3[0].trim()), Double.parseDouble(n3[1].trim())));
                if (Point.isDouble(n4[0]) && Point.isDouble(n4[1]))
                    pointList.add(new Point(Double.parseDouble(n4[0].trim()), Double.parseDouble(n4[1].trim())));
                if (Point.isDouble(n5[0]) && Point.isDouble(n5[1]))
                    pointList.add(new Point(Double.parseDouble(n5[0].trim()), Double.parseDouble(n5[1].trim())));
                if (Point.isDouble(n6[0]) && Point.isDouble(n6[1]))
                    pointList.add(new Point(Double.parseDouble(n6[0].trim()), Double.parseDouble(n6[1].trim())));
                if (Point.isDouble(n7[0]) && Point.isDouble(n7[1]))
                    pointList.add(new Point(Double.parseDouble(n7[0].trim()), Double.parseDouble(n7[1].trim())));
                if (Point.isDouble(n8[0]) && Point.isDouble(n8[1]))
                    pointList.add(new Point(Double.parseDouble(n8[0].trim()), Double.parseDouble(n8[1].trim())));
                // sent point to draw
                OpenStreetMapViewer.writePointList(pointList);
                File htmlFile = new File("index.html");
                System.out.println(htmlFile.toURI());
                // open browser to put point on them and connected it
                Desktop.getDesktop().browse(htmlFile.toURI());
                System.exit(0);
            } catch (Exception e) {
                System.out.println("not enough points " + "\n please try again with more distance");
                System.exit(0);
            }}

        }
    }
}