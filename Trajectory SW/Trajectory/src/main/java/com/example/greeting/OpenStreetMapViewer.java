package com.example.greeting;

import java.awt.*;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.net.URISyntaxException;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.List;

public class OpenStreetMapViewer {

    public static void writePointList(List<Point> pointList) throws IOException {
        String list = "";
        for (Point point : pointList) {
            list += point.toString();
        }
        String js = "var map = L.map('map').setView([51.505, -0.09], 13);\n" +
                "\n" +
                "    // Add OpenStreetMap tile layer\n" +
                "    L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {\n" +
                "        attribution: '&copy; <a href=\"https://www.openstreetmap.org/copyright\">OpenStreetMap</a> contributors'\n" +
                "    }).addTo(map);\n" +
                "\n" +
                "    // Define coordinates for the path\n" +
                "    var latlngs = [ " + list +
                "    ];\n" +
                "\n" +
                "    // Create a polyline and add it to the map\n" +
                "    var polyline = L.polyline(latlngs, { color: 'red' }).addTo(map);\n" +
                "\n" +
                "    // Fit the map to the bounds of the polyline\n" +
                "    map.fitBounds(polyline.getBounds());";

        FileOutputStream fileOutputStream = new FileOutputStream("map.js");
        fileOutputStream.write(js.getBytes(StandardCharsets.UTF_8));
        fileOutputStream.close();
    }


}

class Point {
    private double x;
    private double y;

    public Point(double x, double y) {
        this.x = x;
        this.y = y;
    }
    public static boolean isDouble(String str) {
        if (str == null) {
            return false;
        }
        int length = str.length();
        if (length == 0) {
            return false;
        }
        int i = 0;
        if (str.charAt(0) == '-') {
            return false;
        }
        for (; i < length; i++) {
            char c = str.charAt(i);
            if ((c < '0' || c > '9')&&(c!='.')) {
                return false;
            }
        }
        return true;
    }
    @Override
    public String toString() {
        return "[" + x + "," + y + "],";
    }
}
