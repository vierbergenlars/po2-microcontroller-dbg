#!/usr/bin/node --harmony
/*
 * Copyright (c) 2013 Lars Vierbergen
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
var appjs = module.exports= require('appjs');

process.title="Microcontroller GUI"
appjs.serveFilesFrom(__dirname + "/public");


function createWindow(address, name) {
	if(appjs.windows[name]) {
		appjs.windows[name].close();
		//appjs.windows[name].frame.destroy();
	}
	var sizes = {
		'index': [120, 141],	
		'compile': [650, 252],
		'editor': [557, 100],
		'debug': [650, 444]
	};
	var positions = {
		'index': [65,24],	
		'compile':[65+120+650, 24],
		'editor': [65+120,24],
		'debug': [65+120+650, 24+252+22]
	};
	var opts = {
		width: 0,
		height: 0,
		alpha: false,
		url: 'http://appjs/'+address,
		name: name,
		resizable: (name =='index'?false: true),
		autoResize: (name=='editor'?true: false)
	}
	if(sizes[name]) {
		opts.width = sizes[name][0];
		opts.height = sizes[name][1];
	}
	if(positions[name]) {
		opts.left = positions[name][0];
		opts.top = positions[name][1];
	}
	var window = appjs.createWindow(opts);

	window.on('create', function() {
		window.frame.show();
	});

	window.on('ready', function() {
		window.require = require;
		window.process = process;
		window.module = module;
		window.node_console = console;
		window.__dirname = __dirname;
		window.open2 = createWindow;
		window.quit = function() {
			for( i in appjs.windows) {
				appjs.windows[i].frame.fade(0, function() {this.destroy() });
			}
		}
		
	    window.addEventListener('keydown', function(e){
	    // show chrome devtools on f12 or commmand+option+j
	    if (e.keyIdentifier === 'F12' || e.keyCode === 74 && e.metaKey && e.altKey) {
	      window.frame.openDevTools();
	    }
	  });
	});
	return window;
}
createWindow('/index.html', 'index');
