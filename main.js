var SerialPort = require('serialport').SerialPort,
	midi = require('midi')
	output = new midi.output(),
	chalk = require('chalk');

// find the loopbe virtual midi port
for (var i = 0; i < output.getPortCount(); i++) {
	if (output.getPortName(i).indexOf('LoopBe') > -1) {
		output.openPort(i);
		console.log(chalk.blue('[INFO] Connecté à live ' + output.getPortName(i)));
	}
};

// open serial port
var serialPort = new SerialPort('COM5');
serialPort.on('open', function() {
	console.log(chalk.blue('[INFO] Connecté au boitier'));
});

// intercept midi notes
serialPort.on('data', function(data) {
	msg += data;
	if (msg.indexOf('#') > 0) {
		var note = msg.substring(0, test.lastIndexOf('#'));
		console.log(chalk.bold.red('[INFO] ' + note));
		output.sendMessage([144,note,1]);
		msg = '';
	}
});