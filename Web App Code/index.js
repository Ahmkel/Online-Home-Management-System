var express = require('express');
var cors = require('cors');
var app = express();
var path = require('path');

app.use(express.static(__dirname + '/'));
app.use(cors());
var mongoose = require('mongoose');
mongoose.connect("<<insert Database link from the MongoLab website>>");

var HMSSchema = mongoose.Schema({ Lights: String, DoorLock: String, Windows: String, Temperature: String, PIR: String });
var HMS = mongoose.model('MyHome', HMSSchema);

  //Upload and run the file or run it on local server
  //for the first time with the next line uncommented
  //then comment it and reupload the file again
  
//var MyHome = new HMS({Lights:'0',DoorLock:'0',Windows:'0',Temperature:'27',PIR:'0'});

var db = mongoose.connection;
db.on('error', console.error.bind(console, 'connection error:'));
db.once('open', function (callback) {
  //Upload and run the file or run it on local server
  //for the first time with the next line uncommented
  //then comment it and reupload the file again
  //MyHome.save(function(err,MyHome){if(err)return console.error(err);});
});

app.set('port', (process.env.PORT || 5000));

//Get Control Value "Lights,DoorLock,Windows"
app.get('/api/GetControl', function(req, res) {
    var HMS1 = HMS.find(function(err,HMS1){
        var tmpHMS=HMS1[0];
        res.send(tmpHMS.Lights+tmpHMS.DoorLock+tmpHMS.Windows);
    });
});

//Set Lights
app.get('/api/SetControl/Lights/:Lights', function (req, res) {
    var HMS1 = HMS.find(function (err, HMS1) {
        var tmpHMS = HMS1[0];
        tmpHMS.Lights = req.params.Lights;
        tmpHMS.save(function (err, tmpHMS) { if (err) return console.error(err); });
        res.send({ "NewLIGHTS": tmpHMS.Lights });
    });
});

//Set DoorLock
app.get('/api/SetControl/DoorLock/:DoorLock', function (req, res) {
    var HMS1 = HMS.find(function (err, HMS1) {
        var tmpHMS = HMS1[0];
        tmpHMS.DoorLock = req.params.DoorLock;
        tmpHMS.save(function (err, tmpHMS) { if (err) return console.error(err); });
        res.send({ "NewDOORLOCK": tmpHMS.DoorLock });
    });
});

//Set Windows
app.get('/api/SetControl/Windows/:Windows', function (req, res) {
    var HMS1 = HMS.find(function (err, HMS1) {
        var tmpHMS = HMS1[0];
        tmpHMS.Windows = req.params.Windows;
        tmpHMS.save(function (err, tmpHMS) { if (err) return console.error(err); });
        res.send({ "NewWINDOWS": tmpHMS.Windows });
    });
});

//Get Sensors Reading "Temperature,PIR"
app.get('/api/GetSensors', function (req, res) {
    var HMS1 = HMS.find(function (err, HMS1) {
        var tmpHMS = HMS1[0];
        res.send({ "PIR": tmpHMS.PIR, "Temperature": tmpHMS.Temperature });
    });
});

//Set Temperature
app.get('/api/SetSensors/Temperature/:Temperature', function (req, res) {
    var HMS1 = HMS.find(function (err, HMS1) {
        var tmpHMS = HMS1[0];
        tmpHMS.Temperature = req.params.Temperature;
        tmpHMS.save(function (err, tmpHMS) { if (err) return console.error(err); });
        res.send({ "NewTMP": tmpHMS.Temperature });
    });
});

//Set PIR
app.get('/api/SetSensors/PIR/:PIRState', function (req, res) {
    var HMS1 = HMS.find(function (err, HMS1) {
        var tmpHMS = HMS1[0];
        tmpHMS.PIR = req.params.PIRState;
        tmpHMS.save(function (err, tmpHMS) { if (err) return console.error(err); });
        res.send({ "NewPIRState": tmpHMS.PIR });
    });
});

app.listen(app.get('port'), function () {
    console.log('Node app is running on port', app.get('port'));
});
