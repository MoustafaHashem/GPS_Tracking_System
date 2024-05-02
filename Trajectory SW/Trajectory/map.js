var map = L.map('map').setView([51.505, -0.09], 13);

    // Add OpenStreetMap tile layer
    L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
        attribution: '&copy; <a href="https://www.openstreetmap.org/copyright">OpenStreetMap</a> contributors'
    }).addTo(map);

    // Define coordinates for the path
    var latlngs = [ [30.1514,31.3346],[30.1514,31.3345],[30.1514,31.3346],[30.1515,31.3346],[30.1513,31.3346],[30.1513,31.3346],    ];

    // Create a polyline and add it to the map
    var polyline = L.polyline(latlngs, { color: 'red' }).addTo(map);

    // Fit the map to the bounds of the polyline
    map.fitBounds(polyline.getBounds());