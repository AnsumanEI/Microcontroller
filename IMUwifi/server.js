const express = require('express');
const bodyParser = require('body-parser');
const axios = require('axios');
const app = express();
const port = 3000;

let imuData = {};

app.use(bodyParser.json());
app.use(express.static('public'));

app.post('/data', (req, res) => {
  imuData = req.body;
  console.log('Data received: ', imuData);
  res.send('Data received');

  // Update ThingSpeak
  axios.post(`https://api.thingspeak.com/update.json?api_key=L4ZA2L24TO09SB81&field1=${imuData.accelX}&field2=${imuData.accelY}&field3=${imuData.accelZ}&field4=${imuData.gyroX}&field5=${imuData.gyroY}&field6=${imuData.gyroZ}`, {})
    .then(response => {
      console.log('Updated ThingSpeak');
    })
    .catch(error => {
      console.error('Error updating ThingSpeak:', error);
    });
});

app.get('/imu-data', (req, res) => {
  res.json(imuData);
});

app.listen(port, () => {
  console.log(`Server running at http://localhost:${port}`);
});
