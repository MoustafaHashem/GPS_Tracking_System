var map = L.map('map').setView([51.505, -0.09], 13);

    // Add OpenStreetMap tile layer
    L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
        attribution: '&copy; <a href="https://www.openstreetmap.org/copyright">OpenStreetMap</a> contributors'
    }).addTo(map);

    // Define coordinates for the path
    var latlngs = [ [30.0644,31.2801],[30.0645,31.2801],[30.0646,31.2801],[30.0647,31.2801],[30.0647,31.28],[30.0648,31.2799],[30.0647,31.2798],[30.0647,31.2797],    ];

    // Create a polyline and add it to the map
    var polyline = L.polyline(latlngs, { color: 'red' }).addTo(map);

    // Fit the map to the bounds of the polyline
    map.fitBounds(polyline.getBounds());