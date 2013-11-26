var SerialPort = require("serialport").SerialPort;
var begin = false;

var portName = '/dev/tty.usbmodemfa131';
var sp = new SerialPort(portName, 
    {
      baudRate: 9600,
    });
sp.on('open',function()
    {
      console.log("open");
    });
sp.on('data',function(data)
    {
      begin = true;
    });
sp.on('error', function(err) {
  console.log('err ' + err);
});

var degree = 0;
var mode = 0;
var webSocket = require('ws'),
    //Leapのサーバーに接続する
    ws = new webSocket('ws://127.0.0.1:6437');
    ws.on('message', function(data, flags) {
      var d = JSON.parse(data);
      if(d.hands && d.hands.length == 1){
        var x = Math.abs(Math.floor(d.hands[0].palmPosition[0])) % 64;
        var y = Math.abs(Math.floor(d.hands[0].palmPosition[1])) % 64;
        var z = Math.abs(Math.floor(d.hands[0].palmPosition[2])) % 64;
        console.log(x + " " + y + " " + z);
        mode = "1," + x + "," + y + "," + z;
      }else {
        mode = 0;
      }
    });

    setInterval(function() {
      if(begin) {
        console.log(mode);
        sp.write(mode + "\n");
      }
    },20)
