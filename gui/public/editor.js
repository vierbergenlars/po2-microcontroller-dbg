function main() {
	block();
	save = function() {
		block();
		var fs = require('fs')
		var data = fs.readFileSync(__dirname+'/../program/main.c', 'ascii');
		data = data.replace("\r\n", "\n");
		if(!vars.isClean()) {
			var vars_dta = vars.getValue();
			data = replace(data, vars_dta, '// @vars start', '// @vars end');
			vars.markClean();
		}
		if(!init.isClean()) {
			var init_dta = init.getValue();
			data = replace(data, init_dta, '// @init start', '// @init end');
			init.markClean();
		}
		if(!loop.isClean()) {
			var loop_dta = loop.getValue()
			data = replace(data, loop_dta, '// @loop start', '// @loop end');
			loop.markClean();
		}
		fs.writeFileSync(__dirname+'/../program/main.c', data, 'ascii');
		unblock();
	}
	var fs = require('fs');
	var data = fs.readFileSync(__dirname+'/../program/main.c', 'ascii');

	loop = CodeMirror(document.getElementById('loop'), {
	  value: cut(data, '// @loop start', '// @loop end'),
	matchBrackets: true,
	  mode: "text/x-csrc"
	});
	loop.on("blur", save);
	init = CodeMirror(document.getElementById('init'), {
	  value: cut(data, '// @init start', '// @init end'),
	matchBrackets: true,
	  mode: "text/x-csrc"
	});
	init.on("blur", save);
	vars = CodeMirror(document.getElementById('vars'), {
	  value: cut(data, '// @vars start', '// @vars end'),
	matchBrackets: true,
	  mode: "text/x-csrc"
	});
	vars.on("blur", save);

	window.beforeunload = function() { save(); }
	unblock();
}

function block() {
	document.getElementById('spinner').display = "block";
}

function unblock() {
	document.getElementById('spinner').display = "none";
}

function cut(data, start_text, end_text) {
	var loop_start = data.indexOf(start_text) + start_text.length + 1;
	var loop_end = data.indexOf(end_text)-1;
	return data.substring(loop_start, loop_end);
}

function replace(data, replacement, start_text, end_text) {
	var loop_start = data.indexOf(start_text) + start_text.length + 1;
	var loop_end = data.indexOf(end_text)-1;
	return (data.substring(0, loop_start)+replacement+data.substring(loop_end)).trim();
}

