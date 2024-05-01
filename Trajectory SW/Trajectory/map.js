var map = L.map('map').setView([51.505, -0.09], 13);

    // Add OpenStreetMap tile layer
    L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
        attribution: '&copy; <a href="https://www.openstreetmap.org/copyright">OpenStreetMap</a> contributors'
    }).addTo(map);

    // Define coordinates for the path
    var latlngs = [ [48.864716,2.349014],[31.0,31.0],[40.0,40.0],[60.0,35.0],[55.751244,37.618423],[40.0,40.0],[60.0,35.0],[55.751244,37.618423],    ];

    // Create a polyline and add it to the map
    var polyline = L.polyline(latlngs, { color: 'red' }).addTo(map);

    // Fit the map to the bounds of the polyline
    map.fitBounds(polyline.getBounds());