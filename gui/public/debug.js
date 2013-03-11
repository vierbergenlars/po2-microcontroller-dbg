function setPin(pin, to) {
	if(to == "1")
		window.document.getElementById("led"+pin).checked = true;
	else
		window.document.getElementById("led"+pin).checked = false;
}

function setPinIO(pin, to) {
	if(to == "0") {
		window.document.getElementById("pin"+pin+"Type").innerText = "OUT";
		window.document.getElementById("led"+pin).disabled = true;
	}
	else {
		window.document.getElementById("pin"+pin+"Type").innerText = "IN";
		window.document.getElementById("led"+pin).disabled = false;
	}
}

function updatePin(elem) {
	if(block_run_controls) return
	block();
	if(elem.checked) {
		send('set '+elem.id[3]+' 1');
	}
	else {
		send('set '+elem.id[3]+' 0');
	}

}

function set_run_controls_active(enable) {
	block_run_controls = !enable
	var controls = document.getElementById('run_controls').children;
	for(i in controls) {
		controls[i].disabled = !enable
	}

}

function set_app_controls_active(enable) {
	block_run_controls = !enable
	var controls = document.getElementById('app_controls').children;
	for(i in controls) {
		controls[i].disabled = !enable
	}
}

function block() {
	window.document.getElementById("spinner").display = "block";
}

function unblock() {
	window.document.getElementById("spinner").display = "none";
}

function send(data) {
	block()
	set_run_controls_active(false);
	textarea.value+=data+"\n";
	textarea.scrollByPages(20);
	app.stdin.write(data+"\n");
}

function parse_data(data) {
	parts = data.split("\n")
	for(i in parts) {
		line = parts[i];
		if(matches = /pin ([1-7]): (0|1)/.exec(line)) {
			setPin(matches[1], matches[2]);
		}
		else if(matches = /io ([1-7]): (0|1)/.exec(line)) {
			setPinIO(matches[1], matches[2]);
		}
		else if(line == "done") {
			if(document.getElementById('run').checked)
				send('cont')
			else
				set_run_controls_active(true)
		}
	}
}

function start_program() {
	if(typeof app !== 'undefined') app.kill('SIGKILL');
	var spawn = require('child_process').spawn;
	textarea = document.getElementsByTagName('textarea')[0];
	textarea.innerHTML+='$ ./app\n';
	block()
	set_app_controls_active(false)
	app = spawn('./app', [], {'cwd': __dirname+'/../program'});
	window.beforeunload = function() { app.kill('SIGKILL');};
	set_run_controls_active(true)
	unblock()
	app.on('exit', function(code, signal) {
		set_run_controls_active(false);
		set_app_controls_active(true)
		if(code > 0) {
			textarea.value+='[app] exited with errorcode '+code+"\n";
		}
		else if(signal !== null) {
			textarea.value+='[app] killed by '+signal+"\n";
		}
		textarea.scrollByPages(20);
		unblock();

	});
	app.stdout.on('data', function(data) {
		parse_data(data.toString('ascii'));
		textarea.value+=data;
		textarea.scrollByPages(20);
	});
	app.stderr.on('data', function(data) {
		textarea.value+='[stderr] '+data;
		textarea.scrollByPages(20);
	});
	
}




