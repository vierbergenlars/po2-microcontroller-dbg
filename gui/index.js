var appjs = module.exports= require('appjs');
var net = require('net');

appjs.serveFilesFrom(__dirname + "/public");

var window = appjs.createWindow({
	width: 640,
	height: 460,
	alpha: false
});

window.on('create', function() {
	window.frame.show();
});



window.on('ready', function() {
	window.require = require;
	window.process = process;
	window.module = module;
	window.socket = socket = net.createConnection(process.argv[2]);
	function setPin(pin, to) {
		console.log('setPin: '+pin+' to '+to);
		if(to == "1")
			window.document.getElementById("led"+pin).checked = true;
		else
			window.document.getElementById("led"+pin).checked = false;
	}

	function setPinIO(pin, to) {
		console.log('setPinIO: '+pin+' to '+to);
		if(to == "1") {
			window.document.getElementById("pin"+pin+"Type").innerHTML = "OUT";
			window.document.getElementById("led"+pin).enabled = false;
		}
		else {
			window.document.getElementById("pin"+pin+"Type").innerHTML = "IN";
			window.document.getElementById("led"+pin).enabled = true;
		}
	}

	window.updatePin = function(elem) {
		if(elem.checked) {
			socket.write('set '+elem.id[3]+' 1');
		}
		else {
			socket.write('set '+elem.id[3]+' 0');
		}

	}

	setInterval(function() {if(window.document.getElementById('run').checked)socket.write('cont')}, 1000);

	socket.on('connect', function() {
		socket.on('data', function(data) {
			data = data.toString();
			pins = data.split("\n");
			for(i in pins) {
				if(result = /pin ([1-7]): (0|1)/.exec(pins[i])) {
					setPin(result[1], result[2]);
				}
				else if(result = /io ([1-7]): (0|1)/.exec(pins[i])) {
					setPinIO(result[1], result[2]);
				}
			}
		});
		socket.write('get all');
		socket.write('gio all');
	});
    window.addEventListener('keydown', function(e){
    // show chrome devtools on f12 or commmand+option+j
    if (e.keyIdentifier === 'F12' || e.keyCode === 74 && e.metaKey && e.altKey) {
      window.frame.openDevTools();
    }
  });
});
