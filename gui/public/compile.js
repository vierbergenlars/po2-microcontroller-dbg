function exec_make() {
	var spawn = require('child_process').spawn;
	var make = spawn('make', [], {'cwd': __dirname+'/..'});
	var textarea = document.getElementsByTagName('textarea')[0];
	make.on('exit', function(code) {
		if(code > 0) {
			textarea.value+='[make] exited with errorcode '+code+"\n";
		}
		else {
			document.getElementById('enter_debugger').disabled = false;
			document.getElementById('enter_debugger').click();
		}
		document.getElementById('spinner').display="none";

	});
	document.getElementById('spinner').display="block";
	textarea.value+="$ make\n";
	
	make.stdout.on('data', function(data) {
		textarea.value+=data;
	});
	make.stderr.on('data', function(data) {
		textarea.value+='[stderr]'+data;
	});

}
